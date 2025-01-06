#include "../include/GraphicsLibrarry/libs.h"
// #include "../include/MGE/Utils.hpp"

// #include "../include/MGE/math/vec2.hpp"
#include "../include/MGE/math/vec3.hpp"
#include "../include/MGE/math/tringles.hpp"

// #include "../include/MGE/render/drawFun.h"
#include "../include/MGE/render/model.h"
#include "../include/MGE/render/camera.h"

// #include <stdexcept>
#include <thread>
#include <iostream>
// #include <cmath>


int main() {
    InitializeWindow(800, 600);

    // Вершины куба
    mge::vec3<float> vertices[8] = {
        mge::vec3<float>(2, 2, 2),   // Вершина 0
        mge::vec3<float>(-2, 2, 2),  // Вершина 1
        mge::vec3<float>(-2, -2, 2), // Вершина 2
        mge::vec3<float>(2, -2, 2),  // Вершина 3
        mge::vec3<float>(2, 2, -2),  // Вершина 4
        mge::vec3<float>(-2, 2, -2), // Вершина 5
        mge::vec3<float>(-2, -2, -2),// Вершина 6
        mge::vec3<float>(2, -2, -2)  // Вершина 7
    };

    // Треугольники для построения куба
    mge::Triangles<int> triangles[12] = {
        mge::Triangles<int>{0, 1, 2, 50}, // Передняя грань 0
        mge::Triangles<int>{0, 2, 3, 50}, // Передняя грань 1
        mge::Triangles<int>{4, 5, 6, 50}, // Задняя грань 0
        mge::Triangles<int>{4, 6, 7, 50}, // Задняя грань 1
        mge::Triangles<int>{1, 5, 6, 50}, // Левый грань 0
        mge::Triangles<int>{1, 6, 2, 50}, // Левый грань 1
        mge::Triangles<int>{0, 4, 7, 50}, // Правый грань 0
        mge::Triangles<int>{0, 7, 3, 50}, // Правый грань 1
        mge::Triangles<int>{4, 5, 1, 50}, // Верхний грань 0
        mge::Triangles<int>{4, 1, 0, 50}, // Верхний грань 1
        mge::Triangles<int>{2, 6, 7}, // Нижний грань 0
        mge::Triangles<int>{2, 7, 3}  // Нижний грань 1
    };

    mge::Model cube(vertices, 8, triangles, 12);
    cube.move(mge::vec3<float>(0, 0, 0));

    // Инициализация камеры
    mge::camera cam(800, 600, 60.0f, 0.1f, 1000.0f, mge::vec3<float>(0, 0, -5), mge::vec3<float>(0, 0, 0), mge::vec3<float>(0, -1, 0));

    // Переменные для углов вращения камеры
    float i = 0.0f;

    while (IsWindowOpen()) {
        ClearScreen(0, 100, 100);

        cam.RenderModel(DrawPixel, cube);

        cam.updateTargetMatrix(mge::vec3<float>((float)GetMousePosXScreenToClient() / 80, (float)GetMousePosYScreenToClient() / -60, 0));
        if (GetStateKey(65)) cam.move(mge::vec3<float>(-0.11 + cam.target.normalize().x, 0, 0)); // a
        if (GetStateKey(68)) cam.move(mge::vec3<float>(0.11 + cam.target.normalize().x, 0, 0)); // d 
        if (GetStateKey(87)) cam.move(mge::vec3<float>(0, 0, 0.11 + cam.target.normalize().z)); // w 
        if (GetStateKey(83)) cam.move(mge::vec3<float>(0, 0, -0.11 + cam.target.normalize().z)); // s 
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << cube.getR() << "\n";

    std::cout << cube.getCenter().x << "\n";
    std::cout << cube.getCenter().y << "\n";
    std::cout << cube.getCenter().z << "\n";
    

    return 0; // Завершаем программу
}