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


        void updateVectors() {
            f = (target - pos).normalize();
            f.w = 0;

            s = (up * f).normalize();
            s.w = 0;

            u = f * s;
            u.w = 0;


            float view_matrix[4][4] = {
                {s.x, s.y, s.z, -dot(s, pos)},
                {u.x, u.y, u.z, -dot(u, pos)},
                {-f.x, -f.y, -f.z, dot(f, pos)},
                {0, 0, 0, 1}
            };

            this->view_matrix = mat4x4<float>(view_matrix);

            float projection_matrix[4][4] = {
                { 1 / (aspect * std::tan(FOVy / 2)), 0, 0, 0 },
                { 0, 1 / std::tan(FOVy / 2), 0, 0 },
                { 0, 0, -1 * (zFar + zNear) / (zFar - zNear), -1},
                { 0, 0, -1 * (2 * zFar * zNear) / (zFar - zNear), 0}
            };

            this->projection_matrix = mat4x4<float>(projection_matrix);
        }

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
        camera(float w, float h, vec3<float> pos = vec3<float>(0, 0, 0), vec3<float> target = vec3<float>(0, 0, -1), vec3<float> up = vec3<float>(0, 1, 0, 0)) : aspect(w / h), pos(pos), target(target), up(up) {
            updateVectors();
        };

        // конструктор по высоте, ширине и углу обзора
        camera(float w, float h, float FOVy, vec3<float> pos = vec3<float>(0, 0, 0), vec3<float> target = vec3<float>(0, 0, -1), vec3<float> up = vec3<float>(0, 1, 0)) : aspect(w / h), FOVy(FOVy), pos(pos), target(target), up(up) {
            updateVectors();
        };

        // конструктор по высоте, ширинеи буверам z
        camera(float w, float h, float zNear, float zFar, vec3<float> pos = vec3<float>(0, 0, 0), vec3<float> target = vec3<float>(0, 0, -1), vec3<float> up = vec3<float>(0, 1, 0)) : aspect(w / h), zNear(zNear), zFar(zFar), pos(pos), target(target), up(up) {
            updateVectors();
        };

        // конструктор по высоте, ширине, полю зрения и z буферам
        camera(float w, float h, float FOVy, float zNear, float zFar, vec3<float> pos = vec3<float>(0, 0, 0), vec3<float> target = vec3<float>(0, 0, 0), vec3<float> up = vec3<float>(0, 1, 0)) : aspect(w / h), FOVy(FOVy), zNear(zNear), zFar(zFar), pos(pos), target(target), up(up) {
            updateVectors();
        };

        void updateMatrix(vec3<float> pos = vec3<float>(0, 0, 0), vec3<float> target = vec3<float>(0, 0, -1), vec3<float> up = vec3<float>(0, 1, 0)) {
            this->pos = pos;
            this->target = target;
            this->up = up;

            updateVectors();
        }

        void updateTargetMatrix(vec3<float> newTarget) {
            updateMatrix(pos, newTarget);
        }

        vec2<int> renderVertices(vec3<float> v) {
            v = view_matrix * v;
            v = projection_matrix * v;
            return vec2<int>(
                (int)(v.x / v.w),
                (int)(v.y / v.w));
        };

        void RenderModel(void (*PutPixel)(int x, int y, int r, int g, int b), Model model) {
            for (int i = 0; i < model.getTrianglsCount(); i++) {
                mge::DrawFilledTriangle(PutPixel,
                    renderVertices(model.getVertex(model.getTriangls(i).n1)),
                    renderVertices(model.getVertex(model.getTriangls(i).n2)),
                    renderVertices(model.getVertex(model.getTriangls(i).n3)), model.getTriangls(i).r, model.getTriangls(i).g, model.getTriangls(i).b);
                mge::DrawWireframeTringle(PutPixel,
                    renderVertices(model.getVertex(model.getTriangls(i).n1)),
                    renderVertices(model.getVertex(model.getTriangls(i).n2)),
                    renderVertices(model.getVertex(model.getTriangls(i).n3)));
            }
        }
        // поворот позиции не изменяя напровление 
        void rotatePosCameraAroundPoint(float ax_deg, float ay_deg, float az_deg, vec3<float> rotationPoint = vec3<float>(0, 0, 0)) {
            // Преобразование углов из градусов в радианы
            float ax = ax_deg * (M_PI / 180.0f);
            float ay = ay_deg * (M_PI / 180.0f);
            float az = az_deg * (M_PI / 180.0f);

            // 1. Перемещаем камеру в систему координат, где точка вращения в начале (центр вращения - это точка)
            vec3<float> localPos = pos - rotationPoint;

            // 2. Матрицы вращения по осям X, Y, Z
            // Матрица для вращения по X
            float rotationMatrixX[4][4] = {
                { 1,         0,          0, 0 },
                { 0, std::cos(ax), -std::sin(ax),  0 },
                { 0, std::sin(ax),  std::cos(ax),  0 },
                { 0,         0,          0, 1 }
            };
            mat4x4<float> rx(rotationMatrixX);

            // Матрица для вращения по Y
            float rotationMatrixY[4][4] = {
                { std::cos(ay),  0, std::sin(ay), 0 },
                { 0,        1, 0,       0 },
                { -std::sin(ay), 0, std::cos(ay), 0 },
                { 0,        0, 0,       1 }
            };
            mat4x4<float> ry(rotationMatrixY);

            // Матрица для вращения по Z
            float rotationMatrixZ[4][4] = {
                { std::cos(az), -std::sin(az), 0, 0 },
                { std::sin(az),  std::cos(az), 0, 0 },
                { 0,        0,       1, 0 },
                { 0,        0,       0, 1 }
            };
            mat4x4<float> rz(rotationMatrixZ);

            // 3. Применяем вращение к позиции камеры (поочередно применяем матрицы вращения)
            localPos = rx * localPos;
            localPos = ry * localPos;
            localPos = rz * localPos;

            // 4. Возвращаем камеру обратно в исходную систему координат
            pos = localPos + rotationPoint;

            // 5. Обновляем вектора ориентации камеры
            updateVectors();
        }

        void setPos(vec3<float> v) {
            pos = v;
        }

        void move(vec3<float> v) {
            pos = pos + v;
        }

    };
}