#include "Window.h"

Window::Window( unsigned int x, unsigned int y, unsigned int width, unsigned int height ):
FBO( width, height ),
m_X( x ),
m_Y( y ),
m_Title( "Window Title" )
{
    //ctor
}

void Window::Draw()
{
    Begin2D();

    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );

    // 'Window' border
	glBegin( GL_QUADS );
        glColor3ub( 20, 35, 55 ); glVertex2i( 0, 0 );
        glColor3ub( 65, 100, 155 ); glVertex2i( m_Width - 1, 0 );
        glColor3ub( 75, 120, 170 ); glVertex2i( m_Width - 1, m_Height - 1 );
        glColor3ub( 75, 120, 170 ); glVertex2i( 0, m_Height - 1 );
    glEnd();

    // 'Window' edge
    glColor3ub( 80, 100, 145 );
    glBegin( GL_LINE_LOOP );
        glVertex2i( 0, 0 );
        glVertex2i( m_Width - 1, 0 );
        glVertex2i( m_Width - 1, m_Height - 1 );
        glVertex2i( 0, m_Height - 1 );
    glEnd();

    // Inner frame
    glColor3ub( 25, 25, 25 );
    glBegin( GL_QUADS );
        glVertex2i( 5, 25 );
        glVertex2i( m_Width - 5, 25 );
        glVertex2i( m_Width - 5, m_Height - 5 );
        glVertex2i( 5, m_Height - 5 );
    glEnd();

    End();

	glLoadIdentity();
    glTranslatef( 0.375, 0.375, 0 );

    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, m_TextureID );
    glBegin( GL_QUADS );
        glTexCoord2f( 0.0f, 0.0f ); glVertex2i( m_X, m_Y );
        glTexCoord2f( 0.0f, 1.0f ); glVertex2i( m_X, m_Y + m_Height );
        glTexCoord2f( 1.0f, 1.0f ); glVertex2i( m_X + m_Width, m_Y + m_Height );
        glTexCoord2f( 1.0f, 0.0f ); glVertex2i( m_X + m_Width, m_Y );
    glEnd();
    glDisable( GL_TEXTURE_2D );
}

Window::~Window()
{
    //dtor
}
