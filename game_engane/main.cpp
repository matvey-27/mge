#include"main.h"

class Model {
private:
    Point3D<float>* vertices;
    size_t count_v; // Количество текущих вершин
    Point3D<int>* triangles;
    size_t count_t; // Количество текущих вершин

public:
    Model() : vertices(new Point3D<float>[0]), count_v(0), triangles(new Point3D<int>[0]), count_t(0) {};

    Model(Point3D<float> vertices[], int count_v, Point3D<int> triangles[], int count_t) {
        this->count_v = count_v;
        this->count_t = count_t;

        this->vertices = new Point3D<float>[count_v];
        for (size_t i = 0; i < count_v; ++i) {
            this->vertices[i] = vertices[i];
        }

        this->triangles = new Point3D<int>[count_t];
        for (size_t i = 0; i < count_t; ++i) {
            this->triangles[i] = triangles[i];
        }
    }

    ~Model() {
        delete[] vertices; // Освобождение памяти
        vertices = nullptr;

        delete[] triangles; // Освобождение памяти
        triangles = nullptr;
    }

    Model(const Model& other) {
        count_v = other.count_v;
        count_t = other.count_t;
        vertices = new Point3D<float>[count_v];
        for (size_t i = 0; i < count_v; ++i) {
            vertices[i] = other.vertices[i];
        }
        triangles = new Point3D<int>[count_t];
        for (size_t i = 0; i < count_t; ++i) {
            triangles[i] = other.triangles[i];
        }
    }

    Model& operator=(const Model& other) {
        if (this != &other) {
            delete[] vertices;
            delete[] triangles;

            count_v = other.count_v;
            count_t = other.count_t;
            vertices = new Point3D<float>[count_v];
            for (size_t i = 0; i < count_v; ++i) {
                vertices[i] = other.vertices[i];
            }
            triangles = new Point3D<int>[count_t];
            for (size_t i = 0; i < count_t; ++i) {
                triangles[i] = other.triangles[i];
            }
        }
        return *this;
    }

    // Метод для добавления новой вершины
    void addVertex(const Point3D<float>& point) {
        addElement(vertices, count_v, point);
    }

    // Метод для получения количества вершин
    size_t getVertexCount() const {
        return count_v;
    }

    // Метод для доступа к вершине
    Point3D<float>& getVertex(size_t index) {
        if (index >= count_v) {
            throw std::out_of_range("Index out of range");
        }
        return vertices[index];
    }

    // Метод для добавления новой треугольников
    void addTriangls(const Point3D<int>& point) {
        addElement(triangles, count_t, point);
    }

    // Метод для получения количества треугольников
    size_t getTrianglsCount() const {
        return count_t;
    }

    // Метод для доступа к треугольников
    Point3D<int>& getTriangls(size_t index) {
        if (index >= count_t) {
            throw std::out_of_range("Index out of range");
        }
        return triangles[index];
    }

    void translate(int dx, int dy, int dz) {
        for (size_t i = 0; i < count_v; ++i) {
            vertices[i].x += dx;
            vertices[i].y += dy;
            vertices[i].z += dz;
        }
    }

    void translate(Vector3D<float> v) {
        for (size_t i = 0; i < count_v; i += 1) {
            vertices[i] += v;
        }
    }
};


// НУЖНО СДЕЛАТЬ КЛАСС ТРЕУГОЛЬНИКОВ и исправить функции и классы RenderTriengle() RenderObject() Model()
Point2D<int> ViewportToCanvas(Point2D<float> p, int Cw = 800, int Vw = 800, int Ch = 600, int Vh = 600) {
    return Point2D<int>((int)p.x * Cw/Vw, (int)p.y * Ch/Vh);
}

Point2D<int> ProjectVertex(Point3D<float> v, float d = 200.0){
    return ViewportToCanvas(Point2D<float>(v.x * d / v.z, v.y * d / v.z));
}

void RenderTriengle(Canvas& canvas, Point3D<int> triangle, Point2D<int>* project) {
    DrawWireframeTringle(canvas,
                        project[triangle.x],
                        project[triangle.y],
                        project[triangle.z]);
}

void RenderObject(Canvas& canvas, Model& model) {
    Point2D<int>* projected = new Point2D<int>[0];
    int size = 0;

    for (int i = 0; i < model.getVertexCount(); i++) {
        addElement(projected, size, ProjectVertex(model.getVertex(i)));
    }

    for (int i = 0; i < model.getTrianglsCount(); i++) {
        RenderTriengle(canvas, model.getTriangls(i), projected);
    }
    
    delete[] projected;
}

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

    cube.translate(Vector3D<float>(-5, 0, 5));

    RenderObject(canvas, cube);
}

// Главная функция
int main() {
    Canvas canvas(800, 600, L"hello world"); // Передаем платформенный класс в Canvas
    canvas.Run(DrawExample, 600); // Запускаем отрисовку
    return 0; // Завершаем программу
}
