#include <iostream>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

#include "HouseWindow.h"

int main(int, char **) {
	SDL_Init(SDL_INIT_EVERYTHING);
	try {
		HouseWindow w;
		w.main_loop();
	} catch (const std::exception &e) {
		std::cerr <<
				"Произошла ошибка:\n" <<
				e.what() <<
				std::endl;
		exit(1);
	}
	return 0;
}

