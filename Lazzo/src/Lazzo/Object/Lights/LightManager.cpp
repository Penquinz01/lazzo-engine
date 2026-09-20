#include "lzpch.h"
#include "LightManager.h"
#include "Lazzo/Log.h"
#include <imgui.h>
#include <algorithm>
#include <stdexcept>

namespace Lazzo::Object::Lights {

    LightManager& LightManager::GetInstance()
    {
        static LightManager instance;
        return instance;
    }

    PointLight& LightManager::AddPointLight()
    {
        m_PointLights.emplace_back();
        return m_PointLights.back();
    }

    PointLight& LightManager::AddPointLight(const glm::vec3& position, const glm::vec3& color, float intensity, float range)
    {
        m_PointLights.emplace_back(position, color, intensity, range);
        return m_PointLights.back();
    }

    PointLight& LightManager::GetPointLight(size_t index)
    {
        if (index >= m_PointLights.size())
        {
            LZ_CORE_WARN("GetPointLight: index {0} out of range!", index);
            throw std::out_of_range("GetPointLight: index out of range!");
        }
        return m_PointLights[index];
    }

    void LightManager::EditPointLight(size_t index, const PointLight& light)
    {
        if (index >= m_PointLights.size())
        {
            LZ_CORE_WARN("EditPointLight: index {0} out of range!", index);
            return;
        }
        m_PointLights[index] = light;
    }

    bool LightManager::RemovePointLight(size_t index)
    {
        if (index >= m_PointLights.size())
        {
            LZ_CORE_WARN("RemovePointLight: index {0} out of range!", index);
            return false;
        }
        m_PointLights.erase(m_PointLights.begin() + index);
        return true;
    }

    SpotLight& LightManager::AddSpotLight()
    {
        m_SpotLights.emplace_back();
        return m_SpotLights.back();
    }

    SpotLight& LightManager::AddSpotLight(const glm::vec3& position, const glm::vec3& direction,
                                         const glm::vec3& color, float intensity,
                                         float innerCutoff, float outerCutoff)
    {
        m_SpotLights.emplace_back(position, direction, color, intensity, innerCutoff, outerCutoff);
        return m_SpotLights.back();
    }

    SpotLight& LightManager::GetSpotLight(size_t index)
    {
        if (index >= m_SpotLights.size())
        {
            LZ_CORE_WARN("GetSpotLight: index {0} out of range!", index);
            throw std::out_of_range("GetSpotLight: index out of range!");
        }
        return m_SpotLights[index];
    }

    void LightManager::EditSpotLight(size_t index, const SpotLight& light)
    {
        if (index >= m_SpotLights.size())
        {
            LZ_CORE_WARN("EditSpotLight: index {0} out of range!", index);
            return;
        }
        m_SpotLights[index] = light;
    }

    bool LightManager::RemoveSpotLight(size_t index)
    {
        if (index >= m_SpotLights.size())
        {
            LZ_CORE_WARN("RemoveSpotLight: index {0} out of range!", index);
            return false;
        }
        m_SpotLights.erase(m_SpotLights.begin() + index);
        return true;
    }

    std::vector<PointLight*> LightManager::GetNearestPointLights(size_t n, const glm::vec3& position)
    {
        std::vector<PointLight*> nearest;
        nearest.reserve(m_PointLights.size());

        for (PointLight& light : m_PointLights)
            nearest.push_back(&light);

        std::sort(nearest.begin(), nearest.end(), [&position](const PointLight* a, const PointLight* b)
        {
            const glm::vec3 toA = a->GetPosition() - position;
            const glm::vec3 toB = b->GetPosition() - position;
            return glm::dot(toA, toA) < glm::dot(toB, toB);
        });

        if (nearest.size() > n)
            nearest.resize(n);

        return nearest;
    }

    std::vector<SpotLight*> LightManager::GetNearestSpotLights(size_t n, const glm::vec3& position)
    {
        std::vector<SpotLight*> nearest;
        nearest.reserve(m_SpotLights.size());

        for (SpotLight& light : m_SpotLights)
            nearest.push_back(&light);

        std::sort(nearest.begin(), nearest.end(), [&position](const SpotLight* a, const SpotLight* b)
        {
            const glm::vec3 toA = a->GetPosition() - position;
            const glm::vec3 toB = b->GetPosition() - position;
            return glm::dot(toA, toA) < glm::dot(toB, toB);
        });

        if (nearest.size() > n)
            nearest.resize(n);

        return nearest;
    }

    std::vector<Light*> LightManager::GetAllLights()
    {
        std::vector<Light*> lights;
        lights.reserve(1 + m_PointLights.size() + m_SpotLights.size());

        lights.push_back(&m_DirectionalLight);
        for (PointLight& light : m_PointLights)
            lights.push_back(&light);
        for (SpotLight& light : m_SpotLights)
            lights.push_back(&light);

        return lights;
    }

    void LightManager::DrawUI()
    {
        ImGui::PushID("LightManager");
        ImGui::SeparatorText("Lights");

        m_DirectionalLight.DrawUI();

        if (ImGui::CollapsingHeader("Point Lights", ImGuiTreeNodeFlags_DefaultOpen))
        {
            for (size_t i = 0; i < m_PointLights.size(); i++)
            {
                ImGui::PushID(static_cast<int>(i));
                m_PointLights[i].DrawUI();
                if (ImGui::Button("Remove Point Light"))
                    RemovePointLight(i--);
                ImGui::Spacing();
                ImGui::PopID();
            }

            if (ImGui::Button("Add Point Light"))
                AddPointLight();
            ImGui::Spacing();
        }

        if (ImGui::CollapsingHeader("Spot Lights", ImGuiTreeNodeFlags_DefaultOpen))
        {
            for (size_t i = 0; i < m_SpotLights.size(); i++)
            {
                ImGui::PushID(static_cast<int>(i));
                m_SpotLights[i].DrawUI();
                if (ImGui::Button("Remove Spot Light"))
                    RemoveSpotLight(i--);
                ImGui::Spacing();
                ImGui::PopID();
            }

            if (ImGui::Button("Add Spot Light"))
                AddSpotLight();
            ImGui::Spacing();
        }

        ImGui::Separator();
        ImGui::PopID();
    }
}