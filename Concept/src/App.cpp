#include "App.h"

App::App():
m_Initialised( false ),
m_FullScreen( false ),
m_RotT( 0.0f ),
m_RotS( 0.0f ),
m_ScreenWidth( 0 ),
m_ScreenHeight( 0 ),
m_ScreenDepth( 0 ),
wnd( NULL )
{

}

unsigned int App::Init( const unsigned int& width, const  unsigned int& height, const unsigned int& depth, const bool& full_screen )
{
    if( width  < 1 || height < 1 || depth < 1 )
        return 1;

    m_FullScreen = full_screen;
    m_ScreenWidth = width;
    m_ScreenHeight = height;
    m_ScreenDepth = depth;

    if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
        return 2;

    const SDL_VideoInfo* video_info = SDL_GetVideoInfo();

	if ( !video_info )
        return 3;

    int video_flags  = SDL_OPENGL;      /* Enable OpenGL in SDL */
    video_flags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
    video_flags |= SDL_HWPALETTE;       /* Store the palette in hardware */
    if( full_screen )
        video_flags |= SDL_FULLSCREEN;
    //videoFlags |= SDL_RESIZABLE;

	if( video_info->hw_available )
		video_flags |= SDL_HWSURFACE;
    else
		video_flags |= SDL_SWSURFACE;

 	if( video_info->blit_hw )
		video_flags |= SDL_HWACCEL;

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    if( SDL_SetVideoMode( m_ScreenWidth, m_ScreenHeight, m_ScreenDepth, video_flags ) == NULL )
        return 4;

    SDL_WM_SetCaption( "SOGui Test Window", NULL );

    // OpenGL setup stuff
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.5f, 0.5f, 0.5f, 0.5f );
    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );
    // Set up 2D drawing
    glViewport( 0, 0, m_ScreenWidth, m_ScreenHeight );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0, m_ScreenWidth, m_ScreenHeight, 0 );
	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    if( glGetError() != GL_NO_ERROR )
        return 5;

    if( TTF_Init() == -1 )
        return 6;

    wnd = new Window( 20, 20, 600, 600, "Title Here" );

    m_Initialised = true;
    return 0;
}

unsigned int App::Run()
{
    bool done = false;
    bool window_active = false;
	SDL_Event event;

	while( !done )
	{
	    while( SDL_PollEvent( &event ) )
		{
		    switch( event.type )
			{
			    case SDL_MOUSEBUTTONDOWN:
                    if( event.button.button == SDL_BUTTON_LEFT && wnd->IsInActiveArea( event.button.x, event.button.y ) )
                        window_active = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    window_active = false;
                    break;
                case SDL_MOUSEMOTION:
                    if( window_active )
                        wnd->MoveWindowPos( event.motion.xrel, event.motion.yrel );
                    break;
				case SDL_KEYDOWN:
				    // handle key presses here
				    switch( event.key.keysym.sym )
					{
					case SDLK_ESCAPE:
					    done = true;
					    break;
					default:
					    break;
					}
				    break;
				case SDL_QUIT:
				    done = true;
				    break;
				default:
				    break;
			}
		}
		DrawScene();
    }
	return 0;
}

void App::DrawScene()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    wnd->Draw();

	SDL_GL_SwapBuffers();
}

App::~App()
{
    if( m_Initialised )
    {
        delete wnd;
        SDL_Quit();
    }
}
