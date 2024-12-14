#pragma once

namespace my_fun {
    template <typename T>
    void addElement(T*& arr, int& size, T newElement);

    template <typename T>
    void addElement(T*& arr, size_t& size, T newElement);

    template <typename T>
    void swap(T& a, T& b);
}

