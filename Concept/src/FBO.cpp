#include "FBO.h"

bool FBO::m_ExtensionsLoaded = false;
PFNGLGENFRAMEBUFFERSEXTPROC         FBO::glGenFramebuffersEXT = NULL;
PFNGLBINDFRAMEBUFFEREXTPROC         FBO::glBindFramebufferEXT = NULL;
PFNGLGENRENDERBUFFERSEXTPROC        FBO::glGenRenderbuffersEXT = NULL;
PFNGLBINDRENDERBUFFEREXTPROC        FBO::glBindRenderbufferEXT = NULL;
PFNGLRENDERBUFFERSTORAGEEXTPROC     FBO::glRenderbufferStorageEXT = NULL;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC FBO::glFramebufferRenderbufferEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC    FBO::glFramebufferTexture2DEXT = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC  FBO::glCheckFramebufferStatusEXT = NULL;
PFNGLDELETEFRAMEBUFFERSEXTPROC      FBO::glDeleteFramebuffersEXT = NULL;
PFNGLDELETERENDERBUFFERSEXTPROC     FBO::glDeleteRenderbuffersEXT = NULL;
PFNGLGENERATEMIPMAPEXTPROC          FBO::glGenerateMipmapEXT = NULL;

FBO::FBO( unsigned int width, unsigned int height ):
m_Width( width ),
m_Height( height )
{
    if( !m_ExtensionsLoaded )
    {
        // Load up the GL Extensions
        glGenFramebuffersEXT = ( PFNGLGENFRAMEBUFFERSEXTPROC ) SDL_GL_GetProcAddress( "glGenFramebuffersEXT" );
        if( !glGenFramebuffersEXT )
            return;

        glBindFramebufferEXT = ( PFNGLBINDFRAMEBUFFEREXTPROC ) SDL_GL_GetProcAddress( "glBindFramebufferEXT" );
        if( !glBindFramebufferEXT )
            return;

        glGenRenderbuffersEXT = ( PFNGLGENRENDERBUFFERSEXTPROC ) SDL_GL_GetProcAddress( "glGenRenderbuffersEXT" );
        if( !glGenRenderbuffersEXT )
            return;

        glBindRenderbufferEXT = ( PFNGLBINDRENDERBUFFEREXTPROC ) SDL_GL_GetProcAddress( "glBindRenderbufferEXT" );
        if( !glBindRenderbufferEXT )
            return;

        glRenderbufferStorageEXT = ( PFNGLRENDERBUFFERSTORAGEEXTPROC ) SDL_GL_GetProcAddress( "glRenderbufferStorageEXT" );
        if( !glRenderbufferStorageEXT )
            return;

        glFramebufferRenderbufferEXT = ( PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC ) SDL_GL_GetProcAddress( "glFramebufferRenderbufferEXT" );
        if( !glFramebufferRenderbufferEXT )
            return;

        glFramebufferTexture2DEXT = ( PFNGLFRAMEBUFFERTEXTURE2DEXTPROC ) SDL_GL_GetProcAddress( "glFramebufferTexture2DEXT" );
        if( !glFramebufferTexture2DEXT )
            return;

        glCheckFramebufferStatusEXT = ( PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC ) SDL_GL_GetProcAddress( "glCheckFramebufferStatusEXT" );
        if( !glCheckFramebufferStatusEXT )
            return;

        glDeleteFramebuffersEXT = ( PFNGLDELETEFRAMEBUFFERSEXTPROC ) SDL_GL_GetProcAddress( "glDeleteFramebuffersEXT" );
        if( !glDeleteFramebuffersEXT )
            return;

        glDeleteRenderbuffersEXT = ( PFNGLDELETERENDERBUFFERSEXTPROC ) SDL_GL_GetProcAddress( "glDeleteRenderbuffersEXT" );
        if( !glDeleteRenderbuffersEXT )
            return;

        glGenerateMipmapEXT = ( PFNGLGENERATEMIPMAPEXTPROC ) SDL_GL_GetProcAddress( "glGenerateMipmapEXT" );
        if( !glGenerateMipmapEXT )
            return;

        m_ExtensionsLoaded = true;
    }

    // Create the frame buffer object & grab a valid handle for it
    glGenFramebuffersEXT( 1, &m_FBOID );
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_FBOID );
    // Create the render buffer & grab a handle to it
    glGenRenderbuffersEXT( 1, &m_RenderBufferID );
    glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, m_RenderBufferID );
    // Allocate memory space for a given width & height
    glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, m_Width, m_Height );

    // Create a texture & grab a valid handle for it (usual texture stuff here)
    glGenTextures( 1, &m_TextureID );
    glBindTexture( GL_TEXTURE_2D, m_TextureID );
    // IMPORTANT: the width & height of the destination texture has to be the same as given to the render buffer
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    // Enable mipmap filtering and generate mipmap data
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glGenerateMipmapEXT( GL_TEXTURE_2D );

    // Attach the FBO to the texture itself
    glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_TextureID, 0 );

    // Attach the render buffer to the frame buffer object
    glFramebufferRenderbufferEXT( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_RenderBufferID );

    if( GL_FRAMEBUFFER_COMPLETE_EXT != glCheckFramebufferStatusEXT( GL_FRAMEBUFFER_EXT ) )
        throw;
}

void FBO::Begin()
{
    // Push currently unknown screen attribs
    glPushAttrib( GL_ALL_ATTRIB_BITS );
    // Render a scene to texture
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_FBOID );
    // Store the old projection matrix
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    // Store the old model matrix and reset
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
}

void FBO::Begin2D()
{
    Begin();
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glViewport( 0, 0, m_Width, m_Height );
    gluOrtho2D( 0, m_Width, 0, m_Height );
    glDisable( GL_DEPTH_TEST );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( 0.375, 0.375, 0 );
}

void FBO::End()
{
    // Switch rendering back to screen
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );

    // Push back the old projection and model matricies
    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
    glPopMatrix();

    // Pop unknown screen attribs back
	glPopAttrib();
}

FBO::~FBO()
{
    glDeleteTextures( 1, &m_TextureID );
    glDeleteRenderbuffersEXT( 1, &m_RenderBufferID );
    glDeleteFramebuffersEXT( 1, &m_FBOID );
}
