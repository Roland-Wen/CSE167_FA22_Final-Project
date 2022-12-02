/**************************************************
Plane is subclass class of Geometry
that represents a 2D plane
*****************************************************/
#include "Geometry.h"
#ifndef __PLANE_H__
#define __PLANE_H__

class Plane: public Geometry {
    public:

    void init(void){
        // vertex positions
        const GLfloat positions[4][3] ={
            { -0.5f, -0.5f, 0.0f },{ -0.5f, 0.5f, 0.0f },{ 0.5f, 0.5f, 0.0f },{ 0.5f, -0.5f, 0.0f },
        };
        // vertex normals
        const GLfloat normals[4][3] ={
            { 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f },
        };
        // Cube indices
        const GLuint indices[6] ={
            0, 1, 2, 0, 2, 3, // Front face
        };
        glGenVertexArrays(1,&vao);
        buffers.resize(3); // recall that buffers is std::vector<GLuint>
        glGenBuffers(3,buffers.data());
        glBindVertexArray(vao);

        // 0th attribute: position
        glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
        glBufferData(GL_ARRAY_BUFFER,sizeof(positions),positions,GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

        // 1st attribute: normal
        glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
        glBufferData(GL_ARRAY_BUFFER,sizeof(normals),normals,GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);

        // indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

        count = sizeof(indices)/sizeof(indices[0]);
        glBindVertexArray(0);
    }


};

#endif 
