#pragma once
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include <vector>

namespace Lazzo::Object::Lights {

    class LAZZO_API LightManager
    {
    public:
        static LightManager& GetInstance();

        LightManager(const LightManager&) = delete;
        LightManager& operator=(const LightManager&) = delete;

        // Directional light
        DirectionalLight& GetDirectionalLight() { return m_DirectionalLight; }
        void SetDirectionalLight(const DirectionalLight& light) { m_DirectionalLight = light; }

        // Point lights
        PointLight& AddPointLight();
        PointLight& AddPointLight(const glm::vec3& position, const glm::vec3& color, float intensity, float range);
        PointLight& GetPointLight(size_t index);
        void EditPointLight(size_t index, const PointLight& light);
        bool RemovePointLight(size_t index);
        std::vector<PointLight>& GetPointLights() { return m_PointLights; }
        const std::vector<PointLight>& GetPointLights() const { return m_PointLights; }

        // Spot lights
        SpotLight& AddSpotLight();
        SpotLight& AddSpotLight(const glm::vec3& position, const glm::vec3& direction,
                                const glm::vec3& color, float intensity,
                                float innerCutoff, float outerCutoff);
        SpotLight& GetSpotLight(size_t index);
        void EditSpotLight(size_t index, const SpotLight& light);
        bool RemoveSpotLight(size_t index);
        std::vector<SpotLight>& GetSpotLights() { return m_SpotLights; }
        const std::vector<SpotLight>& GetSpotLights() const { return m_SpotLights; }

        // Nearest lights
        std::vector<PointLight*> GetNearestPointLights(size_t n, const glm::vec3& position);
        std::vector<SpotLight*> GetNearestSpotLights(size_t n, const glm::vec3& position);

        // All lights (directional + point + spot) as base pointers
        std::vector<Light*> GetAllLights();

        void DrawUI();

    private:
        LightManager() = default;
        ~LightManager() = default;

        DirectionalLight m_DirectionalLight;
        std::vector<PointLight> m_PointLights;
        std::vector<SpotLight> m_SpotLights;
    };
}