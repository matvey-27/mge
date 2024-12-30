#pragma once

class RgbColor {
public:
    int r = 0;
    int g = 0;
    int b = 0;

    RgbColor(int r, int g, int b) : r(r), g(g), b(b) {};

    int getIntColor() {
        return r, g, b;
    }
};