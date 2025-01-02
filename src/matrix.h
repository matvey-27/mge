#pragma once

#include <cmath>

// Матрица для вращения по X
float ax = 0; // угол поворота 
float rotationMatrixX[4][4] = {
    { 1,         0,          0, 0 },
    { 0, std::cos(ax), -std::sin(ax),  0 },
    { 0, std::sin(ax),  std::cos(ax),  0 },
    { 0,         0,          0, 1 }
};

// Матрица для вращения по Y
float ay = 0; // угол поворота
float rotationMatrixY[4][4] = {
    { std::cos(ay),  0, std::sin(ay), 0 },
    { 0,             1, 0,             0 },
    { -std::sin(ay), 0, std::cos(ay), 0 },
    { 0,             0, 0,             1 }
};


// Матрица для вращения по Z
float az = 0; // угол поворота
float rotationMatrixZ[4][4] = {
    { std::cos(az), -std::sin(az), 0, 0 },
    { std::sin(az),  std::cos(az), 0, 0 },
    { 0,             0,            1, 0 },
    { 0,             0,            0, 1 }
};

// Матрица трансляции (перемещения)
float tx, ty, tz;
float translationMatrix[4][4] = {
    { 1, 0, 0, tx },  // Смещение по X
    { 0, 1, 0, ty },  // Смещение по Y
    { 0, 0, 1, tz },  // Смещение по Z
    { 0, 0, 0, 1 }
};

// Матрица масштабирования
float sx, sy, sz;
float scalingMatrix[4][4] = {
    { sx, 0,  0,  0 },  // Масштабирование по X
    { 0,  sy,  0,  0 },  // Масштабирование по Y
    { 0,  0,  sz,  0 },  // Масштабирование по Z
    { 0,  0,  0,  1 }
};