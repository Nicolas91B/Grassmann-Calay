#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace glimac {

	class TrackballCamera{
		float m_fDistance;
		float m_fAngleX; 
		float m_fAngleY;

	public:
		TrackballCamera(){m_fDistance = 5; m_fAngleX = 0; m_fAngleY = 0;}
		void moveFront(float delta);
		void rotateLeft(float degrees);
		void rotateUp(float degrees);
		glm::mat4 getViewMatrix() const;
	};


}