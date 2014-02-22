#pragma once
#include <iostream>
#include <GL/glew.h>
#include <vector>



namespace glimac {

	struct Vertex2DRGB {
		GLfloat x, y;
		GLfloat r, g, b;

		Vertex2DRGB(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b):
			x(x), y(y), r(r), g(g), b(b) {
		}
	};

	std::vector < GLfloat > computeDiscVertices(unsigned int discretization);

	inline const GLvoid* bufferOffset(int offset) {
		return reinterpret_cast<const GLvoid*>(offset);
	}

}
