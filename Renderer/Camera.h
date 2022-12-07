#pragma once
#include "../Math/MathUtils.h"
#include "../Math/Ray.h"

class Camera {
public:
	Camera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, float fov, float aspectratio);

	void LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up);

	Ray PointToRay(const glm::vec2& point) const;

private:
	void CalculateViewPlane();

private:
	// Eye position
	glm::vec3 m_eye{ 0, 0, 0 };

	// Camera axis
	glm::vec3 m_right{ 0, 0, 0 };
	glm::vec3 m_up{ 0, 0, 0 };
	glm::vec3 m_forward{ 0, 0, 0 };

	// View plane origin and horizontal and vertical axis
	glm::vec3 m_lowerleft{ 0, 0, 0 };
	glm::vec3 m_horizontal{ 0, 0, 0 };
	glm::vec3 m_vertical{ 0, 0, 0 };

	float m_fov{ 0 }; // Field of view (Angle in degrees of view)
	float m_aspectratio{ 0 }; // Screen width / screen height (800 / 600 = 1.333)
};