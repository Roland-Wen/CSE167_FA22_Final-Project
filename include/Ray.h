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

		float a = cam->aspect;
		float fovy = cam->fovy * M_PI/360.0f;
		float alpha = 2.0f*(i+0.5f)/width-1.0f;
		float beta = 1.0f-2.0f*(j+0.5f)/height;

		ans.dir = glm::normalize(alpha*a*glm::tan(fovy)*u+beta*glm::tan(fovy)*v-w);

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

		// no hit
		if(solution[0]<0.0f||solution[1]<0.0f||solution[2]<0.0f||solution[3]<0.0f) {
			ans.dist = INF+10.0f;
			return ans;
		}

		// build ans
		ans.dist = solution[3];
		ans.P = solution[0]*triangle.P[0]+solution[1]*triangle.P[1]+solution[2]*triangle.P[2];
		ans.N = glm::normalize(solution[0]*triangle.N[0]+solution[1]*triangle.N[1]+solution[2]*triangle.N[2]);
		ans.V = -1.0f * ray.dir;
		ans.triangle = triangle;
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
		for(Triangle& object:scene.triangle_soup) { // Find closest intersection; test all objects
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
	glm::vec3 FindColor(Intersection hit,int recursion_depth,
		std::vector<Light*> lights, RTScene scene) {																			   // grab the coefficients of the material
		glm::vec4 emision = hit.triangle.material->emision;
		float shininess = hit.triangle.material->shininess;
		glm::vec4 ambient = hit.triangle.material->ambient;
		glm::vec4 diffuse = hit.triangle.material->diffuse;
		glm::vec4 specular = hit.triangle.material->specular;

		glm::vec4 R = emision;
		for(int i=0;i<lights.size();i++){
			glm::vec4 delta = ambient;

			// l = direction to the light = light postion - hit position
			glm::vec4 hitPosition = glm::vec4(hit.P,1.0f);
			glm::vec3 l;
			for(int j = 0; j<3; j++)
				l[j] = lights[i]->position[j]*hitPosition.w-hitPosition[j]*lights[i]->position.w;
			l = glm::normalize(l);
			glm::vec3 hitNormal = hit.N;

			// shoot a light slightly above(?) the hitting point towards the light
			// if interesect with any triangle, delta = 0
			Ray shadowRay;
			shadowRay.p0 = hit.P + 0.01f*hit.N;
			shadowRay.dir = l;
			Intersection hit2 = Intersect(shadowRay,scene);
			if(hit2.dist<=INF-10.0f) continue;

			delta += diffuse*glm::max(glm::dot(hitNormal,l),0.0f);

			// shoot a mirror reflecting ray from the hit position
			// intersect that ray with the scene --> hit2
			// call findColor(hit2, depth+1)
			// mutiply the result by specular and add that to delta
			// when depth reaches maximum(6), use the model (what we have now)
			// TODO:


			// v is the direction to the viewer
			glm::vec3 v,h;
			v = glm::normalize(hit.V);
			h = glm::normalize(v+l);
			delta += specular*glm::pow(glm::max(glm::dot(hitNormal,h),0.0f),shininess);

			delta *= lights[i]->color;
			R += delta;
		}
		return glm::vec3(R[0],R[1],R[2]);
	}

	/**
	* main framework
	* page 9
	*/
	void Raytrace(Camera* cam,RTScene scene,Image& image) {
		int w = image.width; int h = image.height;
		std::cout<<"Soup size: "<<scene.triangle_soup.size()<<"\n";

		std::vector<Light*> lights;
		// get lights
		for(auto light:scene.light) lights.push_back(light.second);
		std::cout<<lights.size()<<"\n";

		// main loops
		for(int j=0; j<h; j++){
			for(int i=0; i<w; i++){
				//std::cout<<j*w+i<<"/"<<h*w<<"\n";
				Ray ray = RayThruPixel(cam,i,j,w,h);
				Intersection hit = Intersect(ray,scene);
				if(hit.dist>=INF-10.0f) image.pixels[j*w+i] = glm::vec3(0.1f,0.2f,0.3f);
				else image.pixels[j*w+i] = FindColor(hit,0,lights,scene);
			}
			//std::cout<<j<<"/"<<h<<"\n";
		}
	}
};