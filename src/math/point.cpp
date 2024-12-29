#include "Point.h"

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