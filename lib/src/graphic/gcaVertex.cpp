#include <cmath>
#include <iostream>
#include <graphic/gcaVertex.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace glimac {
    void gcaVertex::getBlade(const gca::K_blade& blade, const glm::vec3& color){
        switch(blade.base[0]){
            case 8:
                getPoint(blade, color);
            break;
            case 12:
                getDroite(blade, color);
            break;
            case 14 :
                getPlan(blade, color);
            break;
            default:break;
        }
    }

    void gcaVertex::getPoint(const gca::K_blade& blade, const glm::vec3& color){

        m_nVertexCount += 4;

        glimac::ShapeVertex vertex;

        vertex.position = glm::vec3((blade[0] / blade[3]) +0.1, (blade[1] / blade[3]) +0.1, (blade[2] / blade[3]));
        vertex.normal = color;
        m_Vertices.push_back(vertex);

        vertex.position = glm::vec3((blade[0] / blade[3]) -0.1, (blade[1] / blade[3]) -0.1, (blade[2] / blade[3]));
        vertex.normal = color;
        m_Vertices.push_back(vertex);

        vertex.position = glm::vec3((blade[0] / blade[3]) +0.1, (blade[1] / blade[3]) -0.1, (blade[2] / blade[3]));
        vertex.normal = color;
        m_Vertices.push_back(vertex);

        vertex.position = glm::vec3((blade[0] / blade[3]) -0.1, (blade[1] / blade[3]) +0.1, (blade[2] / blade[3]));
        vertex.normal = color;
        m_Vertices.push_back(vertex);


    }

    void gcaVertex::getDroite(const gca::K_blade& blade, const glm::vec3& color){

        m_nVertexCount += 2;

        glm::vec3 V = glm::vec3(-blade[3], blade[1], -blade[0]);
        glm::vec3 U = glm::vec3(blade[2], blade[4], blade[5]);

        float normeU =  pow(U.x, 2) + pow(U.y, 2) + pow(U.z, 2);
        glm::vec3 origine = glm::cross(U , V);
        origine =  glm::vec3(origine.x/normeU, origine.y/normeU, origine.z/normeU);
        U *= 1000;

        glimac::ShapeVertex vertex;

        vertex.position = origine;
        vertex.position += U;
        vertex.normal = color;
        m_Vertices.push_back(vertex);

        vertex.position = origine;
        vertex.position -= U;
        vertex.normal = color;
        m_Vertices.push_back(vertex);
    }

    void gcaVertex::getPlan(const gca::K_blade& blade, const glm::vec3& color){

        m_nVertexCount += 40;

        glm::vec3 normal = glm::normalize(glm::vec3(blade[3], -blade[2], blade[1]));
        float factor = blade[0] / sqrt(pow(blade[3], 2) + pow(-blade[2], 2) + pow(blade[1], 2));
        normal = glm::vec3(normal.x*factor, normal.y*factor, normal.z*factor);
        glm::vec3 direction1 = glm::normalize(glm::cross(glm::vec3(normal.x, normal.y, normal.z+10), normal));
        glm::vec3 direction2 = glm::rotate(direction1, (float)90, normal);

        direction2 = glm::vec3(direction2.x*5, direction2.y*5, direction2.z*5);

        glimac::ShapeVertex vertex;

        for (int i = -5; i < 5; ++i)
        {
            glm::vec3 tmp = glm::vec3(direction1.x * i, direction1.y*i, direction1.z*i);
            vertex.position = normal;
            vertex.position += tmp;
            vertex.position += direction2;
            vertex.normal = color;
            m_Vertices.push_back(vertex);

            vertex.position = normal;
            vertex.position += tmp;
            vertex.position -= direction2;
            vertex.normal = color;
            m_Vertices.push_back(vertex);
        }
        
        direction2 = glm::vec3(direction2.x/5, direction2.y/5, direction2.z/5);
        direction1 = glm::vec3(direction1.x*5, direction1.y*5, direction1.z*5);

        for (int i = -5; i < 5; ++i)
        {
            glm::vec3 tmp = glm::vec3(direction2.x * i, direction2.y*i, direction2.z*i);
            vertex.position = normal;
            vertex.position += tmp;
            vertex.position += direction1;
            vertex.normal = color;
            m_Vertices.push_back(vertex);

            vertex.position = normal;
            vertex.position += tmp;
            vertex.position -= direction1;
            vertex.normal = color;
            m_Vertices.push_back(vertex);
        }
    }
}