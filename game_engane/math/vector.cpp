#include "math.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace math;

// Vector2D

template <typename T>
void Vector2D<T>::print_vector() {
    // Вывод координат вектора
    cout << "x = " << this->x << endl;
    cout << "y = " << this->y << endl;
}

// Vector3D

template <typename T>
void Vector3D<T>::print_vector() {
    // Вывод координат вектора
    cout << "x = " << this->x << endl;
    cout << "y = " << this->y << endl;
    cout << "z = " << this->z << endl;
}

// Оператор сложения векторов

template <typename T>
Point3D<T> Vector3D<T>::operator+(Point3D<T> p) {
    // Сложение координат векторов
    p.x += this->x;
    p.y += this->y;
    p.z += this->z;

    return p;
}

// Оператор сложения векторов

template <typename T>
Vector3D<T> Vector3D<T>::operator+(Vector3D<T> vec) {
    // Сложение координат векторов
    return Vector3D<T>(this->x + vec.x,
        this->y + vec.y,
        this->z + vec.z);
}

// Оператор умножения вектора на скаляр

template <typename T>
Vector3D<T> Vector3D<T>::operator*(T num) {
    // Умножение координат вектора на скаляр
    return Vector3D<T>(this->x * num,
        this->y * num,
        this->z * num);
}

// Длина вектора

template <typename T>
T Vector3D<T>::length() {
    // Вычисление длины вектора
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

// Скалярное произведение векторов

template <typename T>
T Vector3D<T>::scoliar_product(Vector3D<T> vec) {
    // Вычисление скалярного произведения векторов
    return this->x * vec.x + this->y * vec.y + this->z * vec.z;
}

// Векторное произведение векторов

template <typename T>
Vector3D<T> Vector3D<T>::vector_product(Vector3D<T> vec) {
    // Вычисление векторного произведения векторов
    return Vector3D<T>(
        this->y * vec.z - this->z * vec.y,
        this->z * vec.x - this->x * vec.z,
        this->x * vec.y - this->y * vec.x);
}
