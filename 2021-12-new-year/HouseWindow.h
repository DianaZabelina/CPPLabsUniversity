#ifndef HOUSEWINDOW_H_
#define HOUSEWINDOW_H_

#include "Window.h"

class HouseWindow: public Window {
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
