#include <windows.h>
#include <stdlib.h>
#include <time.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "Msimg32.lib")



#define TIMER_ID 1
#define DROP_COUNT 600     // पानी की बूंदों की संख्या
#define MIN_SPEED 8        // न्यूनतम गति
#define MAX_SPEED 20       // अधिकतम गति
#define MIN_SIZE 8         // न्यूनतम लंबाई
#define MAX_SIZE 25        // अधिकतम लंबाई

typedef struct {
    int x, y, speed, size, alpha;
} Raindrop;

Raindrop raindrops[DROP_COUNT];
int screenWidth, screenHeight;

// विंडो प्रोसीजर
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

            // स्क्रीन साइज प्राप्त करें
            screenWidth = GetSystemMetrics(SM_CXSCREEN);
            screenHeight = GetSystemMetrics(SM_CYSCREEN);

            // पानी की बूंदों को रेंडम पोजीशन पर सेट करें
            for (i = 0; i < DROP_COUNT; i++) {
                raindrops[i].x = rand() % screenWidth;
                raindrops[i].y = rand() % screenHeight;
                raindrops[i].speed = MIN_SPEED + rand() % (MAX_SPEED - MIN_SPEED);
                raindrops[i].size = MIN_SIZE + rand() % (MAX_SIZE - MIN_SIZE);
                raindrops[i].alpha = 100 + rand() % 156;  // बूंदों की ट्रांसपेरेंसी
            }
            break;

        case WM_TIMER:
            if (wParam == TIMER_ID) {
                // बूंदों को नीचे गिराएं
                for (i = 0; i < DROP_COUNT; i++) {
                    raindrops[i].y += raindrops[i].speed;
                    if (raindrops[i].y > screenHeight) {
                        raindrops[i].y = 0;
                        raindrops[i].x = rand() % screenWidth;
                        raindrops[i].speed = MIN_SPEED + rand() % (MAX_SPEED - MIN_SPEED);
                        raindrops[i].size = MIN_SIZE + rand() % (MAX_SIZE - MIN_SIZE);
                        raindrops[i].alpha = 100 + rand() % 156; // ट्रांसपेरेंसी को रेंडमाइज़ करें
                    }
                }
                InvalidateRect(hwnd, NULL, FALSE);
            }
            break;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);

            // डबल बफरिंग (स्मूद रेंडरिंग के लिए)
            hdcMem = CreateCompatibleDC(hdc);
            hbmMem = CreateCompatibleBitmap(hdc, screenWidth, screenHeight);
            SelectObject(hdcMem, hbmMem);

            // बैकग्राउंड को ग्रेडिएंट ब्लू करें (रियलिस्टिक वाटरफॉल बैकग्राउंड)
            TRIVERTEX vertex[2] = {
                {0, 0, 0, 0, 50 << 8, 255 << 8},       // ऊपर हल्का ब्लू
                {screenWidth, screenHeight, 0, 0, 0, 120 << 8}  // नीचे गहरा ब्लू
            };
            GRADIENT_RECT gRect = {0, 1};
            GradientFill(hdcMem, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_V);

            // बूंदों को ड्रा करें (हल्की ट्रांसपेरेंसी के साथ)
            for (i = 0; i < DROP_COUNT; i++) {
                int alpha = raindrops[i].alpha;
                HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 150 + (alpha / 5), 255 - (alpha / 8))); // हल्का चमकीला प्रभाव
                SelectObject(hdcMem, hPen);
                MoveToEx(hdcMem, raindrops[i].x, raindrops[i].y, NULL);
                LineTo(hdcMem, raindrops[i].x, raindrops[i].y + raindrops[i].size);
                DeleteObject(hPen);
            }

            // बफर से स्क्रीन पर कॉपी करें
            BitBlt(hdc, 0, 0, screenWidth, screenHeight, hdcMem, 0, 0, SRCCOPY);

            // क्लीनअप
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

// मुख्य फ़ंक्शन (फुल स्क्रीन मोड में लाने के लिए)
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
