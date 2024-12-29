#include "math/Vector.h"
#include "math/Point.h"
#include "render/RenderUtils.h"
#include "render/Model.h"
#include "libs.h"

// нужно добавить алгоритм как там https://gist.github.com/vurtun/29727217c269a2fbf4c0ed9a1d11cb40
//     для колизий 
// нужно добавить opengl
// засунуть все в динамическую библиотеку 

using namespace std;
using namespace math;
using namespace my_fun;

int main() {
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
    Model cube2(vertices, 8, triangles, 12);

    cube.move(Vector3D<float>(0, 2, 10));
    cube2.move(Vector3D<float>(0, -1, 10));

    cube2.rotate(0, 0, 1);

    InitializeWindow(1000, 1000);

    while (true) {

        ClearScreen(255, 255, 255);

        //cube2.move(Vector3D<float>(0, +0.1, 0));

        cube2.rotate(0, 1, 1);

        RenderObject(DrawPixel, cube2);

        RenderObject(DrawPixel, cube);

        cube2.PrintPosition();

        if (cube2.getPosition().x < 3) {
            cube2.move(Vector3D<float>(1, 0, 0));
        }
        else if (cube2.getPosition().x >= 3) {
            cube2.move(Vector3D<float>(-6, 0, 0));
        }
        //Sleep(100);
    }

    return 0; // Завершаем программу
}