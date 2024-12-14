#pragma once

#include <cmath>
#include "Model.h"
#include "../Utils.h"
#include "../math/Vector.h"
#include "../math/Point.h"
#include "../canvas/canvas.h"

using namespace std;
using namespace math;
using namespace my_fun;
using namespace canvas;

int* interpolated(int i0, int d0, int i1, int d1, int& size);

void DrawLine(Canvas canvas, Point2D<int> P0, Point2D<int> P1, rgb_color color = rgb_color(0, 0, 0));

void DrawWireframeTringle(Canvas canvas, Point2D<int> P0, Point2D<int> P1, Point2D<int> P2, rgb_color color = rgb_color(0, 0, 0));

void DrawCircle(Canvas canvas, int centerX, int centerY, int radius, rgb_color color = rgb_color(0, 0, 0));

template <typename T>
Vector3D<T> move(Vector3D<T>, float a);

template <typename T>
Point3D<T> rotateX(Point3D<T> p, float a);

Point2D<int> ViewportToCanvas(Point2D<float> p, int Cw = 800, int Vw = 800, int Ch = 600, int Vh = 600);

Point2D<int> ProjectVertex(Point3D<float> v, float d = 150.0);

void RenderTriengle(Canvas& canvas, Point3D<int> triangle, Point2D<int>* project);

void RenderObject(Canvas& canvas, Model& model, int a);