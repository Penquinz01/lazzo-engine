#pragma once
#include "Primitives.h"

namespace Lazzo {
    class Cube : public Primitives {
    public:
        Cube();
        ~Cube();
        void Draw();
        void ChangePosition(const glm::vec3 pos);
        void ChangeRotation(const glm::vec3 rot);
        void ChangeScale(const glm::vec3 sc);
    private:
        inline static constexpr float cubeVertices[] = {
            // Back face
            -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,

            // Front face
            -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,

            // Left face
            -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,

            // Right face
             0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,

             // Bottom face
             -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
              0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
              0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
              0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
             -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
             -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,

             // Top face
             -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
              0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
              0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
              0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
             -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
             -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f
        };
    };
}