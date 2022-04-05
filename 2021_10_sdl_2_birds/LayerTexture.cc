#include "LayerTexture.h"
#include <algorithm>

LayerTexture::LayerTexture(std::shared_ptr<SDL_Renderer> &renderer,
		const char *filename, double spd)
		: Texture(renderer, filename), _speed(spd)
{

}

void LayerTexture::draw(int x, int y, int w, int h)
{
	int lx = 0;
	int tx = int(_offset);
	int tw = std::min(width() - tx, w - lx);

	do {
		SDL_Rect src_rect { tx, 0, tw, h };
		SDL_Rect dst_rect { x, y, tw, h };
		SDL_RenderCopy(ren(), tex(), &src_rect, &dst_rect);

		lx += tw;
		tx = 0;
		x += tw;
		tw = std::min(width(), w - lx);
	} while (lx < w);
}

void LayerTexture::update()
{
	_offset += _speed;
	while (_offset >= width())
		_offset -= width();
}

