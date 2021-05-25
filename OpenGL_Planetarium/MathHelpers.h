#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"


// GLM provides a lot of the basic math as it is,
// so there hasn't been much buildup in this namespace for now at least. 
namespace MathHelpers {

	// Returns radian float of origo-centered angle to point (x, y)
	// Useful for sphere creation for example. 
	// Algorirhm taken from Frank Luna's Dx11 book.
	float PolarAngleFromXY(float x, float y) {

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


}