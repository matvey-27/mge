#pragma once

namespace my_fun {
    // Реализация шаблонной функции addElement с int как размер
    template <typename T>
    void addElement(T*& arr, int& size, T newElement) {
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

    // Реализация шаблонной функции addElement с size_t как размер
    template <typename T>
    void addElement(T*& arr, size_t& size, T newElement) {
        // Создаем новый массив с увеличенной вместимостью
        T* newArr = new T[size + 1];

        // Копируем старые элементы в новый массив
        for (size_t i = 0; i < size; ++i) {
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

    // Реализация шаблонной функции swap
    template <typename T>
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }
}