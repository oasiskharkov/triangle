#define _USE_MATH_DEFINES

#pragma once 

#include <windows.h>
#include <windowsx.h>
#include <cmath>

struct Point2D
{
  double x;
  double y;
};

extern RECT Rect;

void drawAxis(HDC hdc, POINT p1, POINT p2);
void drawPoint(HDC hdc, Point2D p);
void drawLine(HDC hdc, Point2D p1, Point2D p2);
void RotatePoint(double angle, Point2D& p);
LONG toLong(double x);
