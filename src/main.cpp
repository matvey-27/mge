// нужно добавить алгоритм как там https://gist.github.com/vurtun/29727217c269a2fbf4c0ed9a1d11cb40
//     для колизий 
// нужно добавить vulkan
// засунуть все в динамическую библиотеку 

#include "../include/GraphicsLibrarry/libs.h"
#include "../include/MGE/Utils.hpp"
#include "matrix.h"

#include <stdexcept>
#include <thread>
#include <cmath>

// тест vec2 (если все работает -> движок *("MGE/math/vec2")* )
namespace mge {
    template <typename T>
    class vec2 {
    public:
        T x, y, w;

        // Конструкторы
        vec2() : x(0), y(0), w(1) {}
        vec2(T x, T y, T w = 1) : x(x), y(y), w(w) {}
        ~vec2() = default;

        // Оператор сравнения на равенство
        bool operator==(const vec2& other) const {
            return x == other.x && y == other.y && w == other.w;
        }

        // Оператор неравенства
        bool operator!=(const vec2& other) const {
            return !(*this == other);
        }

        // Оператор сложения
        vec2 operator+(const vec2& other) const {
            return vec2(x + other.x, y + other.y, w + other.w);
        }

        // Оператор вычитания
        vec2 operator-(const vec2& other) const {
            return vec2(x - other.x, y - other.y, w - other.w);
        }

        // Оператор умножения (поэлементное умножение)
        vec2 operator*(const vec2& other) const {
            return vec2(x * other.x, y * other.y, w * other.w);
        }

        // Оператор деления (поэлементное деление)
        vec2 operator/(const vec2& other) const {
            return vec2(x / other.x, y / other.y, w / other.w);
        }

        // Оператор умножения на скаляр
        vec2 operator*(T scalar) const {
            return vec2(x * scalar, y * scalar, w * scalar);
        }

        // Оператор деления на скаляр
        vec2 operator/(T scalar) const {
            return vec2(x / scalar, y / scalar, w / scalar);
        }

        // Оператор присваивания
        vec2& operator=(const vec2& other) {
            if (this != &other) {
                x = other.x;
                y = other.y;
                w = other.w;
            }
            return *this;
        }

        // Оператор присваивания с добавлением
        vec2& operator+=(const vec2& other) {
            x += other.x;
            y += other.y;
            w += other.w;
            return *this;
        }

        // Оператор присваивания с вычитанием
        vec2& operator-=(const vec2& other) {
            x -= other.x;
            y -= other.y;
            w -= other.w;
            return *this;
        }

        // Индексатор для доступа к элементам (по индексу)
        T& operator[](size_t index) {
            if (index == 0) return x;
            if (index == 1) return y;
            return w; // Для индекса 2 вернем w
        }

        // Константный индексатор
        const T& operator[](size_t index) const {
            if (index == 0) return x;
            if (index == 1) return y;
            return w;
        }
    };

    template <typename T>
    T dot(vec2<T> vector1, vec2<T> vector2){
            return vector1.x * vector2.x + vector1.y * vector2.y;
    }
}
// тест vec3 (если все работает -> движок *("MGE/math/vec3")* )
namespace mge {
    template <typename T>
    class vec3 : public vec2<T>{
    public:
        T z;
        
        vec3() : vec2<T>::vec2(), z(0) {};
        vec3(T x, T y, T z, T w = 1): vec2<T>::vec2(x, y, w), z(z) {};
        ~vec3() = default;

        // оператор +=
        vec3<T>& operator+=(const vec3<T>& v) {
            this->x += v.x;
            this->y += v.y;
            this->z += v.z;
            return *this; // Возвращаем this
        }

        // оператор -
        vec3<T> operator-(vec3<T> p) {
            return vec3<T>(this->x - p.x, this->y - p.y, this->z - p.z);
        }

        // Оператор +  
        vec3<T> operator+(vec3<T> p) {
            return vec3<T>(this->x + p.x, this->y + p.y, this->z + p.z);
        }

