#pragma once

#include <GL/glew.h>

namespace glimac {

	class VAO {
		private:
			GLuint m_nGLId;

			VAO(const VAO& vbo); // Constructeur par copie
			VAO& operator =(const VAO& vbo); // Opérateur de recopie


		public:
			GLuint getGLId() const{
				return m_nGLId;
			}
			VAO(){
				glGenVertexArrays(1, &m_nGLId);
			}
			~VAO() {
				glDeleteVertexArrays(1, &m_nGLId);
			}
			void bind() const{
				glBindVertexArray(m_nGLId);
			}

			VAO(VAO&& rvalue): m_nGLId(rvalue.m_nGLId) {
				rvalue.m_nGLId = 0;
			}

			VAO& operator =(VAO&& rvalue) {
				m_nGLId = rvalue.m_nGLId;
				rvalue.m_nGLId = 0;
			}

	};

}