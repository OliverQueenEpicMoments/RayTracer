#include "Plane.h"

bool Plane::Hit(const Ray& ray, float min, float max, RaycastHit& hit) {
    // If dot product (direction and plane normal) is 0 direction is parallel
    float Denominator = Dot(ray.Direction, m_normal);
    if (abs(Denominator) < std::numeric_limits<float>::epsilon()) {
        return false; // Direction and plane parallel, no intersection 
    }

    float T = glm::dot(m_center - ray.Origin, m_normal) / Denominator;
    if (T < 0) {
        return false; // Plane behind ray's origin
    }

    // Check if t (distance is within range)
    if (T > min && T < max) {
        hit.Distance = T;
        hit.Point = ray.GetPoint(T);
        hit.Normal = m_normal;
        hit.material = m_material.get();
        return true;
    }

    return false;
}