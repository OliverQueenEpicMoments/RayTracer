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

bool Dielectric::Scatter(const Ray& ray, const RaycastHit& hit, color3& attenuation, Ray& scattered) const {
    // set color
    attenuation = m_albedo;

    glm::vec3 out_normal;
    float ni_over_nt;
    float cosine;

    // ray hits inside of surface
    if (glm::dot(ray.Direction, hit.Normal) > 0)
    {
        // flip hit normal (points inward)
        out_normal = -hit.Normal;
        ni_over_nt = m_index;
        cosine = m_index * glm::dot(ray.Direction, hit.Normal) / ray.Direction.length();
    }
    else
    {
        // ray hits outside of surface
        out_normal = hit.Normal;
        ni_over_nt = 1.0f / m_index;
        cosine = -glm::dot(ray.Direction, hit.Normal) / ray.Direction.length();
    }

    // get refraction vector
    glm::vec3 refracted;
    float reflectProbability = 1.0f;
    if (Refract(ray.Direction, out_normal, ni_over_nt, refracted))
    {
        reflectProbability = Schlick(cosine, m_index);
    }

    // get reflected vector
    glm::vec3 reflected = Reflect(glm::normalize(ray.Direction), hit.Normal);

    // get reflected or refracted ray
    scattered = (Random01() < reflectProbability) ? Ray{ hit.Point, reflected } : Ray{ hit.Point, refracted };

    return true;
}