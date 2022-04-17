#include "Texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <memory>

Texture::Texture(const char *filename) {
	auto tex_image = std::shared_ptr<SDL_Surface>(
			IMG_Load(filename),
			SDL_FreeSurface);

	if (tex_image == nullptr)
		throw std::runtime_error(
				std::string("Не могу открыть как файл текстуры: ") +
				std::string(SDL_GetError()));
	_width = tex_image->w;
	_height = tex_image->h;

	auto tex_image_2 = std::shared_ptr<SDL_Surface>(
			SDL_CreateRGBSurfaceWithFormat(
					0, _width, _height, 32, SDL_PIXELFORMAT_RGBA32),
			SDL_FreeSurface);
	SDL_UpperBlit(
			tex_image.get(), nullptr,
			tex_image_2.get(), nullptr);

	glGenTextures(1, &_tex_name);

	glBindTexture(GL_TEXTURE_2D, _tex_name);
	gluBuild2DMipmaps(
			GL_TEXTURE_2D,
			GL_RGBA,
			_width, _height,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			tex_image_2->pixels);
	/*
	 * GL_NEAREST - взять цвет ближайшей точки
	 * GL_LINEAR - линейная интерполяция
	 * GL_***_MIPMAP_*** - с использованием карт пиромидальной фильтрации
	 */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
Texture::~Texture() {

}
