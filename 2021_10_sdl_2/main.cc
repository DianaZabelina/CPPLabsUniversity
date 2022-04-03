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
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

#include "WindowWithRectangles.h"

/*
 * 1) Инкапсуляция
 * 		- состояние
 *      - поведение
 * 1.5) Агрегация
 *      - объект может включать в себя другие объекты
 * 2) Наследование
 * 3) Полиморфизм
 *
 * Области видимости:
 * 						Сам объект		Потомки		Остальные
 *      public				+				+			+
 *      protected			+				+
 *      private				+
 *
 */

int main(int, char**) {
	WindowWithRectangles window1;
	//std::shared_ptr<Window> w;
	// = std::make_shared<Window>();

	std::cout << "Program started!" << std::endl;
	SDL_Init(SDL_INIT_EVERYTHING);

	window1.main_loop();
	//w->main_loop();

	std::cout << "Program ended!" << std::endl;
	return 0;
}
