#pragma once

#include <cmath>
#include "../Utils.h"
#include "../math/Vector.h"
#include "../math/Point.h"
#include "../canvas/canvas.h"
#include "Model.h"

using namespace std;
using namespace math;
using namespace my_fun;
using namespace canvas;

int* interpolated(int i0, int d0, int i1, int d1, int& size);

void DrawLine(Canvas canvas, Point2D<int> P0, Point2D<int> P1, RgbColor color = RgbColor(0, 0, 0));

void DrawWireframeTringle(Canvas canvas, Point2D<int> P0, Point2D<int> P1, Point2D<int> P2, RgbColor color = RgbColor(0, 0, 0));

void DrawCircle(Canvas canvas, int centerX, int centerY, int radius, RgbColor color = RgbColor(0, 0, 0));

Point2D<int> ViewportToCanvas(Point2D<float> p, float Cw = 1000, float Vw = 1, float Ch = 1000, float Vh = 1);

Point2D<int> ProjectVertex(Point3D<float> v, float d = 1);

void RenderTriengle(Canvas& canvas, Point3D<int> triangle, Point2D<int>* project);

void RenderObject(Canvas& canvas, Model& model);