#pragma once

#include "../math/vec2.h"
#include "../Utils.hpp"

namespace mge {
    int* interpolated(int i0, int d0, int i1, int d1, int& size);

    void DrawLine(void (*PutPixel)(int x, int y, int r, int g, int b), vec2<int> P0, vec2<int> P1, int color_r, int color_g, int color_b);

    void DrawWireframeTringle(void (*PutPixel)(int x, int y, int r, int g, int b), vec2<int> P0, vec2<int> P1, vec2<int> P2, int color_r = 0, int color_g = 0, int color_b = 0);

    bool IsInTriangle(vec2<int> a, vec2<int> b, vec2<int> c, vec2<int> p);

    void DrawFilledTriangle(void (*PutPixel)(int x, int y, int r, int g, int b), vec2<int> P0, vec2<int> P1, vec2<int> P2, int color_r = 0, int color_g = 0, int color_b = 0);

    void DrawGradientTriangle(void (*PutPixel)(int x, int y, int r, int g, int b),
        vec2<int> P0, int C0_r, int C0_g, int C0_b,
        vec2<int> P1, int C1_r, int C1_g, int C1_b,
        vec2<int> P2, int C2_r, int C2_g, int C2_b);

    void DrawCircle(void (*PutPixel)(int x, int y, int r, int g, int b), int centerX, int centerY, int radius, int color_r, int color_g, int color_b);
}