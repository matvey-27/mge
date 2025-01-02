#pragma once
#include <cstddef>
#include <iostream>

namespace mge {
    const float M_PI = 3.1415f;

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
    
    template <typename T>
    void removeLastElement(T* &arr, size_t &size) {
        // Проверяем, что массив не пуст
        if (size > 0) {
            size--;  // Уменьшаем размер массива

            // Создаем новый массив размером на 1 меньше
            int* newArr = new int[size];
            
            // Копируем старый массив в новый, за исключением последнего элемента
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
            }

            // Освобождаем память, занятую старым массивом
            delete[] arr;
            
            // Указываем указатель на новый массив
            arr = newArr;
        } else {
            std::cout << "Массив пуст. Невозможно удалить элемент." << std::endl;
        }
    }

    template <typename T>
    void removeLastElement(T* &arr, int &size) {
        // Проверяем, что массив не пуст
        if (size > 0) {
            size--;  // Уменьшаем размер массива

            // Создаем новый массив размером на 1 меньше
            int* newArr = new int[size];
            
            // Копируем старый массив в новый, за исключением последнего элемента
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
            }

            // Освобождаем память, занятую старым массивом
            delete[] arr;
            
            // Указываем указатель на новый массив
            arr = newArr;
        } else {
            std::cout << "Массив пуст. Невозможно удалить элемент." << std::endl;
        }
    }

    template <typename T>
    T* combineArray(T* &arr1, T* &arr2, int size1, int size2){
        T* newArr = new T[size1 + size2];

        for(int i = 0; i < size1; i++) newArr[i] = arr1[i];

        for(int i = 0; i < size2; i++) newArr[size2 + i] = arr1[i];

        return newArr;
    }
}