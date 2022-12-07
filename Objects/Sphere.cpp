#include "Sphere.h"

bool Sphere::Hit(const Ray& ray, float min, float max, RaycastHit& hit) {
    glm::vec3 OC = ray.Origin - m_center;
    float A = glm::dot(ray.Direction, ray.Direction);
    float B = 2 * glm::dot(ray.Direction, OC);
    float C = glm::dot(OC, OC) - (m_radius * m_radius);

    // B^2 - 4AC
    float Discriminant = (B * B) - (4 * A * C);

    // 0 = 1 Hit
    // 1 = 2 Hit
    if (Discriminant >= 0) {
        float T = (-B - sqrt(Discriminant)) / (2 * A);
        if (T > min && T < max) {
            hit.Distance = T;
            hit.Point = ray.GetPoint(T);
            hit.Normal = (hit.Point - m_center) / m_radius;

            hit.material = m_material.get();
            return true;
        }

        T = (-B + sqrt(Discriminant)) / (2 * A);
        if (T > min && T < max) {
            hit.Distance = T;
            hit.Point = ray.GetPoint(T);
            hit.Normal = (hit.Point - m_center) / m_radius;

            hit.material = m_material.get();
            return true;
        }
    }
    return false;
}