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

inline float Dot(const glm::vec3& V1, const glm::vec3& V2) {
    return V1.x * V2.x + V1.y * V2.y + V1.z * V2.z;
}

inline glm::vec3 Reflect(const glm::vec3& V, const glm::vec3& N) {
    return V - (N * Dot(N, V)) * 2.0f;
}

inline bool Refract(const glm::vec3& v, const glm::vec3& n, float index, glm::vec3& refracted) {
    glm::vec3 NV = glm::normalize(v);
    float DT = dot(NV, n);
    float discriminant = 1 - (index * index) * (1 - DT * DT);
    if (discriminant > 0) {
        refracted = index * (NV - (n * DT)) - (n * std::sqrt(discriminant));
        return true;
    }

    return false;
}

// calculate specular reflection coefficient, or probability of reflection
inline float Schlick(float cosine, float index) {
    float R0 = (1.0f - index) / (1 + index);
    R0 = R0 * R0;
    return R0 + (1.0f - R0) * (float)std::pow((1.0f - cosine), 5);
}