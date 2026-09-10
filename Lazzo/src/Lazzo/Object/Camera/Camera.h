#pragma once
#include "Lazzo/Core.h"
#include <glm/glm.hpp>

namespace Lazzo::Object::Camera {

	// Unity-style camera: one class, flip between Perspective (3D) and
	// Orthographic (2D) via SetProjectionMode() / the DrawUI() combo box.
	enum class ProjectionMode : int {
		Perspective,
		Orthographic
	};

	class LAZZO_API Camera
	{
	public:
		Camera() = default;
		Camera(const glm::vec3& position, const glm::vec3& rotation = glm::vec3(0.0f, 0.0f, 0.0f));
		~Camera() = default;

		// Transform
		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& pos);
		glm::vec3 GetPosition() const;
		void SetRotation(float pitch, float yaw, float roll);
		void SetRotation(const glm::vec3& rot);
		glm::vec3 GetRotation() const;

		// Projection
		void SetProjectionMode(ProjectionMode mode);
		ProjectionMode GetProjectionMode() const;
		void SetFOV(float fov);                    // Perspective
		float GetFOV() const;
		void SetOrthographicSize(float size);       // Orthographic (half-height in world units)
		float GetOrthographicSize() const;
		void SetAspectRatio(float aspectRatio);
		float GetAspectRatio() const;
		void SetNearPlane(float nearPlane);
		float GetNearPlane() const;
		void SetFarPlane(float farPlane);
		float GetFarPlane() const;

		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix() const;

		glm::vec3 GetFront() const;
		void DrawUI();

	private:
		glm::vec3 m_Position{ 0.0f, 0.0f, 3.0f };
		glm::vec3 m_Rotation{ 0.0f, 0.0f, 0.0f };
		ProjectionMode m_ProjectionMode{ ProjectionMode::Perspective };
		float m_FOV{ 45.0f };
		float m_OrthographicSize{ 3.0f };
		float m_AspectRatio{ 16.0f / 9.0f };
		float m_NearPlane{ 0.1f };
		float m_FarPlane{ 100.0f };
	};
}