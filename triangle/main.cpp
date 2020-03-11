// include the basic windows header file
#include "draw.h"

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

RECT Rect{ 0, 0 };
Point2D p1{ 40.0, 40.0 };
Point2D p2{ 40.0, -40.0 };
Point2D p3{ -40.0,  0.0 };

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
  UINT message,
  WPARAM wParam,
  LPARAM lParam);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR lpCmdLine,
  int nCmdShow)
{
  // the handle for the window, filled by a function
  HWND hWnd;
  // this struct holds information for the window class
  WNDCLASSEX wc;

  // clear out the window class for use
  ZeroMemory(&wc, sizeof(WNDCLASSEX));

  // fill in the struct with the needed information
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wc.lpszClassName = L"WindowClass1";

  // register the window class
  RegisterClassEx(&wc);

  // create the window and use the result as the handle
  hWnd = CreateWindowEx(NULL,
    L"WindowClass1",    // name of the window class
    L"Triangle",   // title of the window
    WS_OVERLAPPEDWINDOW ^ WS_MINIMIZEBOX ^ WS_MAXIMIZEBOX,    // window style
    300,    // x-position of the window
    300,    // y-position of the window
    SCREEN_WIDTH,    // width of the window
    SCREEN_HEIGHT,    // height of the window
    NULL,    // we have no parent window, NULL
    NULL,    // we aren't using menus, NULL
    hInstance,    // application handle
    NULL);    // used with multiple windows, NULL

// display the window on the screen
  ShowWindow(hWnd, nCmdShow);

  // enter the main loop:

  // this struct holds Windows event messages
  MSG msg;

  // enter the infinite message loop
  while (GetMessage(&msg, NULL, 0, 0))
  {
    // translate keystroke messages into the right format
    TranslateMessage(&msg);

    // send the message to the WindowProc function
    DispatchMessage(&msg);
  }

  // return this part of the WM_QUIT message to Windows
  return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
	HDC hdc, hCompatibleDC;
	HBITMAP hBmp;
  
  // sort through and find what code to run for the message given
  switch (message)
  {
    // this message is read when the window is closed
  case WM_DESTROY:
  {
    // close the application entirely
    PostQuitMessage(0);
    return 0;
  } break;
  case WM_PAINT:
    GetClientRect(hWnd, &Rect);
    hdc = BeginPaint(hWnd, &ps);
    // Создание нового контекста для двойной буфферизации
    hCompatibleDC = CreateCompatibleDC(hdc);
    hBmp = CreateCompatibleBitmap(hdc, Rect.right - Rect.left,
      Rect.bottom - Rect.top);
    SelectObject(hCompatibleDC, hBmp);
    // Закраска фоновым цветом
    LOGBRUSH br;
    br.lbStyle = BS_SOLID;
    br.lbColor = 0xEECCCC;
    HBRUSH brush;
    brush = CreateBrushIndirect(&br);
    FillRect(hCompatibleDC, &Rect, brush);
    DeleteObject(brush);

    // draw axis
    drawAxis(hCompatibleDC, { Rect.left, (Rect.bottom - Rect.top) / 2 }, { Rect.right, (Rect.bottom - Rect.top) / 2 });
    drawAxis(hCompatibleDC, { (Rect.right - Rect.left) / 2, Rect.top }, { (Rect.right - Rect.left) / 2, Rect.bottom });

    // draw triangle
    drawLine(hCompatibleDC, p1, p2);
    drawLine(hCompatibleDC, p2, p3);
    drawLine(hCompatibleDC, p3, p1);

    // draw to the screen
    SetStretchBltMode(hdc, COLORONCOLOR);
    BitBlt(hdc, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top,
      hCompatibleDC, 0, 0, SRCCOPY);
    DeleteDC(hCompatibleDC);
    DeleteObject(hBmp);
    hCompatibleDC = NULL;
    EndPaint(hWnd, &ps);
    break;
  case WM_KEYDOWN:
  {
    if (wParam == VK_LEFT)
    {
      RotatePoint(5 * M_PI / 180, p1);
      RotatePoint(5 * M_PI / 180, p2);
      RotatePoint(5 * M_PI / 180, p3);
      InvalidateRect(hWnd, NULL, false);
    }
    if (wParam == VK_RIGHT)
    {
      RotatePoint(-5 * M_PI / 180, p1);
      RotatePoint(-5 * M_PI / 180, p2);
      RotatePoint(-5 * M_PI / 180, p3);
      InvalidateRect(hWnd, NULL, false);
    }
    if (wParam == VK_UP)
    {
      ScalePoint(0.1, p1);
      ScalePoint(0.1, p2);
      ScalePoint(0.1, p3);
      InvalidateRect(hWnd, NULL, false);
    }
    if (wParam == VK_DOWN)
    {
      ScalePoint(-0.1, p1);
      ScalePoint(-0.1, p2);
      ScalePoint(-0.1, p3);
      InvalidateRect(hWnd, NULL, false);
    }
    if ((char)wParam == 'a' || (char)wParam == 'A')
    {
      MovePoint(-1.0, 0, p1);
      MovePoint(-1.0, 0, p2);
      MovePoint(-1.0, 0, p3);
      InvalidateRect(hWnd, NULL, false);
    }
    if ((char)wParam == 'd' || (char)wParam == 'D')
    {
      MovePoint(1.0, 0, p1);
      MovePoint(1.0, 0, p2);
      MovePoint(1.0, 0, p3);
      InvalidateRect(hWnd, NULL, false);
    }
    if ((char)wParam == 'w' || (char)wParam == 'W')
    {
      MovePoint(0.0, -1.0, p1);
      MovePoint(0.0, -1.0, p2);
      MovePoint(0.0, -1.0, p3);
      InvalidateRect(hWnd, NULL, false);
    }
    if ((char)wParam == 's' || (char)wParam == 'S')
    {
      MovePoint(0.0, 1.0, p1);
      MovePoint(0.0, 1.0, p2);
      MovePoint(0.0, 1.0, p3);
      InvalidateRect(hWnd, NULL, false);
    }
  } break;
  }

  // Handle any messages the switch statement didn't
  return DefWindowProc (hWnd, message, wParam, lParam);
}