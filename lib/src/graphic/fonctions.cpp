#include <cmath>
#include "graphic/fonctions.hpp"
#include <iostream>

namespace glimac {

	std::vector<GLfloat> computeDiscVertices(unsigned int discretization){

		std::vector<GLfloat> vect;
		vect.push_back(0);
		vect.push_back(0);
		vect.push_back(1);
		vect.push_back(1);
		vect.push_back(1);
		for(int i = 0; i < discretization+2; ++i){
			vect.push_back(0.5*cos(((float)i/discretization)*2.*M_PI));
			vect.push_back(0.5*sin(((float)i/discretization)*2.*M_PI));
			vect.push_back((float)i/discretization);
			vect.push_back((float)i/(2*discretization));
			vect.push_back(0.6);
		}
		return vect;
	}

}
