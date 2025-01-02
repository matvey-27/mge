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
        // »нициализаци€ переменных
        float width;        // Ўирина окна
        float height;       // ¬ысота окна
        float FOVy = 45.0f * (M_PI / 180.0f); // ѕеревод ‘ќ¬ в радианы

        float zNear = 0.1f;          // Ѕлижн€€ плоскость
        float zFar = 100.0f;        // ƒальн€€ плоскость
        float aspect;

        // - f: Ќаправл€ющий вектор, указывающий направление взгл€да камеры.
        // - s: ¬ектор направлени€ вправо, который определ€ет горизонтальную ориентацию камеры.
        // - u: ¬ектор, определ€ющий направление вверх дл€ камеры, основанный на векторах f и s.

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
        // - pos: ѕозици€ камеры в мировом пространстве.
        // - target: “очка, на которую ориентирована камера (например, объект, который мы хотим видеть).
        // - up: ¬ектор "вверх", который определ€ет, что считаетс€ "верхом" дл€ камеры (обычно вектор (0, 1, 0) дл€ стандартной ориентации).

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

        // конструктор по высоте, ширине, полю зрени€ и z буферам
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
        // поворот позиции не измен€€ напровление 
        void rotatePosCameraAroundPoint(float ax_deg, float ay_deg, float az_deg, vec3<float> rotationPoint = vec3<float>(0, 0, 0)) {
            // ѕреобразование углов из градусов в радианы
            float ax = ax_deg * (M_PI / 180.0f);
            float ay = ay_deg * (M_PI / 180.0f);
            float az = az_deg * (M_PI / 180.0f);

            // 1. ѕеремещаем камеру в систему координат, где точка вращени€ в начале (центр вращени€ - это точка)
            vec3<float> localPos = pos - rotationPoint;

            // 2. ћатрицы вращени€ по ос€м X, Y, Z
            // ћатрица дл€ вращени€ по X
            float rotationMatrixX[4][4] = {
                { 1,         0,          0, 0 },
                { 0, std::cos(ax), -std::sin(ax),  0 },
                { 0, std::sin(ax),  std::cos(ax),  0 },
                { 0,         0,          0, 1 }
            };
            mat4x4<float> rx(rotationMatrixX);

            // ћатрица дл€ вращени€ по Y
            float rotationMatrixY[4][4] = {
                { std::cos(ay),  0, std::sin(ay), 0 },
                { 0,        1, 0,       0 },
                { -std::sin(ay), 0, std::cos(ay), 0 },
                { 0,        0, 0,       1 }
            };
            mat4x4<float> ry(rotationMatrixY);

            // ћатрица дл€ вращени€ по Z
            float rotationMatrixZ[4][4] = {
                { std::cos(az), -std::sin(az), 0, 0 },
                { std::sin(az),  std::cos(az), 0, 0 },
                { 0,        0,       1, 0 },
                { 0,        0,       0, 1 }
            };
            mat4x4<float> rz(rotationMatrixZ);

            // 3. ѕримен€ем вращение к позиции камеры (поочередно примен€ем матрицы вращени€)
            localPos = rx * localPos;
            localPos = ry * localPos;
            localPos = rz * localPos;

            // 4. ¬озвращаем камеру обратно в исходную систему координат
            pos = localPos + rotationPoint;

            // 5. ќбновл€ем вектора ориентации камеры
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