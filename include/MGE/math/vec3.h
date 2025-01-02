#pragma once

#include "vec2.h"

namespace mge {
    template <typename T>
    class vec3 : public vec2<T> {
    public:
        T z;

        vec3() : vec2<T>::vec2(), z(0) {};
        vec3(T x, T y, T z, T w = 1) : vec2<T>::vec2(x, y, w), z(z) {};
        ~vec3() = default;

        // �������� +=
        vec3<T>& operator+=(const vec3<T>& v) {
            this->x += v.x;
            this->y += v.y;
            this->z += v.z;
            return *this; // ���������� this
        }

        // �������� -
        vec3<T> operator-(vec3<T> p) {
            return vec3<T>(this->x - p.x, this->y - p.y, this->z - p.z);
        }

        // �������� +  
        vec3<T> operator+(vec3<T> p) {
            return vec3<T>(this->x + p.x, this->y + p.y, this->z + p.z);
        }

        // �������� * ��������� �������� (cross)
        vec3<T> operator*(const vec3<T>& other) const {
            return vec3<T>(
                this->y * other.z - this->z * other.y,  // ���������� x
                this->z * other.x - this->x * other.z,  // ���������� y
                this->x * other.y - this->y * other.x   // ���������� z
            );
        }

        // ����� �������
        T length() const {
            return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
        }

        // ����� ��� ������������ �������
        vec3<T> normalize() const {
            T len = length();
            if (len == 0) {
                throw std::runtime_error("Cannot normalize a zero-length vector");
            }
            return vec3<T>(this->x / len, this->y / len, this->z / len);
        }
    };

    template <typename T>
    T dot(vec3<T> vector1, vec3<T> vector2) {
        return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
    }
}