#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "FBO.h"
#include "FontTexture.h"

class Window : public FBO
{
    public:
        Window( unsigned int x, unsigned int y, unsigned int width, unsigned int height );
        virtual ~Window();

        void Draw();

    protected:
        unsigned int m_X, m_Y;
        std::string m_Title;
        FontTexture* m_FontTexture;

    private:
};

#endif // WINDOW_H
