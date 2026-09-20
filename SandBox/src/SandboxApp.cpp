#include "lzpch.h"
#include <Lazzo.h>
#include <Lazzo/Primitives/Cube.h>
#include <Lazzo/Object/Camera/Camera.h>
#include <Lazzo/Object/Lights/LightManager.h>
#include "editor inputs/EditorInputLayer.h"

class SandBox : public Lazzo::Application {
public:
	SandBox() {
        m_Cube2 = std::make_unique<Lazzo::Cube>("Cube2");
		m_Cube2->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
		m_Camera.SetAspectRatio(16.0f / 9.0f);
		m_Camera.SetFOV(45.0f);
		m_Camera.SetPosition(0.0f, 0.0f, 3.0f);
		m_Camera.SetNearPlane(0.1f);
		m_Camera.SetFarPlane(100.0f);
		m_Cube.SetRotation(glm::vec3(30.0f, 45.0f, 0.0f));

		auto& lightManager = Lazzo::Object::Lights::LightManager::GetInstance();

		lightManager.GetDirectionalLight().SetDirection(glm::vec3(-0.4f, -0.7f, -1.0f));
		lightManager.GetDirectionalLight().SetColor(glm::vec3(1.0f, 0.95f, 0.9f));
		lightManager.GetDirectionalLight().SetIntensity(1.0f);

		lightManager.AddPointLight();
		lightManager.AddSpotLight();

		PushLayer(new EditorInputLayer(m_Camera, GetWindow().GetSDLWindow()));
	}
	~SandBox() {
	}

protected:
	void OnRender() override {
		auto& lightManager = Lazzo::Object::Lights::LightManager::GetInstance();
		m_Cube.Draw(m_Camera, lightManager.GetAllLights());
		m_Cube2->Draw(m_Camera, lightManager.GetAllLights());
	}

	void OnImGuiRender() override {
		BeginRightPanel();
		m_Cube.DrawUI();
        m_Cube2->DrawUI();
		m_Camera.DrawUI();
		Lazzo::Object::Lights::LightManager::GetInstance().DrawUI();
		EndRightPanel();
	}

private:
	Lazzo::Cube m_Cube;
    std::unique_ptr<Lazzo::Cube> m_Cube2;
	Lazzo::Object::Camera::Camera m_Camera{};
};

 
Lazzo::Application* Lazzo::CreateApplication() {
	return new SandBox();
}