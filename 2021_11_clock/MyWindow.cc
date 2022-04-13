#include "MyWindow.h"
#include <cmath>
#include <chrono>
#include <ctime>

/*
 * 1.  Дорисовать циферблат, сделав мин/сек штрихи
 * 1.5 Нарисовть цифры (опционально)
 * 2.  Добавить мин и час стрелки
 * 3.  Дорисовать часы (параллелепипед с цветными гранями)
 * 4.  Сцена должна медленно вращаться
 */

MyWindow::MyWindow()
: Window(WINDOW_WIDTH, WINDOW_HEIGHT) {
	SDL_SetWindowTitle(_window.get(), "My OpenGL Window");
}

void MyWindow::draw_clock() {
	for (double a = 0.0; a < 360.0; a += 360.0 / 12.0) {
		glPushMatrix();
		glRotated(a, 0.0, 0.0, 1.0);
		glTranslated(0.0, 0.9, 0.0);
		glBegin(GL_QUADS);
		glColor3d(0.0, 0.7, 0.3);
		glVertex2d(-0.05, 0.05);
		glVertex2d(0.05, 0.05);
		glVertex2d(0.05, -0.05);
		glVertex2d(-0.05, -0.05);
		glEnd();
		glPopMatrix();
	}

	for (double a = 0.0; a < 360.0; a += 360.0 / 12.0 / 5.0) {
		glPushMatrix();
		glRotated(a, 0.0, 0.0, 1.0);
		glTranslated(0.0, 0.9, 0.0);
		glBegin(GL_QUADS);
		glColor3d(0.0, 0.7, 0.3);
		glVertex2d(-0.025, 0.025);
		glVertex2d(0.025, 0.025);
		glVertex2d(0.025, -0.025);
		glVertex2d(-0.025, -0.025);
		glEnd();
		glPopMatrix();
	}

	double seconds_angle = fmod(_seconds, 60) / 60 * 360;
	glPushMatrix();
	glRotated(seconds_angle, 0.0, 0.0, -1.0);
	glBegin(GL_QUADS);
	glColor3d(1.0, 0.5, 0.0);
	glVertex2d(0.0, 0.0);
	glVertex2d(-0.025, 0.1);
	glVertex2d(0.0, 0.9);
	glVertex2d(0.025, 0.1);
	glEnd();
	glPopMatrix();

	double minutes_angle = fmod((_seconds / 60), 60) / 60 * 360.;
	glPushMatrix();
	glRotated(minutes_angle, 0.0, 0.0, -1.0);
	glBegin(GL_QUADS);
	glColor3d(0.9, 0.0, 0.3);
	glVertex2d(0.0, 0.0);
	glVertex2d(-0.05, 0.1);
	glVertex2d(0.0, 0.7);
	glVertex2d(0.05, 0.1);
	glEnd();
	glPopMatrix();

	double hours_angle = (_seconds / 3600) / 60 * 360;
	glPushMatrix();
	glRotated(hours_angle, 0.0, 0.0, -1.0);
	glBegin(GL_QUADS);
	glColor3d(0.9, 1.0, 0.0);
	glVertex2d(0.0, 0.0);
	glVertex2d(-0.1, 0.1);
	glVertex2d(0.0, 0.5);
	glVertex2d(0.1, 0.1);
	glEnd();
	glPopMatrix();
}

