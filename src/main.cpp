// нужно добавить алгоритм как там https://gist.github.com/vurtun/29727217c269a2fbf4c0ed9a1d11cb40
//     для колизий 
// нужно добавить vulkan
// засунуть все в динамическую библиотеку 

#include "../include/GraphicsLibrarry/libs.h"
#include "../include/MGE/Utils.hpp"
#include "../include/MGE/Utils.hpp"
#include <iostream>
#include <thread>

// тест vec2 (если все работает -> движок *("MGE/math/vec2")* )
namespace mge {
    template <typename T>
    class vec2{
    public:
        T x, y, w = 0;
        
        vec2() : x(x), y(y) {};
        vec2(T x, T y) : x(x), y(y) {};
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
        ~vec3() = default;

        vec3<T>& operator+=(const vec3<T>& v) {
            this->x += v.x;
            this->y += v.y;
            this->z += v.z;
            return *this; // Возвращаем this
        }
    };
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

    void DrawWireframeTringle(void (*PutPixel)(int x, int y, int r, int g, int b), vec2<int> P0, vec2<int> P1, vec2<int> P2, int color_r, int color_g, int color_b)
    {
        DrawLine(PutPixel, P0, P1, color_r, color_g, color_b);
        DrawLine(PutPixel, P1, P2, color_r, color_g, color_b);
        DrawLine(PutPixel, P2, P0, color_r, color_g, color_b);

    }

    void DrawCircle(void (*PutPixel)(int x, int y, int r, int g, int b), int centerX, int centerY, int radius, int color_r, int color_g, int color_b) {
        for (int angle = 0; angle < 360; angle++) {
            int x = centerX + static_cast<int>(radius * cos(angle * 3.14159 / 180));
            int y = centerY + static_cast<int>(radius * sin(angle * 3.14159 / 180));
            PutPixel(x, y, color_r, color_g, color_b);  // Рисуем каждый пиксель круга
        }
    }
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
}




int main() {
    InitializeWindow(500, 500);

    while (IsWindowOpen()) {
        ClearScreen(0, 255, 0);

        mge::DrawCircle(DrawPixel,  0,  0,  50, 50, 50, 50);

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Задержка для снижения нагрузки на CPU
    }

    return 0; // Завершаем программу
}