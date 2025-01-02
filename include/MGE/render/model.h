#pragma once

#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../math/mat4x4.h"

#include "../math/tringles.hpp"
#include "../Utils.hpp"

#include <stdexcept>

namespace mge {
    class Model {
    private:
        vec3<float> global_position = vec3<float>(0, 0, 0); // ���������� ������� �������

        vec3<float>* vertices;
        size_t count_v; // ���������� ������� ������
        Triangles<int>* triangles;
        size_t count_t; // ���������� ������� ������
    public:
        Model() : vertices(new vec3<float>[0]), count_v(0), triangles(new Triangles<int>[0]), count_t(0) {};

        Model(vec3<float> vertices[], int count_v, Triangles<int> triangles[], int count_t);

        ~Model();

        Model(const Model& other);

        Model& operator=(const Model& other);

        // ����� ��� ���������� ����� �������
        void addVertex(const vec3<float>& point);

        // ����� ��� ��������� ���������� ������
        size_t getVertexCount() const;

        // ����� ��� ������� � �������
        vec3<float>& getVertex(size_t index);

        // ����� ��� ���������� ����� �������������
        void addTriangls(const Triangles<int>& point);

        // ����� ��� ��������� ���������� �������������
        size_t getTrianglsCount();

        // ����� ��� ������� � �������������
        Triangles<int>& getTriangls(size_t index);

        // ������������
        void move(vec3<float> v);

        // -- �������� 
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
        delete[] vertices; // ������������ ������
        vertices = nullptr;

        delete[] triangles; // ������������ ������
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


    // ����� ��� ���������� ����� �������
    void Model::addVertex(const vec3<float>& point) {
        addElement(vertices, count_v, point);
    }

    // ����� ��� ��������� ���������� ������
    size_t Model::getVertexCount() const {
        return count_v;
    }

    // ����� ��� ������� � �������
    vec3<float>& Model::getVertex(size_t index) {
        if (index >= count_v) {
            throw std::out_of_range("Index out of range");
        }
        return vertices[index];
    }

    // ����� ��� ���������� ����� �������������
    void Model::addTriangls(const Triangles<int>& point) {
        addElement(triangles, count_t, point);
    }

    // ����� ��� ��������� ���������� �������������
    size_t Model::getTrianglsCount()
    {
        return count_t;
    }

    // ����� ��� ������� � �������������
    Triangles<int>& Model::getTriangls(size_t index) {
        if (index >= count_t) {
            throw std::out_of_range("Index out of range");
        }
        return triangles[index];
    }

    // ����� ��� ����������� 
    void Model::move(vec3<float> v) {
        global_position += v;

        for (size_t i = 0; i < count_v; i += 1) {
            vertices[i] += v;
        }
    }

    // ����� ��� �������� 
    void Model::rotate(float ax_deg, float ay_deg, float az_deg) {
        // �������������� ����� �� �������� � �������
        float ax = ax_deg * (M_PI / 180.0f);
        float ay = ay_deg * (M_PI / 180.0f);
        float az = az_deg * (M_PI / 180.0f);

        // ������� ��� �������� �� X
        float rotationMatrixX[4][4] = {
            { 1,         0,          0, 0 },
            { 0, std::cos(ax), -std::sin(ax),  0 },
            { 0, std::sin(ax),  std::cos(ax),  0 },
            { 0,         0,          0, 1 }
        };
        mat4x4<float> rx(rotationMatrixX);

        // ������� ��� �������� �� Y
        float rotationMatrixY[4][4] = {
            { std::cos(ay),  0, std::sin(ay), 0 },
            { 0,        1, 0,       0 },
            { -std::sin(ay), 0, std::cos(ay), 0 },
            { 0,        0, 0,       1 }
        };
        mat4x4<float> ry(rotationMatrixY);

        // ������� ��� �������� �� Z
        float rotationMatrixZ[4][4] = {
            { std::cos(az), -std::sin(az), 0, 0 },
            { std::sin(az),  std::cos(az), 0, 0 },
            { 0,        0,       1, 0 },
            { 0,        0,       0, 1 }
        };
        mat4x4<float> rz(rotationMatrixZ);

        // ���������� �������� � ��������
        for (size_t i = 0; i < count_v; ++i) {
            // ��������� �������� �� ���� X, Y � Z ���������������
            vertices[i] = rz * (ry * (rx * (vertices[i] - global_position))) + global_position;
        }
    }
}