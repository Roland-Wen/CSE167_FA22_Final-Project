/**************************************************

*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_normalized_axis.hpp>
#include <math.h>

#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
#include <stack>

#include "Camera.h"
#include "SurfaceShader.h"
#include "Light.h"
#include "Geometry.h"
#include "Material.h"
#include "Model.h"

#ifndef __IMAGE_H__
#define __IMAGE_H__

class Image {
public:
    unsigned int fbo; // framebuffer object
    unsigned int tbo; // texture buffer object
    int width;
    int height;
    std::vector<glm::vec3> pixels;
    
    Image(int w, int h){
        width = w;
        height = h;
    }
    
    void init(void) {
        pixels.resize(width*height);
        glGenFramebuffers(1,&fbo);
        glGenTextures(1,&tbo);
    }

    void draw(void) {
        glBindTexture(GL_TEXTURE_2D,tbo);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_FLOAT,&pixels[0][0]);
        glBindFramebuffer(GL_READ_FRAMEBUFFER,fbo);
        glFramebufferTexture2D(GL_READ_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,tbo,0);// attach texture and the read frame
        // glBindFramebuffer(GL_WRITE_FRAMEBUFFER,0); // if not already so
        glBlitFramebuffer(0,0,width,height,0,0,width,height,GL_COLOR_BUFFER_BIT,GL_NEAREST); // copy framebuffer from read to write
    }

    void putSomeColor() {
        for(int i=0;i<height;i++) for(int j=0;j<width;j++)
            pixels[i*width+j]=glm::vec3(j*1.0f/width,j*1.0f/width,j*1.0f/width);
    }
};

#endif 
