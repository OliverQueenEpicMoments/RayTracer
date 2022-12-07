#include "Camera.h"

Camera::Camera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, float fov, float aspectratio) : m_fov{ fov }, m_aspectratio{ aspectratio } {
	LookAt(eye, target, up);
}

void Camera::LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) {
	m_eye = eye;

	// Set the camera axis vectors (forward, right, up)
	// Forward is the vector (target -> eye).
	m_forward = glm::normalize(eye - target);

	// Right is the cross product of the up and forward vector
	// Up * forward = vector perpendicular which is the right vector
	m_right = glm::normalize(glm::cross(up, m_forward));

	// Up is the cross product of the forward and right vector
	m_up = glm::cross(m_forward, m_right);

	CalculateViewPlane();
}

Ray Camera::PointToRay(const glm::vec2& point) const {
	Ray ray;
	ray.Origin = m_eye;

	// Calculate direction from point * view plane 
	ray.Direction = m_lowerleft + (point.x * m_horizontal) + (point.y * m_vertical) - m_eye;

	return ray;
}

void Camera::CalculateViewPlane() {
	// Convert fov angle to radians
	float Theta = glm::radians(m_fov);

	// Calculate the width / height of the view plane
	float HalfHeight = tan(Theta * 0.5f);
	float HalfWidth = HalfHeight * m_aspectratio;
	float Height = HalfHeight * 2;
	float Width = HalfWidth * 2;

	// Calculate horizontal view plane vector (width * right vector)
	m_horizontal = Width * m_right;

	// Calculate vertical view plane vector (height * up vector)
	m_vertical = Height * m_up;

	// Calculate lower left location of the view plane
	m_lowerleft = m_eye - (m_horizontal * 0.5f) - (m_vertical * 0.5f) - m_forward;
}