#include <iostream>
#include <string>
#include <functional>
#include <chrono>
#include <thread>
#include <cmath>
#ifdef _WIN32
#include <windows.h>
#endif

// Абстрактный базовый класс для платформы
class PlatformCanvas {
public:
    virtual ~PlatformCanvas() {}
    virtual void Clear() = 0;
    virtual void PutPixel(int x, int y, COLORREF color) = 0;
    virtual void Initialize(size_t width, size_t height, const std::wstring& title) = 0; // Используем size_t
    virtual void ProcessEvents() = 0; // Обработка событий
    virtual bool ShouldQuit() const = 0; // Проверка на завершение
    virtual void DrawText(int x, int y, const std::wstring& text, COLORREF color) = 0; // Новый метод для отрисовки текста
};

// Класс для Windows
class WindowsCanvas : public PlatformCanvas {
public:
    WindowsCanvas() : hwnd(nullptr), hInstance(GetModuleHandle(NULL)) {}

    void Initialize(size_t width, size_t height, const std::wstring& title) override {
        WNDCLASS wc = {};
        wc.lpfnWndProc = StaticWindowProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = L"CanvasWindowClass";
        RegisterClass(&wc);

        hwnd = CreateWindowEx(
            0, L"CanvasWindowClass", title.c_str(),
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, static_cast<int>(width), static_cast<int>(height), // Приведение к int
            NULL, NULL, hInstance, this
        );
    }

    void Clear() override {
        HDC hdc = GetDC(hwnd);
        RECT rect;
        GetClientRect(hwnd, &rect);
        FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
        ReleaseDC(hwnd, hdc);
    }

    void PutPixel(int x, int y, COLORREF color) override {
        HDC hdc = GetDC(hwnd);
        SetPixel(hdc, x, y, color);
        ReleaseDC(hwnd, hdc);
    }

    void DrawText(int x, int y, const std::wstring& text, COLORREF color) override {
        HDC hdc = GetDC(hwnd);
        SetTextColor(hdc, color);
        TextOut(hdc, x, y, text.c_str(), static_cast<int>(text.length()));
        ReleaseDC(hwnd, hdc);
    }

    void ProcessEvents() override {
        MSG msg;
        while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) { // Исправлено: добавлен hwnd
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    bool ShouldQuit() const override {
        return (GetAsyncKeyState(VK_ESCAPE) & 0x8000);
    }

protected:
    HWND hwnd;
    HINSTANCE hInstance;

    static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        if (uMsg == WM_NCCREATE) {
            CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
            WindowsCanvas* pCanvas = reinterpret_cast<WindowsCanvas*>(pCreate->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pCanvas);
        }
        else {
            WindowsCanvas* pCanvas = reinterpret_cast<WindowsCanvas*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            if (pCanvas && uMsg == WM_DESTROY) {
                PostQuitMessage(0);
                return 0;
            }
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
};

// Заглушка для LinuxCanvas
class LinuxCanvas : public PlatformCanvas {
public:
    LinuxCanvas() {
        // Здесь должна быть инициализация для Linux
    }

    void Initialize(size_t width, size_t height, const std::wstring& title) override {
        std::wcout << L"LinuxCanvas: Инициализация окна " << title << L" (" << width << L"x" << height << L")" << std::endl;
    }

    void Clear() override {
        std::wcout << L"LinuxCanvas: Очистка экрана" << std::endl;
    }

    void PutPixel(int x, int y, COLORREF color) override {
        std::wcout << L"LinuxCanvas: Установка пикселя (" << x << L", " << y << L") цвет: " << color << std::endl;
    }

    void DrawText(int x, int y, const std::wstring& text, COLORREF color) override {
        std::wcout << L"LinuxCanvas: Отрисовка текста '" << text << L"' в позиции (" << x << L", " << y << L") цвет: " << color << std::endl;
    }

    void ProcessEvents() override {
        // Здесь должна быть обработка событий для Linux
    }

    bool ShouldQuit() const override {
        return false; // Заглушка
    }
};

// Класс Canvas, который использует PlatformCanvas
class Canvas {
public:
    Canvas(PlatformCanvas* platformCanvas) : platformCanvas(platformCanvas), clearScreen(true) {}

    void Run(std::function<void(Canvas&)> drawFunc, int targetFPS) {
        platformCanvas->Initialize(800, 600, L"Canvas Application"); // Изменено на L""

        auto frameDuration = std::chrono::milliseconds(1000 / targetFPS);
        auto lastTime = std::chrono::high_resolution_clock::now();
        int frameCount = 0;

        while (true) {
            platformCanvas->ProcessEvents();
            if (platformCanvas->ShouldQuit()) {
                break; // Выход из цикла
            }

            if (clearScreen) {
                platformCanvas->Clear();
            }

            drawFunc(*this);
            frameCount++;

            // Вычисление и отображение FPS
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = currentTime - lastTime;
            if (elapsed.count() >= 1.0) {
                std::wstring fpsText = L"FPS: " + std::to_wstring(frameCount);
                platformCanvas->DrawText(10, 10, fpsText, RGB(255, 0, 0)); // Отображение FPS в верхнем левом углу
                frameCount = 0;
                lastTime = currentTime;
            }

            std::this_thread::sleep_for(frameDuration); // Ограничение FPS
        }
    }

    void Clear() {
        platformCanvas->Clear();
    }

    void PutPixel(int x, int y, COLORREF color) {
        platformCanvas->PutPixel(x, y, color);
    }

    void DrawCircle(int centerX, int centerY, int radius, COLORREF color) {
        for (int angle = 0; angle < 360; angle++) {
            int x = centerX + static_cast<int>(radius * cos(angle * 3.14159 / 180));
            int y = centerY + static_cast<int>(radius * sin(angle * 3.14159 / 180));
            PutPixel(x, y, color);
        }
    }

    void ToggleClearScreen() {
        clearScreen = !clearScreen; // Переключение флага очистки экрана
    }

private:
    PlatformCanvas* platformCanvas; // Указатель на платформенный класс
    bool clearScreen; // Флаг для управления очисткой экрана
};
