#include "lzpch.h"
#include "LightUniforms.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include <glm/glm.hpp>

namespace Lazzo::Object::Lights {
    void SetLightUniforms(const Lazzo::Graphics::Material& material, const std::vector<Light*>& lights) {
        int pointCount = 0;
        int spotCount = 0;

        for (auto* light : lights) {
            if (light->GetType() == LightType::Directional) {
                auto* dl = static_cast<DirectionalLight*>(light);
                material.SetFloat3("u_DirLight.direction", dl->GetDirection());
                material.SetFloat3("u_DirLight.color", dl->GetColor());
                material.SetFloat("u_DirLight.intensity", dl->GetIntensity());
            }
            else if (light->GetType() == LightType::Point && pointCount < 4) {
                auto* pl = static_cast<PointLight*>(light);
                std::string prefix = "u_PointLights[" + std::to_string(pointCount) + "]";
                material.SetFloat3(prefix + ".position", pl->GetPosition());
                material.SetFloat3(prefix + ".color", pl->GetColor());
                material.SetFloat(prefix + ".intensity", pl->GetIntensity());
                material.SetFloat(prefix + ".constant", pl->GetConstant());
                material.SetFloat(prefix + ".linear", pl->GetLinear());
                material.SetFloat(prefix + ".quadratic", pl->GetQuadratic());
                pointCount++;
            }
            else if (light->GetType() == LightType::Spot && spotCount < 4) {
                auto* sl = static_cast<SpotLight*>(light);
                std::string prefix = "u_SpotLights[" + std::to_string(spotCount) + "]";
                material.SetFloat3(prefix + ".position", sl->GetPosition());
                material.SetFloat3(prefix + ".direction", sl->GetDirection());
                material.SetFloat3(prefix + ".color", sl->GetColor());
                material.SetFloat(prefix + ".intensity", sl->GetIntensity());
                material.SetFloat(prefix + ".innerCutoff", glm::cos(glm::radians(sl->GetInnerCutoff())));
                material.SetFloat(prefix + ".outerCutoff", glm::cos(glm::radians(sl->GetOuterCutoff())));
                material.SetFloat(prefix + ".constant", sl->GetConstant());
                material.SetFloat(prefix + ".linear", sl->GetLinear());
                material.SetFloat(prefix + ".quadratic", sl->GetQuadratic());
                spotCount++;
            }
        }

        material.SetInt("u_NumPointLights", pointCount);
        material.SetInt("u_NumSpotLights", spotCount);
    }
}