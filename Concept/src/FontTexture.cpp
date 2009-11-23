#include "FontTexture.h"

unsigned int FontTexture::m_Count = 0;

FontTexture::FontTexture( const char* font_file, const int& point_size, const char* text, const SDL_Color& color )
{
    if( !TTF_WasInit() && TTF_Init() == -1 )
        throw;
    m_Font = TTF_OpenFont( font_file, point_size );

    SDL_Surface* base = TTF_RenderText_Blended( m_Font, text, color );
    SDL_Surface* blend = SDL_CreateRGBSurface( 0, base->w, base->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_BlitSurface( base, 0, blend, 0 );

    glGenTextures( 1, &m_TextureID );
	glBindTexture( GL_TEXTURE_2D, m_TextureID );
	glTexImage2D( GL_TEXTURE_2D, 0, 4, blend->w, blend->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, blend->pixels );

	m_Width = blend->w; m_Height = blend->h;

	// GL_NEAREST looks horrible, if scaled...
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	SDL_FreeSurface( blend );
    SDL_FreeSurface( base );

    TTF_CloseFont( m_Font );

    m_Count++;
}

FontTexture::~FontTexture()
{
    glDeleteTextures( 1, &m_TextureID );

    m_Count--;
    if( m_Count == 0 )
        TTF_Quit();
}
