#ifndef WINDOW_H
#define WINDOW_H

#include <FBO.h>
#include <string>

class Window : public FBO
{
    public:
        Window( unsigned int x, unsigned int y, unsigned int width, unsigned int height );
        virtual ~Window();

        void Draw();

    protected:
        unsigned int m_X, m_Y;
        std::string m_Title;

    private:
};

#endif // WINDOW_H
