#pragma once

#include "vec3.h"

namespace mge {
    template <typename T>
    class mat4x4
    {
    private:
        T matrix[4][4];
    public:
        mat4x4() {};

        mat4x4(T mx[4][4]) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    matrix[i][j] = mx[i][j];
                }
            }
        }

        mat4x4<T> operator +(mat4x4<T> mx) {
            T matrix_r[4][4];

            for (int i = 0; i <= 4; i++) {
                for (int f = 0; f <= 4; f++) {
                    matrix_r[i][f] = matrix[i][f] + mx[i][f];
                }
            }
            return mat4x4(matrix_r);

        }

        vec3<T> operator *(vec3<T> v) {
            return vec3<T>(
                v.x * matrix[0][0] + v.y * matrix[0][1] + v.z * matrix[0][2] + v.w * matrix[0][3],
                v.x * matrix[1][0] + v.y * matrix[1][1] + v.z * matrix[1][2] + v.w * matrix[1][3],
                v.x * matrix[2][0] + v.y * matrix[2][1] + v.z * matrix[2][2] + v.w * matrix[2][3],
                v.x * matrix[3][0] + v.y * matrix[3][1] + v.z * matrix[3][2] + v.w * matrix[3][3]
            );
        }

    };
}