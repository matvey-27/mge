#include <iostream>
#include <windows.h>
#include "math/math.h"
#include "canvas/canvas.h"


namespace math {
    // переместить в /math
    template <typename T>
    T abs(T value) {
        return (value < 0) ? -value : value; // Возвращаем положительное значение
    }
}

namespace my_fun {
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

    template <typename T>
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }
}

using namespace std;
using namespace math;
using namespace my_fun;
// namespace canvas;

int* interpolated(int i0, int d0, int i1, int d1, int& size) {
    size = abs(i1 - i0) + 1; // Количество интерполированных значений
    int* values = new int[size]; // Создаем массив нужного размера

    // Проверяем, если i0 равно i1
    if (i0 == i1) {
        values[0] = d0; // Добавляем d0 в массив
    }
    else {
        int delta = d1 - d0;
        for (int i = 0; i < size; ++i) {
            values[i] = d0 + (delta * i) / (i1 - i0); // Линейная интерполяция
        }
    }

    return values; // Возвращаем массив
}

void DrawLine(Canvas canvas, point_2D<int> P0, point_2D<int> P1, COLORREF color = RGB(0, 0, 0)) {
    int dx = P1.x - P0.x;
    int dy = P1.y - P0.y;

    if (std::abs(dx) > abs(dy)) {
        if (P0.x > P1.x) {
            my_fun::swap(P0, P1);
        }

        int size;
        int* ys = interpolated(P0.x, P0.y, P1.x, P1.y, size);

        for (int x = P0.x; x <= P1.x; ++x) {
            int i = x - P0.x;
            canvas.PutPixel(x, ys[i], color);
        }

        delete[] ys; // Освобождаем память
    }
    else {
        if (P0.y > P1.y) {
            my_fun::swap(P0, P1);
        }

        int size;
        int* xs = interpolated(P0.y, P0.x, P1.y, P1.x, size);

        for (int y = P0.y; y <= P1.y; ++y) {
            int i = y - P0.y;
            canvas.PutPixel(xs[i], y, color);
        }

        delete[] xs; // Освобождаем память
    }
}

void DrawWireframeTringle(Canvas canvas, point_2D<int> P0, point_2D<int> P1, point_2D<int> P2, COLORREF color = RGB(0, 0, 0))
{
    DrawLine(canvas, P0, P1, color);
    DrawLine(canvas, P1, P2, color);
    DrawLine(canvas, P2, P0, color);

}

void DrawCircle(Canvas canvas, int centerX, int centerY, int radius, COLORREF color = RGB(0, 0, 0)) {
    for (int angle = 0; angle < 360; angle++) {
        int x = centerX + static_cast<int>(radius * cos(angle * 3.14159 / 180));
        int y = centerY + static_cast<int>(radius * sin(angle * 3.14159 / 180));
        canvas.PutPixel(x, y, color);  // Рисуем каждый пиксель круга
    }
}



// Глобальная функция для отрисовки
void DrawExample(Canvas& canvas) {
    static int angle = 0;
    int centerX = 200;
    int centerY = 150;
    int radius = 50;

    DrawCircle(canvas, centerX, centerY, radius, RGB(0, 255, 0));
    angle = (angle + 5) % 360;

    DrawWireframeTringle(
        canvas,
        point_2D<int>(14, 124),
        point_2D<int>(51, 14),
        point_2D<int>(189, 14)
    );
}

// Главная функция
int main() {
#ifdef _WIN32
    WindowsCanvas* platformCanvas = new WindowsCanvas();
#elif __linux__
    LinuxCanvas* platformCanvas = new LinuxCanvas();
#endif

    Canvas canvas(platformCanvas); // Передаем платформенный класс в Canvas
    canvas.Run(DrawExample, 600); // Запускаем отрисовку
    delete platformCanvas; // Освобождаем память
    return 0; // Завершаем программу
}
