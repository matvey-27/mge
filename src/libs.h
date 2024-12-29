#pragma once
#include "render/RgbColor.h"

namespace dll {
    extern "C" {
        __declspec(dllimport) void InitializeWindow(int width, int height);
        __declspec(dllimport) void ClearScreen(int r, int g, int b);
        __declspec(dllimport) void DrawPixel(int x, int y, int r, int g, int b);
        __declspec(dllimport) void RenderLoop();
    }
}

void DrawPixel(int x, int y, RgbColor color) {
    dll::DrawPixel(x, y, color.r, color.g, color.b);
}

using namespace dll;