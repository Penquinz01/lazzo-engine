#pragma once
#include "Light.h"

namespace Lazzo::Object::Lights {

    class LAZZO_API DirectionalLight : public Light
    {
    public:
        DirectionalLight();
        DirectionalLight(const glm::vec3& direction, const glm::vec3& color, float intensity);

        void SetDirection(const glm::vec3& direction) { m_Direction = direction; }
        glm::vec3 GetDirection() const { return m_Direction; }

        void DrawUI() override;

    private:
        glm::vec3 m_Direction{ -0.4f, -0.7f, -1.0f };
    };
}
