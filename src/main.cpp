// нужно добавить алгоритм как там https://gist.github.com/vurtun/29727217c269a2fbf4c0ed9a1d11cb40
//     для колизий 
// нужно добавить vulkan
// засунуть все в динамическую библиотеку 

#include "../include/GraphicsLibrarry/libs.h"
#include "../include/MGE/Utils.hpp"
#include <stdexcept>
#include <thread>
#include <cmath>

// тест vec2 (если все работает -> движок *("MGE/math/vec2")* )
namespace mge {
    template <typename T>
    class vec2{
    public:
        T x, y, w = 0;
        
        vec2() : x(0), y(0) {};
        vec2(T x, T y) : x(x), y(y) {};
        vec2(T x, T y, T w) : x(x), y(y) {};
        ~vec2() = default;
    };
}
// тест vec3 (если все работает -> движок *("MGE/math/vec3")* )
namespace mge {
    template <typename T>
    class vec3 : public vec2<T>{
    public:
        T z;
        
        vec3() : vec2<T>::vec2(), z(0) {};
        vec3(T x, T y, T z): vec2<T>::vec2(x, y), z(z) {};
        vec3(T x, T y, T z, T w): vec2<T>::vec2(x, y, w), z(z) {};
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
    };
}
// тест mat4
namespace mge{
    template <typename T>
    class mat4
    {
    private:
        T matrix[4][4];
    public:
    mat4(T mx[4][4]) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                matrix[i][j] = mx[i][j];
            }
        }
    }

    mat4<T> operator +(mat4<T> mx) {
        T matrix_r[4][4];

        for (int i = 0; i <= 4; i++) {
            for (int f = 0; f <= 4; f++) {
                matrix_r[i][f] = matrix[i][f] + mx[i][f];
            }
        }
        return mat4(matrix_r);

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
        mat4<float> rx(rotationMatrixX);

        // Матрица для вращения по Y
        float rotationMatrixY[4][4] = {
            { std::cos(ay),  0, std::sin(ay), 0 },
            { 0,        1, 0,       0 },
            { -std::sin(ay), 0, std::cos(ay), 0 },
            { 0,        0, 0,       1 }
        };
        mat4<float> ry(rotationMatrixY);
        
        // Матрица для вращения по Z
        float rotationMatrixZ[4][4] = {
            { std::cos(az), -std::sin(az), 0, 0 },
            { std::sin(az),  std::cos(az), 0, 0 },
            { 0,        0,       1, 0 },
            { 0,        0,       0, 1 }
        };
        mat4<float> rz(rotationMatrixZ);

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
        size = abs(i1 - i0) + 1; // Количество интерполированных значений
        int* values = new int[size]; // Создаем массив нужного размера

        // Проверяем, если i0 равно i1
        if (i0 == i1) {
            values[0] = d0; // Добавляем d0 в массив
        }
        else {
            int delta = d1 - d0;
            for (int i = 0; i < size; ++i) {
                values[i] = d0 + (delta * i) / (i1 - i0); // Линейная интерполяция
            }
        }

        return values; // Возвращаем массив
        delete[] values;
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

    void DrawWireframeTringle(void (*PutPixel)(int x, int y, int r, int g, int b), vec2<int> P0, vec2<int> P1, vec2<int> P2, int color_r = 0, int color_g = 0, int color_b = 0)
    {
        DrawLine(PutPixel, P0, P1, color_r, color_g, color_b);
        DrawLine(PutPixel, P1, P2, color_r, color_g, color_b);
        DrawLine(PutPixel, P2, P0, color_r, color_g, color_b);

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
// class canvas
namespace mge {
    class canvas{
        public:
            float width = 800.0f;        // Ширина окна
            float height = 600.0f;       // Высота окна
            float FOVy = 45.0f * (M_PI / 180.0f); // Перевод ФОВ в радианы
            float zNear = 0.1f;          // Ближняя плоскость
            float zFar = 1000.0f;        // Дальняя плоскость
    };
}

int main() {
    InitializeWindow(500, 500);

    mge::vec3<float> vertices[8] = {
        mge::vec3<float>(1, 1, 1),   // Вершина 0
        mge::vec3<float>(-1, 1, 1),  // Вершина 1
        mge::vec3<float>(-1, -1, 1), // Вершина 2
        mge::vec3<float>(1, -1, 1),  // Вершина 3
        mge::vec3<float>(1, 1, -1),  // Вершина 4
        mge::vec3<float>(-1, 1, -1), // Вершина 5
        mge::vec3<float>(-1, -1, -1),// Вершина 6
        mge::vec3<float>(1, -1, -1)  // Вершина 7
    };

    mge::Triangles<int> triangles[12] = {
        mge::Triangles<int>{0, 1, 2, 255, }, // Передняя гра грань 0
        mge::Triangles<int>{0, 2, 3, 255, }, // Передняя гра грань 1
        mge::Triangles<int>{4, 5, 6, 255, }, // Задняя гра грани 0
        mge::Triangles<int>{4, 6, 7, 255, }, // Задняя гра грани 1
        mge::Triangles<int>{1, 5, 6, 255, }, // Левый грань 0
        mge::Triangles<int>{1, 6, 2, 255, }, // Левый грань 1
        mge::Triangles<int>{0, 4, 7, 255, }, // Правый грань 0
        mge::Triangles<int>{0, 7, 3, 255, }, // Правый грань 1
        mge::Triangles<int>{4, 5, 1, 255, }, // Верхний грань 0
        mge::Triangles<int>{4, 1, 0, 255, }, // Верхний грань 1
        mge::Triangles<int>{2, 6, 7, 255}, // Нижний грань 0
        mge::Triangles<int>{2, 7, 3, 255}  // Нижний грань 1
    };

    mge::Model cube(vertices, 8, triangles, 12);
    cube.move(mge::vec3<float>(0, 0, 10));

    while (IsWindowOpen()) {
        ClearScreen(0, 100, 100);

        cube.rotate(0, 1, 0);

        RenderObject(DrawPixel, cube);

        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Задержка для снижения нагрузки на CPU
    }

    return 0; // Завершаем программу
}