void MyWindow::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
	//1
	glLoadIdentity();
	glTranslated(0.5, 0.5, 0.0);
	glScaled(0.5, 0.2, 1.0);

	glBegin(GL_TRIANGLES);
	glColor3d(1.0, 0.0, 0.0);
	glVertex2d(0.0, 0.9);
	glColor3d(0.0, 1.0, 0.0);
	glVertex2d(0.9, -0.9);
	glColor3d(0.0, 0.0, 1.0);
	glVertex2d(-0.9, -0.9);
	glEnd();

	//2
	glLoadIdentity();
	glScaled(0.5, 0.2, 1.0);
	glTranslated(0.5, 0.5, 0.0);

	glBegin(GL_TRIANGLES);
	glColor3d(1.0, 0.0, 0.0);
	glVertex2d(0.0, 0.9);
	glColor3d(0.0, 1.0, 0.0);
	glVertex2d(0.9, -0.9);
	glColor3d(0.0, 0.0, 1.0);
	glVertex2d(-0.9, -0.9);
	glEnd();

	//3
	static double a = 0.0;
	a += 0.5;
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glRotated(a, 0.0, 0.0, 1.0);

	glBegin(GL_TRIANGLES);
	glColor3d(1.0, 0.0, 0.0);
	glVertex2d(0.0, 0.9);
	glColor3d(0.0, 1.0, 0.0);
	glVertex2d(0.9, -0.9);
	glColor3d(0.0, 0.0, 1.0);
	glVertex2d(-0.9, -0.9);
	glEnd();
	*/

	glLoadIdentity();
	//наклон
	gluLookAt(3.0, 3.0, 2.0,
				0.0, 0.0, 0.5,
				0.0, 0.0, 1.0);
	//поворот
	glRotated(_step, 0.0, 0.0, 1.0);

	glBegin(GL_QUADS);
	//светлая основа
	glColor3d(0.3, 0.3, 0.3);
	glVertex3d(-1.0, 1.0, 0.0);
	glVertex3d(1.0, 1.0, 0.0);
	glVertex3d(1.0, -1.0, 0.0);
	glVertex3d(-1.0, -1.0, 0.0);
	//тёмная основа
	glColor3d(0.2, 0.2, 0.2);
	glVertex3d(-1.0, 1.0, -0.1);
	glVertex3d(1.0, 1.0, -0.1);
	glVertex3d(1.0, -1.0, -0.1);
	glVertex3d(-1.0, -1.0, -0.1);

	//оранжевая сторона
	glColor3d(0.9, 0.3, 0.0);
	glVertex3d(-1.0, -1.0, 0.0);
	glVertex3d(-1.0, 1.0, 0.0);
	glVertex3d(-1.0, 1.0, -0.1);
	glVertex3d(-1.0, -1.0, -0.1);
	//салатовая сторона
	glColor3d(0.5, 1.0, 0.0);
	glVertex3d(-1.0, 1.0, 0.0);
	glVertex3d(1.0, 1.0, 0.0);
	glVertex3d(1.0, 1.0, -0.1);
	glVertex3d(-1.0, 1.0, -0.1);
	//голубая сторона
	glColor3d(0.0, 0.5, 1.0);
	glVertex3d(1.0, -1.0, 0.0);
	glVertex3d(1.0, 1.0, 0.0);
	glVertex3d(1.0, 1.0, -0.1);
	glVertex3d(1.0, -1.0, -0.1);
	//фиолетовая сторона
	glColor3d(0.5, 0.0, 0.5);
	glVertex3d(-1.0, -1.0, 0.0);
	glVertex3d(1.0, -1.0, 0.0);
	glVertex3d(1.0, -1.0, -0.1);
	glVertex3d(-1.0, -1.0, -0.1);

	glEnd();
	//парение циферблата
	glTranslated(0.0, 0.0, 0.05);
	draw_clock();
}

void MyWindow::setupGL() {
	//проверка на глубину
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.1f, 0.25f, 0.45f, 1.0f);

	double aspect_ratio = double(width()) / double(height());

	glMatrixMode(GL_PROJECTION);
	//gluOrtho2D(-aspect_ratio, aspect_ratio, -1, 1);
	gluPerspective(45.0, aspect_ratio, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void MyWindow::update() {
	auto now = std::chrono::high_resolution_clock::now();
	auto tt = std::chrono::high_resolution_clock::to_time_t(now);
	auto local_time = *localtime(&tt);
	_seconds = local_time.tm_sec + 60 * local_time.tm_min
			+ 3600 * local_time.tm_hour;
	_step += 0.025;
}