        // Оператор * умнажение векторов (cross)
        vec3<T> operator*(const vec3<T>& other) const {
            return vec3<T>(
                this->y * other.z - this->z * other.y,  // Компонента x
                this->z * other.x - this->x * other.z,  // Компонента y
                this->x * other.y - this->y * other.x   // Компонента z
            );
        }

        // длина вектора
        T length() const {
            return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
        }

        // Метод для нормализации вектора
        vec3<T> normalize() const {
            T len = length();
            if (len == 0) {
                throw std::runtime_error("Cannot normalize a zero-length vector");
            }
            return vec3<T>(this->x / len, this->y / len, this->z / len);
        }
    };

    template <typename T>
    T dot(vec3<T> vector1, vec3<T> vector2){
            return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
    }
}
// тест mat4x4
namespace mge{
    template <typename T>
    class mat4x4
    {
    private:
        T matrix[4][4];
    public:
     mat4x4(){};

    mat4x4(T mx[4][4]) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                matrix[i][j] = mx[i][j];
            }
        }
    }

    mat4x4<T> operator +(mat4x4<T> mx) {
        T matrix_r[4][4];

        for (int i = 0; i <= 4; i++) {
            for (int f = 0; f <= 4; f++) {
                matrix_r[i][f] = matrix[i][f] + mx[i][f];
            }
        }
        return mat4x4(matrix_r);

    }

    vec3<T> operator *(vec3<T> v) {
        return vec3<T>(
            v.x * matrix[0][0] + v.y * matrix[0][1] + v.z * matrix[0][2] + v.w * matrix[0][3],
            v.x * matrix[1][0] + v.y * matrix[1][1] + v.z * matrix[1][2] + v.w * matrix[1][3],
            v.x * matrix[2][0] + v.y * matrix[2][1] + v.z * matrix[2][2] + v.w * matrix[2][3],
            v.x * matrix[3][0] + v.y * matrix[3][1] + v.z * matrix[3][2] + v.w * matrix[3][3]
        );
    }

    };
}
// #include <iostream>
// класс model 
namespace mge {
    // .h
    template <typename T>
    struct Triangles{
        T n1, n2, n3; 
        int r = 0, g = 0, b = 0; // color 
    };

    class Model{
    private:
        vec3<float> global_position = vec3<float>(0, 0, 0); // глобальная позиция позиция

        vec3<float>* vertices;
        size_t count_v; // Количество текущих вершин
        Triangles<int>* triangles;
        size_t count_t; // Количество текущих вершин
    public:
        Model() : vertices(new vec3<float>[0]), count_v(0), triangles(new Triangles<int>[0]), count_t(0) {};

        Model(vec3<float> vertices[], int count_v, Triangles<int> triangles[], int count_t);

        ~Model();

        Model(const Model& other);

        Model& operator=(const Model& other);

        // Метод для добавления новой вершины
        void addVertex(const vec3<float>& point);

        // Метод для получения количества вершин
        size_t getVertexCount() const;

        // Метод для доступа к вершине
        vec3<float>& getVertex(size_t index);

        // Метод для добавления новой треугольников
        void addTriangls(const Triangles<int>& point);

        // Метод для получения количества треугольников
        size_t getTrianglsCount();

        // Метод для доступа к треугольников
        Triangles<int>& getTriangls(size_t index);

        // передвижение
        void move(vec3<float> v);

        // -- вращение 
        void rotate(float ax, float ay, float az);
    };

    // .cpp
    Model::Model(vec3<float> vertices[], int count_v, Triangles<int> triangles[], int count_t) {
        this->count_v = count_v;
        this->count_t = count_t;

        this->vertices = new vec3<float>[count_v];
        for (size_t i = 0; i < count_v; ++i) {
            this->vertices[i] = vertices[i];
        }

        this->triangles = new Triangles<int>[count_t];
        for (size_t i = 0; i < count_t; ++i) {
            this->triangles[i] = triangles[i];
        }
    }

    Model::~Model() {
        delete[] vertices; // Освобождение памяти
        vertices = nullptr;

        delete[] triangles; // Освобождение памяти
        triangles = nullptr;
    }

