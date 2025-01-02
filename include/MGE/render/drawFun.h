#pragma once

#include "../math/vec2.h"
#include "../Utils.hpp"

namespace mge {
    int* interpolated(int i0, int d0, int i1, int d1, int& size) {
        // Проверка на то, что i0 и i1 разные
        if (i0 == i1) {
            size = 1;
            int* values = new int[size];
            values[0] = d0;  // Если индексы одинаковые, возвращаем одно значение
            return values;
        }

        size = abs(i1 - i0) + 1;  // Количество интерполированных значений
        if (size <= 0) {
            return nullptr;  // Невозможно интерполировать, если размер 0 или меньше
        }

        int* values = new int[size]; // Выделяем память для массива

        if (!values) {
            return nullptr; // Ошибка выделения памяти
        }

        // Если i0 не равно i1, выполняем интерполяцию
        int delta = d1 - d0;
        for (int i = 0; i < size; ++i) {
            values[i] = d0 + (delta * i + (i1 - i0) / 2) / (i1 - i0); // Линейная интерполяция с округлением
        }

        return values; // Возвращаем массив
    }

    void DrawLine(void (*PutPixel)(int x, int y, int r, int g, int b), vec2<int> P0, vec2<int> P1, int color_r, int color_g, int color_b) {
        int dx = P1.x - P0.x;
        int dy = P1.y - P0.y;

        if (abs(dx) > abs(dy)) {
            if (P0.x > P1.x) {
                swap(P0, P1);
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
                swap(P0, P1);
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

    void DrawWireframeTringle(void (*PutPixel)(int x, int y, int r, int g, int b), vec2<int> P0, vec2<int> P1, vec2<int> P2, int color_r = 0, int color_g = 0, int color_b = 0) {
        DrawLine(PutPixel, P0, P1, color_r, color_g, color_b);
        DrawLine(PutPixel, P1, P2, color_r, color_g, color_b);
        DrawLine(PutPixel, P2, P0, color_r, color_g, color_b);


    }

    bool IsInTriangle(vec2<int> a, vec2<int> b, vec2<int> c, vec2<int> p) {
        // Вычисляем значения для каждой стороны треугольника
        int d1 = (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x); // Относительно стороны AB
        int d2 = (c.x - b.x) * (p.y - b.y) - (c.y - b.y) * (p.x - b.x); // Относительно стороны BC
        int d3 = (a.x - c.x) * (p.y - c.y) - (a.y - c.y) * (p.x - c.x); // Относительно стороны CA

        // Возвращаем результат в одной строке
        return (d1 >= 0 && d2 >= 0 && d3 >= 0) || (d1 <= 0 && d2 <= 0 && d3 <= 0);
    }

    void DrawFilledTriangle(void (*PutPixel)(int x, int y, int r, int g, int b), vec2<int> P0, vec2<int> P1, vec2<int> P2, int color_r = 0, int color_g = 0, int color_b = 0) {
        vec2<int> box_min(std::min<int>({ P0.x, P1.x, P2.x }), std::min<int>({ P0.y, P1.y, P2.y }));
        vec2<int> box_max(std::max<int>({ P0.x, P1.x, P2.x }), std::max<int>({ P0.y, P1.y, P2.y }));

        for (int y = box_min.y; y <= box_max.y; ++y) {
            for (int x = box_min.x; x <= box_max.x; ++x) {
                vec2<int> p = { x, y };
                // Проверяем, находится ли пиксель внутри треугольника
                if (IsInTriangle(P0, P1, P2, p)) {
                    PutPixel(x, y, color_r, color_g, color_b); // Рисуем пиксель
                }
            }
        }
    }

    void DrawGradientTriangle(void (*PutPixel)(int x, int y, int r, int g, int b),
        vec2<int> P0, int C0_r, int C0_g, int C0_b,
        vec2<int> P1, int C1_r, int C1_g, int C1_b,
        vec2<int> P2, int C2_r, int C2_g, int C2_b) {
        vec2<int> box_min(std::min({ P0.x, P1.x, P2.x }), std::min({ P0.y, P1.y, P2.y }));
        vec2<int> box_max(std::max({ P0.x, P1.x, P2.x }), std::max({ P0.y, P1.y, P2.y }));

        for (int y = box_min.y; y <= box_max.y; ++y) {
            for (int x = box_min.x; x <= box_max.x; ++x) {
                vec2<int> p = { x, y };
                // Проверяем, находится ли пиксель внутри треугольника
                if (IsInTriangle(P0, P1, P2, p)) {
                    // Вычисляем весовые коэффициенты для интерполяции цвета
                    float areaTotal = 0.5f * (-P1.y * P2.x + P0.y * (-P1.x + P2.x) + P0.x * (P1.y - P2.y) + P1.x * P2.y);
                    float area0 = 0.5f * (-P1.y * P2.x + p.y * (-P1.x + P2.x) + p.x * (P1.y - P2.y) + P1.x * P2.y);
                    float area1 = 0.5f * (-p.y * P2.x + P0.y * (-p.x + P2.x) + P0.x * (p.y - P2.y) + p.x * P2.y);
                    float area2 = 0.5f * (-P1.y * p.x + P0.y * (-P1.x + p.x) + P0.x * (P1.y - p.y) + P1.x * p.y);

                    float alpha = area0 / areaTotal;
                    float beta = area1 / areaTotal;
                    float gamma = area2 / areaTotal;

                    // Интерполируем цвет
                    int interpolated_r = static_cast<int>(C0_r * alpha + C1_r * beta + C2_r * gamma);
                    int interpolated_g = static_cast<int>(C0_g * alpha + C1_g * beta + C2_g * gamma);
                    int interpolated_b = static_cast<int>(C0_b * alpha + C1_b * beta + C2_b * gamma);

                    // Рисуем пиксель
                    PutPixel(x, y, interpolated_r, interpolated_g, interpolated_b);
                }
            }
        }
    }

    void DrawCircle(void (*PutPixel)(int x, int y, int r, int g, int b), int centerX, int centerY, int radius, int color_r, int color_g, int color_b) {
        for (int angle = 0; angle < 360; angle++) {
            int x = centerX + static_cast<int>(radius * std::cos(angle * 3.14159 / 180));
            int y = centerY + static_cast<int>(radius * std::sin(angle * 3.14159 / 180));
            PutPixel(x, y, color_r, color_g, color_b);  // Рисуем каждый пиксель круга
        }
    }
}