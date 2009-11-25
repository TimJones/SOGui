#ifndef WINDOW_H
#define WINDOW_H

#include "FBO.h"
#include "FontTexture.h"

class Window : public FBO
{
    public:
        Window( unsigned int x, unsigned int y, unsigned int width, unsigned int height, const char* title );
        virtual ~Window();

        void Draw();
        void SetWindowPos( unsigned int x, unsigned int y ) { m_X = x; m_Y = y; };
        void MoveWindowPos( unsigned int x_diff, unsigned int y_diff ) { m_X += x_diff; m_Y += y_diff; };
        bool IsInWindow( unsigned int x, unsigned int y ) { return x >= m_X && x <= m_X + m_Width && y >= m_Y && y <= m_Y + m_Height; };
        bool IsInActiveArea( unsigned int x, unsigned int y ) { return IsInWindow( x, y ) && y <= m_Y + m_FontTexture->GetHeight(); };

    protected:
        unsigned int m_X, m_Y;
        const char* m_Title;
        FontTexture* m_FontTexture;

    private:
};

#endif // WINDOW_H
