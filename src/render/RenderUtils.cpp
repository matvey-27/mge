#include"RenderUtils.h"

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

void DrawLine(void (*PutPixel)(int x, int y, RgbColor color), Point2D<int> P0, Point2D<int> P1, RgbColor color) {
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

void DrawWireframeTringle(void (*PutPixel)(int x, int y, RgbColor color), Point2D<int> P0, Point2D<int> P1, Point2D<int> P2, RgbColor color)
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

Point2D<int> ViewportToCanvas(Point2D<float> p, float Cw, float Vw, float Ch, float Vh) {
    return Point2D<int>((int)(p.x * Cw / Vw), (int)(p.y * Ch / Vh));
}

Point2D<int> ProjectVertex(Point3D<float> v, float d) {
    return ViewportToCanvas(Point2D<float>(v.x * d / v.z, v.y * d / v.z));
}

void RenderTriengle(void (*PutPixel)(int x, int y, RgbColor color), Point3D<int> triangle, Point2D<int>* project) {
    DrawWireframeTringle(PutPixel,
        project[triangle.x],
        project[triangle.y],
        project[triangle.z]);
}

void RenderObject(void (*PutPixel)(int x, int y, RgbColor color), Model& model) {
    Point2D<int>* projected = new Point2D<int>[0];
    int size = 0;

    for (int i = 0; i < model.getVertexCount(); i++) {
        addElement(projected, size, ProjectVertex(model.getVertex(i)));
    }

    for (int i = 0; i < model.getTrianglsCount(); i++) {
        RenderTriengle(PutPixel, model.getTriangls(i), projected);
    }

    delete[] projected;
}