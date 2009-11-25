#ifndef MYFBO_H
#define MYFBO_H

#include <FBO.h>


class MyFBO : public FBO
{
	public:
		MyFBO( unsigned int width, unsigned int height );
		virtual ~MyFBO();

		void Draw();
	protected:
	private:
};

#endif // MYFBO_H