    Model::Model(const Model& other) {
        count_v = other.count_v;
        count_t = other.count_t;
        vertices = new vec3<float>[count_v];
        for (size_t i = 0; i < count_v; ++i) {
            vertices[i] = other.vertices[i];
        }
        triangles = new Triangles<int>[count_t];
        for (size_t i = 0; i < count_t; ++i) {
            triangles[i] = other.triangles[i];
        }
    }

    Model& Model::operator=(const Model& other)
    {
        if (this != &other) {
            delete[] vertices;
            delete[] triangles;

            count_v = other.count_v;
            count_t = other.count_t;
            vertices = new vec3<float>[count_v];
            for (size_t i = 0; i < count_v; ++i) {
                vertices[i] = other.vertices[i];
            }
            triangles = new Triangles<int>[count_t];
            for (size_t i = 0; i < count_t; ++i) {
                triangles[i] = other.triangles[i];
            }
        }
        return *this;
    }


    // Метод для добавления новой вершины
    void Model::addVertex(const vec3<float>& point) {
        addElement(vertices, count_v, point);
    }

    // Метод для получения количества вершин
    size_t Model::getVertexCount() const {
        return count_v;
    }

    // Метод для доступа к вершине
    vec3<float>&  Model::getVertex(size_t index) {
        if (index >= count_v) {
            throw std::out_of_range("Index out of range");
        }
        return vertices[index];
    }

    // Метод для добавления новой треугольников
    void Model::addTriangls(const Triangles<int>& point) {
        addElement(triangles, count_t, point);
    }

    // Метод для получения количества треугольников
    size_t Model::getTrianglsCount()
    {
        return count_t;
    }

    // Метод для доступа к треугольников
    Triangles<int>& Model::getTriangls(size_t index) {
        if (index >= count_t) {
            throw std::out_of_range("Index out of range");
        }
        return triangles[index];
    }

    // Метод для перемещения 
    void Model::move(vec3<float> v) {
        global_position += v;

        for (size_t i = 0; i < count_v; i += 1) {
            vertices[i] += v;
        }
    }

    // Метод для вращения 
    void Model::rotate(float ax_deg, float ay_deg, float az_deg) {
        // Преобразование углов из градусов в радианы
        float ax = ax_deg * (M_PI / 180.0f);
        float ay = ay_deg * (M_PI / 180.0f);
        float az = az_deg * (M_PI / 180.0f);

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

        // Применение вращения к вершинам
        for (size_t i = 0; i < count_v; ++i) {
            // Применяем вращение по осям X, Y и Z последовательно
            vertices[i] = rz * (ry * (rx * (vertices[i] - global_position))) + global_position;
        }
    }
}
// !!! зависит от vec2 котоорый описан выше *("MGE/math/vec2")_vec2*
// тест функций отрисовки без rgbcolor (если все работает -> движок)
namespace mge {
    int* interpolated(int i0, int d0, int i1, int d1, int& size) {
        // Проверка на то, что i0 и i1 разные
        if (i0 == i1) {
            size = 1;
            int* values = new int[size];
            values[0] = d0;  // Если индексы одинаковые, возвращаем одно значение
            return values;
        }

        size = abs(i1 - i0) + 1;  // Количество интерполированных значений
        if (size <= 0) {
            return nullptr;  // Невозможно интерполировать, если размер 0 или меньше
        }

        int* values = new int[size]; // Выделяем память для массива

        if (!values) {
            return nullptr; // Ошибка выделения памяти
        }

        // Если i0 не равно i1, выполняем интерполяцию
        int delta = d1 - d0;
        for (int i = 0; i < size; ++i) {
            values[i] = d0 + (delta * i + (i1 - i0) / 2) / (i1 - i0); // Линейная интерполяция с округлением
        }

        return values; // Возвращаем массив
    }

