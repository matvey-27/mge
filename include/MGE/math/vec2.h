#pragma once

namespace mge {
    template <typename T>
    class vec2 {
    public:
        T x, y, w;

        // ������������
        vec2() : x(0), y(0), w(1) {}
        vec2(T x, T y, T w = 1) : x(x), y(y), w(w) {}
        ~vec2() = default;

        // �������� ��������� �� ���������
        bool operator==(const vec2& other) const {
            return x == other.x && y == other.y && w == other.w;
        }

        // �������� �����������
        bool operator!=(const vec2& other) const {
            return !(*this == other);
        }

        // �������� ��������
        vec2 operator+(const vec2& other) const {
            return vec2(x + other.x, y + other.y, w + other.w);
        }

        vec2 operator*(const int& other) const {
            return vec2(x * other, y * other, w * other);
        }


        // �������� ���������
        vec2 operator-(const vec2& other) const {
            return vec2(x - other.x, y - other.y, w - other.w);
        }

        // �������� ��������� (������������ ���������)
        vec2 operator*(const vec2& other) const {
            return vec2(x * other.x, y * other.y, w * other.w);
        }

        // �������� ������� (������������ �������)
        vec2 operator/(const vec2& other) const {
            return vec2(x / other.x, y / other.y, w / other.w);
        }

        // �������� ��������� �� ������
        vec2 operator*(T scalar) const {
            return vec2(x * scalar, y * scalar, w * scalar);
        }

        // �������� ������� �� ������
        vec2 operator/(T scalar) const {
            return vec2(x / scalar, y / scalar, w / scalar);
        }

        // �������� ������������
        vec2& operator=(const vec2& other) {
            if (this != &other) {
                x = other.x;
                y = other.y;
                w = other.w;
            }
            return *this;
        }

        // �������� ������������ � �����������
        vec2& operator+=(const vec2& other) {
            x += other.x;
            y += other.y;
            w += other.w;
            return *this;
        }

        // �������� ������������ � ����������
        vec2& operator-=(const vec2& other) {
            x -= other.x;
            y -= other.y;
            w -= other.w;
            return *this;
        }

        // ���������� ��� ������� � ��������� (�� �������)
        T& operator[](size_t index) {
            if (index == 0) return x;
            if (index == 1) return y;
            return w; // ��� ������� 2 ������ w
        }

        // ����������� ����������
        const T& operator[](size_t index) const {
            if (index == 0) return x;
            if (index == 1) return y;
            return w;
        }
    };

    template <typename T>
    T dot(vec2<T> vector1, vec2<T> vector2) {
        return vector1.x * vector2.x + vector1.y * vector2.y;
    }
}