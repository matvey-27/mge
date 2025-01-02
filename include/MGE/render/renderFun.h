#pragma once

#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../math/mat4x4.h"
#include "../math/tringles.hpp"

#include "drawFun.h"
#include "model.h"

#include "../Utils.hpp"

#include <stdexcept>

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