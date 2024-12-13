#pragma once
#include <cmath>
#include "Model.h"
#include "../math/Vector.h"
#include "../math/Point.h"
#include "../canvas/windows/canvas.h"
#include "../Utils.h"

using namespace std;
using namespace math;
using namespace my_fun;
using namespace canvas;

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

// отрисовка линиц
void DrawLine(Canvas canvas, Point2D<int> P0, Point2D<int> P1, rgb_color color = rgb_color(0, 0, 0)) {
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

// отрисовка пустого треугольника 
void DrawWireframeTringle(Canvas canvas, Point2D<int> P0, Point2D<int> P1, Point2D<int> P2, rgb_color color = rgb_color(0, 0, 0))
{
    DrawLine(canvas, P0, P1, color);
    DrawLine(canvas, P1, P2, color);
    DrawLine(canvas, P2, P0, color);

}

// отрисовка круга
void DrawCircle(Canvas canvas, int centerX, int centerY, int radius, rgb_color color = rgb_color(0, 0, 0)) {
    for (int angle = 0; angle < 360; angle++) {
        int x = centerX + static_cast<int>(radius * cos(angle * 3.14159 / 180));
        int y = centerY + static_cast<int>(radius * sin(angle * 3.14159 / 180));
        canvas.PutPixel(x, y, color);  // Рисуем каждый пиксель круга
    }
}

template <typename T>
Vector3D<T> move(Vector3D<T>, float a) {
};
template <typename T>
Point3D<T> rotateX(Point3D<T> p, float a) {


    float mx1[3]{ 1, 0, 0 }; // 1st row
    float mx2[3]{ 0, cos(a), -sin(a) }; // 2nd row
    float mx3[3]{ 0, sin(a), cos(a) }; // 3rd row

    return Point3D<T>(
        p.x * mx1[0] + p.y * mx1[1] + p.z * mx1[2], // x' = x  1 + y  0 + z  0
        p.x * mx2[0] + p.y * mx2[1] + p.z * mx2[2], // y' = x  0 + y  cos(a) + z  -sin(a)
        p.x * mx3[0] + p.y * mx3[1] + p.z * mx3[2]  // z' = x  0 + y  sin(a) + z  cos(a)
    );
}

// НУЖНО СДЕЛАТЬ КЛАСС ТРЕУГОЛЬНИКОВ и исправить функции и классы RenderTriengle() RenderObject() Model()
Point2D<int> ViewportToCanvas(Point2D<float> p, int Cw = 800, int Vw = 800, int Ch = 600, int Vh = 600) {
    return Point2D<int>((int)p.x * Cw / Vw, (int)p.y * Ch / Vh);
}

Point2D<int> ProjectVertex(Point3D<float> v, float d = 150.0) {
    return ViewportToCanvas(Point2D<float>(v.x * d / v.z, v.y * d / v.z));
}

void RenderTriengle(Canvas& canvas, Point3D<int> triangle, Point2D<int>* project) {
    DrawWireframeTringle(canvas,
        project[triangle.x],
        project[triangle.y],
        project[triangle.z]);
}

void RenderObject(Canvas& canvas, Model& model, int a) {
    Point2D<int>* projected = new Point2D<int>[0];
    int size = 0;

    for (int i = 0; i < model.getVertexCount(); i++) {
        addElement(projected, size, ProjectVertex(rotateX(model.getVertex(i), a)));
    }

    for (int i = 0; i < model.getTrianglsCount(); i++) {
        RenderTriengle(canvas, model.getTriangls(i), projected);
    }

    delete[] projected;
}