#include "lzpch.h"
#include <functional>
#include <limits>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <Lazzo.h>
#include <Lazzo/Primitives/Cube.h>
#include <Lazzo/Object/Camera/Camera.h>
#include <Lazzo/Object/Model/Model.h>
#include <Lazzo/Object/Picking.h>
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

		model = std::make_unique<Lazzo::Object::Model>("Textures/Imp.fbx");

		auto& lightManager = Lazzo::Object::Lights::LightManager::GetInstance();

		lightManager.GetDirectionalLight().SetDirection(glm::vec3(-0.4f, -0.7f, -1.0f));
		lightManager.GetDirectionalLight().SetColor(glm::vec3(1.0f, 0.95f, 0.9f));
		lightManager.GetDirectionalLight().SetIntensity(1.0f);

		lightManager.AddPointLight();
		lightManager.AddSpotLight();

		PushLayer(new EditorInputLayer(m_Camera, GetWindow().GetSDLWindow()));

		m_InspectorNames = { "Cube", "Cube2", "Imp", "Camera", "Lights" };
		m_UICallbacks.emplace_back([this]() { m_Cube.DrawUI(); });
		m_UICallbacks.emplace_back([this]() { if (m_Cube2) m_Cube2->DrawUI(); });
		m_UICallbacks.emplace_back([this]() { if (model) model->DrawUI("Imp"); });
		m_UICallbacks.emplace_back([this]() { m_Camera.DrawUI(); });
		m_UICallbacks.emplace_back([]() { Lazzo::Object::Lights::LightManager::GetInstance().DrawUI(); });

		m_ClickCallbackId = Lazzo::InputManager::GetInstance().RegisterCallback(
			Lazzo::EventType::MouseButtonPressed,
			[this](const Lazzo::Event& e) { OnClick(e); });
	}
	~SandBox() override {
		Lazzo::InputManager::GetInstance().UnregisterCallback(m_ClickCallbackId);
	}

protected:
	void OnRender() override {
		SyncCameraAspect();
		auto& lightManager = Lazzo::Object::Lights::LightManager::GetInstance();
		m_Cube.Draw(m_Camera, lightManager.GetAllLights());
		if (model)
			model->Draw(m_Camera, lightManager.GetAllLights());
		if (m_Cube2)
			m_Cube2->Draw(m_Camera, lightManager.GetAllLights());
	}

	void OnImGuiRender() override {
		BeginRightPanel();
		InspectorTitle("Inspector");

		// Scene list fallback so Camera/Lights (not ray-pickable) can still be selected.
		InspectorSelectableList(m_InspectorNames, m_SelectedInspector);

		InspectorTitle("Details");

		if (m_SelectedInspector < 0 || m_SelectedInspector >= static_cast<int>(m_UICallbacks.size())) {
			InspectorEmptyHint();
		}
		else {
			m_UICallbacks[m_SelectedInspector]();
		}
		EndRightPanel();
	}

private:
	void OnClick(const Lazzo::Event& event) {
		if (event.GetEventType() != Lazzo::EventType::MouseButtonPressed)
			return;
		const auto& click = static_cast<const Lazzo::MouseButtonPressedEvent&>(event);
		if (click.GetButton() != SDL_BUTTON_LEFT)
			return; // right button drives the fly camera

		int viewW = 0, viewH = 0;
		SDL_GetWindowSize(GetWindow().GetSDLWindow(), &viewW, &viewH);
		if (viewW <= 0 || viewH <= 0)
			return;

		// Right panel overlays the viewport: ignore clicks on the inspector itself.
		constexpr float kPanelWidth = 300.0f;
		if (click.GetX() >= static_cast<float>(viewW) - kPanelWidth)
			return;
		if (IsUIMouseCaptured())
			return;

		SyncCameraAspect();
		Pick(click.GetX(), click.GetY(), viewW, viewH);
	}

	void SyncCameraAspect() {
		int w = 0, h = 0;
		SDL_GetWindowSize(GetWindow().GetSDLWindow(), &w, &h);
		if (w > 0 && h > 0)
			m_Camera.SetAspectRatio(static_cast<float>(w) / static_cast<float>(h));
	}

	void Pick(float mouseX, float mouseY, int viewW, int viewH) {
		Lazzo::Object::Ray ray = Lazzo::Object::ScreenPointToRay(
			mouseX, mouseY, static_cast<float>(viewW), static_cast<float>(viewH), m_Camera);

		int best = -1;
		float bestT = std::numeric_limits<float>::max();
		float t = 0.0f;
		Lazzo::Object::AABB box;

		// Inspector indices 0/1/2 are the world-pickable objects; nearest hit wins.
		if (m_Cube.GetWorldAABB(box) && Lazzo::Object::RayIntersectsAABB(ray, box, t) && t < bestT) {
			bestT = t;
			best = 0;
		}
		if (m_Cube2 && m_Cube2->GetWorldAABB(box) && Lazzo::Object::RayIntersectsAABB(ray, box, t) && t < bestT) {
			bestT = t;
			best = 1;
		}
		if (model && model->GetWorldAABB(box) && Lazzo::Object::RayIntersectsAABB(ray, box, t) && t < bestT) {
			bestT = t;
			best = 2;
		}

		m_SelectedInspector = best; // -1 keeps the inspector empty on miss
	}

private:
	Lazzo::Cube m_Cube;
	std::unique_ptr<Lazzo::Cube> m_Cube2;
	Lazzo::Object::Camera::Camera m_Camera{};
	std::unique_ptr<Lazzo::Object::Model> model;
	std::vector<std::function<void()>> m_UICallbacks;
	std::vector<std::string> m_InspectorNames;
	int m_SelectedInspector{ -1 }; // -1 = nothing selected -> empty inspector
	Lazzo::CallbackID m_ClickCallbackId{ 0 };
};


Lazzo::Application* Lazzo::CreateApplication() {
	return new SandBox();
}
