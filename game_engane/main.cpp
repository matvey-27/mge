#include"main.h"

// НУЖНО СДЕЛАТЬ КЛАСС ТРЕУГОЛЬНИКОВ и исправить функции и классы RenderTriengle() RenderObject() Model()
Point2D<int> ViewportToCanvas(Point2D<int> p, int d = 1, int Cw = 800, int Vw = 800, int Ch = 600, int Vh = 600) {
    return Point2D<int>(p.x * Cw/Vw, p.y * Ch/Vh);
}

Point2D<int> ProjectVertex(Point3D<int> v, int d = 200){
    return ViewportToCanvas(Point2D<int>(v.x * d / v.z, v.y * d / v.z), d);
}

void RenderTriengle(Canvas& canvas, Point3D<int> triangle, Point2D<int>* project) {
    DrawWireframeTringle(canvas,
                        project[triangle.x],
                        project[triangle.y],
                        project[triangle.z]);
}

void RenderObject(Canvas& canvas, Model& model) {
    Point2D<int>* projected = new Point2D<int>[0];
    int size = 0;

    for (int i = 0; i < model.getVertexCount(); i++) {
        addElement(projected, size, ProjectVertex(model.getVertex(i)));
    }

    for (int i = 0; i < model.getTrianglsCount(); i++) {
        RenderTriengle(canvas, model.getTriangls(i), projected);
    }
    
    delete[] projected;
}


//void DrawExample(Canvas& canvas) {
//    // 4 пердених вершины
//    Point3D<int> vAf(-1, 1, 1);
//    Point3D<int> vBf(1, 1, 1);
//    Point3D<int> vCf(1, -1, 1);
//    Point3D<int> vDf(-1, -1, 1);
//
//    // 4 задних вершины
//    Point3D<int> vAb(-1, 1, 2);
//    Point3D<int> vBb(1, 1, 2);
//    Point3D<int> vCb(1, -1, 2);
//    Point3D<int> vDb(-1, -1, 2);
//
//    DrawLine(canvas, ProjectVertex(vAf), ProjectVertex(vBf));
//    DrawLine(canvas, ProjectVertex(vBf), ProjectVertex(vCf));
//    DrawLine(canvas, ProjectVertex(vCf), ProjectVertex(vDf));
//    DrawLine(canvas, ProjectVertex(vDf), ProjectVertex(vAf));
//
//    DrawLine(canvas, ProjectVertex(vAb), ProjectVertex(vBb));
//    DrawLine(canvas, ProjectVertex(vBb), ProjectVertex(vCb));
//    DrawLine(canvas, ProjectVertex(vCb), ProjectVertex(vDb));
//    DrawLine(canvas, ProjectVertex(vDb), ProjectVertex(vAb));
//
//    DrawLine(canvas, ProjectVertex(vAb), ProjectVertex(vAf));
//    DrawLine(canvas, ProjectVertex(vBb), ProjectVertex(vBf));
//    DrawLine(canvas, ProjectVertex(vCb), ProjectVertex(vCf));
//    DrawLine(canvas, ProjectVertex(vDb), ProjectVertex(vDf));
//}

void DrawExample(Canvas& canvas) {
    Point3D<int> vertices[8] = {
        Point3D<int>(1, 1, 1),   // Вершина 0
        Point3D<int>(-1, 1, 1),  // Вершина 1
        Point3D<int>(-1, -1, 1), // Вершина 2
        Point3D<int>(1, -1, 1),  // Вершина 3
        Point3D<int>(1, 1, -1),  // Вершина 4
        Point3D<int>(-1, 1, -1), // Вершина 5
        Point3D<int>(-1, -1, -1),// Вершина 6
        Point3D<int>(1, -1, -1)  // Вершина 7
    };

    Point3D<int> triangles[12] = {
        Point3D<int>(0, 1, 2), // Передняя гра грань 0
        Point3D<int>(0, 2, 3), // Передняя гра грань 1
        Point3D<int>(4, 5, 6), // Задняя гра грани 0
        Point3D<int>(4, 6, 7), // Задняя гра грани 1
        Point3D<int>(1, 5, 6), // Левый грань 0
        Point3D<int>(1, 6, 2), // Левый грань 1
        Point3D<int>(0, 4, 7), // Правый грань 0
        Point3D<int>(0, 7, 3), // Правый грань 1
        Point3D<int>(4, 5, 1), // Верхний грань 0
        Point3D<int>(4, 1, 0), // Верхний грань 1
        Point3D<int>(2, 6, 7), // Нижний грань 0
        Point3D<int>(2, 7, 3)  // Нижний грань 1
    };

    Model cube(vertices, 8, triangles, 12);

    cube.translate(Vector3D<int>(-5, 0, 5));

    RenderObject(canvas, cube);
}

// Главная функция
int main() {
    Canvas canvas(800, 600, L"hello world"); // Передаем платформенный класс в Canvas
    canvas.Run(DrawExample, 600); // Запускаем отрисовку
    return 0; // Завершаем программу
}
