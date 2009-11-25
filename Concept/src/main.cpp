#include "App.h"

int main ( int argc, char** argv )
{
	App app;
	int ret = app.Init( 1024, 768, 32, false );
	app.Run();

	return ret;
}
