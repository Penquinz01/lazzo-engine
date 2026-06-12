#pragma once
#include "../GraphicsAPI/GraphicsAPI.h"
#include "../GraphicsAPI/OpenGLAPI.h"
#include "SDL3/SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

namespace Lazzo
{
  struct DeleteImgui
  {
    void operator()(ImGuiContext* context) {
      ImGui::DestroyContext(context);
    }
  };
  class ImguiUI
  {
  public:
    ImguiUI(SDL_Window* window, SDL_GLContext *context);
    ~ImguiUI();
    void Init();
    void Render();
    void Shutdown();
    void ProcessEvent(const SDL_Event& event);
  private:
    SDL_Window* m_Window{ nullptr };
    char* glsl_version = "#version 460 core";
    float mainScale;
    bool show_demo_window{ true };
    float clear_color[4] = { 0.45f, 0.55f, 0.60f, 1.00f };
    int counter{ 0 };
  };
}
