#include "lzpch.h"
#include <Lazzo.h>
#include <Lazzo/Primitives/Cube.h>
#include <Lazzo/Object/Camera/Camera.h>

class SandBox : public Lazzo::Application {
public:
	SandBox() {
		m_Camera.SetAspectRatio(16.0f / 9.0f);
		m_Camera.SetFOV(45.0f);
		m_Camera.SetPosition(0.0f, 0.0f, 3.0f);
		m_Camera.SetNearPlane(0.1f);
		m_Camera.SetFarPlane(100.0f);
		m_Cube.SetRotation(glm::vec3(30.0f, 45.0f, 0.0f));
	}
	~SandBox() {
	}

protected:
	void OnRender() override {
		m_Cube.Draw(m_Camera);
	}

	void OnImGuiRender() override {
		m_Cube.DrawUI();
		m_Camera.DrawUI();
	}

private:
	Lazzo::Cube m_Cube;
	Lazzo::Object::Camera::Camera m_Camera{};
};


Lazzo::Application* Lazzo::CreateApplication() {
	return new SandBox();
}
