#pragma once
#include "Primitives.h"
#include "Lazzo/Utilities/Utilities.h"
#include "Lazzo/Object/GameObject.h"

using namespace Lazzo::Object;

namespace Lazzo {
    class Cube : public Primitives, public GameObject {
    public:
        Cube();
        ~Cube();
        void Draw();
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