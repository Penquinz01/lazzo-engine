#include "lzpch.h"
#include "Application.h"

#include "Lazzo/Log.h"
#include <imgui.h>

namespace Lazzo
{
	Application::Application()
	{
		window = std::make_unique<Window>("Lazzo Engine", 1280, 720);
		running = true;
	}
	void Application::Run()
	{
		window->OnUpdate(
			[this]() { for (auto* layer : m_LayerStack) layer->OnUpdate(); },
			[this]() { OnRender(); },
			[this]() { OnImGuiRender(); });
	}
    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }
    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
    }

    void Application::BeginRightPanel(float width)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - width, 0.0f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(width, io.DisplaySize.y), ImGuiCond_Always);
        ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    }

    void Application::EndRightPanel()
    {
        ImGui::End();
    }

    void Application::InspectorSelectableList(const std::vector<std::string>& names, int& selectedIndex)
    {
        for (int i = 0; i < static_cast<int>(names.size()); i++) {
            ImGui::PushID(i);
            bool selected = (selectedIndex == i);
            if (ImGui::Selectable(names[i].c_str(), selected))
                selectedIndex = selected ? -1 : i;
            ImGui::PopID();
        }
        if (selectedIndex != -1 && ImGui::Button("Deselect"))
            selectedIndex = -1;
    }

    void Application::InspectorEmptyHint()
    {
        ImGui::TextDisabled("No selection.");
        ImGui::TextDisabled("Left-click an object in the viewport.");
    }

    void Application::InspectorTitle(const char* text)
    {
        ImGui::SeparatorText(text);
    }

    bool Application::IsUIMouseCaptured() const
    {
        return ImGui::GetIO().WantCaptureMouse;
    }

}
