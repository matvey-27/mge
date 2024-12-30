// нужно добавить алгоритм как там https://gist.github.com/vurtun/29727217c269a2fbf4c0ed9a1d11cb40
//     для колизий 
// нужно добавить vulkan
// засунуть все в динамическую библиотеку 

#include "../include/GraphicsLibrarry/libs.h"
#include "../include/MGE/Utils.hpp"
#include "../include/GraphicsLibrarry/RgbColor.h"
#include <thread>

// тест vec2 (если все работает -> движок)
namespace mge {
    template <typename T>
    class vec2{
    public:
        T x, y;
        T w = 0;
        
        vec2() : x(0), y(0) {};
        vec2(T x, T y) : x(x), y(y) {};
        ~vec2() = default;
    };
}

// тест функций отрисовки с rgbcolor (если все работает -> движок)
namespace mge {
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
        delete[] values;
    }

    void DrawLine(void (*PutPixel)(int x, int y, RgbColor color), vec2<int> P0, vec2<int> P1, RgbColor color) {
        int dx = P1.x - P0.x;
        int dy = P1.y - P0.y;

        if (abs(dx) > abs(dy)) {
            if (P0.x > P1.x) {
                my_fun::swap(P0, P1);
            }

            int size;
            int* ys = interpolated(P0.x, P0.y, P1.x, P1.y, size);

            for (int x = P0.x; x <= P1.x; ++x) {
                int i = x - P0.x;
                PutPixel(x, ys[i], color);
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
                PutPixel(xs[i], y, color);
            }

            delete[] xs; // Освобождаем память
        }
    }

    void DrawWireframeTringle(void (*PutPixel)(int x, int y, RgbColor color), vec2<int> P0, vec2<int> P1, vec2<int> P2, RgbColor color)
    {
        DrawLine(PutPixel, P0, P1, color);
        DrawLine(PutPixel, P1, P2, color);
        DrawLine(PutPixel, P2, P0, color);

    }

    void DrawCircle(void (*PutPixel)(int x, int y, RgbColor color), int centerX, int centerY, int radius, RgbColor color) {
        for (int angle = 0; angle < 360; angle++) {
            int x = centerX + static_cast<int>(radius * cos(angle * 3.14159 / 180));
            int y = centerY + static_cast<int>(radius * sin(angle * 3.14159 / 180));
            PutPixel(x, y, color);  // Рисуем каждый пиксель круга
        }
    }
}

// тест функций отрисовки без rgbcolor (если все работает -> движок)
namespace mge {
    void DrawLine(void (*PutPixel)(int x, int y, int r, int g, int b), vec2<int> P0, vec2<int> P1, int color_r, int color_g, int color_b) {
        int dx = P1.x - P0.x;
        int dy = P1.y - P0.y;

        if (abs(dx) > abs(dy)) {
            if (P0.x > P1.x) {
                my_fun::swap(P0, P1);
            }

            int size;
            int* ys = interpolated(P0.x, P0.y, P1.x, P1.y, size);

            for (int x = P0.x; x <= P1.x; ++x) {
                int i = x - P0.x;
                PutPixel(x, ys[i], color_r, color_g, color_b);
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
                PutPixel(xs[i], y, color_r, color_g, color_b);
            }

            delete[] xs; // Освобождаем память
        }
    }

    void DrawWireframeTringle(void (*PutPixel)(int x, int y, int r, int g, int b), vec2<int> P0, vec2<int> P1, vec2<int> P2, int color_r, int color_g, int color_b)
    {
        DrawLine(PutPixel, P0, P1, color_r, color_g, color_b);
        DrawLine(PutPixel, P1, P2, color_r, color_g, color_b);
        DrawLine(PutPixel, P2, P0, color_r, color_g, color_b);

    }

    void DrawCircle(void (*PutPixel)(int x, int y, int r, int g, int b), int centerX, int centerY, int radius, int color_r, int color_g, int color_b) {
        for (int angle = 0; angle < 360; angle++) {
            int x = centerX + static_cast<int>(radius * cos(angle * 3.14159 / 180));
            int y = centerY + static_cast<int>(radius * sin(angle * 3.14159 / 180));
            PutPixel(x, y, color_r, color_g, color_b);  // Рисуем каждый пиксель круга
        }
    }
}


int main() {
    InitializeWindow(500, 500);

    while (IsWindowOpen()) {
        ClearScreen(0, 255, 0);

        mge::DrawCircle(DrawPixel,  0,  0,  50, 50, 50, 50);

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Задержка для снижения нагрузки на CPU
    }

    return 0; // Завершаем программу
}