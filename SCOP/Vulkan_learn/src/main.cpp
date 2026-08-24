#include <SDL3/SDL_main.h>
#include "application.h"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	
	Application app;
	if (app.initialize())
	{
		app.run();
	}
	app.shutdown();

	return 0;
}
