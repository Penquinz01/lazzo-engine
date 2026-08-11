#pragma once
#include "Primitives.h"
#include "Lazzo/Utilities/Utilities.h"

namespace Lazzo {
    class Cube : public Primitives {
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
        Lazzo::Utilities::Vector3 position;
        Lazzo::Utilities::Vector3 rotation;
        Lazzo::Utilities::Vector3 scale;


    };
}