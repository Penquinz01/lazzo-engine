#include "lzpch.h"
#include "Camera.h"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Lazzo::Object::Camera {

	Camera::Camera(const glm::vec3& position, const glm::vec3& rotation)
		: m_Position(position), m_Rotation(rotation)
	{
	}

	void Camera::SetPosition(float x, float y, float z) { m_Position = glm::vec3(x, y, z); }
	void Camera::SetPosition(const glm::vec3& pos) { m_Position = pos; }
	glm::vec3 Camera::GetPosition() const { return m_Position; }
	void Camera::SetRotation(float pitch, float yaw, float roll) { m_Rotation = glm::vec3(pitch, yaw, roll); }
	void Camera::SetRotation(const glm::vec3& rot) { m_Rotation = rot; }
	glm::vec3 Camera::GetRotation() const { return m_Rotation; }

	void Camera::SetProjectionMode(ProjectionMode mode) { m_ProjectionMode = mode; }
	ProjectionMode Camera::GetProjectionMode() const { return m_ProjectionMode; }
	void Camera::SetFOV(float fov) { m_FOV = fov; }
	float Camera::GetFOV() const { return m_FOV; }
	void Camera::SetOrthographicSize(float size) { m_OrthographicSize = size; }
	float Camera::GetOrthographicSize() const { return m_OrthographicSize; }
	void Camera::SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }
	float Camera::GetAspectRatio() const { return m_AspectRatio; }
	void Camera::SetNearPlane(float nearPlane) { m_NearPlane = nearPlane; }
	float Camera::GetNearPlane() const { return m_NearPlane; }
	void Camera::SetFarPlane(float farPlane) { m_FarPlane = farPlane; }
	float Camera::GetFarPlane() const { return m_FarPlane; }

	glm::mat4 Camera::GetViewMatrix() const
	{
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::rotate(view, glm::radians(-m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		view = glm::rotate(view, glm::radians(-m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::rotate(view, glm::radians(-m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::translate(view, -m_Position);
		return view;
	}

	glm::mat4 Camera::GetProjectionMatrix() const
	{
		if (m_ProjectionMode == ProjectionMode::Orthographic)
		{
			// RH ortho matches the RH view matrix so the two modes share the same view.
			float halfHeight = m_OrthographicSize;
			float halfWidth = halfHeight * m_AspectRatio;
			return glm::orthoRH_ZO(-halfWidth, halfWidth, -halfHeight, halfHeight, m_NearPlane, m_FarPlane);
		}
		return glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_FarPlane);
	}

	glm::vec3 Camera::GetFront() const
	{
		glm::mat4 rot = glm::mat4(1.0f);
		rot = glm::rotate(rot, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		rot = glm::rotate(rot, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		rot = glm::rotate(rot, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		return glm::normalize(glm::vec3(rot * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
	}

	void Camera::DrawUI()
	{
		ImGui::Begin("Camera");
		ImGui::DragFloat3("Position", glm::value_ptr(m_Position), 0.01f);
		ImGui::DragFloat3("Rotation", glm::value_ptr(m_Rotation), 0.1f);
		ImGui::Combo("Projection", reinterpret_cast<int*>(&m_ProjectionMode), "Perspective\0Orthographic\0");
		if (m_ProjectionMode == ProjectionMode::Perspective)
			ImGui::SliderFloat("FOV", &m_FOV, 10.0f, 120.0f);
		else
			ImGui::DragFloat("Orthographic Size", &m_OrthographicSize, 0.01f, 0.1f, 100.0f);
		ImGui::DragFloat("Aspect Ratio", &m_AspectRatio, 0.01f, 0.1f, 10.0f);
		ImGui::DragFloat("Near", &m_NearPlane, 0.001f, 0.001f, 10.0f);
		ImGui::DragFloat("Far", &m_FarPlane, 0.1f, 1.0f, 1000.0f);
		ImGui::End();
	}
}