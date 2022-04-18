#include "HouseWindow.h"
#include <memory>

HouseWindow::HouseWindow()
: Window(WINDOW_WIDTH, WINDOW_HEIGHT),
  _house_model("House.txt") {
	SDL_SetWindowTitle(_window.get(), "House Window");
}

void HouseWindow::update() {
	_angle += 0.5;
}

void HouseWindow::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(	4.0, 4.0, 4.5,
				0.0, 0.0, 1.5,
				0.0, 0.0, 1.0);
	glRotated(_angle, 0.0, 0.0, 1.0);
	Texture::disable();

	/*
	 * "Ќовогоднее настроение"
	 *
	 * - плоскость/крива€ поверхность
	 * - в центре - Єлка, ствол - цилиндр, ветки - несколько конусов
	 * вокруг Єлки - несколько снеговиков:  3 сферы,
	 * 										нос - морковка (конус),
	 * 										руки - цилиндры,
	 * 										глаза - сферы и т.п.
	 */

	//_house_texture.bind();
	//_house_model.draw();

	//glDisable(GL_LIGHTING);
	//glDisable(GL_FOG);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_FOG);

	glDisable(GL_LIGHTING);

	Texture::enable();
	_sky_texture.bind();
	draw_sphere(32, 16, 20.0);

	glEnable(GL_LIGHTING);

	glPopMatrix();

	Texture::disable();

	//поверхность
	glBegin(GL_QUADS);
	glNormal3d(0.0, 0.0, 1.0);
	for (int i = -50; i < 50; i++)
		for (int j = -50; j < 50; j++) {
			glVertex3d(i + 0, j + 0, 0.0);
			glVertex3d(i + 1, j + 0, 0.0);
			glVertex3d(i + 1, j + 1, 0.0);
			glVertex3d(i + 0, j + 1, 0.0);
		}
	//Єлка
	glPushMatrix();
	glTranslated(10.0, 0.0, 0.75);
	Texture::enable();
	//ствол
	_tree_texture.bind();
	draw_cylinder(12, 0.25, 1.5);
	glTranslated(0.0, 0.0, 1.25);
	//ветки
	_spruce_texture.bind();
	draw_cone(12, 1, 1.5);
	glTranslated(0.0, 0.0, 1.0);
	draw_cone(12, 0.75, 1.5);
	glPopMatrix();
	Texture::disable();


	//снеговик
	glPushMatrix();
	glTranslated(10.0, 0.0, -2.0);
	draw_sphere(16, 10, 1.0);
	glTranslated(0.0, 0.0, 1.25);
	draw_sphere(12, 8, 0.7);
	glTranslated(0.0, 0.0, 0.9);
	draw_sphere(10, 6, 0.4);
	//нос
	Texture::enable();
	_carrot_texture.bind();
	glRotated(90.0, 1.0, 1.0, 0.0);
	draw_cone(8, 0.1, 1.0);
	//руки
	_tree_texture.bind();
	glTranslated(0.05, 0.0, -0.05);
	glRotated(90.0, 1.0, 0.0, 0.0);
	draw_cylinder(8, 0.05, 1.75);
	glTranslated(0.05, 0.0, 0.05);
	glRotated(90.0, 0.0, 1.0, 0.0);
	draw_cylinder(8, 0.05, 1.75);
	//глаза
	_rock_texture.bind();
	glTranslated(0.25, 0.35, 0.0);
	draw_sphere(10, 6, 0.05);
	glTranslated(-0.3, 0.0, -0.3);
	draw_sphere(10, 6, 0.05);
	glTranslated(-0.4, 0.25, 0.5);
	draw_sphere(10, 6, 0.1);
	glTranslated(-0.3, 0.075, 0.3);
	draw_sphere(10, 6, 0.1);
	glPopMatrix();
	Texture::disable();

	/*
	 * draw_prism(24, 1, 2);
	 * _cylinder_texture.bind();
	 * draw_cylinder(24, 1, 2);
	 * draw_pyramid(16, 1, 2);
	 * _cone_texture.bind();
	 * draw_cone(12, 1, 2);
	 * draw_disco_ball(16, 8, 2.0);
	 * _earth_texture.bind();
	 * _moon_texture.bind();
	 * _sun_texture.bind();
	 * draw_sphere(24, 12, 2.0);
	 */
}

void HouseWindow::setupGL() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearColor(0.1f, 0.25f, 0.45f, 1.0f);

	double aspect_ratio = double(width()) / double(height());
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, aspect_ratio, 0.1, 40.0);
	glMatrixMode(GL_MODELVIEW);
}
