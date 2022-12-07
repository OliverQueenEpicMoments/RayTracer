#include "Scene.h"
#include "Object.h"

color3 Scene::Trace(const Ray& ray, float min, float max, RaycastHit& hit, int depth) {
    bool RayHit = false;
    float Closest = max;

    // Get closest ray hit
    for (auto& object : m_objects) {
        if (object->Hit(ray, min, Closest, hit)) {
            RayHit = true;
            Closest = hit.Distance;
        }
    }

    // If ray hit object, scatter (bounce) ray and check for next hit
    if (RayHit) {
        Ray Scattered;
        color3 Attenuation;

        // limit the number of bounces to depth, get color attenuation
        // final color is product of object colors (object->material * object->material * ...)
        if (depth > 0 && hit.material->Scatter(ray, hit, Attenuation, Scattered)) {
            return Attenuation * Trace(Scattered, min, max, hit, depth - 1);
        } else {
            return { 0, 0, 0 };
        }
    } else {
        glm::vec3 Direction = glm::normalize(ray.Direction);
        float T = (Direction.y + 1) * 0.5f;
        return Lerp(glm::vec3(0.5f, 0.7f, 1.0f), glm::vec3(1, 1, 1), T);
    }
}

void Scene::AddObject(std::unique_ptr<Object> object) {
	m_objects.push_back(std::move(object));
}