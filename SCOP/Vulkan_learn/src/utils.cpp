#include "utils.h"

#ifdef USING_SDL2
	#include <SDL2/SDL.h> //para SDL2 instalado en 42.
#else
	#include <SDL3/SDL.h>
#endif


#include <fstream>
#include <sstream>

void showError(SDL_Window *window, const std::string &errorMessasge)
{
}

std::string readTextFile(const std::string &filePath)
{
	std::ifstream infile(filePath);
	if (infile.is_open())
	{
		std::stringstream buffer;
		buffer << infile.rdbuf();
		const std::string output = buffer.str();
		infile.close();
		return output;
	}
	return std::string();
}
