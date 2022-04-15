#include "HouseWindow.h"

HouseWindow::HouseWindow()
: Window(WINDOW_WIDTH, WINDOW_HEIGHT) {
	SDL_SetWindowTitle(_window.get(), "House Window");
}

void HouseWindow::update() {
}

void HouseWindow::render() {
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
