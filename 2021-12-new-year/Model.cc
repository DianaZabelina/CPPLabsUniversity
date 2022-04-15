#include "Model.h"

Model::Model(VerticesType vertices, FacesType faces,
		NormalsType normals, TexCoordsType tex_coords)
:_vertices(vertices),
 _faces(faces),
 _normals(normals),
 _texcoords(tex_coords) {
}

void Model::draw() {
	unsigned face_count = _faces.size();
	for (unsigned face = 0; face < face_count; face++) {
		unsigned vertex_count = _faces[face].size();
		switch (vertex_count) {
		case 3:
			glBegin(GL_TRIANGLES);
			break;
		case 4:
			glBegin(GL_QUADS);
			break;
		default:
			glBegin(GL_POLYGON);
			break;
		}

		glNormal3fv (&_normals[face][0]);
		for (unsigned vertex = 0; vertex < vertex_count; vertex++) {
			glTexCoord2fv (&_texcoords[face][vertex][0]);
			glVertex3fv (&_vertices[_faces[face][vertex]][0]);
		}
		glEnd();
	}
}
