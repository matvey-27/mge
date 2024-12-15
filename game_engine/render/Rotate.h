#pragma once

#include <cmath>
#include "../math/Vector.h"
#include "../math/Point.h"

using namespace std;
using namespace math;

template <typename T>
Point3D<T> RotateX(Point3D<T> p, float a) {
    float Rx[3][3] = {
    { 1,        0,         0 },
    { 0, cos(a), -sin(a) },
    { 0, sin(a),  cos(a) }
    };

    return Point3D<T>(
        p.x * Rx[0][0] + p.y * Rx[0][1] + p.z * Rx[0][2], // x' = x  1 + y  0 + z  0
        p.x * Rx[1][0] + p.y * Rx[1][1] + p.z * Rx[1][2], // y' = x  0 + y  cos(a) + z  -sin(a)
        p.x * Rx[2][0] + p.y * Rx[2][1] + p.z * Rx[2][2]  // z' = x  0 + y  sin(a) + z  cos(a)
    );
}

template <typename T>
Point3D<T> RotateY(Point3D<T> p, float a) {


    float Ry[3][3] = {
    { cos(a),  0, sin(a) },
    { 0,       1,       0 },
    { -sin(a), 0, cos(a) }
    };


    return Point3D<T>(
        p.x * Ry[0][0] + p.y * Ry[0][1] + p.z * Ry[0][2], // x' = x  1 + y  0 + z  0
        p.x * Ry[1][0] + p.y * Ry[1][1] + p.z * Ry[1][2], // y' = x  0 + y  cos(a) + z  -sin(a)
        p.x * Ry[2][0] + p.y * Ry[2][1] + p.z * Ry[2][2]  // z' = x  0 + y  sin(a) + z  cos(a)
    );
}

template <typename T>
Point3D<T> RotateZ(Point3D<T> p, float a) {


    float Rz[3][3] = {
    { cos(a), -sin(a), 0 },
    { sin(a),  cos(a), 0 },
    { 0,       0,      1 }
    };

    return Point3D<T>(
        p.x * Rz[0][0] + p.y * Rz[0][1] + p.z * Rz[0][2], // x' = x  1 + y  0 + z  0
        p.x * Rz[1][0] + p.y * Rz[1][1] + p.z * Rz[1][2], // y' = x  0 + y  cos(a) + z  -sin(a)
        p.x * Rz[2][0] + p.y * Rz[2][1] + p.z * Rz[2][2]  // z' = x  0 + y  sin(a) + z  cos(a)
    );
}


template <typename T>
Point3D<T> RotateX(Vector3D<T> p, float a) {
    float Rx[3][3] = {
    { 1,        0,         0 },
    { 0, cos(a), -sin(a) },
    { 0, sin(a),  cos(a) }
    };

    return Point3D<T>(
        p.x * Rx[0][0] + p.y * Rx[0][1] + p.z * Rx[0][2], // x' = x  1 + y  0 + z  0
        p.x * Rx[1][0] + p.y * Rx[1][1] + p.z * Rx[1][2], // y' = x  0 + y  cos(a) + z  -sin(a)
        p.x * Rx[2][0] + p.y * Rx[2][1] + p.z * Rx[2][2]  // z' = x  0 + y  sin(a) + z  cos(a)
    );
}

template <typename T>
Point3D<T> RotateY(Vector3D<T> p, float a) {


    float Ry[3][3] = {
    { cos(a),  0, sin(a) },
    { 0,       1,       0 },
    { -sin(a), 0, cos(a) }
    };


    return Point3D<T>(
        p.x * Ry[0][0] + p.y * Ry[0][1] + p.z * Ry[0][2], // x' = x  1 + y  0 + z  0
        p.x * Ry[1][0] + p.y * Ry[1][1] + p.z * Ry[1][2], // y' = x  0 + y  cos(a) + z  -sin(a)
        p.x * Ry[2][0] + p.y * Ry[2][1] + p.z * Ry[2][2]  // z' = x  0 + y  sin(a) + z  cos(a)
    );
}

template <typename T>
Point3D<T> RotateZ(Vector3D<T> p, float a) {


    float Rz[3][3] = {
    { cos(a), -sin(a), 0 },
    { sin(a),  cos(a), 0 },
    { 0,       0,      1 }
    };

    return Point3D<T>(
        p.x * Rz[0][0] + p.y * Rz[0][1] + p.z * Rz[0][2], // x' = x  1 + y  0 + z  0
        p.x * Rz[1][0] + p.y * Rz[1][1] + p.z * Rz[1][2], // y' = x  0 + y  cos(a) + z  -sin(a)
        p.x * Rz[2][0] + p.y * Rz[2][1] + p.z * Rz[2][2]  // z' = x  0 + y  sin(a) + z  cos(a)
    );
}