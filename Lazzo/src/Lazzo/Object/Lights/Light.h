#pragma once
#include <glm/glm.hpp>

namespace Lazzo::Object::Lights {
    class Light
    {
    public:
        virtual ~Light() = default;
        void SetPosition(float x, float y, float z) { position.x = x; position.y = y; position.z = z; }
        void SetPosition(const glm::vec3& pos) { position = pos; }
        glm::vec3 GetPosition() const { return position; }



    public:
        glm::vec3 position;
        float intensity;
        LightType type;
        float range;

    };

    enum class LightType
    {
        Directional,
        Point,
        Spot
    };
}
