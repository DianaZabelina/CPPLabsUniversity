#include "GooseWindow.h"
#include <cmath>

GooseWindow::GooseWindow()
: _goose(_renderer, "goose.png"),
  _cloud(_renderer, "cloud.png")
{
	SDL_SetWindowTitle(_window.get(), "Some evil birds window o_O");
	x = 50.0;
	y = 0.0;
	phase = 0.0;
}

void GooseWindow::render()
{
	//небо
	SDL_SetRenderDrawColor(_renderer.get(), 63, 192, 255, 255);
	SDL_RenderClear(_renderer.get());
	for (unsigned i = 0; i < 6; i++)
		_cloud.draw(clouds[i]);
	_goose.draw(x, y, (sin(phase) + cos(phase)) / 2 * 180 / 3.1415);
	//_goose.draw(x, y, phase*20);
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
	phase += pi / 90.0;
	x += 4;
	if (x >= width())
		x = -_goose.width();
	y = height() / 2 * (1 + 0.3 * sin(phase)) - height() / 4;

	for (unsigned i = 0; i < 6; i++) {
		clouds[i].x -= clouds[i].w / 32;
		if (clouds[i].x <= -clouds[i].w)
			clouds[i].x = width();
	}
}
