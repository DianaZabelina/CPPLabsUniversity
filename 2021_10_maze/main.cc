/*
 * mingw32
 * SDL2main
 * SDL2
 * SDL2_image
 *
 */

#include "MazeWindow.h"
#include <iostream>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

int main(int, char**) {
	SDL_Init(SDL_INIT_EVERYTHING);
	try {
		MazeWindow w;
		w.main_loop();
	} catch (const std::exception &e) {
		std::cerr <<
				"��������� ������:\n" <<
				e.what() <<
				std::endl;
		return 1;
	} catch (...) {
		std::cerr <<
				"��������� ����������� ������!" <<
				std::endl;
		return 1;
	}
	return 0;
}
