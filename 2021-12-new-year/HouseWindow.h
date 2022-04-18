#ifndef HOUSEWINDOW_H_
#define HOUSEWINDOW_H_

#include "Window.h"
#include "Model.h"
#include "Texture.h"
#include "Primitives.h"

class HouseWindow: public Window {
private:
	Model _house_model;
	Texture _house_texture { "House.png" };
	Texture _sky_texture { "Stars.jpg" };
	Texture _tree_texture { "Tree.png" };
	Texture _spruce_texture { "Spruce.png" };
	Texture _carrot_texture { "Carrot.png" };
	Texture _rock_texture { "Rock.png" };

	/*
	 * Texture _cylinder_texture { "Cylinder.png" };
	 * Texture _cone_texture { "Cone.png" };
	 * Texture _earth_texture { "Earth.jpg" };
	 * Texture _moon_texture { "Moon.jpg" };
	 * Texture _sun_texture { "Sun.jpg" };
	 */

	double _angle = 0.0;
public:
	static constexpr int WINDOW_WIDTH = 1280;
	static constexpr int WINDOW_HEIGHT = 640;

	virtual void update() override;
	virtual void render() override;
	virtual void setupGL() override;

public:
	HouseWindow();
	virtual ~HouseWindow() = default;
};

#endif /* HOUSEWINDOW_H_ */
