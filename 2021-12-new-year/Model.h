#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include <memory>
#include <GL/gl.h>
#include <glm/glm/glm.hpp>

/*
 * - Координаты каждой вершины модели
 * - Описание граней (по индексам вершин)
 * - Вектора нормалей к каждой грани
 * - Текстурные координаты для каждой грани
 */

class Model {
public:
	using VerticesType = std::vector<glm::vec3>;
	using FacesType = std::vector<std::vector<unsigned>>;
	using NormalsType = std::vector<glm::vec3>;
	using TexCoordsType = std::vector<std::vector<glm::vec2>>;

protected:
	VerticesType _vertices;
	FacesType _faces;
	NormalsType _normals;
	TexCoordsType _texcoords;

public:
	Model(	VerticesType vertices,
			FacesType faces,
			NormalsType normals,
			TexCoordsType tex_coords);
	virtual ~Model() = default;

	void draw();
};

#endif /* MODEL_H_ */
