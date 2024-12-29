namespace dll {
    extern "C" {
        __declspec(dllimport) void InitializeWindow(int width, int height);
        __declspec(dllimport) void ClearScreen(int r, int g, int b);
        __declspec(dllimport) void DrawPixel(int x, int y, int r, int g, int b);
        __declspec(dllimport) void RenderLoop();
    }
}