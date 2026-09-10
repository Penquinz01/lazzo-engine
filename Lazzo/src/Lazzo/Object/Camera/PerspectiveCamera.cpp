#include "lzpch.h"
#include "PerspectiveCamera.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Lazzo::Object::Camera {

	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane,
		const glm::vec3& position, const glm::vec3& rotation)
		: m_FOV(fov), m_AspectRatio(aspectRatio), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
		m_Position = position;
		m_Rotation = rotation;
	}

	void PerspectiveCamera::SetPosition(float x, float y, float z) { m_Position = glm::vec3(x, y, z); }
	void PerspectiveCamera::SetPosition(const glm::vec3& pos) { m_Position = pos; }
	glm::vec3 PerspectiveCamera::GetPosition() const { return m_Position; }

	void PerspectiveCamera::SetRotation(float pitch, float yaw, float roll) { m_Rotation = glm::vec3(pitch, yaw, roll); }
	void PerspectiveCamera::SetRotation(const glm::vec3& rot) { m_Rotation = rot; }
	glm::vec3 PerspectiveCamera::GetRotation() const { return m_Rotation; }

	void PerspectiveCamera::SetFOV(float fov) { m_FOV = fov; }
	float PerspectiveCamera::GetFOV() const { return m_FOV; }

	void PerspectiveCamera::SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }
	float PerspectiveCamera::GetAspectRatio() const { return m_AspectRatio; }

	void PerspectiveCamera::SetNearPlane(float nearPlane) { m_NearPlane = nearPlane; }
	float PerspectiveCamera::GetNearPlane() const { return m_NearPlane; }

	void PerspectiveCamera::SetFarPlane(float farPlane) { m_FarPlane = farPlane; }
	float PerspectiveCamera::GetFarPlane() const { return m_FarPlane; }

	glm::mat4 PerspectiveCamera::GetViewMatrix() const
	{
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::rotate(view, glm::radians(-m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		view = glm::rotate(view, glm::radians(-m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::rotate(view, glm::radians(-m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::translate(view, -m_Position);
		return view;
	}

	glm::mat4 PerspectiveCamera::GetProjectionMatrix() const
	{
		return glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_FarPlane);
	}

	glm::vec3 PerspectiveCamera::GetFront() const
	{
		glm::mat4 rot = glm::mat4(1.0f);
		rot = glm::rotate(rot, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		rot = glm::rotate(rot, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		rot = glm::rotate(rot, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		return glm::normalize(glm::vec3(rot * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
	}

	void PerspectiveCamera::DrawUI()
	{
		ImGui::Begin("Camera");
		if (ImGui::DragFloat3("Position", glm::value_ptr(m_Position), 0.01f)) {}
		if (ImGui::DragFloat3("Rotation", glm::value_ptr(m_Rotation), 0.1f)) {}
		if (ImGui::SliderFloat("FOV", &m_FOV, 10.0f, 120.0f)) {}
		ImGui::End();
	}
}