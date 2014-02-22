#pragma once

#include <GL/glew.h>

namespace glimac {

	class VBO {
		private:
			GLuint m_nGLId;

			VBO(const VBO& vbo); // Constructeur par copie
			VBO& operator =(const VBO& vbo); // Opérateur de recopie


		public:
			GLuint getGLId() const{
				return m_nGLId;
			}
			VBO(){
				glGenBuffers(1, &m_nGLId);
			}
			~VBO() {
				glDeleteBuffers(1, &m_nGLId);
			}
			void bind(GLenum target = GL_ARRAY_BUFFER) const{
				glBindBuffer(target, m_nGLId);
			}

			VBO(VBO&& rvalue): m_nGLId(rvalue.m_nGLId) {
				rvalue.m_nGLId = 0;
			}

			VBO& operator =(VBO&& rvalue) {
				m_nGLId = rvalue.m_nGLId;
				rvalue.m_nGLId = 0;
			}

	};

}