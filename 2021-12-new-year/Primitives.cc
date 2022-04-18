#include "Primitives.h"

static constexpr double Pi = acos(-1.0);

/*
 * В полярных/сферических координатах:
 * x, [0] - радиус
 * y, [1] - phi
 * z, [2] - theta
 */

glm::vec2 cart2pol(const glm::vec2 &cart) {
	return glm::vec2(
				hypot(cart.y, cart.x),
				atan2(cart.y, cart.x));
}

glm::vec2 pol2cart(const glm::vec2 &pol) {
	return glm::vec2(
				pol[0] * cos(pol[1]),
				pol[0] * sin(pol[1]));
}

glm::vec3 cart2cyl(const glm::vec3 &cart) {
	return glm::vec3(
				hypot(cart.y, cart.x),
				atan2(cart.y, cart.x),
				cart.z);
}

glm::vec3 cyl2cart(const glm::vec3 &cyl) {
	return glm::vec3(
				cyl[0] * cos(cyl[1]),
				cyl[0] * sin(cyl[1]),
				cyl.z);
}

glm::vec3 cart2sph(const glm::vec3 &cart) {
	return glm::vec3(
				sqrt(cart.x * cart.x + cart.y * cart.y + cart.z * cart.z),
				atan2(cart.y, cart.x),
				atan2(hypot(cart.x, cart.y), cart.z));
}

glm::vec3 sph2cart(const glm::vec3 &sph) {
	return glm::vec3(
				sph[0] * sin(sph[2]) * cos(sph[1]),
				sph[0] * sin(sph[2]) * sin(sph[1]),
				sph[0] * cos(sph[2]));
}

