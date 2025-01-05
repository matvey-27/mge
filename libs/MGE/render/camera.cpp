#include "../../../Include/MGE/render/camera.h"

namespace mge {
    void camera::updateVectors() {
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
            { 1 / (aspect * std::tan(FOVy * (mge::M_PI / 360.0f) / 2)), 0, 0, 0 },
            { 0, 1 / std::tan(FOVy * (mge::M_PI / 360.0f) / 2), 0, 0 },
            { 0, 0, -1 * (zFar + zNear) / (zFar - zNear), -1},
            { 0, 0, -1 * (2 * zFar * zNear) / (zFar - zNear), 0}
        };

        this->projection_matrix = mat4x4<float>(projection_matrix);
    }

    

    // конструктор по высоте и ширине
    camera::camera(float w, float h, vec3<float> pos, vec3<float> target, vec3<float> up) : aspect(w / h), pos(pos), target(target), up(up) {
        updateVectors();
    };

    // конструктор по высоте, ширине и углу обзора
    camera::camera(float w, float h, float FOVy, vec3<float> pos, vec3<float> target, vec3<float> up) : aspect(w / h), FOVy(FOVy), pos(pos), target(target), up(up) {
        updateVectors();
    };

    // конструктор по высоте, ширинеи буверам z
    camera::camera(float w, float h, float zNear, float zFar, vec3<float> pos, vec3<float> target, vec3<float> up) : aspect(w / h), zNear(zNear), zFar(zFar), pos(pos), target(target), up(up) {
        updateVectors();
    };

    // конструктор по высоте, ширине, полю зрения и z буферам
    camera::camera(float w, float h, float FOVy, float zNear, float zFar, vec3<float> pos, vec3<float> target, vec3<float> up) : aspect(w / h), FOVy(FOVy), zNear(zNear), zFar(zFar), pos(pos), target(target), up(up) {
        updateVectors();
    };

    void camera::updateMatrix(vec3<float> pos, vec3<float> target, vec3<float> up) {
        this->pos = pos;
        this->target = target;
        this->up = up;

        updateVectors();
    }

    void camera::updateTargetMatrix(vec3<float> newTarget) {
        updateMatrix(pos, newTarget);
    }

    vec2<int> camera::renderVertices(vec3<float> v) {
        v = view_matrix * v;
        v = projection_matrix * v;
        return vec2<int>(
            (int)(v.x / v.w),
            (int)(v.y / v.w));
    };

    void camera::RenderModel(void (*PutPixel)(int x, int y, int r, int g, int b), Model model) {
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
    void camera::rotatePosCameraAroundPoint(float ax_deg, float ay_deg, float az_deg, vec3<float> rotationPoint) {
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

    void camera::setPos(vec3<float> v) {
        pos = v;
    }

    void camera::move(vec3<float> v) {
        pos = pos + v;
    }
}