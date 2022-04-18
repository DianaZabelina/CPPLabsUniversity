#include "HouseWindow.h"
#include <memory>

HouseWindow::HouseWindow()
: Window(WINDOW_WIDTH, WINDOW_HEIGHT),
  _house_model("House.txt") {
	SDL_SetWindowTitle(_window.get(), "House Window");
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void HouseWindow::update() {
	_angle1 += 0.15;
	_angle2 += 0.25;
	_angle3 += 0.35;
	_angle4 += 0.45;
}

void HouseWindow::render() {
	auto eye = _player.position();
	auto center = _player.center();

	glm::vec3 moon_position {12.f, 12.f, 60.f};
	glm::vec3 light_position {0.f, 0.f, 0.f};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(	eye.x, eye.y, eye.z,
				center.x, center.y, center.z,
				0.0, 0.0, 1.0);

	/*
	 * "Новогоднее настроение"
	 *
	 * - плоскость/кривая поверхность
	 * - в центре - ёлка, ствол - цилиндр, ветки - несколько конусов
	 * вокруг ёлки - несколько снеговиков:  3 сферы,
	 * 										нос - морковка (конус),
	 * 										руки - цилиндры,
	 * 										глаза - сферы и т.п.
	 */

	//_house_texture.bind();
	//_house_model.draw();

	//небо
	glPushMatrix();
	glTranslated(eye.x, eye.y, eye.z);
	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);

	Texture::enable();
	_sky_texture.bind();
	draw_sphere(32, 16, 100.0);
	glEnable(GL_LIGHTING);
	Texture::disable();

	//луна
	GLfloat white[4] { 1.f, 1.f, 1.f, 1.f };
	GLfloat black[4] { 0.f, 0.f, 0.f, 1.f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, white);
	glTranslated(moon_position.x, moon_position.y, moon_position.z);
	glLightfv(GL_LIGHT0, GL_POSITION, &light_position[0]);
	glRotated(-80.0, 0.0f, 1.0f, 0.0f);
	Texture::enable();
	_moon_texture.bind();
	draw_sphere(32, 16, 2.5);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

	glEnable(GL_FOG);
	glPopMatrix();

	Texture::disable();

	//поверхность
	glBegin(GL_QUADS);
	glNormal3d(0.0, 0.0, 1.0);
	for (int i = -150; i < 150; i++)
		for (int j = -150; j < 150; j++) {
			glVertex3d(i + 0, j + 0, 0.0);
			glVertex3d(i + 1, j + 0, 0.0);
			glVertex3d(i + 1, j + 1, 0.0);
			glVertex3d(i + 0, j + 1, 0.0);
		}
	glEnd();

	//ёлка
	glPushMatrix();
	glTranslated(0.0, 0.0, 0.75);
	Texture::enable();
	//ствол
	_tree_texture.bind();
	draw_cylinder(12, 0.25, 1.5);
	//ветки
	glTranslated(0.0, 0.0, 1.0);
	_spruce_texture.bind();
	draw_cone(12, 1.25, 1.5);
	glTranslated(0.0, 0.0, 1.0);
	draw_cone(12, 1.0, 1.5);
	glTranslated(0.0, 0.0, 1.0);
	draw_cone(12, 0.75, 1.5);
	glPopMatrix();
	Texture::disable();

	//снеговик 1
	glPushMatrix();
	glRotated(_angle1, 0.0, 0.0, 1.0);
	glTranslated(10.0, 0.0, 1.0);
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
	//пуговки
	glTranslated(-0.4, 0.25, 0.5);
	draw_sphere(10, 6, 0.1);
	glTranslated(-0.3, 0.075, 0.3);
	draw_sphere(10, 6, 0.1);
	glPopMatrix();
	Texture::disable();

	//снеговик 2
	glPushMatrix();
	glRotated(_angle2, 0.0, 0.0, 1.0);
	glTranslated(-10.0, 0.0, 1.0);
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
	//пуговки
	glTranslated(-0.4, 0.25, 0.5);
	draw_sphere(10, 6, 0.1);
	glTranslated(-0.3, 0.075, 0.3);
	draw_sphere(10, 6, 0.1);
	glPopMatrix();
	Texture::disable();

	//снеговик 2
	glPushMatrix();
	glRotated(_angle3, 0.0, 0.0, 1.0);
	glTranslated(20.0, 0.0, 1.0);
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
	//пуговки
	glTranslated(-0.4, 0.25, 0.5);
	draw_sphere(10, 6, 0.1);
	glTranslated(-0.3, 0.075, 0.3);
	draw_sphere(10, 6, 0.1);
	glPopMatrix();
	Texture::disable();

	//снеговик 1
	glPushMatrix();
	glRotated(_angle4, 0.0, 0.0, 1.0);
	glTranslated(-20.0, 0.0, 1.0);
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
	//пуговки
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
	glEnable(GL_FOG);

	//GLfloat fog_color[4] {0.3f, 0.3f, 0.3f, 1.0f};

	glFogf(GL_FOG_END, 70.f);
	glFogf(GL_FOG_DENSITY, 0.2f);
	glFogi(GL_FOG_MODE, GL_LINEAR);

	//glFogfv(GL_FOG_COLOR, fog_color);

	glClearColor(0.1f, 0.25f, 0.45f, 1.0f);

	double aspect_ratio = double(width()) / double(height());

	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, aspect_ratio, 0.1, 120.0);
	glMatrixMode(GL_MODELVIEW);
}

void HouseWindow::handle_event(const SDL_Event &event) {
	switch (event.type) {
	case SDL_MOUSEMOTION:
		_player.turn_phi(-event.motion.xrel * Player::TURN_ANGLE);
		_player.turn_theta(event.motion.yrel * Player::TURN_ANGLE);
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.scancode == SDL_SCANCODE_F)
			_player.toggle_fly();
		break;
	}
}

void HouseWindow::handle_keys(const Uint8 *keys) {
	if (keys[SDL_SCANCODE_W])
		_player.move_forward();
	if (keys[SDL_SCANCODE_S])
		_player.move_backward();
	if (keys[SDL_SCANCODE_A])
		_player.move_left();
	if (keys[SDL_SCANCODE_D])
		_player.move_right();
}
