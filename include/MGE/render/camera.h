#pragma once

#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../math/mat4x4.h"
#include "../math/tringles.hpp"

#include "drawFun.h"
#include "model.h"

#include "../Utils.hpp"

#include <stdexcept>
#include <cmath>

namespace mge {
    // https://rekovalev.site/3d-camera-basics/

    class camera {
    private:
        // Инициализация переменных
        float width;        // Ширина окна
        float height;       // Высота окна
        float FOVy = 60.0f * (M_PI / 380.0f); // Перевод ФОВ в радианы

        float zNear = 0.1f;          // Ближняя плоскость
        float zFar = 100.0f;        // Дальняя плоскость
        float aspect;

        // - f: Направляющий вектор, указывающий направление взгляда камеры.
        // - s: Вектор направления вправо, который определяет горизонтальную ориентацию камеры.
        // - u: Вектор, определяющий направление вверх для камеры, основанный на векторах f и s.

        vec3<float> f;
        vec3<float> s;
        vec3<float> u;


        void updateVectors();

    public:
        // - pos: Позиция камеры в мировом пространстве.
        // - target: Точка, на которую ориентирована камера (например, объект, который мы хотим видеть).
        // - up: Вектор "вверх", который определяет, что считается "верхом" для камеры (обычно вектор (0, 1, 0) для стандартной ориентации).

        vec3<float> target;
        vec3<float> pos;
        vec3<float> up;

        mat4x4<float> view_matrix;
        mat4x4<float> projection_matrix;

        // конструктор по высоте и ширине
        camera(float w, float h, vec3<float> pos = vec3<float>(0, 0, 0), vec3<float> target = vec3<float>(0, 0, -1), vec3<float> up = vec3<float>(0, 1, 0, 0));

        // конструктор по высоте, ширине и углу обзора
        camera(float w, float h, float FOVy, vec3<float> pos = vec3<float>(0, 0, 0), vec3<float> target = vec3<float>(0, 0, -1), vec3<float> up = vec3<float>(0, 1, 0));
        // конструктор по высоте, ширинеи буверам z
        camera(float w, float h, float zNear, float zFar, vec3<float> pos = vec3<float>(0, 0, 0), vec3<float> target = vec3<float>(0, 0, -1), vec3<float> up = vec3<float>(0, 1, 0));
        // конструктор по высоте, ширине, полю зрения и z буферам
        camera(float w, float h, float FOVy, float zNear, float zFar, vec3<float> pos = vec3<float>(0, 0, 0), vec3<float> target = vec3<float>(0, 0, 0), vec3<float> up = vec3<float>(0, 1, 0));

        void updateMatrix(vec3<float> pos = vec3<float>(0, 0, 0), vec3<float> target = vec3<float>(0, 0, -1), vec3<float> up = vec3<float>(0, 1, 0));

        void updateTargetMatrix(vec3<float> newTarget);

        vec2<int> renderVertices(vec3<float> v);

        void RenderModel(void (*PutPixel)(int x, int y, int r, int g, int b), Model model);

        // поворот позиции не изменяя напровление 
        void rotatePosCameraAroundPoint(float ax_deg, float ay_deg, float az_deg, vec3<float> rotationPoint = vec3<float>(0, 0, 0));

        void setPos(vec3<float> v);

        void move(vec3<float> v);
    };
}