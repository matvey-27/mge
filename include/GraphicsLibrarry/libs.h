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
        // Клавиша	    Код клавиши (Hex)	Код клавиши (Decimal)
        // A	        0x41	            65
        // B	        0x42	            66
        // C	        0x43	            67
        // D	        0x44	            68
        // E	        0x45	            69
        // F	        0x46	            70
        // G	        0x47	            71
        // H	        0x48	            72
        // I	        0x49	            73
        // J	        0x4A	            74
        // K	        0x4B	            75
        // L	        0x4C	            76
        // M	        0x4D	            77
        // N	        0x4E	            78
        // O	        0x4F	            79
        // P	        0x50	            80
        // Q	        0x51	            81
        // R	        0x52	            82
        // S	        0x53	            83
        // T	        0x54	            84
        // U	        0x55	            85
        // V	        0x56	            86
        // W	        0x57	            87
        // X	        0x58	            88
        // Y	        0x59	            89
        // Z	        0x5A	            90
        // 0	        0x30	            48
        // 1	        0x31	            49
        // 2	        0x32	            50
        // 3	        0x33	            51
        // 4	        0x34	            52
        // 5	        0x35	            53
        // 6	        0x36	            54
        // 7	        0x37	            55
        // 8	        0x38	            56
        // 9	        0x39	            57
        // Esc	        0x1B	            27
        // Space	    0x20	            32
        // Enter	    0x0D	            13
        // Shift	    0x10	            16
        // Ctrl	        0x11	            17
        // Alt	        0x12	            18
        // Arrow Up	    0x26	            38
        // Arrow Down	0x28	            40
        // Arrow Left	0x25	            37
        // Arrow Right	0x27	            39
    }
}

void DrawPixel(int x, int y, RgbColor color) {
    dll::DrawPixel(x, y, color.r, color.g, color.b);
}

using namespace dll;