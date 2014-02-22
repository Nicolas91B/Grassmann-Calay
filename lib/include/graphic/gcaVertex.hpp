#pragma once

#include <grassmannCalay.hpp>

#include <vector>

#include "graphic/common.hpp"

namespace glimac{
	class gcaVertex{

		void getPoint(const gca::K_blade& blade, const glm::vec3& color);
	    void getDroite(const gca::K_blade& blade, const glm::vec3& color);
	    void getPlan(const gca::K_blade& blade, const glm::vec3& color);
		// Alloue et construit les données (implantation dans le .cpp)
	public:
	    // Constructeur: alloue le tableau de données et construit les attributs des vertex
	    gcaVertex():
	        m_nVertexCount(0) {}


	    void getBlade(const gca::K_blade& blade, const glm::vec3& color);
	    // Renvoit le pointeur vers les données
	    const glimac::ShapeVertex* getDataPointer() const {
	        return &m_Vertices[0];
	    }
	    
	    // Renvoit le nombre de vertex
	    GLsizei getVertexCount() const {
	        return m_nVertexCount;
	    }
	private:
	    std::vector<glimac::ShapeVertex> m_Vertices;
	    GLsizei m_nVertexCount; // Nombre de sommets
	};
}