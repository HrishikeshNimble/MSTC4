#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "..\include\global.h"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "Msimg32.lib")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    static TCHAR szClassName[] = TEXT("The Standard Window");
    static TCHAR szWindowTitle[] = TEXT("HelloWin");

    HWND hwnd = NULL;
    WNDCLASSEX wnd;
    MSG msg;

    ZeroMemory(&wnd, sizeof(WNDCLASSEX));
    ZeroMemory(&msg, sizeof(MSG));

    wnd.cbSize = sizeof(WNDCLASSEX);
    wnd.cbClsExtra = 0;
    wnd.cbWndExtra = 0;
    wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wnd.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
    wnd.hIconSm = wnd.hIcon;
    wnd.hInstance = hInstance;
    wnd.lpfnWndProc = WndProc;
    wnd.lpszClassName = szClassName;
    wnd.lpszMenuName = NULL;
    wnd.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&wnd))
    {
        MessageBox(NULL, TEXT("Failed to register a window class"), TEXT("RegisterClassEx"), MB_ICONERROR | MB_TOPMOST);
        ExitProcess(EXIT_FAILURE);
    }

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    hwnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        szClassName,
        szWindowTitle,
        WS_POPUP,
        0, 0,
        screenWidth,
        screenHeight,
        (HWND)NULL,
        (HMENU)NULL,
        hInstance,
        (LPVOID)NULL);

    if (hwnd == NULL)
    {
        MessageBox((HWND)NULL, TEXT("Failed to create a window"), TEXT("CreateWindowEx"), MB_ICONERROR | MB_TOPMOST);
        ExitProcess(EXIT_FAILURE);
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc, hdcMem;
    HBITMAP hbmMem;
    HBRUSH hBrush;
    PAINTSTRUCT ps;
    int i;

    static float scaleX = 1.0f, scaleY = 1.0f;

    switch (msg)
    {
    case WM_CREATE:
        SetTimer(hwnd, TIMER_ID_RAIN, 30, NULL);
        SetTimer(hwnd, TIMER_ID_QUOTE, 5000, NULL);

        srand((unsigned)time(0));

        screenWidth = GetSystemMetrics(SM_CXSCREEN);
        screenHeight = GetSystemMetrics(SM_CYSCREEN);

        scaleX = screenWidth / 1920.0f;
        scaleY = screenHeight / 1080.0f;

        for (i = 0; i < DROP_COUNT; i++)
        {
            raindrops[i].x = rand() % screenWidth;
            raindrops[i].y = rand() % screenHeight;
            raindrops[i].speed = MIN_SPEED + rand() % (MAX_SPEED - MIN_SPEED);
            raindrops[i].size = MIN_SIZE + rand() % (MAX_SIZE - MIN_SIZE);
            raindrops[i].alpha = 100 + rand() % 156;
        }

        hwndParent = (HWND)((CREATESTRUCT *)lParam)->lpCreateParams;
        break;

    case WM_TIMER:
        if (wParam == TIMER_ID_RAIN)
        {
            for (i = 0; i < DROP_COUNT; i++)
            {
                raindrops[i].y += raindrops[i].speed;
                if (raindrops[i].y > screenHeight)
                {
                    raindrops[i].y = 0;
                    raindrops[i].x = rand() % screenWidth;
                    raindrops[i].speed = MIN_SPEED + rand() % (MAX_SPEED - MIN_SPEED);
                    raindrops[i].size = MIN_SIZE + rand() % (MAX_SIZE - MIN_SIZE);
                    raindrops[i].alpha = 100 + rand() % 156;
                }
            }
            InvalidateRect(hwnd, NULL, FALSE);
        }

        if (wParam == TIMER_ID_QUOTE)
        {
            static int step = 0;
            step = (step + 1) % 9;

            switch (step)
            {
            case 1:
                showLine1 = TRUE;
                break;
            case 2:
                showPinkRect = TRUE;
                break;
            case 3:
                showLine2 = TRUE;
                break;
            case 4:
                showBlueRect = TRUE;
                break;
            case 5:
                showLine3 = TRUE;
                break;
            case 6:
                showorangeRect = TRUE;
                break;
            case 7:
                showLine4 = TRUE;
                break;
            case 8:
                showaorangeRect = TRUE;
                break;
            }
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);
        hdcMem = CreateCompatibleDC(hdc);
        hbmMem = CreateCompatibleBitmap(hdc, screenWidth, screenHeight);
        HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hbmMem);

        TRIVERTEX vertex[2] = {
            {0, 0, 0, 0, 50 << 8, 255 << 8},
            {screenWidth, screenHeight, 0, 0, 0, 120 << 8}};
        GRADIENT_RECT gRect = {0, 1};
        GradientFill(hdcMem, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_V);

        for (i = 0; i < DROP_COUNT; i++)
        {
            int alpha = raindrops[i].alpha;
            HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 150 + (alpha / 5), 255 - (alpha / 8)));
            HPEN hOldPen = (HPEN)SelectObject(hdcMem, hPen);

            MoveToEx(hdcMem, raindrops[i].x, raindrops[i].y, NULL);
            LineTo(hdcMem, raindrops[i].x, raindrops[i].y + raindrops[i].size);

            SelectObject(hdcMem, hOldPen);
            DeleteObject(hPen);
        }

        RECT rect;
        GetClientRect(hwnd, &rect);

        HBRUSH hBrushYellow = CreateSolidBrush(RGB(255, 255, 153));
        RECT yellowRect = {0, 0, rect.right, (int)(150 * scaleY)};
        FillRect(hdcMem, &yellowRect, hBrushYellow);
        DeleteObject(hBrushYellow);

        int quoteFontSize;
        if ((screenWidth == 1680 && screenHeight == 1050) ||
            (screenWidth == 1280 && screenHeight == 1024) ||
            (screenWidth == 1024 && screenHeight == 768) ||
            (screenWidth == 800 && screenHeight == 600))
        {
            quoteFontSize = 28;
        }
        else
        {
            quoteFontSize = 35;
        }

        HFONT hFontYellow = CreateFont((int)(80 * scaleY), 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                       DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                       CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                       DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
        HFONT hOldFont = (HFONT)SelectObject(hdcMem, hFontYellow);

        SetTextColor(hdcMem, RGB(0, 0, 0));
        SetBkMode(hdcMem, TRANSPARENT);

        const TCHAR *quote = TEXT("QUOTES");
        RECT textRect = {0, 0, rect.right, (int)(150 * scaleY)};
        DrawText(hdcMem, quote, -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        SelectObject(hdcMem, hOldFont);
        DeleteObject(hFontYellow);

        // Draw lines and rectangles with quotes

        if (showLine1)
        {
            HPEN hPen = CreatePen(PS_SOLID, 10, RGB(227, 227, 227));
            HPEN hOld = (HPEN)SelectObject(hdcMem, hPen);
            int x = (int)(850 * scaleX), y = (int)(150 * scaleY);
            MoveToEx(hdcMem, x, y, NULL);
            LineTo(hdcMem, x, y + (int)(200 * scaleY));
            SelectObject(hdcMem, hOld);
            DeleteObject(hPen);
        }

        if (showPinkRect)
        {
            RECT r = {
                (int)(800 * scaleX), (int)(350 * scaleY),
                (int)((800 + 700) * scaleX), (int)((350 + 100) * scaleY)};
            HBRUSH hBrush = CreateSolidBrush(RGB(255, 182, 193));
            FillRect(hdcMem, &r, hBrush);
            DeleteObject(hBrush);

            HFONT hFont = CreateFont((int)(quoteFontSize * scaleY), 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                     DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                     CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                     DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
            HFONT hOldFont = (HFONT)SelectObject(hdcMem, hFont);

            DrawText(hdcMem, TEXT("Basic is advanced and advanced is basic"), -1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            SelectObject(hdcMem, hOldFont);
            DeleteObject(hFont);
        }

        if (showBlueRect)
        {
            RECT r = {
                (int)(600 * scaleX), (int)(600 * scaleY),
                (int)((600 + 700) * scaleX), (int)((400 + 100) * scaleY)};
            HBRUSH hBrush = CreateSolidBrush(RGB(173, 216, 230));
            FillRect(hdcMem, &r, hBrush);
            DeleteObject(hBrush);

            HFONT hFont = CreateFont((int)(quoteFontSize * scaleY), 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                     DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                     CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                     DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
            HFONT hOld = (HFONT)SelectObject(hdcMem, hFont);
            DrawText(hdcMem, TEXT("Unix is mother of all OS"), -1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            SelectObject(hdcMem, hOld);
            DeleteObject(hFont);
        }

        if (showLine2)
        {
            HPEN hPen = CreatePen(PS_SOLID, 10, RGB(255, 213, 128));
            HPEN hOld = (HPEN)SelectObject(hdcMem, hPen);
            int x = (int)(650 * scaleX), y = (int)(150 * scaleY);
            MoveToEx(hdcMem, x, y, NULL);
            LineTo(hdcMem, x, y + (int)(350 * scaleY));
            SelectObject(hdcMem, hOld);
            DeleteObject(hPen);
        }

        if (showLine3)
        {
            HPEN hPen = CreatePen(PS_SOLID, 10, RGB(178, 164, 150));
            HPEN hOld = (HPEN)SelectObject(hdcMem, hPen);
            int x = (int)(450 * scaleX), y = (int)(150 * scaleY);
            MoveToEx(hdcMem, x, y, NULL);
            LineTo(hdcMem, x, y + (int)(550 * scaleY));
            SelectObject(hdcMem, hOld);
            DeleteObject(hPen);
        }

        if (showorangeRect)
        {
            RECT r = {
                (int)(400 * scaleX), (int)(700 * scaleY),
                (int)((400 + 700) * scaleX), (int)((700 + 100) * scaleY)};
            HBRUSH hBrush = CreateSolidBrush(RGB(255, 247, 8));
            FillRect(hdcMem, &r, hBrush);
            DeleteObject(hBrush);

            HFONT hFont = CreateFont((int)(quoteFontSize * scaleY), 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                     DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                     CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                     DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
            HFONT hOld = (HFONT)SelectObject(hdcMem, hFont);
            DrawText(hdcMem, TEXT("Knowledge is inter-related"), -1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            SelectObject(hdcMem, hOld);
            DeleteObject(hFont);
        }

        if (showLine4)
        {
            HPEN hPen = CreatePen(PS_SOLID, 10, RGB(242, 194, 238));
            HPEN hOld = (HPEN)SelectObject(hdcMem, hPen);
            int x = (int)(250 * scaleX), y = (int)(150 * scaleY);
            MoveToEx(hdcMem, x, y, NULL);
            LineTo(hdcMem, x, y + (int)(750 * scaleY));
            SelectObject(hdcMem, hOld);
            DeleteObject(hPen);
        }

        if (showaorangeRect)
        {
            RECT r = {
                (int)(200 * scaleX), (int)(900 * scaleY),
                (int)((200 + 700) * scaleX), (int)((900 + 100) * scaleY)};
            HBRUSH hBrush = CreateSolidBrush(RGB(84, 182, 202));
            FillRect(hdcMem, &r, hBrush);
            DeleteObject(hBrush);

            HFONT hFont = CreateFont((int)(quoteFontSize * scaleY), 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                     DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                     CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                     DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
            HFONT hOld = (HFONT)SelectObject(hdcMem, hFont);
            DrawText(hdcMem, TEXT("C is the mother of all programming languages."), -1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            SelectObject(hdcMem, hOld);
            DeleteObject(hFont);
        }

        BitBlt(hdc, 0, 0, screenWidth, screenHeight, hdcMem, 0, 0, SRCCOPY);

        SelectObject(hdcMem, hOldBitmap);
        DeleteObject(hbmMem);
        DeleteDC(hdcMem);

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        KillTimer(hwnd, TIMER_ID_RAIN);
        KillTimer(hwnd, TIMER_ID_QUOTE);
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
        {
            PostQuitMessage(0);
        }
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

// मुख्य फ़ंक्शन (फुल स्क्रीन मोड में लाने के लिए)
