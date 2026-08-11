#include "lzpch.h"
#include "Vector.h"

namespace Lazzo::Utilities {
    Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3::~Vector3() {}

    float Vector3::GetDistance(const Vector3& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        float dz = z - other.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    Vector3 Vector3::operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 Vector3::operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 Vector3::Normalize() const {
        float length = GetDistance(Vector3(0.0f, 0.0f, 0.0f));
        if (length == 0.0f) {
            return Vector3(0.0f, 0.0f, 0.0f);
        }
        return Vector3(x / length, y / length, z / length);
    }
}