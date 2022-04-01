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
 *
 * Основной цикл программы:
 *		1) Обработка событий, состояния ввода и т.п.
 *		2) Изменение состояния программы
 *		3) Отображение текущего состояния
 */

#include <iostream>
#include <cerrno>
#include <memory>

#include <SDL2/SDL.h>

#include <SDL2/SDL_main.h>

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 600;

std::shared_ptr<SDL_Window> window;
std::shared_ptr<SDL_Renderer> renderer;

void create_window() {
	window = std::shared_ptr<SDL_Window>(
			SDL_CreateWindow("SDL Window", /*название*/
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, /*расположение верхнего левого угла*/
					WINDOW_WIDTH,
					WINDOW_HEIGHT,
					SDL_WINDOW_SHOWN),
			SDL_DestroyWindow);
	if (window == nullptr) { //окно не создалось
		std::cerr <<
				"Не могу создать окно: " <<
				SDL_GetError() << std::endl;
		exit(1);
	}
}

void create_renderer() {
	//окно успешно создалось
	renderer = std::shared_ptr<SDL_Renderer>(
			SDL_CreateRenderer(
					window.get(), -1,
					SDL_RENDERER_ACCELERATED),
			SDL_DestroyRenderer);
	if (renderer == nullptr) { //рендерер не создался
		std::cerr <<
				"Не могу создать рендерер: " <<
				SDL_GetError() << std::endl;
		exit(1);
	}
}

void render() {
	SDL_SetRenderDrawColor(renderer.get(), 31, 63, 95, 255);
	SDL_RenderClear(renderer.get());
	SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
	for (int i = 0; i <= 50; i++) {
		SDL_RenderDrawLine(renderer.get(),
				100 + i * 8, 100,
				100, 500 - i * 8);
		SDL_RenderDrawLine(renderer.get(),
				500 - i * 8, 500,
				500, 100 + i * 8);
	}
}

void main_loop() {
	SDL_Event event;
	for (;;) {
		//	1) Обработка событий, состояния ввода и т.п.
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				exit(0);
		}
		//	2) Изменение состояния программы
		//	3) Отображение текущего состояния
		render();
		SDL_RenderPresent(renderer.get());
	}
}

int main(int, char**) {
	SDL_Init(SDL_INIT_EVERYTHING);
	create_window();
	create_renderer();
	main_loop();
	return 0;
}
