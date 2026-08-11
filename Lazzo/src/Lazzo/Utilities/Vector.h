#pragma once

namespace Lazzo::Utilities {
    struct Vector3 {
        Vector3();
        Vector3(float x, float y, float z);
        ~Vector3();
        float GetDistance(const Vector3& other) const;
        Vector3 Normalize() const;


        Vector3 operator+(const Vector3& other) const;
        Vector3 operator-(const Vector3& other) const;


        float x, y, z;
    };
}