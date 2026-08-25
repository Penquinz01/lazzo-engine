#pragma once
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "ShaderFileData.h"
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

  virtual SDL_GLContext GetContext() const = 0;

};