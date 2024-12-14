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

void DrawLine(Canvas canvas, Point2D<int> P0, Point2D<int> P1, rgb_color color) {
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

void DrawWireframeTringle(Canvas canvas, Point2D<int> P0, Point2D<int> P1, Point2D<int> P2, rgb_color color)
{
    DrawLine(canvas, P0, P1, color);
    DrawLine(canvas, P1, P2, color);
    DrawLine(canvas, P2, P0, color);

}

void DrawCircle(Canvas canvas, int centerX, int centerY, int radius, rgb_color color) {
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


    float Rx[3][3] = {
    { 1,        0,         0 },
    { 0, cos(a), -sin(a) },
    { 0, sin(a),  cos(a) }
    };

    return Point3D<T>(
        p.x * Rx[0][0] + p.y * Rx[0][1] + p.z * Rx[0][2], // x' = x  1 + y  0 + z  0
        p.x * Rx[1][0] + p.y * Rx[1][1] + p.z * Rx[1][2], // y' = x  0 + y  cos(a) + z  -sin(a)
        p.x * Rx[2][0] + p.y * Rx[2][1] + p.z * Rx[2][2]  // z' = x  0 + y  sin(a) + z  cos(a)
    );
}

template <typename T>
Point3D<T> rotateY(Point3D<T> p, float a) {


    float Ry[3][3] = {
    { cos(a),  0, sin(a) },
    { 0,       1,       0 },
    { -sin(a), 0, cos(a) }
    };


    return Point3D<T>(
        p.x * Ry[0][0] + p.y * Ry[0][1] + p.z * Ry[0][2], // x' = x  1 + y  0 + z  0
        p.x * Ry[1][0] + p.y * Ry[1][1] + p.z * Ry[1][2], // y' = x  0 + y  cos(a) + z  -sin(a)
        p.x * Ry[2][0] + p.y * Ry[2][1] + p.z * Ry[2][2]  // z' = x  0 + y  sin(a) + z  cos(a)
    );
}

template <typename T>
Point3D<T> rotateZ(Point3D<T> p, float a) {


    float Rz[3][3] = {
    { cos(a), -sin(a), 0 },
    { sin(a),  cos(a), 0 },
    { 0,       0,      1 }
    };

    return Point3D<T>(
        p.x * Rz[0][0] + p.y * Rz[0][1] + p.z * Rz[0][2], // x' = x  1 + y  0 + z  0
        p.x * Rz[1][0] + p.y * Rz[1][1] + p.z * Rz[1][2], // y' = x  0 + y  cos(a) + z  -sin(a)
        p.x * Rz[2][0] + p.y * Rz[2][1] + p.z * Rz[2][2]  // z' = x  0 + y  sin(a) + z  cos(a)
    );
}

Point2D<int> ViewportToCanvas(Point2D<float> p, float Cw, float Vw, float Ch, float Vh) {
    return Point2D<int>((int)(p.x * Cw / Vw), (int)(p.y * Ch / Vh));
}

Point2D<int> ProjectVertex(Point3D<float> v, float d) {
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