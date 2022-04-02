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
const int WINDOW_WIDTH = 800;

std::shared_ptr<SDL_Window> window;
std::shared_ptr<SDL_Renderer> renderer;

SDL_Rect rect1 { 50, 50, 15, 15 };
int rect1_dx = 1, rect1_dy = 1;

SDL_Rect rect2 { 685, 485, 15, 15 };

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
					SDL_RENDERER_ACCELERATED |
					SDL_RENDERER_PRESENTVSYNC),
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

	//белый
	//SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
	for (int i = 0; i <= 50; i++) {
		SDL_SetRenderDrawColor(renderer.get(), 255 - 5 * i, 5 * i, 255, 255);
		SDL_RenderDrawLine(renderer.get(),
				100 + i * 8, 100,
				100, 500 - i * 8);
		SDL_RenderDrawLine(renderer.get(),
				500 - i * 8, 500,
				500, 100 + i * 8);
	}

	//красный
	SDL_SetRenderDrawColor(renderer.get(), 255, 63, 63, 255);
	SDL_RenderFillRect(renderer.get(), &rect1);

	//зелёный
	SDL_SetRenderDrawColor(renderer.get(), 63, 255, 63, 255);

	//жёлтый при пересечении прямоугольников
	SDL_Rect r;
	if (SDL_IntersectRect(&rect1, &rect2, &r))
		SDL_SetRenderDrawColor(renderer.get(), 255, 255, 63, 255);
	SDL_RenderFillRect(renderer.get(), &rect2);
}

void main_loop() {
	auto keys = SDL_GetKeyboardState(nullptr);

	SDL_Event event;
	for (;;) {
		//	1) Обработка событий, состояния ввода и т.п.
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				return;
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					return;
				default:
					;
				}
			}
		}
		if (keys[SDL_SCANCODE_RIGHT]) rect2.x += 2;
		if (keys[SDL_SCANCODE_LEFT])  rect2.x -= 2;
		if (keys[SDL_SCANCODE_DOWN])  rect2.y += 2;
		if (keys[SDL_SCANCODE_UP])    rect2.y -= 2;

		//	2) Изменение состояния программы
		rect1.x += rect1_dx;
		rect1.y += rect1_dy;
		if (rect1.x <= 0)						rect1_dx =  1;
		if (rect1.x + rect1.w >= WINDOW_WIDTH)	rect1_dx = -1;
		if (rect1.y <= 0)						rect1_dy =  1;
		if (rect1.y + rect1.h >= WINDOW_HEIGHT)	rect1_dy = -1;

		//	3) Отображение текущего состояния
		render();
		SDL_RenderPresent(renderer.get());
	}
}

int main(int, char**) {
	std::cout << "Program started!" << std::endl;
	SDL_Init(SDL_INIT_EVERYTHING);
	create_window();
	create_renderer();
	main_loop();
	std::cout << "Program ended!" << std::endl;
	return 0;
}
