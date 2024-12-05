#include <iostream>
#include <string>
#include <functional>
#include <chrono>
#include <thread>
#include <cmath>
#include <windows.h>


// класс цвета 

class rgb_color {
public:
    int r = 0;
    int g = 0;
    int b = 0;

    rgb_color(int r, int g, int b) : r(r), g(g), b(b) {};

    COLORREF get_color_win(){
        return RGB(r, g, b);
    }
};

// Абстрактный базовый класс для платформы, от которого будут наследоваться все платформенные реализации.
class PlatformCanvas {
public:
    virtual ~PlatformCanvas() {}

    // Чисто виртуальные методы, которые будут переопределены в каждой платформе.
    virtual void Clear() = 0;  // Очистить экран
    virtual void PutPixel(int x, int y, rgb_color color) = 0;  // Нарисовать пиксель в определенной позиции с заданным цветом
    virtual void Initialize(size_t width, size_t height, const std::wstring& title) = 0;  // Инициализация окна с заданными параметрами
    virtual void ProcessEvents() = 0;  // Обработка событий (например, нажатия клавиш)
    virtual bool ShouldQuit() const = 0;  // Проверка, нужно ли завершить выполнение (например, по нажатию Escape)
    virtual void DrawText(int x, int y, const std::wstring& text, COLORREF color) = 0;  // Отрисовка текста на экране

    // Методы для получения размеров окна (теперь возвращают int).
    virtual int GetWidth() const = 0;  // Возвращает ширину окна
    virtual int GetHeight() const = 0;  // Возвращает высоту окна
};

// Класс для Windows-платформы, реализует методы для рисования на экране в Windows.
class WindowsCanvas : public PlatformCanvas {
public:
    WindowsCanvas() : hwnd(nullptr), hInstance(GetModuleHandle(NULL)), width(800), height(600) {}

    // Инициализация окна с заданными размерами и названием
    void Initialize(size_t width, size_t height, const std::wstring& title) override {
        this->width = width;  // Сохраняем переданные размеры
        this->height = height;

        WNDCLASS wc = {};
        wc.lpfnWndProc = StaticWindowProc;  // Указываем обработчик сообщений окна
        wc.hInstance = hInstance;
        wc.lpszClassName = L"CanvasWindowClass";  // Имя класса окна
        RegisterClass(&wc);  // Регистрируем класс окна

        // Создаем окно с указанными параметрами
        hwnd = CreateWindowEx(
            0, L"CanvasWindowClass", title.c_str(),
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,  // Стандартный стиль окна
            CW_USEDEFAULT, CW_USEDEFAULT, static_cast<int>(width), static_cast<int>(height),
            NULL, NULL, hInstance, this
        );
    }

    // Очистка экрана
    void Clear() override {
        HDC hdc = GetDC(hwnd);  // Получаем контекст устройства для рисования
        RECT rect;
        GetClientRect(hwnd, &rect);  // Получаем размеры клиентской области окна
        FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));  // Заполняем экран фоном
        ReleaseDC(hwnd, hdc);  // Освобождаем контекст устройства
    }

    // Установка пикселя на экран
    void PutPixel(int x, int y, rgb_color color) override {
        HDC hdc = GetDC(hwnd);  // Получаем контекст устройства
        SetPixel(hdc, x, y, color.get_color_win());  // Устанавливаем пиксель в заданной позиции
        ReleaseDC(hwnd, hdc);  // Освобождаем контекст устройства
    }

    // Отрисовка текста на экране
    void DrawText(int x, int y, const std::wstring& text, COLORREF color) override {
        HDC hdc = GetDC(hwnd);  // Получаем контекст устройства
        SetTextColor(hdc, color);  // Устанавливаем цвет текста
        TextOut(hdc, x, y, text.c_str(), static_cast<int>(text.length()));  // Отрисовываем текст
        ReleaseDC(hwnd, hdc);  // Освобождаем контекст устройства
    }

    // Обработка сообщений и событий окна
    void ProcessEvents() override {
        MSG msg;
        while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {  // Проверка на наличие сообщений
            TranslateMessage(&msg);
            DispatchMessage(&msg);  // Обработка сообщений
        }
    }

    // Проверка, нужно ли завершить выполнение (например, по нажатию клавиши Escape)
    bool ShouldQuit() const override {
        return (GetAsyncKeyState(VK_ESCAPE) & 0x8000);  // Проверяем состояние клавиши Escape
    }

    // Возвращает ширину окна
    int GetWidth() const override {
        return static_cast<int>(width);  // Возвращаем ширину окна как int
    }

    // Возвращает высоту окна
    int GetHeight() const override {
        return static_cast<int>(height);  // Возвращаем высоту окна как int
    }

protected:
    HWND hwnd;  // Дескриптор окна
    HINSTANCE hInstance;  // Дескриптор приложения
    size_t width, height;  // Ширина и высота окна

    // Статическая функция для обработки сообщений окна
    static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        if (uMsg == WM_NCCREATE) {
            CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
            WindowsCanvas* pCanvas = reinterpret_cast<WindowsCanvas*>(pCreate->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pCanvas);  // Сохраняем указатель на объект Canvas
        }
        else {
            WindowsCanvas* pCanvas = reinterpret_cast<WindowsCanvas*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            if (pCanvas && uMsg == WM_DESTROY) {
                PostQuitMessage(0);  // Закрываем окно
                return 0;
            }
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);  // Обрабатываем стандартные сообщения
    }
};

// Заглушка для LinuxCanvas (реализуем только вывод в консоль)
class LinuxCanvas : public PlatformCanvas {
public:
    LinuxCanvas() {};
};

// Класс Canvas, который использует PlatformCanvas для рисования на экране.
class Canvas {
public:
    // Конструктор принимает платформенный класс, который будет использоваться для рисования.
    Canvas(PlatformCanvas* platformCanvas) : platformCanvas(platformCanvas), clearScreen(true) {}

    // Основной цикл приложения, где происходит отрисовка.
    void Run(std::function<void(Canvas&)> drawFunc, int targetFPS) {
        while (true) {
            platformCanvas->ProcessEvents();  // Обработка событий
            if (platformCanvas->ShouldQuit()) {
                break;  // Выход из цикла, если нужно завершить программу
            }

            if (clearScreen) {
                platformCanvas->Clear();  // Очистка экрана
            }

            drawFunc(*this);  // Вызов переданной функции для рисования
        }
    }

    // Очистка экрана
    void Clear() {
        platformCanvas->Clear();
    }

    // Переключатель режима очистки экрана (например, чтобы не очищать экран каждый раз)
    void ToggleClearScreen() {
        clearScreen = !clearScreen;
    }

    // Получение ширины окна
    int GetWidth() const {
        return platformCanvas->GetWidth();  // Вызываем метод платформенного класса
    }

    // Получение высоты окна
    int GetHeight() const {
        return platformCanvas->GetHeight();  // Вызываем метод платформенного класса
    }


    // Установка пикселя на экране
    void PutPixel(int x, int y, rgb_color color) {
        platformCanvas->PutPixel(
            GetWidth() / 2 + x,
            GetHeight() / 2 + y,
            color);
    }

private:
    PlatformCanvas* platformCanvas;  // Указатель на платформенный класс для рисования
    bool clearScreen;  // Флаг, указывающий, нужно ли очищать экран при каждом кадре
};


