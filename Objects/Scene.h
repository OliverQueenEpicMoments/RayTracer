#pragma once
#include <vector>
#include <memory>
#include "../Math/Color.h"

class Object;
struct Ray;
struct RaycastHit;

class Scene {
public:
    Scene() = default;
    Scene(color3& topcolor, color3& bottomcolor) : m_topcolor{ topcolor }, m_bottomcolor{ bottomcolor } {}

    color3 Trace(const Ray& ray, float min, float max, RaycastHit& hit, int depth);
    void AddObject(std::unique_ptr<Object> object);

private:
    color3 m_topcolor{ 0.5f, 0.7f, 1.0f };
    color3 m_bottomcolor{ 1 };
    std::vector <std::unique_ptr<Object>> m_objects;
};