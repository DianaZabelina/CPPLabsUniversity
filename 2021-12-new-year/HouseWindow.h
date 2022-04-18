#ifndef HOUSEWINDOW_H_
#define HOUSEWINDOW_H_

#include "Window.h"
#include "Model.h"
#include "Texture.h"
#include "Primitives.h"
#include "Player.h"

class HouseWindow: public Window {
private:
	Model _house_model;
	Texture _house_texture { "House.png" };
	Texture _sky_texture { "Stars.jpg" };
	Texture _moon_texture { "Moon.jpg" };
	Texture _tree_texture { "Tree.png" };
	Texture _spruce_texture { "Christmas_tree.png" };
	Texture _carrot_texture { "Carrot.png" };
	Texture _rock_texture { "Rock.png" };

	/*
	 * Texture _cylinder_texture { "Cylinder.png" };
	 * Texture _cone_texture { "Cone.png" };
	 * Texture _earth_texture { "Earth.jpg" };
	 * Texture _sun_texture { "Sun.jpg" };
	 */

	double _angle1 = 0.0, _angle2 = 0.0, _angle3 = 0.0, _angle4 = 0.0;
	Player _player { glm::vec3(3.f, 3.f, 1.5f), 0.f, 1.6f };
public:
	static constexpr int WINDOW_WIDTH = 1280;
	static constexpr int WINDOW_HEIGHT = 640;

	virtual void handle_event(const SDL_Event &event);
	virtual void handle_keys(const Uint8 *keys);

	virtual void update() override;
	virtual void render() override;
	virtual void setupGL() override;

public:
	HouseWindow();
	virtual ~HouseWindow() = default;
};

#endif /* HOUSEWINDOW_H_ */
