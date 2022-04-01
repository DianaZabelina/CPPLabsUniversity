/*
 * Simple DirectMedia Layer 2 (SDL2)
 *
 * mingw32
 * SDL2main
 * SDL2
 *
 * raw pointer - сырой указатель
 * int a;
 * int *p=&a;
 *
 * "smart" pointer - "умный" указатель
 * std::shared_ptr
 * std::unique_ptr
 * std::weak_ptr
 */

#include <iostream>
#include <cerrno>
#include <memory>

#include <SDL2/SDL.h>

#include <SDL2/SDL_main.h>

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;

int main(int, char**) {
	SDL_Init(SDL_INIT_EVERYTHING);

	std::shared_ptr<SDL_Window> window;
	std::shared_ptr<SDL_Renderer> renderer;

	window = std::shared_ptr<SDL_Window>(
			SDL_CreateWindow(
					"SDL Window", /*название*/
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, /*расположение верхнего левого угла*/
					WINDOW_WIDTH,
					WINDOW_HEIGHT,
					SDL_WINDOW_SHOWN /*показ*/),
			SDL_DestroyWindow);

	if(window==nullptr){//окно не создалось
		std::cerr << "Не могу создать окно: " << SDL_GetError() << std::endl;
		return 1;
	}

	//окно успешно создалось
	renderer = std::shared_ptr<SDL_Renderer>(
			SDL_CreateRenderer(
					window.get(), -1,
					SDL_RENDERER_ACCELERATED),
			SDL_DestroyRenderer);

	if (renderer == nullptr) {//рендерер не создался
		std::cerr << "Не могу создать рендерер: " << SDL_GetError()
				<< std::endl;
		return 1;
	}


	if (renderer != nullptr) {
		SDL_SetRenderDrawColor(renderer.get(), 31, 63, 95, 255);
		SDL_RenderClear(renderer.get());

		SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
		for (int i = 0; i < 50; i++) {
			SDL_RenderDrawLine(renderer.get(), 100 + i * 8, 100, 100, 500 - i * 8);
			SDL_RenderDrawLine(renderer.get(), 500 - i * 8, 500, 500, 100 + i * 8);
		}

		SDL_RenderPresent(renderer.get());
		SDL_Delay(10'000); /*задержка окна*/
		SDL_DestroyRenderer(renderer.get());
	}

	return 0;
}
