#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#ifndef __RAY_H__
#define __RAY_H__
struct RAY {
	glm::vec3 p0; // basepoint
    glm::vec3 dir; // direction
};
#endif