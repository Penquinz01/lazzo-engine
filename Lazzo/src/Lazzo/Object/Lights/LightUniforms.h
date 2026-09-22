#pragma once
#include <vector>
#include "Light.h"
#include "Lazzo/Window/GraphicsAPI/Material.h"

namespace Lazzo::Object::Lights {
    void SetLightUniforms(const Lazzo::Graphics::Material& material, const std::vector<Light*>& lights);
}