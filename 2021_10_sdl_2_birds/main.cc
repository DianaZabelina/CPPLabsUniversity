/*
 * mingw32
 * SDL2main
 * SDL2
 * SDL2_image
 *
 */

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

#include "GooseWindow.h"

int main(int, char**)
{
	GooseWindow window1;

	std::cout << "Program started!" << std::endl;
	SDL_Init(SDL_INIT_EVERYTHING);

	window1.main_loop();

	std::cout << "Program ended!" << std::endl;
	return 0;
}
