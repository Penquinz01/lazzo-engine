#pragma once
#include "Light.h"

namespace Lazzo::Object::Lights {

    class LAZZO_API SpotLight : public Light
    {
    public:
        SpotLight();
        SpotLight(const glm::vec3& position, const glm::vec3& direction,
                  const glm::vec3& color, float intensity,
                  float innerCutoff, float outerCutoff);

        void SetPosition(const glm::vec3& position) { m_Position = position; }
        glm::vec3 GetPosition() const { return m_Position; }

        void SetDirection(const glm::vec3& direction) { m_Direction = direction; }
        glm::vec3 GetDirection() const { return m_Direction; }

        void SetInnerCutoff(float angle) { m_InnerCutoff = angle; }
        float GetInnerCutoff() const { return m_InnerCutoff; }

        void SetOuterCutoff(float angle) { m_OuterCutoff = angle; }
        float GetOuterCutoff() const { return m_OuterCutoff; }

        void SetRange(float range) { m_Range = range; }
        float GetRange() const { return m_Range; }

        void SetConstant(float constant) { m_Constant = constant; }
        float GetConstant() const { return m_Constant; }

        void SetLinear(float linear) { m_Linear = linear; }
        float GetLinear() const { return m_Linear; }

        void SetQuadratic(float quadratic) { m_Quadratic = quadratic; }
        float GetQuadratic() const { return m_Quadratic; }

        void DrawUI() override;

    private:
        glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
        glm::vec3 m_Direction{ 0.0f, -1.0f, 0.0f };
        float m_InnerCutoff{ 12.5f };
        float m_OuterCutoff{ 17.5f };
        float m_Range{ 10.0f };
        float m_Constant{ 1.0f };
        float m_Linear{ 0.09f };
        float m_Quadratic{ 0.032f };
    };
}