void draw_prism(unsigned sides, double radius, double height) {
	float delta_phi = Pi * 2.0 / sides;
	glm::vec3 top_center    { 0.f, 0.f, height };
	glm::vec3 top_normal    { 0.f, 0.f, 1.f };
	glm::vec3 bottom_center { 0.f, 0.f, 0.f };
	glm::vec3 bottom_normal { 0.f, 0.f, -1.f };
	
	glBegin(GL_POLYGON);
	glNormal3fv(&bottom_normal[0]);
	for (unsigned s = 0; s < sides; s++) {
		float phi = delta_phi * s;
		glm::vec3 vertex_cyl { radius, phi, 0.f };
		auto vertex_cart = cyl2cart(vertex_cyl);
		auto t = glm::vec2(0.875f + 0.125f * sin(phi),
				0.75f - 0.25f * cos(phi));
		glTexCoord2fv(&t[0]);
		glVertex3fv(&vertex_cart[0]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3fv(&top_normal[0]);
	for (unsigned s = 0; s < sides; s++) {
		float phi = delta_phi * s;
		glm::vec3 vertex_cyl { radius, phi, height };
		auto vertex_cart = cyl2cart(vertex_cyl);
		auto t = glm::vec2(0.875f + 0.125f * sin(phi),
				0.25f + 0.25f * cos(phi));
		glTexCoord2fv(&t[0]);
		glVertex3fv(&vertex_cart[0]);
	}
	glEnd();

	glBegin(GL_QUADS);
	for (unsigned s = 0; s < sides; s++) {
		float phi1 = delta_phi * (s + 0);
		float phi2 = delta_phi * (s + 1);
		float phi_n = (phi1 + phi2) / 2.f;
		glm::vec3 v1_cyl { radius, phi1, height };
		glm::vec3 v2_cyl { radius, phi2, height };
		glm::vec3 v3_cyl { radius, phi2, 0.f };
		glm::vec3 v4_cyl { radius, phi1, 0.f };
		glm::vec3 n_cyl { 1, phi_n, 0.f };
		auto t1 = glm::vec2(0.75f / sides * (s + 0), 0.0f);
		auto t2 = glm::vec2(0.75f / sides * (s + 1), 0.0f);
		auto t3 = glm::vec2(0.75f / sides * (s + 1), 1.0f);
		auto t4 = glm::vec2(0.75f / sides * (s + 0), 1.0f);
		auto v1 = cyl2cart(v1_cyl);
		auto v2 = cyl2cart(v2_cyl);
		auto v3 = cyl2cart(v3_cyl);
		auto v4 = cyl2cart(v4_cyl);
		auto n = cyl2cart(n_cyl);
		glNormal3fv(&n[0]);
		glTexCoord2fv(&t1[0]);
		glVertex3fv(&v1[0]);
		glTexCoord2fv(&t2[0]);
		glVertex3fv(&v2[0]);
		glTexCoord2fv(&t3[0]);
		glVertex3fv(&v3[0]);
		glTexCoord2fv(&t4[0]);
		glVertex3fv(&v4[0]);
	}
	glEnd();
}

void draw_cylinder(unsigned sides, double radius, double height) {
	float delta_phi = Pi * 2.0 / sides;
	glm::vec3 bottom_center { 0.f, 0.f, 0.f };
	glm::vec3 bottom_normal { 0.f, 0.f, -1.f };
	glm::vec3 top_center { 0.f, 0.f, height };
	glm::vec3 top_normal { 0.f, 0.f, 1.f };

	glBegin(GL_POLYGON);
	glNormal3fv(&bottom_normal[0]);
	for (unsigned s = 0; s < sides; s++) {
		float phi = delta_phi * s;
		glm::vec3 vertex_cyl { radius, phi, 0.f };
		auto vertex_cart = cyl2cart(vertex_cyl);
		auto t = glm::vec2(0.875f + 0.125f * sin(phi),
				0.75f - 0.25f * cos(phi));
		glTexCoord2fv(&t[0]);
		glVertex3fv(&vertex_cart[0]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3fv(&top_normal[0]);
	for (unsigned s = 0; s < sides; s++) {
		float phi = delta_phi * s;
		glm::vec3 vertex_cyl { radius, phi, height };
		auto vertex_cart = cyl2cart(vertex_cyl);
		auto t = glm::vec2(0.875f + 0.125f * sin(phi),
				0.25f + 0.25f * cos(phi));
		glTexCoord2fv(&t[0]);
		glVertex3fv(&vertex_cart[0]);
	}
	glEnd();

	glBegin(GL_QUADS);
	for (unsigned s = 0; s < sides; s++) {
		float phi1 = delta_phi * (s + 0);
		float phi2 = delta_phi * (s + 1);
		glm::vec3 v1_cyl { radius, phi1, height };
		glm::vec3 v2_cyl { radius, phi2, height };
		glm::vec3 v3_cyl { radius, phi2, 0.f };
		glm::vec3 v4_cyl { radius, phi1, 0.f };
		glm::vec3 n1_cyl { 1, phi1, 0.f };
		glm::vec3 n2_cyl { 1, phi2, 0.f };
		auto t1 = glm::vec2(0.75f / sides * (s + 0), 0.0f);
		auto t2 = glm::vec2(0.75f / sides * (s + 1), 0.0f);
		auto t3 = glm::vec2(0.75f / sides * (s + 1), 1.0f);
		auto t4 = glm::vec2(0.75f / sides * (s + 0), 1.0f);
		auto v1 = cyl2cart(v1_cyl);
		auto v2 = cyl2cart(v2_cyl);
		auto v3 = cyl2cart(v3_cyl);
		auto v4 = cyl2cart(v4_cyl);
		auto n1 = cyl2cart(n1_cyl);
		auto n2 = cyl2cart(n2_cyl);
		glNormal3fv(&n1[0]);
		glTexCoord2fv(&t1[0]);
		glVertex3fv(&v1[0]);
		glNormal3fv(&n2[0]);
		glTexCoord2fv(&t2[0]);
		glVertex3fv(&v2[0]);
		glNormal3fv(&n2[0]);
		glTexCoord2fv(&t3[0]);
		glVertex3fv(&v3[0]);
		glNormal3fv(&n1[0]);
		glTexCoord2fv(&t4[0]);
		glVertex3fv(&v4[0]);

	}
	glEnd();
}

void draw_pyramid(unsigned sides, double radius, double height) {
	glm::vec3 bottom_normal { 0.f, 0.f, -1.f };
	glm::vec3 top_vertex { 0.f, 0.f, height };
	float delta_phi = Pi * 2.0 / sides;

	glBegin(GL_POLYGON);
	glNormal3fv(&bottom_normal[0]);
	for (unsigned s = 0; s < sides; s++) {
		float phi = delta_phi * s;
		glm::vec3 vertex_cyl { radius, phi, 0.f };
		auto vertex_cart = cyl2cart(vertex_cyl);
		auto t = glm::vec2(0.75f + 0.25f * sin(phi), 0.5f - 0.5f * cos(phi));
		glTexCoord2fv(&t[0]);
		glVertex3fv(&vertex_cart[0]);
	}
	glEnd();

	float theta_n = atan2(height, radius * cos(delta_phi / 2.f));
	glBegin(GL_TRIANGLES);
	for (unsigned s = 0; s < sides; s++) {
		float phi1 = delta_phi * (s + 0);
		float phi2 = delta_phi * (s + 1);
		float phi_n = (phi1 + phi2) / 2.f;
		glm::vec3 normal_sph { 1.f, phi_n, theta_n };
		auto normal_cart = sph2cart(normal_sph);
		auto v1 = cyl2cart(glm::vec3(radius, phi1, 0.f));
		auto v2 = cyl2cart(glm::vec3(radius, phi2, 0.f));
		auto tt = glm::vec2(0.25f, 0.5f);
		auto t1 = glm::vec2(0.25f + 0.25f * sin(phi1), 0.5f + 0.5f * cos(phi1));
		auto t2 = glm::vec2(0.25f + 0.25f * sin(phi2), 0.5f + 0.5f * cos(phi2));
		glNormal3fv(&normal_cart[0]);
		glTexCoord2fv(&tt[0]);
		glVertex3fv(&top_vertex[0]);
		glTexCoord2fv(&t1[0]);
		glVertex3fv(&v1[0]);
		glTexCoord2fv(&t2[0]);
		glVertex3fv(&v2[0]);

	}
	glEnd();
}

void draw_cone(unsigned sides, double radius, double height) {
	glm::vec3 bottom_normal { 0.f, 0.f, -1.f };
	glm::vec3 top_vertex { 0.f, 0.f, height };
	float delta_phi = Pi * 2.0 / sides;

	glBegin(GL_POLYGON);
	glNormal3fv(&bottom_normal[0]);
	for (unsigned s = 0; s < sides; s++) {
		float phi = delta_phi * s;
		glm::vec3 vertex_cyl { radius, phi, 0.f };
		auto vertex_cart = cyl2cart(vertex_cyl);
		auto t = glm::vec2(0.75f + 0.25f * sin(phi), 0.5f - 0.5f * cos(phi));
		glTexCoord2fv(&t[0]);
		glVertex3fv(&vertex_cart[0]);
	}
	glEnd();
	float theta_n = atan2(height, radius * cos(delta_phi / 2.f));
	glBegin(GL_QUADS);
	for (unsigned s = 0; s < sides; s++) {
		float phi1 = delta_phi * (s + 0);
		float phi2 = delta_phi * (s + 1);
		auto n1 = sph2cart(glm::vec3(1.f, phi1, theta_n));
		auto n2 = sph2cart(glm::vec3(1.f, phi2, theta_n));
		auto v1 = cyl2cart(glm::vec3(radius, phi1, 0.f));
		auto v2 = cyl2cart(glm::vec3(radius, phi2, 0.f));
		auto tt = glm::vec2(0.25f, 0.5f);
		auto t1 = glm::vec2(0.25f + 0.25f * sin(phi1), 0.5f + 0.5f * cos(phi1));
		auto t2 = glm::vec2(0.25f + 0.25f * sin(phi2), 0.5f + 0.5f * cos(phi2));
		glNormal3fv(&n1[0]);
		glTexCoord2fv(&tt[0]);
		glVertex3fv(&top_vertex[0]);
		glTexCoord2fv(&t1[0]);
		glVertex3fv(&v1[0]);
		glNormal3fv(&n2[0]);
		glTexCoord2fv(&t2[0]);
		glVertex3fv(&v2[0]);
		glTexCoord2fv(&tt[0]);
		glVertex3fv(&top_vertex[0]);

	}
	glEnd();
}

void draw_disco_ball(unsigned cols, double rows, double radius) {
	float delta_theta = Pi / rows;
	float delta_phi = 2.f * Pi / cols;
	glBegin(GL_QUADS);
	for (unsigned row = 0; row < rows; row++) {
		for (unsigned col = 0; col < cols; col++) {
			float theta1 = delta_theta * (row + 0);
			float theta2 = delta_theta * (row + 1);
			float phi1 = delta_phi * (col + 0);
			float phi2 = delta_phi * (col + 1);
			float theta_n = (theta1 + theta2) / 2.f;
			float phi_n = (phi1 + phi2) / 2.f;
			auto n = sph2cart(glm::vec3(1.f, phi_n, theta_n));
			auto v1 = sph2cart(glm::vec3(radius, phi1, theta1));
			auto v2 = sph2cart(glm::vec3(radius, phi2, theta1));
			auto v3 = sph2cart(glm::vec3(radius, phi2, theta2));
			auto v4 = sph2cart(glm::vec3(radius, phi1, theta2));
			auto t1 = glm::vec2(1.f * (col + 0) / cols, 1.f * (row + 0) / rows);
			auto t2 = glm::vec2(1.f * (col + 1) / cols, 1.f * (row + 0) / rows);
			auto t3 = glm::vec2(1.f * (col + 1) / cols, 1.f * (row + 1) / rows);
			auto t4 = glm::vec2(1.f * (col + 0) / cols, 1.f * (row + 1) / rows);
			glNormal3fv(&n[0]);
			glTexCoord2fv(&t1[0]);
			glVertex3fv(&v1[0]);
			glTexCoord2fv(&t2[0]);
			glVertex3fv(&v2[0]);
			glTexCoord2fv(&t3[0]);
			glVertex3fv(&v3[0]);
			glTexCoord2fv(&t4[0]);
			glVertex3fv(&v4[0]);
		}
	}
	glEnd();
}

void draw_sphere(unsigned cols, double rows, double radius) {
	float delta_theta = Pi / rows;
	float delta_phi = 2.f * Pi / cols;
	glBegin(GL_QUADS);
	for (unsigned row = 0; row < rows; row++) {
		for (unsigned col = 0; col < cols; col++) {
			float theta1 = delta_theta * (row + 0);
			float theta2 = delta_theta * (row + 1);
			float phi1 = delta_phi * (col + 0);
			float phi2 = delta_phi * (col + 1);
			auto n1 = sph2cart(glm::vec3(1.f, phi1, theta1));
			auto n2 = sph2cart(glm::vec3(1.f, phi2, theta1));
			auto n3 = sph2cart(glm::vec3(1.f, phi2, theta2));
			auto n4 = sph2cart(glm::vec3(1.f, phi1, theta2));
			auto v1 = sph2cart(glm::vec3(radius, phi1, theta1));
			auto v2 = sph2cart(glm::vec3(radius, phi2, theta1));
			auto v3 = sph2cart(glm::vec3(radius, phi2, theta2));
			auto v4 = sph2cart(glm::vec3(radius, phi1, theta2));
			auto t1 = glm::vec2(1.f * (col + 0) / cols, 1.f * (row + 0) / rows);
			auto t2 = glm::vec2(1.f * (col + 1) / cols, 1.f * (row + 0) / rows);
			auto t3 = glm::vec2(1.f * (col + 1) / cols, 1.f * (row + 1) / rows);
			auto t4 = glm::vec2(1.f * (col + 0) / cols, 1.f * (row + 1) / rows);
			glNormal3fv(&n1[0]);
			glTexCoord2fv(&t1[0]);
			glVertex3fv(&v1[0]);
			glNormal3fv(&n2[0]);
			glTexCoord2fv(&t2[0]);
			glVertex3fv(&v2[0]);
			glNormal3fv(&n3[0]);
			glTexCoord2fv(&t3[0]);
			glVertex3fv(&v3[0]);
			glNormal3fv(&n4[0]);
			glTexCoord2fv(&t4[0]);
			glVertex3fv(&v4[0]);
		}
	}
	glEnd();
}
