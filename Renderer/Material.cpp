#include "Material.h"

bool Lambertian::Scatter(const Ray& ray, const RaycastHit& hit, color3& attenuation, Ray& scattered) const {
    glm::vec3 Target = hit.Point + hit.Normal + RandomInUnitSphere();
    glm::vec3 Direction = glm::normalize(Target - hit.Point);

    scattered = { hit.Point, Direction };
    attenuation = m_albedo;

    return true;
}

bool Metal::Scatter(const Ray& ray, const RaycastHit& hit, color3& attenuation, Ray& scattered) const {
    glm::vec3 Reflected = Reflect(glm::normalize(ray.Direction), hit.Normal);

    scattered = { hit.Point, Reflected + RandomInUnitSphere() * m_fuzz };
    attenuation = m_albedo;

    return Dot(hit.Normal, scattered.Direction) >= 0;
}