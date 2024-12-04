#include"main.h"

Point2D<int> ProjectVertex(Vector3D<int> v, int d = 150) {
    return Point2D<int>(v.x * d / v.z, v.y * d / v.z);
}

// Глобальная функция для отрисовки
//void DrawExample(Canvas& canvas) {
//    static int angle = 0;
//    int centerX = 200;
//    int centerY = 150;
//    int radius = 50;
//
//    DrawCircle(canvas, centerX, centerY, radius, rgb_color(0, 0, 0));
//    angle = (angle + 5) % 360;
//
//    DrawWireframeTringle(
//        canvas,
//        Point2D<int>(14, 124),
//        Point2D<int>(51, 14),
//        Point2D<int>(189, 14)
//    );
//}

void DrawExample(Canvas& canvas) {
    // 4 пердених вершины
    Vector3D<int> vAf(-1, 1, 1);
    Vector3D<int> vBf(1, 1, 1);
    Vector3D<int> vCf(1, -1, 1);
    Vector3D<int> vDf(-1, -1, 1);

    // 4 задних вершины
    Vector3D<int> vAb(-1, 1, 2);
    Vector3D<int> vBb(1, 1, 2);
    Vector3D<int> vCb(1, -1, 2);
    Vector3D<int> vDb(-1, -1, 2);

    DrawLine(canvas, ProjectVertex(vAf), ProjectVertex(vBf));
    DrawLine(canvas, ProjectVertex(vBf), ProjectVertex(vCf));
    DrawLine(canvas, ProjectVertex(vCf), ProjectVertex(vDf));
    DrawLine(canvas, ProjectVertex(vDf), ProjectVertex(vAf));

    DrawLine(canvas, ProjectVertex(vAb), ProjectVertex(vBb));
    DrawLine(canvas, ProjectVertex(vBb), ProjectVertex(vCb));
    DrawLine(canvas, ProjectVertex(vCb), ProjectVertex(vDb));
    DrawLine(canvas, ProjectVertex(vDb), ProjectVertex(vAb));

    DrawLine(canvas, ProjectVertex(vAb), ProjectVertex(vAf));
    DrawLine(canvas, ProjectVertex(vBb), ProjectVertex(vBf));
    DrawLine(canvas, ProjectVertex(vCb), ProjectVertex(vCf));
    DrawLine(canvas, ProjectVertex(vDb), ProjectVertex(vDf));
}

// Главная функция
int main() {
    Canvas canvas(800, 600, L"hello world"); // Передаем платформенный класс в Canvas
    canvas.Run(DrawExample, 600); // Запускаем отрисовку
    return 0; // Завершаем программу
}
