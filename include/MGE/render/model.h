#pragma once

#include "../math/vec2.hpp"
#include "../math/vec3.hpp"
#include "../math/mat4x4.hpp"

#include "../math/tringles.hpp"
#include "../Utils.hpp"

#include <stdexcept>

namespace mge {
    class Model {
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
}