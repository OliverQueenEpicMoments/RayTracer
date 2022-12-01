#pragma once
#include <glm/glm.hpp>
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
inline T Interp(T A, T B, float t) {
	return (A * (1.0f - t)) + (B * t);
}