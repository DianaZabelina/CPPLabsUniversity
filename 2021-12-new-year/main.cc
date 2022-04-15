#include <iostream>
#include <stdexcept>

#include <SDL2/SDl.h>
#include <SDL2/SDL_main.h>

#include "Window.h"

int main(int, char **) {
	SDL_Init(SDL_INIT_EVERYTHING);
	try {
		Window w;
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

