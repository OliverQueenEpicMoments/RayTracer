#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <cstdlib>
#include <algorithm>

inline float Random01() {
	return rand() / (float)RAND_MAX;
}

inline float Random(float min, float max) {
	if (min > max) std::swap(min, max);

	return min + (max - min) * Random01();
}

template <typename T>
inline T Lerp(T A, T B, float t) {
	return (A * (1.0f - t)) + (B * t);
}

inline glm::vec3 RandomInUnitSphere() {
    glm::vec3 Point;

    do {
        Point = glm::vec3{ Random(-1, 1), Random(-1, 1), Random(-1, 1) };
    } while (glm::length2(Point) >= 1);

    return Point;
}