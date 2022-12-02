/**************************************************
RTPlane is subclass class of RTGeometry
that represents a 2D plane
*****************************************************/
#include "RTGeometry.h"
#ifndef __RTPLANE_H__
#define __RTPLANE_H__

class RTPlane: public RTGeometry {
    public:

    void init(void){
        // vertex positions
        const float positions[4][3] ={
            { -0.5f, -0.5f, 0.0f },{ -0.5f, 0.5f, 0.0f },{ 0.5f, 0.5f, 0.0f },{ 0.5f, -0.5f, 0.0f },
        };
        // vertex normals
        const float normals[4][3] ={
            { 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f },
        };
        // Cube indices
        const int indices[6] ={
            0, 1, 2, 0, 2, 3, // Front face
        };
        for(int i=0;i<6;i+=3){
            Triangle curr;

            curr.P.push_back(glm::vec3(positions[indices[i]][0],positions[indices[i]][1],positions[indices[i]][2]));
            curr.P.push_back(glm::vec3(positions[indices[i+1]][0],positions[indices[i+1]][1],positions[indices[i+1]][2]));
            curr.P.push_back(glm::vec3(positions[indices[i+2]][0],positions[indices[i+2]][1],positions[indices[i+2]][2]));

            curr.N.push_back(glm::vec3(normals[indices[i]][0],normals[indices[i]][1],normals[indices[i]][2]));
            curr.N.push_back(glm::vec3(normals[indices[i+1]][0],normals[indices[i+1]][1],normals[indices[i+1]][2]));
            curr.N.push_back(glm::vec3(normals[indices[i+2]][0],normals[indices[i+2]][1],normals[indices[i+2]][2]));

            elements.push_back(curr);
        }
        count = elements.size();
    }
};

#endif 
