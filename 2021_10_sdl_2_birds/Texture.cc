#include "Texture.h"
#include <SDL2/SDL_image.h>

Texture::Texture(	std::shared_ptr<SDL_Renderer> &renderer,
					const char *filename)
: _renderer(renderer)
{
	_texture = std::shared_ptr<SDL_Texture>(
			IMG_LoadTexture(ren(), filename),
			SDL_DestroyTexture);
	SDL_QueryTexture(tex(), nullptr, nullptr, &_width, &_height);

}

void Texture::draw(int x, int y)
{
	SDL_Rect target { x, y, width(), height() };
	SDL_RenderCopy(ren(), tex(), nullptr, &target);
}

void Texture::draw(int x, int y, int w, int h)
{
	SDL_Rect target { x, y, w, h };
	SDL_RenderCopy(ren(), tex(), nullptr, &target);
}

void Texture::draw(double x, double y, double angle)
{
	SDL_FRect target { float(x), float(y), float(width()), float(height()) };
	SDL_FPoint center { target.w / 2, target.h / 2 };
	SDL_RenderCopyExF(ren(), tex(), nullptr, &target,
			angle, &center, SDL_FLIP_NONE);
}

void Texture::draw(const SDL_FRect &r)
{
	SDL_RenderCopyF(ren(), tex(), nullptr, &r);
}
