#ifndef MAZEWINDOW_H_
#define MAZEWINDOW_H_

#include "Window.h"
#include "Map.h"
#include "Player.h"

class MazeWindow: public Window {
private:
	static constexpr int
		   WINDOW_WIDTH = 1080,
		   WINDOW_HEIGHT = 720;
	std::shared_ptr<Map> _map;
	Player _player;
public:
	MazeWindow();
	virtual ~MazeWindow() = default;

	virtual void render() override;
	virtual void handle_keys(const Uint8 *keys) override;
};

#endif /* MAZEWINDOW_H_ */
