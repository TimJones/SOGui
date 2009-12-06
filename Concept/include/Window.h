#ifndef WINDOW_H
#define WINDOW_H

#include "FBO.h"
#include "FontTexture.h"

class Window : public FBO
{
	public:
		Window( int x, int y, unsigned int width, unsigned int height, const char* title );
		virtual ~Window();

		void Draw();
		void SetWindowPos( int x, int y ) { m_X = x; m_Y = y; };
		void MoveWindowPos( int x_diff, int y_diff ) { m_X += x_diff; m_Y += y_diff; };
		bool IsInWindow( int x, int y ) { return x >= m_X && x <= m_X + m_Width && y >= m_Y && y <= m_Y + m_Height; };
		bool IsInActiveArea( int x, int y ) { return IsInWindow( x, y ) && y <= m_Y + m_FontTexture->GetHeight() + 10; };

	protected:
		int m_X, m_Y;
		const char* m_Title;
		FontTexture* m_FontTexture;

	private:
};

#endif // WINDOW_H
