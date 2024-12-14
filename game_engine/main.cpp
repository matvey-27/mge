#include <cmath>
#include "math/Vector.h"
#include "math/Point.h"
#include "render/RenderUtils.h"
#include "render/Model.h"
#include "canvas/canvas.h"
#include "Utils.h"

using namespace std;
using namespace math;
using namespace my_fun;
using namespace canvas;


void DrawExample(Canvas& canvas) {
    Point3D<float> vertices[8] = {
        Point3D<float>(1, 1, 1),   // Вершина 0
        Point3D<float>(-1, 1, 1),  // Вершина 1
        Point3D<float>(-1, -1, 1), // Вершина 2
        Point3D<float>(1, -1, 1),  // Вершина 3
        Point3D<float>(1, 1, -1),  // Вершина 4
        Point3D<float>(-1, 1, -1), // Вершина 5
        Point3D<float>(-1, -1, -1),// Вершина 6
        Point3D<float>(1, -1, -1)  // Вершина 7
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

    if (canvas.safe_data == 100) {
        canvas.safe_data = 50;
    }
    else {
        canvas.safe_data += 1;
    }
    
    int a = canvas.safe_data;

    cube.translate(Vector3D<float>(0, 0, 5));

    RenderObject(canvas, cube, a);

    Sleep(1000);
}


// Главная функция
int main() {
    Canvas canvas(800, 600, L"hello world"); // Передаем платформенный класс в Canvas
    canvas.Run(DrawExample, 600); // Запускаем отрисовку
    return 0; // Завершаем программу
}
