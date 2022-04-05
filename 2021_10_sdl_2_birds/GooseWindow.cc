#include "GooseWindow.h"
#include <cmath>

GooseWindow::GooseWindow()
: _goose(_renderer, "goose.png"),
  _cloud(_renderer, "cloud.png")
{
	SDL_SetWindowTitle(_window.get(), "Some evil birds window o_O");
	for (unsigned i = 0; i < 5; i++)
		phase[i] = 0.0;
}

void GooseWindow::render()
{
	//небо
	SDL_SetRenderDrawColor(_renderer.get(), 63, 192, 255, 255);
	SDL_RenderClear(_renderer.get());
	//облака вдали
	for (unsigned i = 0; i < 3; i++)
		_cloud.draw(clouds[i]);
	//гуси
	//_goose.draw(x, y, phase*20);
	//_goose.draw(x, y, (sin(phase) + cos(phase)) / 2 * 180 / 3.1415);
	for (unsigned i = 0; i < 5; i++) {
		_goose.draw(geese[i].x, geese[i].y, (sin(phase[i]) + cos(phase[i])) / 2 * 180 / 3.1415);
	}
	//облака вблизи
	for (unsigned i = 3; i < 6; i++)
			_cloud.draw(clouds[i]);
}

void GooseWindow::handle_keys(const Uint8 *keys)
{
	/*if (keys[SDL_SCANCODE_RIGHT])
		x += 4;
	if (keys[SDL_SCANCODE_LEFT])
		x -= 4;
	if (keys[SDL_SCANCODE_DOWN])
		y += 4;
	if (keys[SDL_SCANCODE_UP])
		y -= 4;*/
}

void GooseWindow::update()
{
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
