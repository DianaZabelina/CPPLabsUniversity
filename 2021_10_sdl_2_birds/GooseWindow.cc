#include "GooseWindow.h"
#include <cmath>

GooseWindow::GooseWindow()
: _goose(_renderer, "goose.png"),
  _cloud(_renderer, "cloud.png"),
  _eagle(_renderer, "eagle.png"),
  _bg(_renderer, "bg.png"),
  _sun(_renderer, "sun.png")
{
	SDL_SetWindowTitle(_window.get(), "Some evil birds window o_O");
	for (unsigned i = 0; i < 5; i++)
		phase[i] = 0.0;
	eagle_x = 50.0;
	eagle_y = 300.0;
	sun_x = 0;
	sun_y = 50;
}

void GooseWindow::render()
{
	//небо
	SDL_SetRenderDrawColor(_renderer.get(), 63, 192, 255, 255);
	SDL_RenderClear(_renderer.get());
	//солнце
	_sun.draw(sun_x, sun_y);
	//фон
	_bg.draw(0, 0);
	//облака вдали
	for (unsigned i = 0; i < 3; i++)
		_cloud.draw(clouds[i]);
	//гусь
	//_goose.draw(x, y, phase*20);
	//_goose.draw(x, y, (sin(phase) + cos(phase)) / 2 * 180 / 3.1415);
	//гуси
	for (unsigned i = 0; i < 5; i++) {
		_goose.draw(geese[i].x, geese[i].y, (sin(phase[i]) + cos(phase[i])) / 2 * 180 / 3.1415);
	}
	//орёл
	_eagle.draw(eagle_x, eagle_y);
	//облака вблизи
	for (unsigned i = 3; i < 6; i++)
			_cloud.draw(clouds[i]);
}

void GooseWindow::handle_keys(const Uint8 *keys)
{
	if (eagle_x < width() - _eagle.width() and keys[SDL_SCANCODE_RIGHT])
		eagle_x += 4;
	if (eagle_x > 0 and keys[SDL_SCANCODE_LEFT])
		eagle_x -= 4;
	if (eagle_y < height() - _eagle.height() and keys[SDL_SCANCODE_DOWN])
		eagle_y += 4;
	if (eagle_y > 0 and keys[SDL_SCANCODE_UP])
		eagle_y -= 4;
}

void GooseWindow::update()
{
	sun_x += 1.0;
	if (sun_x >= width())
		sun_x = 10.0;

	auto pi = acos(-1.0);
	for (unsigned i = 0; i < 5; i++) {
		phase[i] += pi * (i - 0.6) / 90.0;
		geese[i].x += 4 * (i + 0.5);
		if (geese[i].x >= width())
			geese[i].x = -geese[i].w;
		if (i < 1)
			geese[i].y = height() / 2 * (1 + 0.3 * sin(phase[i])) - height() / 4;
		else
			geese[i].y = height() / 2 * (1 + 0.3 * (i - 0.6) * sin(phase[i])) - height() / 4;
	}

	for (unsigned i = 0; i < 6; i++) {
		clouds[i].x -= clouds[i].w / 32;
		if (clouds[i].x <= -clouds[i].w)
			clouds[i].x = width();
	}
}
