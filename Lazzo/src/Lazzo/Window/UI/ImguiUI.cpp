#include "lzpch.h"

#include "ImguiUI.h"

namespace Lazzo
{
  ImguiUI::ImguiUI(SDL_Window* window, SDL_GLContext* context) : m_Window(window)
  {
    mainScale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    glsl_version = "#version 460 core";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(mainScale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = mainScale;
    ImGui_ImplSDL3_InitForOpenGL(window, *context);
    ImGui_ImplOpenGL3_Init(glsl_version);
  }
  ImguiUI::~ImguiUI()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
  }
  void ImguiUI::Init()
  {
    
  }
  void ImguiUI::BeginFrame()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

  }

  void ImguiUI::Render()
  {
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void ImguiUI::ProcessEvent(const SDL_Event& event)
  {
    ImGui_ImplSDL3_ProcessEvent(&event);
  }
  void ImguiUI::Shutdown()
  {
    
  }
}