    void DrawLine(void (*PutPixel)(int x, int y, int r, int g, int b), vec2<int> P0, vec2<int> P1, int color_r, int color_g, int color_b) {
        int dx = P1.x - P0.x;
        int dy = P1.y - P0.y;

        if (abs(dx) > abs(dy)) {
            if (P0.x > P1.x) {
                swap(P0, P1);
            }

            int size;
            int* ys = interpolated(P0.x, P0.y, P1.x, P1.y, size);

            for (int x = P0.x; x <= P1.x; ++x) {
                int i = x - P0.x;
                PutPixel(x, ys[i], color_r, color_g, color_b);
            }

            delete[] ys; // Освобождаем память
        }
        else {
            if (P0.y > P1.y) {
                swap(P0, P1);
            }

            int size;
            int* xs = interpolated(P0.y, P0.x, P1.y, P1.x, size);

            for (int y = P0.y; y <= P1.y; ++y) {
                int i = y - P0.y;
                PutPixel(xs[i], y, color_r, color_g, color_b);
            }

            delete[] xs; // Освобождаем память
        }
    }

    void DrawWireframeTringle(void (*PutPixel)(int x, int y, int r, int g, int b), vec2<int> P0, vec2<int> P1, vec2<int> P2, int color_r = 0, int color_g = 0, int color_b = 0){
        DrawLine(PutPixel, P0, P1, color_r, color_g, color_b);
        DrawLine(PutPixel, P1, P2, color_r, color_g, color_b);
        DrawLine(PutPixel, P2, P0, color_r, color_g, color_b);


    }

    bool IsInTriangle(vec2<int> a, vec2<int> b, vec2<int> c, vec2<int> p) {
        // Вычисляем значения для каждой стороны треугольника
        int d1 = (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x); // Относительно стороны AB
        int d2 = (c.x - b.x) * (p.y - b.y) - (c.y - b.y) * (p.x - b.x); // Относительно стороны BC
        int d3 = (a.x - c.x) * (p.y - c.y) - (a.y - c.y) * (p.x - c.x); // Относительно стороны CA

        // Возвращаем результат в одной строке
        return (d1 >= 0 && d2 >= 0 && d3 >= 0) || (d1 <= 0 && d2 <= 0 && d3 <= 0);
    }

    void DrawFilledTriangle(void (*PutPixel)(int x, int y, int r, int g, int b), vec2<int> P0, vec2<int> P1, vec2<int> P2, int color_r = 0, int color_g = 0, int color_b = 0) {
        vec2<int> box_min(std::min<int>({ P0.x, P1.x, P2.x }), std::min<int>({ P0.y, P1.y, P2.y }));
        vec2<int> box_max(std::max<int>({ P0.x, P1.x, P2.x }), std::max<int>({ P0.y, P1.y, P2.y }));

        for (int y = box_min.y; y <= box_max.y; ++y) {
            for (int x = box_min.x; x <= box_max.x; ++x) {
                vec2<int> p = { x, y };
                // Проверяем, находится ли пиксель внутри треугольника
                if (IsInTriangle(P0, P1, P2, p)) {
                    PutPixel(x, y, color_r, color_g, color_b); // Рисуем пиксель
                }
            }
        }
    }

    void DrawCircle(void (*PutPixel)(int x, int y, int r, int g, int b), int centerX, int centerY, int radius, int color_r, int color_g, int color_b) {
        for (int angle = 0; angle < 360; angle++) {
            int x = centerX + static_cast<int>(radius * std::cos(angle * 3.14159 / 180));
            int y = centerY + static_cast<int>(radius * std::sin(angle * 3.14159 / 180));
            PutPixel(x, y, color_r, color_g, color_b);  // Рисуем каждый пиксель круга
        }
    }
}
// функции рендеринга
namespace mge {
    vec2<int> ViewportToCanvas(vec2<float> p, float Cw = 500, float Vw = 1, float Ch = 500, float Vh = 1) {
        return vec2<int>((int)(p.x * Cw / Vw), (int)(p.y * Ch / Vh));
    }

    vec2<int> ProjectVertex(vec3<float> v, float d = 1) {
        return ViewportToCanvas(vec2<float>(v.x * d / v.z, v.y * d / v.z));
    }

