#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_

#include <GL/gl.h>
#include <glm/glm/glm.hpp>
#include <cmath>

glm::vec2 cart2pol(const glm::vec2 &cart);
glm::vec2 pol2cart(const glm::vec2 &pol);
glm::vec3 cart2cyl(const glm::vec3 &cart);
glm::vec3 cyl2cart(const glm::vec3 &cyl);
glm::vec3 cart2sph(const glm::vec3 &cart);
glm::vec3 sph2cart(const glm::vec3 &sph);

void draw_prism(unsigned sides, double radius, double height);
void draw_cylinder(unsigned sides, double radius, double height);

void draw_pyramid(unsigned sides, double radius, double height);
void draw_cone(unsigned sides, double radius, double height);

void draw_disco_ball(unsigned cols, double rows, double radius);
void draw_sphere(unsigned cols, double rows, double radius);

#endif /* PRIMITIVES_H_ */
