#pragma once

namespace math {
    template <typename T>
    class vector_2D; // Предварительное объявление класса vector_2D

    template <typename T>
    class vector_3D; // Предварительное объявление класса vector_3D

    template <typename T>
    class point_2D; // Предварительное объявление класса point_2D

    template <typename T>
    class point_3D; // Предварительное объявление класса point_3D


    // point_3D и point_2D
    template <typename T>
    class point_2D {
    public:
        T x, y;
    public:
        point_2D() : x(0), y(0) {}
        point_2D(T x, T y) : x(x), y(y) {};

        void print_position();//Вывод точки в консоль
    };

    template <typename T>
    class point_3D : public point_2D<T> {
    public:
        T z;
    public:
        point_3D() : point_2D<T>(0, 0), z(0) {};
        point_3D(T x, T y, T z) : point_2D<T>(x, y), z(z) {};

        vector_3D<T> operator-(point_3D<T> p); //Вычетание точек

        void print_position();//Вывод точки в консоль
    };

    // vector_3D и vector_2D

    template <typename T>
    class vector_2D {
    public:
        T x, y;

        vector_2D() : x(0), y(0) {}
        vector_2D(T x, T y) : x(x), y(y) {};

        void print_vector();//Вывод вектора в консоль
    };

    template <typename T>
    class vector_3D : public vector_2D<T> {
    public:
        T z;
        vector_3D() : vector_2D<T>(0, 0), z(0) {};
        vector_3D(T x, T y, T z) : vector_2D<T>(x, y), z(z) {};

        void print_vector(); //Вывод вектора в консоль

        point_3D<T> operator+(point_3D<T> p); //Сложение точки и вектора

        vector_3D<T> operator+(vector_3D<T> vec); //Сложение векторов

        vector_3D<T> operator*(T num); // Умножение вектора на число

        T length(); // Метод для нахождения модуля(длина) вектора

        T scoliar_product(vector_3D<T> vec); // Скалярное произведение
        vector_3D<T> vector_product(vector_3D<T> vec); // Векторное произведение
    };
}
