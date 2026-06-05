#pragma once
#include "SDL3/SDL.h"

enum class GraphicAPI
{
	OpenGL,
	Vulkan,
	DirectX11,
	DirectX12,
	Metal
};

class GraphicsAPI
{
public:
	virtual ~GraphicsAPI() = default;

	virtual void Init() = 0;
	virtual void SwapBuffers() = 0;
  virtual void Shutdown() = 0;
};