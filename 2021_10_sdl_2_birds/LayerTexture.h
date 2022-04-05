#ifndef LAYERTEXTURE_H_
#define LAYERTEXTURE_H_

#include "Texture.h"

class LayerTexture: public Texture
{
protected:
	double _speed { }; //пиксель/тик
	double _offset { }; //пиксель

public:
	LayerTexture(std::shared_ptr<SDL_Renderer> &renderer, const char *filename, double spd);
	virtual ~LayerTexture() = default;

	virtual void draw(int x, int y, int w, int h) override;

	virtual void update();
};

#endif /* LAYERTEXTURE_H_ */
