#ifndef WINDOWWITHRECTANGLES_H_
#define WINDOWWITHRECTANGLES_H_

#include "Window.h"

class WindowWithRectangles: public Window {
public:
	SDL_Rect rect1 { 50, 50, 15, 15 };
	int rect1_dx = 1, rect1_dy = 1;

	SDL_Rect rect2 { 685, 485, 15, 15 };
	SDL_Rect border1 { 10, 10, 780, 580 };
	SDL_Rect border2 { 12, 12, 776, 576 };

	WindowWithRectangles();
	//деструктор
	virtual ~WindowWithRectangles() {}

	virtual void handle_keys(const Uint8 *keys) override;
	virtual void update() override;
	virtual void render() override;
};

#endif /* WINDOWWITHRECTANGLES_H_ */
