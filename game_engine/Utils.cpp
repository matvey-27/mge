#include "Utils.h"

template <typename T>
void my_fun::addElement(T*& arr, int& size, T newElement) {
    // Создаем новый массив с увеличенной вместимостью
    T* newArr = new T[size + 1];

    // Копируем старые элементы в новый массив
    for (int i = 0; i < size; ++i) {
        newArr[i] = arr[i];
    }

    // Добавляем новый элемент
    newArr[size] = newElement;

    // Освобождаем память старого массива
    delete[] arr;

    // Указываем на новый массив и обновляем размер
    arr = newArr;
    size++; // Увеличиваем размер
}

template <typename T>
void my_fun::addElement(T*& arr, size_t& size, T newElement) {
    // Создаем новый массив с увеличенной вместимостью
    T* newArr = new T[size + 1];

    // Копируем старые элементы в новый массив
    for (int i = 0; i < size; ++i) {
        newArr[i] = arr[i];
    }

    // Добавляем новый элемент
    newArr[size] = newElement;

    // Освобождаем память старого массива
    delete[] arr;

    // Указываем на новый массив и обновляем размер
    arr = newArr;
    size++; // Увеличиваем размер
}

template <typename T>
void my_fun::swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}