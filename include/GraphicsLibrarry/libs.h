#pragma once
#include "RgbColor.h"

namespace dll {
    extern "C" {
        __declspec(dllimport) void InitializeWindow(int width, int height);
        __declspec(dllimport) void ClearScreen(int r, int g, int b);
        __declspec(dllimport) void DrawPixel(int x, int y, int r, int g, int b);
        __declspec(dllimport) void RenderLoop();
        __declspec(dllimport) bool IsWindowOpen();
        __declspec(dllimport) int GetMousePosX();
        __declspec(dllimport) int GetMousePosY();
        __declspec(dllimport) int GetMousePosXScreenToClient();
        __declspec(dllimport) int GetMousePosYScreenToClient();
        __declspec(dllimport) bool GetStateKey(int key);
    }
}

void DrawPixel(int x, int y, RgbColor color) {
    dll::DrawPixel(x, y, color.r, color.g, color.b);
}

using namespace dll;