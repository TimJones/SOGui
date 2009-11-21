#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "App.h"

int main ( int argc, char** argv )
{
    App app;
    int ret = app.Init( 1280, 800, 32, false );
    app.Run();

    return ret;
}
