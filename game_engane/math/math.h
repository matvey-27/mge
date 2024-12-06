#pragma once

//ПОМЕНЯТЬ ОПЕРАТОРЫ В ПРИМЕР КОД НИЖЕ 
//Point3D<T>& operator+=(const Vector3D<T>& v) {
//    this->x += v.x;
//    this->y += v.y;
//    this->z += v.z;
//    return *this; // Возвращаем this
//}

namespace math {
    template <typename T>
    class Vector2D; // Предварительное объявление класса Vector2D

    template <typename T>
    class Vector3D; // Предварительное объявление класса Vector3D

    template <typename T>
    class Point2D; // Предварительное объявление класса Point2D

    template <typename T>
    class Point3D; // Предварительное объявление класса Point3D


    // Point3D и Point2D
    template <typename T>
    class Point2D {
    public:
        T x, y;
    public:
        Point2D() : x(0), y(0) {}
        Point2D(T x, T y) : x(x), y(y) {};
        ~Point2D() = default;

        void print_position();//Вывод точки в консоль
    };

    template <typename T>
    class Point3D : public Point2D<T> {
    public:
        T z;
    public:
        Point3D() : Point2D<T>(0, 0), z(0) {};
        Point3D(T x, T y, T z) : Point2D<T>(x, y), z(z) {};
        ~Point3D() = default;

        // Оператор += для добавления вектора
        Point3D<T>& operator+=(const Vector3D<T>& v) {
            this->x += v.x;
            this->y += v.y;
            this->z += v.z;
            return *this; // Возвращаем this
        }

        Vector3D<T> operator-(Point3D<T> p); //Вычетание точек

        void print_position();//Вывод точки в консоль
    };

    // Vector3D и Vector2D

    template <typename T>
    class Vector2D {
    public:
        T x, y;

        Vector2D() : x(0), y(0) {}
        Vector2D(T x, T y) : x(x), y(y) {};

        void print_vector();//Вывод вектора в консоль
    };

    template <typename T>
    class Vector3D : public Vector2D<T> {
    public:
        T z;
        Vector3D() : Vector2D<T>(0, 0), z(0) {};
        Vector3D(T x, T y, T z) : Vector2D<T>(x, y), z(z) {};

        void print_vector(); //Вывод вектора в консоль

        Point3D<T> operator+(Point3D<T> p); //Сложение точки и вектора

        Vector3D<T> operator+(Vector3D<T> vec); //Сложение векторов

        Vector3D<T> operator*(T num); // Умножение вектора на число

        T length(); // Метод для нахождения модуля(длина) вектора

        T scoliar_product(Vector3D<T> vec); // Скалярное произведение
        Vector3D<T> vector_product(Vector3D<T> vec); // Векторное произведение
    };
}
