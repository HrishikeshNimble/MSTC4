#include <windows.h>
#include <stdlib.h>
#include <time.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "Msimg32.lib")



#define TIMER_ID 1
#define DROP_COUNT 600     
#define MIN_SPEED 8        
#define MAX_SPEED 20       
#define MIN_SIZE 8         
#define MAX_SIZE 25        

typedef struct {
    int x, y, speed, size, alpha;
} Raindrop;

Raindrop raindrops[DROP_COUNT];
int screenWidth, screenHeight;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    HWND hwnd;
    MSG msg;

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "FullscreenWaterfall";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

    RegisterClass(&wc);

    hwnd = CreateWindowEx(WS_EX_TOPMOST, wc.lpszClassName, "Realistic Waterfall Effect",
        WS_POPUP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    HDC hdc, hdcMem;
    HBITMAP hbmMem;
    HBRUSH hBrush;
    PAINTSTRUCT ps;
    int i;

    switch (msg) {
        case WM_CREATE:
            SetTimer(hwnd, TIMER_ID, 30, NULL);
            srand((unsigned)time(0));

            
            screenWidth = GetSystemMetrics(SM_CXSCREEN);
            screenHeight = GetSystemMetrics(SM_CYSCREEN);

            
            for (i = 0; i < DROP_COUNT; i++) {
                raindrops[i].x = rand() % screenWidth;
                raindrops[i].y = rand() % screenHeight;
                raindrops[i].speed = MIN_SPEED + rand() % (MAX_SPEED - MIN_SPEED);
                raindrops[i].size = MIN_SIZE + rand() % (MAX_SIZE - MIN_SIZE);
                raindrops[i].alpha = 100 + rand() % 156;  
            }
            break;

        case WM_TIMER:
            if (wParam == TIMER_ID) {
               
                for (i = 0; i < DROP_COUNT; i++) {
                    raindrops[i].y += raindrops[i].speed;
                    if (raindrops[i].y > screenHeight) {
                        raindrops[i].y = 0;
                        raindrops[i].x = rand() % screenWidth;
                        raindrops[i].speed = MIN_SPEED + rand() % (MAX_SPEED - MIN_SPEED);
                        raindrops[i].size = MIN_SIZE + rand() % (MAX_SIZE - MIN_SIZE);
                        raindrops[i].alpha = 100 + rand() % 156; 
                    }
                }
                InvalidateRect(hwnd, NULL, FALSE);
            }
            break;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);

            
            hdcMem = CreateCompatibleDC(hdc);
            hbmMem = CreateCompatibleBitmap(hdc, screenWidth, screenHeight);
            SelectObject(hdcMem, hbmMem);

            
            TRIVERTEX vertex[2] = {
                {0, 0, 0, 0, 50 << 8, 255 << 8},       
                {screenWidth, screenHeight, 0, 0, 0, 120 << 8}  
            };
            GRADIENT_RECT gRect = {0, 1};
            GradientFill(hdcMem, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_V);

           
            for (i = 0; i < DROP_COUNT; i++) {
                int alpha = raindrops[i].alpha;
                HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 150 + (alpha / 5), 255 - (alpha / 8))); 
                SelectObject(hdcMem, hPen);
                MoveToEx(hdcMem, raindrops[i].x, raindrops[i].y, NULL);
                LineTo(hdcMem, raindrops[i].x, raindrops[i].y + raindrops[i].size);
                DeleteObject(hPen);
            }

           
            BitBlt(hdc, 0, 0, screenWidth, screenHeight, hdcMem, 0, 0, SRCCOPY);

            
            DeleteObject(hbmMem);
            DeleteDC(hdcMem);
            EndPaint(hwnd, &ps);
            break;

        case WM_DESTROY:
            KillTimer(hwnd, TIMER_ID);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

