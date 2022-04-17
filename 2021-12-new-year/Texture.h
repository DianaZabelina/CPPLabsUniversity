#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/gl.h>
#include <Gl/glu.h>

class Texture {
protected:
	GLuint _tex_name;
	int _width;
	int _height;

public:
	Texture(const char *filename);
	virtual ~Texture();

	void bind() { glBindTexture(GL_TEXTURE_2D, _tex_name); }

	static void enable() { glEnable(GL_TEXTURE_2D); }
	static void disable() { glDisable(GL_TEXTURE_2D); }

	int height() const { return _height; }
	int width() const { return _width; }
};

#endif /* TEXTURE_H_ */
