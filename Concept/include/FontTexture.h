#ifndef FONTTEXTURE_H
#define FONTTEXTURE_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_ttf.h>
#include <string>

class FontTexture
{
    public:
        FontTexture( const char* font_file, const int& point_size, const char* text, const SDL_Color& color );
        virtual ~FontTexture();

        unsigned int GetWidth() { return m_Width; };
        unsigned int GetHeight() { return m_Height; };
        GLuint GetTextureID() { return m_TextureID; };

    protected:
        TTF_Font* m_Font;
        GLuint m_TextureID;
        unsigned int m_Width, m_Height;

    private:
        static unsigned int m_Count;
};

#endif // FONTTEXTURE_H
