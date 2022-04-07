#include "MazeWindow.h"

MazeWindow::MazeWindow()
: Window(WINDOW_WIDTH, WINDOW_HEIGHT) {
	SDL_SetWindowTitle(_window.get(), "Maze Window");
	_map = std::make_shared<Map>("map.txt");
	_player.spawn(_map);
}

void MazeWindow::render() {
	for (int row = 0; row < _map->height(); row++) {
		for (int col = 0; col < _map->width(); col++) {
			if (_map->is_wall(col, row))
				SDL_SetRenderDrawColor(_renderer.get(), 255, 255, 255, 255);
			else
				SDL_SetRenderDrawColor(_renderer.get(), 100, 100, 100, 255);

			SDL_Rect cell_rect { col * 20, row * 20, 20, 20 };
			SDL_RenderFillRect(_renderer.get(), &cell_rect);
		}
	}
	//взгляд
	SDL_Point player_line[2];
	player_line[0].x = int(_player.x() * 20);
	player_line[0].y = int(_player.y() * 20);
	player_line[1].x = player_line[0].x + int(30 * cos(_player.dir()));
	player_line[1].y = player_line[0].y + int(30 * sin(_player.dir()));
	SDL_SetRenderDrawColor(_renderer.get(), 200, 200, 96, 255);
	SDL_RenderDrawLines(_renderer.get(), player_line, 2);

	//игрок
	SDL_Rect player_rect {
		int(_player.x() * 20 - 5),
		int(_player.y() * 20 - 5),
		11, 11 };
	SDL_SetRenderDrawColor(_renderer.get(), 255, 127, 127, 255);
	SDL_RenderFillRect(_renderer.get(), &player_rect);
}

void MazeWindow::handle_keys(const Uint8 *keys) {
	if (keys[SDL_SCANCODE_W])
		_player.walk_forward();
	if (keys[SDL_SCANCODE_S])
		_player.walk_backward();
	if (keys[SDL_SCANCODE_D])
		_player.shift_right();
	if (keys[SDL_SCANCODE_A])
		_player.shift_left();
	if (keys[SDL_SCANCODE_E])
		_player.turn_right();
	if (keys[SDL_SCANCODE_Q])
		_player.turn_left();
}
