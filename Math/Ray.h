#pragma once
#include "MathUtils.h"

struct RaycastHit {
	float Distance = 0;

	glm::vec3 Point{ 0 };
	glm::vec3 Normal{ 0 };

	class Material* material = nullptr;
};

struct Ray {
	Ray() = default;
	Ray(const glm::vec3& origin, const glm::vec3& direction) : Origin{ origin }, Direction{ direction } {}

	glm::vec3 GetPoint(float distance) const { return Origin + (Direction * distance); }

	glm::vec3 Origin{ 0 };
	glm::vec3 Direction{ 0 };
};