#ifndef FBO_H
#define FBO_H

#ifdef __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#else
#include <SDL.h>
#include <SDL_opengl.h>
#endif

class FBO
{
    public:
        FBO( unsigned int width, unsigned int height );
        virtual ~FBO();

        GLuint getTextureID() { return m_TextureID; };

        virtual void Draw() = 0;

    protected:
        unsigned int m_Width, m_Height;
		GLuint m_FBOID, m_TextureID;
		GLuint m_RenderBufferID;

        void Begin();
        void Begin2D();
        void End();

		// OpenGL Extensions functors definsed for us in SDL_opengl.h
        static PFNGLGENFRAMEBUFFERSEXTPROC         glGenFramebuffersEXT;
		static PFNGLBINDFRAMEBUFFEREXTPROC         glBindFramebufferEXT;
		static PFNGLGENRENDERBUFFERSEXTPROC        glGenRenderbuffersEXT;
		static PFNGLBINDRENDERBUFFEREXTPROC        glBindRenderbufferEXT;
		static PFNGLRENDERBUFFERSTORAGEEXTPROC     glRenderbufferStorageEXT;
		static PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT;
		static PFNGLFRAMEBUFFERTEXTURE2DEXTPROC    glFramebufferTexture2DEXT;
		static PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC  glCheckFramebufferStatusEXT;
		static PFNGLDELETEFRAMEBUFFERSEXTPROC      glDeleteFramebuffersEXT;
		static PFNGLDELETERENDERBUFFERSEXTPROC     glDeleteRenderbuffersEXT;
		static PFNGLGENERATEMIPMAPEXTPROC          glGenerateMipmapEXT;

        static bool m_ExtensionsLoaded;
        void LoadExtensions();

    private:
};

#endif // FBO_H
