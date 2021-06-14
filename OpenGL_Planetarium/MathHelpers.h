#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"


// GLM provides a lot of the basic math as it is,
// so there hasn't been much buildup in this namespace for now at least. 
namespace MathHelpers {

	// Returns radian float of origo-centered angle to point (x, y)
	// Useful for sphere creation for example. 
	// Algorirhm taken from Frank Luna's Dx11 book.
	inline float PolarAngleFromXY(float x, float y) {

		float theta = 0.0f;

		// Quadrants I and IV
		if (x >= 0.0f) {

			theta = atanf(y / x);

			if (theta < 0.0f)
				theta += 2.0f * glm::pi<float>();

		}

		else
			theta = atanf(y / x) + glm::pi<float>();

		return theta;

	}

	// Loops angles around desired point. For example 361 goes back to 1
	inline void NormalizeRotationVec3(glm::vec3& rot, float min, float max) {

		if (rot.x > max)
			rot.x -= max;

		else if (rot.x < min)
			rot.x += max; 

		if (rot.y > max)
			rot.y -= max;

		else if (rot.y < min)
			rot.y += max;

		if (rot.z > max)
			rot.z -= max;

		else if (rot.z < min)
			rot.z += max;

	}

	inline void NormalizeRotationF(float& rot, float min, float max) {


		if (rot > max)
			rot -= max;

		else if (rot < min)
			rot += max;

	}

}