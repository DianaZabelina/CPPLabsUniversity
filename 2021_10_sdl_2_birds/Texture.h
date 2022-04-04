#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <memory>
#include <SDL2/SDL.h>

class Texture
{
protected:
	std::shared_ptr<SDL_Renderer> _renderer;
	std::shared_ptr<SDL_Texture> _texture ;
	int _width {}, _height {};

	SDL_Renderer* ren() { return _renderer.get(); }
	SDL_Texture* tex() { return _texture.get(); }

public:
	Texture(std::shared_ptr<SDL_Renderer> &render,
			const char *filename);
	virtual ~Texture() = default;

	virtual void draw(int x, int y);
	virtual void draw(int x, int y, int w, int h);
	virtual void draw(double x, double y, double angle);
	virtual void draw(const SDL_FRect &r);

	int height() const { return _height; }
	int width() const { return _width; }
};

#endif /* TEXTURE_H_ */
