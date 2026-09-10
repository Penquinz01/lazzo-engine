#include "lzpch.h"
#include <Lazzo.h>
#include <Lazzo/Primitives/Cube.h>
#include <Lazzo/Object/Camera/PerspectiveCamera.h>

class SandBox : public Lazzo::Application {
public:
	SandBox() {
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
	Lazzo::Object::Camera::PerspectiveCamera m_Camera{ 45.0f, 16.0f / 9.0f, 0.1f, 100.0f };
};


Lazzo::Application* Lazzo::CreateApplication() {
	return new SandBox();
}
