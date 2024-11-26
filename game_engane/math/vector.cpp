#include "math.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace math;

// vector_2D

template <typename T>
void vector_2D<T>::print_vector() {
    // Вывод координат вектора
    cout << "x = " << this->x << endl;
    cout << "y = " << this->y << endl;
}

// vector_3D

template <typename T>
void vector_3D<T>::print_vector() {
    // Вывод координат вектора
    cout << "x = " << this->x << endl;
    cout << "y = " << this->y << endl;
    cout << "z = " << this->z << endl;
}

// Оператор сложения векторов

template <typename T>
point_3D<T> vector_3D<T>::operator+(point_3D<T> p) {
    // Сложение координат векторов
    p.x += this->x;
    p.y += this->y;
    p.z += this->z;

    return p;
}

// Оператор сложения векторов

template <typename T>
vector_3D<T> vector_3D<T>::operator+(vector_3D<T> vec) {
    // Сложение координат векторов
    return vector_3D<T>(this->x + vec.x,
        this->y + vec.y,
        this->z + vec.z);
}

// Оператор умножения вектора на скаляр

template <typename T>
vector_3D<T> vector_3D<T>::operator*(T num) {
    // Умножение координат вектора на скаляр
    return vector_3D<T>(this->x * num,
        this->y * num,
        this->z * num);
}

// Длина вектора

template <typename T>
T vector_3D<T>::length() {
    // Вычисление длины вектора
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

// Скалярное произведение векторов

template <typename T>
T vector_3D<T>::scoliar_product(vector_3D<T> vec) {
    // Вычисление скалярного произведения векторов
    return this->x * vec.x + this->y * vec.y + this->z * vec.z;
}

// Векторное произведение векторов

template <typename T>
vector_3D<T> vector_3D<T>::vector_product(vector_3D<T> vec) {
    // Вычисление векторного произведения векторов
    return vector_3D<T>(this->y * vec.z - this->z * vec.y,
        this->z * vec.x - this->x * vec.z,
        this->x * vec.y - this->y * vec.x);
}
