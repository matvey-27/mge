#pragma once
#include "Vector.h"
#include "Point.h"

namespace math{
    template <typename T>
    class mat4
    {
    private:
        T matrix[4][4];
    public:
       mat4(T mx[4][4]) {
           matrix = mx;
       };

       mat4<T> operator +(mat4<T> mx) {
           T matrix_r[4][4];

           for (int i = 0; i <= 4; i++) {
               for (int f = 0; f <= 4; f++) {
                   matrix_r[i][f] = matrix[i][f] + mx[i][f];
               }
           }
           return mat4(matrix_r);

       }

       Vector3D<T> operator *(Vector3D<T> v) {
           return Vector3D<T>(
               v.x * matrix[0][0] + v.y * matrix[0][1] + v.z * matrix[0][2] + v.w * matrix[0][3],
               v.x * matrix[1][0] + v.y * matrix[1][1] + v.z * matrix[1][2] + v.w * matrix[1][3],
               v.x * matrix[2][0] + v.y * matrix[2][1] + v.z * matrix[2][2] + v.w * matrix[2][3],
               v.x * matrix[3][0] + v.y * matrix[3][1] + v.z * matrix[3][2] + v.w * matrix[3][3]
           );
       }


       Point3D<T> operator *(Point3D<T> p) {
           return Point3D<T>(
               p.x * matrix[0][0] + p.y * matrix[0][1] + p.z * matrix[0][2] + p.w * matrix[0][3],
               p.x * matrix[1][0] + p.y * matrix[1][1] + p.z * matrix[1][2] + p.w * matrix[1][3],
               p.x * matrix[2][0] + p.y * matrix[2][1] + p.z * matrix[2][2] + p.w * matrix[2][3],
               p.x * matrix[3][0] + p.y * matrix[3][1] + p.z * matrix[3][2] + p.w * matrix[3][3]
           );
       }

    };
}