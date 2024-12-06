#include "math.h"
#include <iostream>

using namespace std;
using namespace math;

template <typename T>
void Point2D<T>::print_position() {
    cout << "x = " << this->x << endl;
    cout << "y = " << this->y << endl;
}

template <typename T>
void Point3D<T>::print_position() {
    cout << "x = " << this->x << endl;
    cout << "y = " << this->y << endl;
    cout << "z = " << this->z << endl;
}

//template<typename T>
//Point3D<T> Point3D<T>::operator+=(Vector3D<T> v){
//    return Point3D<T>(this->x + v.x, this->y + v.y, this->z + v.z);
//}

template <typename T>
Vector3D<T> Point3D<T>::operator-(Point3D<T> p) {
    return Vector3D<T>(this->x - p.x, this->y - p.y, this->z - p.z);
}
