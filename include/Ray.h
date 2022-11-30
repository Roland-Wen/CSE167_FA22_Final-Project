#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "Camera.h"
#include "RTScene.h"
#include "Image.h"
#include "Intersection.h"

#ifndef __RAY_H__
#define __RAY_H__
#endif

struct Ray {
	glm::vec3 p0; // basepoint
    glm::vec3 dir; // direction
};

namespace RayTracer{
	const float INF = 100000.0f;

	void printVec3(glm::vec3 in) {
		std::cout<<"("<<in[0]<<","<<in[1]<<","<<in[2]<<")\n";
	}

	/**
	* IN WORLD COORDINATE
	* generates a ray originated from the camera position,
	* through the center of the (i,j) pixel into the world
	* page 10,18
	*/
	Ray RayThruPixel(Camera* cam,int i,int j,int width,int height) {
		Ray ans;
		ans.p0 = cam->eye;

		glm::mat4 C = glm::inverse(cam -> view);
		glm::vec3 u(C[0][0],C[0][1],C[0][2]);
		glm::vec3 v(C[1][0],C[1][1],C[1][2]);
		v = -1.0f*v;
		glm::vec3 w(C[2][0],C[2][1],C[2][2]);

		
		if(i==0&&j==0){
			std::cout<<"w: "; printVec3(w);
			std::cout<<"u: "; printVec3(u);
			std::cout<<"v: "; printVec3(v);
		}

		float a = cam->aspect;
		float fovy = cam->fovy * M_PI/180.0f;
		float alpha = 2.0f*(i+0.5f)/width-1.0f;
		float beta = 1.0f-2.0f*(j+0.5f)/height;

		ans.dir = alpha*a*glm::tan(fovy/2.0f)*u+beta*glm::tan(fovy/2.0f)*v-w;
		ans.dir = glm::normalize(ans.dir);

		return ans;
	}

	/**
	* page 30,33
	* looks good
	*/
	Intersection IntersectTriangle(Ray ray,Triangle triangle) {
		Intersection ans;

		// solve the equation on page 36
		glm::mat4 matrix;
		matrix[0] = glm::vec4(triangle.P[0],1.0f);
		matrix[1] = glm::vec4(triangle.P[1],1.0f);
		matrix[2] = glm::vec4(triangle.P[2],1.0f);
		matrix[3] = glm::vec4(-1.0f * ray.dir,0.0f);
		glm::vec4 solution = glm::inverse(matrix)*glm::vec4(ray.p0,1.0f);
		float lambda[3] ={solution[0], solution[1], solution[2]};
		for(int i=0;i<3;i++) if(abs(lambda[i]-solution[i])>0.0001f) {
			std::cout<<"diff:"<<abs(lambda[i]-solution[i])<<"\n";
			assert(false);
		}
		float t = solution[3];

		// no hit
		if(lambda[0]<0.0f||lambda[1]<0.0f||lambda[2]<0.0f||t<0.0f) {
			ans.dist = INF+10.0f;
			return ans;
		}

		// build ans
		ans.dist = t;
		ans.P = lambda[0]*triangle.P[0]+lambda[1]*triangle.P[1]+lambda[2]*triangle.P[2];
		ans.N = glm::normalize(lambda[0]*triangle.N[0]+lambda[1]*triangle.N[1]+lambda[2]*triangle.N[2]);
		ans.V = -1.0f * ray.dir;
		ans.triangle = &triangle;
		return ans;
	}

	/**
	* searches over all all geometries in the scene and
	* returns the closest hit
	* page 11,28,31
	*/
	Intersection Intersect(Ray ray,RTScene scene) {
		float mindist = INF;
		Intersection hit;
		hit.dist = INF;
		for(Triangle object:scene.triangle_soup) { // Find closest intersection; test all objects
			Intersection hitTmp = IntersectTriangle(ray,object);
			if(hitTmp.dist<mindist) { // closer than previous hit
				mindist = hitTmp.dist;
				hit = hitTmp;
			}
		}
		return hit;
	}

	/**
	* shade the light color seen by the in-coming ray
	* page 15
	*/
	glm::vec3 FindColor(Intersection hit,int recursion_depth) { //page 15
		return glm::vec3(1.0f,1.0f,1.0f);
	}

	/**
	* main framework
	* page 9
	*/
	void Raytrace(Camera* cam,RTScene scene,Image& image) {
		int w = image.width; int h = image.height;
		int hitCnt = 0;
		std::cout<<"Soup size: "<<scene.triangle_soup.size()<<"\n";
		/*for(Triangle tri:scene.triangle_soup) {
			printVec3(tri.P[0]);
			printVec3(tri.P[1]);
			printVec3(tri.P[2]);
			std::cout<<"----------------------------------\n";
		}*/
		for(int j=0; j<h; j++){
			for(int i=0; i<w; i++){
				//std::cout<<j*w+i<<"/"<<h*w<<"\n";
				Ray ray = RayThruPixel(cam,i,j,w,h);
				Intersection hit = Intersect(ray,scene);
				if(hit.dist>=INF-10.0f) image.pixels[j*w+i] = glm::vec3(0.0f,0.0f,0.0f);
				else {
					image.pixels[j*w+i] = FindColor(hit,0);
					hitCnt++;
				}
			}
		}
		std::cout<<"hitCnt: "<<hitCnt<<"\n";
	}
};