    void RenderTriengle(void (*PutPixel)(int x, int y, int r, int g, int b), Triangles<int> triangle, vec2<int>* project) {
        DrawWireframeTringle(PutPixel,
            project[triangle.n1],
            project[triangle.n2],
            project[triangle.n3],
            triangle.r, triangle.g, triangle.b);
    }

    void RenderObject(void (*PutPixel)(int x, int y, int r, int g, int b), Model& model) {
        vec2<int>* projected = new vec2<int>[0];
        int size = 0;

        for (int i = 0; i < model.getVertexCount(); i++) {
            addElement(projected, size, ProjectVertex(model.getVertex(i)));
        }

        for (int i = 0; i < model.getTrianglsCount(); i++) {
            RenderTriengle(PutPixel, model.getTriangls(i), projected);
        }

        delete[] projected;
    }
}
// class camera
namespace mge {
    // https://rekovalev.site/3d-camera-basics/

    class camera{
    private:
        // Инициализация переменных
        float width;        // Ширина окна
        float height;       // Высота окна
        float FOVy = 45.0f * (M_PI / 180.0f); // Перевод ФОВ в радианы

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
                { 1 / (aspect * std::tan(FOVy/2)), 0, 0, 0 },
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
        camera(float w, float h, vec3<float> pos = vec3<float>(0, 0, 0), vec3<float> target = vec3<float>(0, 0, -1), vec3<float> up = vec3<float>(0, 1, 0, 0)) : aspect(w/h), pos(pos), target(target), up(up) {
            updateVectors();
        };
        
        // конструктор по высоте, ширине и углу обзора
        camera(float w, float h, float FOVy, vec3<float> pos = vec3<float>(0, 0, 0), vec3<float> target = vec3<float>(0, 0, -1), vec3<float> up = vec3<float>(0, 1, 0)) : aspect(w/h), FOVy(FOVy), pos(pos), target(target), up(up) {
            updateVectors();
        };

        // конструктор по высоте, ширинеи буверам z
        camera(float w, float h, float zNear, float zFar, vec3<float> pos = vec3<float>(0, 0, 0), vec3<float> target = vec3<float>(0, 0, -1), vec3<float> up = vec3<float>(0, 1, 0)) : aspect(w/h), zNear(zNear), zFar(zFar), pos(pos), target(target), up(up) {
            updateVectors();
        };

        // конструктор по высоте, ширине, полю зрения и z буферам
        camera(float w, float h, float FOVy, float zNear, float zFar, vec3<float> pos = vec3<float>(0, 0, 0), vec3<float> target = vec3<float>(0, 0,0), vec3<float> up = vec3<float>(0, 1, 0)) : aspect(w/h), FOVy(FOVy), zNear(zNear), zFar(zFar), pos(pos), target(target), up(up) {
            updateVectors();
        };

        void updateMatrix(vec3<float> pos = vec3<float>(0, 0, 0), vec3<float> target = vec3<float>(0, 0, -1), vec3<float> up = vec3<float>(0, 1, 0)) {
            this->pos = pos;
            this->target = target;
            this->up = up;

            updateVectors();
        }
        
        void updateTargetMatrix(vec3<float> newTarget){
            updateMatrix(pos, newTarget);
        }
        
        vec2<int> renderVertices(vec3<float> v){
        v = view_matrix * v;
        v = projection_matrix * v;
        return vec2<int>(
            (int)(v.x / v.w),
            (int)(v.y / v.w));
        };

        // рендер линиями
        void WireRenderModel(void (*PutPixel)(int x, int y, int r, int g, int b), Model model){
            for (int i = 0; i < model.getTrianglsCount(); i++) {
            mge::DrawWireframeTringle(DrawPixel,
                renderVertices(model.getVertex(model.getTriangls(i).n1)),
                renderVertices(model.getVertex(model.getTriangls(i).n2)),
                renderVertices(model.getVertex(model.getTriangls(i).n3)), model.getTriangls(i).r, model.getTriangls(i).g, model.getTriangls(i).b);
        }
        }

