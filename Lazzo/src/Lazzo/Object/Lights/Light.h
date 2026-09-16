#pragma once
#include "Lazzo/Core.h"
#include <glm/glm.hpp>

namespace Lazzo::Object::Lights {

    enum class LightType
    {
        Directional,
        Point,
        Spot
    };

    class LAZZO_API Light
    {
    public:
        Light() = default;
        virtual ~Light() = default;

        LightType GetType() const { return m_Type; }

        void SetColor(const glm::vec3& color) { m_Color = color; }
        glm::vec3 GetColor() const { return m_Color; }

        void SetIntensity(float intensity) { m_Intensity = intensity; }
        float GetIntensity() const { return m_Intensity; }

        virtual void DrawUI() = 0;

    protected:
        LightType m_Type{ LightType::Directional };
        glm::vec3 m_Color{ 1.0f, 1.0f, 1.0f };
        float m_Intensity{ 1.0f };
    };
}
