#ifndef GOOSEWINDOW_H_
#define GOOSEWINDOW_H_

#include "Window.h"
#include "Texture.h"

class GooseWindow final: public Window
{
private:
	Texture _goose;
	Texture _cloud;
	Texture _eagle;
	Texture _bg;
	Texture _sun;

	double phase[5];

	SDL_FRect geese[5] {
			{ 50.0, 0.0, 64.0, 64.0 },
			{ 50.0, 25.0, 64.0, 64.0 },
			{ 50.0, 50.0, 64.0, 64.0 },
			{ 50.0, 75.0, 64.0, 64.0 },
			{ 50.0, 100.0, 64.0, 64.0 }
	};

	SDL_FRect clouds[6] {
			{128.0, 200.0, 128.0, 64.0},
			{356.0, 430.0, 192.0, 70.0},
			{500.0, 340.0, 160.0, 90.0},
			{50.0, 20.0, 384.0, 192.0},
			{420.0, 179.0, 480.0, 200.0},
			{220.0, 230.0, 500.0, 300.0},
	};

	double eagle_x, eagle_y;
	double sun_x, sun_y;

public:
	GooseWindow();
	virtual ~GooseWindow() = default;

	virtual void render() override;
	virtual void handle_keys(const Uint8 *keys) override;
	virtual void update() override;
};

#endif /* GOOSEWINDOW_H_ */
