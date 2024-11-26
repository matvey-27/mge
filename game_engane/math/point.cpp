#include "math.h"
#include <iostream>

using namespace std;
using namespace math;

template <typename T>
void point_2D<T>::print_position() {
    cout << "x = " << this->x << endl;
    cout << "y = " << this->y << endl;
}

template <typename T>
void point_3D<T>::print_position() {
    cout << "x = " << this->x << endl;
    cout << "y = " << this->y << endl;
    cout << "z = " << this->z << endl;
}

template <typename T>
vector_3D<T> point_3D<T>::operator-(point_3D<T> p) {
    return vector_3D<T>(this->x - p.x, this->y - p.y, this->z - p.z);
}
