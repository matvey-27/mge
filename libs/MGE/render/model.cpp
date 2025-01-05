#include "../../../Include/MGE/render/model.h"

using namespace mge;

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
vec3<float>& Model::getVertex(size_t index) {
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
