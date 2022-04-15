#include "Window.h"
#include <stdexcept>

Window::Window(int w,int h)
: _width(w), _height(h)
{
	_window = std::shared_ptr<SDL_Window>(
					SDL_CreateWindow("OpenGL Window", /*название*/
							SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED, /*расположение верхнего левого угла*/
							w, h,
							SDL_WINDOW_OPENGL),
					SDL_DestroyWindow);
	if (_window == nullptr) { //окно не создалось
		throw std::runtime_error(
				std::string("Не могу создать окно: ") +
				std::string(SDL_GetError()));
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	_gl_context = std::shared_ptr<void>(SDL_GL_CreateContext(_window.get()),
			SDL_GL_DeleteContext);
	if (_gl_context == nullptr){
		throw std::runtime_error(
				std::string("Не могу создать контекст OpenGL: ") +
				std::string(SDL_GetError()));
	}
}

void Window::main_loop() {
	setupGL();

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
			handle_event(event);
		}
		handle_keys(keys);
		//	2) Изменение состояния программы
		update();
		//	3) Отображение текущего состояния
		render();
		SDL_GL_SwapWindow(_window.get());
	}
}
