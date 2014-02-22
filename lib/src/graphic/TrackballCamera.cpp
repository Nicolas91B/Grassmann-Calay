#include "graphic/TrackballCamera.hpp"

namespace glimac{

	void TrackballCamera::moveFront(float delta){
		m_fDistance += delta;
	}

	void TrackballCamera::rotateLeft(float degrees){
		m_fAngleX += degrees;
	}

	void TrackballCamera::rotateUp(float degrees){
		m_fAngleY += degrees;
	}

	glm::mat4 TrackballCamera::getViewMatrix() const{
		glm::mat4 ViewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -m_fDistance));
		ViewMatrix = glm::rotate(ViewMatrix, m_fAngleY, glm::vec3(0, 1, 0));
		ViewMatrix = glm::rotate(ViewMatrix, m_fAngleX, glm::vec3(1, 0, 0));

		return ViewMatrix;
	}
}