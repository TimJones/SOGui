#ifndef APP_H
#define APP_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_ttf.h>
#include "Window.h"

class App
{
	public:
		App();
		virtual ~App();

		unsigned int Init( const unsigned int& width, const  unsigned int& height, const unsigned int& depth, const bool& full_screen );
		unsigned int InitFBO();
		unsigned int Run();
	protected:

	private:
		bool m_Initialised;
		bool m_FullScreen;
		float m_RotT, m_RotS;
		unsigned int m_ScreenWidth, m_ScreenHeight, m_ScreenDepth;
		Window* wnd;

		void DrawScene();
};

#endif // APP_H
