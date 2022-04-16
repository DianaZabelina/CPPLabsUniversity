#include "HouseWindow.h"
#include <memory>

HouseWindow::HouseWindow()
: Window(WINDOW_WIDTH, WINDOW_HEIGHT),
  _house_model("House.txt") {
	SDL_SetWindowTitle(_window.get(), "House Window");
}

void HouseWindow::update() {
	_angle += 2.0;
}

void HouseWindow::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(	6.0, 6.0, 4.5,
				0.0, 0.0, 1.5,
				0.0, 0.0, 1.0);
	_house_model.draw();
}

void HouseWindow::setupGL() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	double aspect_ratio = double(width()) / double(height());
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, aspect_ratio, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
}
