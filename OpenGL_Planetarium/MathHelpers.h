#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

namespace MathHelpers {

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