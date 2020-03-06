#include "draw.h"

void drawAxis(HDC hdc, POINT p1, POINT p2)
{
  HPEN pen = CreatePen(PS_SOLID, 1, RGB(0xFF, 0, 0));
  SelectObject(hdc, pen);
  MoveToEx(hdc, p1.x, p1.y, nullptr);
  LineTo(hdc, p2.x, p2.y);
  DeleteObject(pen);
}

void drawPoint(HDC hdc, Point2D p)
{
  SetPixel(hdc, toLong((Rect.right - Rect.left) / 2.0 + p.x) , toLong((Rect.bottom - Rect.top) / 2.0 + p.y), RGB(0, 0, 0));
}

void drawLine(HDC hdc, Point2D p1, Point2D p2)
{
  HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
  SelectObject(hdc, pen);
  MoveToEx(hdc, toLong((Rect.right - Rect.left) / 2.0 + p1.x), toLong((Rect.bottom - Rect.top) / 2.0 + p1.y), nullptr);
  LineTo(hdc, toLong((Rect.right - Rect.left) / 2.0 + p2.x), toLong((Rect.bottom - Rect.top) / 2.0 + p2.y));
  DeleteObject(pen);
}

void RotatePoint(double angle, Point2D& p)
{
  double x = p.x;
  double y = p.y;
  p.x = x * cos(angle) - y * sin(angle);
  p.y = x * sin(angle) + y * cos(angle);
}

LONG toLong(double x)
{
  return static_cast<LONG>(round(x));
}
