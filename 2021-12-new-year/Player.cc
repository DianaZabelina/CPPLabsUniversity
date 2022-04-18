#include "Player.h"
#include <cmath>

static constexpr float Pi = acos(-1.0);

void Player::move_forward(float dist) {
	glm::vec3 offset;
	if (_fly) {
		offset = sph2cart(glm::vec3(dist, _phi, _theta));
	} else {
		offset = cyl2cart(glm::vec3(dist, _phi, 0.f));
	}
	_position += offset;
}

void Player::move_backward(float dist) {
	move_forward(-dist);
}

void Player::move_left(float dist) {
	auto offset = cyl2cart(glm::vec3(dist, _phi + Pi / 2.f, 0.f));
	_position += offset;
}

void Player::move_right(float dist) {
	auto offset = cyl2cart(glm::vec3(dist, _phi - Pi / 2.f, 0.f));
	_position += offset;
}

void Player::turn_phi(float angle) {
	_phi += angle;
	if (_phi >= 2.f * Pi)
		_phi -= 2.f * Pi;
	if (_phi < 0.f)
		_phi += 2.f * Pi;
}

static constexpr float MIN_THETA = Pi / 32.f;
void Player::turn_theta(float angle) {
	_theta += angle;
	if (_theta < MIN_THETA)
		_theta = MIN_THETA;
	if (_theta > Pi - MIN_THETA)
		_theta = Pi - MIN_THETA;
}
