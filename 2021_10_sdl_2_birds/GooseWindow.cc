#include "GooseWindow.h"
#include <cmath>

GooseWindow::GooseWindow()
: Window(GOOSE_WINDOW_WIDTH, GOOSE_WINDOW_HEIGHT),
  _goose(_renderer, "goose.png"),
  _cloud(_renderer, "cloud.png"),
  _eagle(_renderer, "eagle.png"),
  _bg(_renderer, "bg.png"),
  _sun(_renderer, "sun.png"),
  _mountains(_renderer, "mountains.png", 2.0),
  _forest(_renderer, "forest.png", 4.0),
  _river(_renderer, "river.png", 10.0)
{
	SDL_SetWindowTitle(_window.get(), "Some evil birds window o_O");
	for (unsigned i = 0; i < 5; i++)
		phase[i] = 0.0;
	eagle_x = 50.0;
	eagle_y = 300.0;
	sun_x = width();
	sun_y = 50.0;
}

void GooseWindow::render()
{
	//����
	SDL_SetRenderDrawColor(_renderer.get(), 63, 192, 255, 255);
	SDL_RenderClear(_renderer.get());
	//���
	_bg.draw(0, 0);
	//������
	_sun.draw(sun_x, sun_y);
	//����
	_mountains.draw(0, 250, width(), _mountains.height());
	//���
	_forest.draw(0, 300, width(), _forest.height());
	//����
	_river.draw(0, 500, width(), _river.height());
	//������ �����
	for (unsigned i = 0; i < 3; i++)
		_cloud.draw(clouds[i]);
	//����
	//_goose.draw(x, y, phase*20);
	//_goose.draw(x, y, (sin(phase) + cos(phase)) / 2 * 180 / 3.1415);
	//����
	for (unsigned i = 0; i < 5; i++) {
		_goose.draw(geese[i].x, geese[i].y, (sin(phase[i]) + cos(phase[i])) / 2 * 180 / 3.1415);
	}
	//���
	_eagle.draw(eagle_x, eagle_y);
	//������ ������
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
	sun_x -= 0.6;
	if (sun_x <= -50.0)
		sun_x = width();

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

	_mountains.update();
	_forest.update();
	_river.update();
}