        // рендер с линиями и цветом
        void FilledWireRenderModel(void (*PutPixel)(int x, int y, int r, int g, int b), Model model){
            for (int i = 0; i < model.getTrianglsCount(); i++) {
            mge::DrawFilledTriangle(DrawPixel,
                renderVertices(model.getVertex(model.getTriangls(i).n1)),
                renderVertices(model.getVertex(model.getTriangls(i).n2)),
                renderVertices(model.getVertex(model.getTriangls(i).n3)), model.getTriangls(i).r, model.getTriangls(i).g, model.getTriangls(i).b);
            mge::DrawWireframeTringle(DrawPixel,
                renderVertices(model.getVertex(model.getTriangls(i).n1)),
                renderVertices(model.getVertex(model.getTriangls(i).n2)),
                renderVertices(model.getVertex(model.getTriangls(i).n3)), model.getTriangls(i).r, model.getTriangls(i).g, model.getTriangls(i).b);
        }
        }

        //рендер цветной
        void RenderModel(void (*PutPixel)(int x, int y, int r, int g, int b), Model model){
            for (int i = 0; i < model.getTrianglsCount(); i++) {
            mge::DrawFilledTriangle(DrawPixel,
                renderVertices(model.getVertex(model.getTriangls(i).n1)),
                renderVertices(model.getVertex(model.getTriangls(i).n2)),
                renderVertices(model.getVertex(model.getTriangls(i).n3)), model.getTriangls(i).r, model.getTriangls(i).g, model.getTriangls(i).b);;
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

        void setPos(vec3<float> v){
            pos = v;
        }

        void move(vec3<float> v){
            pos = pos + v;
        }

        //relative to direction
        void moveRelativeToDirection(vec3<float> v){
            move( v + target.normalize() );
        }
    };
}

int main() {
    InitializeWindow(800,600);

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
    mge::camera cam(800, 600, 10.0f * (mge::M_PI / 180.0f), 0.1f, 1000.0f, mge::vec3<float>(0, 0, -5), mge::vec3<float>(0, 0, 0), mge::vec3<float>(0,-1,0));

    // Переменные для углов вращения камеры
    float i = 0.0f;

    while (IsWindowOpen()) {
        ClearScreen(0, 100, 100);

        // for (int i = 0; i < cube.getTrianglsCount(); i++) {
        //     mge::DrawFilledTriangle(DrawPixel,
        //         cam.renderVertices(cube.getVertex(cube.getTriangls(i).n1)),
        //         cam.renderVertices(cube.getVertex(cube.getTriangls(i).n2)),
        //         cam.renderVertices(cube.getVertex(cube.getTriangls(i).n3)), 0, 233, 0);
        //     mge::DrawWireframeTringle(DrawPixel,
        //         cam.renderVertices(cube.getVertex(cube.getTriangls(i).n1)),
        //         cam.renderVertices(cube.getVertex(cube.getTriangls(i).n2)),
        //         cam.renderVertices(cube.getVertex(cube.getTriangls(i).n3)));
        // }

        cam.RenderModel(DrawPixel, cube);

        //cam.updateTargetMatrix(mge::vec3<float>((float)GetMousePosXScreenToClient() / 80, (float)GetMousePosYScreenToClient() / -60, 0));
        if (GetStateKey(65)) cam.move(mge::vec3<float>(-0.11 + cam.target.normalize().x, 0, 0) ); // a
        if (GetStateKey(68)) cam.move(mge::vec3<float>(0.11 + cam.target.normalize().x, 0, 0) ); // d 
        if (GetStateKey(87)) cam.move(mge::vec3<float>(0, 0, 0.11 + cam.target.normalize().z) ); // w 
        if (GetStateKey(83)) cam.move(mge::vec3<float>(0, 0, -0.11 + cam.target.normalize().z) ); // s 
        std::this_thread::sleep_for(std::chrono::milliseconds(100) );
    }

    return 0; // Завершаем программу
}