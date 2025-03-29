#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "..\include\global.h"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "Winmm.lib")



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    static TCHAR szClassName[] = TEXT("The standard window");
    static TCHAR szWindowTitle[] = TEXT("HelloWin--> Manasi Shete");

    HWND hwnd = NULL;

    WNDCLASSEX wnd;
    MSG msg;

    ZeroMemory(&wnd, sizeof(WNDCLASSEX));
    ZeroMemory(&msg, sizeof(MSG));

    wnd.cbSize = sizeof(WNDCLASSEX);
    wnd.cbClsExtra = 0;
    wnd.cbWndExtra = 0;
    wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wnd.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
    wnd.hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    wnd.hIconSm = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    wnd.hInstance = hInstance;
    wnd.lpfnWndProc = WndProc;
    wnd.lpszClassName = szClassName;
    wnd.lpszMenuName = NULL;
    wnd.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&wnd))
    {
        MessageBox(
            NULL,
            TEXT("Failed to register a window class"),
            TEXT("RegisterClassEx"),
            MB_ICONERROR | MB_TOPMOST);
        ExitProcess(EXIT_FAILURE);
    }

    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);

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
        MessageBox(
            (HWND)NULL,
            TEXT("Failed to create an application window"),
            TEXT("CreateWindowEx"),
            MB_ICONERROR | MB_TOPMOST);
        ExitProcess(EXIT_FAILURE);
    }

    // Initialize particles
    srand((unsigned int)time(NULL));
    for (int i = 0; i < NUM_PARTICLES; i++)
    {
        particles[i].x = rand() % screenWidth;
        particles[i].y = rand() % screenHeight;
        particles[i].dx = (rand() % 5) - 2;
        particles[i].dy = (rand() % 5) - 2;
        particles[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
    }

    AnimateWindow(hwnd, 400, AW_SLIDE | AW_HOR_POSITIVE | AW_VER_POSITIVE);
    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    SetTimer(hwnd, TIMER_ID, 20, NULL);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return ((int)msg.wParam);
}

// Window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int cxScreen, cyScreen;
    static int rectWidth = 0, rectHeight = 200;
    static int rectSpeed = 5;
    static BOOL rectExpanded = FALSE;
    static BOOL textDisplayed = FALSE;
    static BOOL lineDisplayed = FALSE;
    static BOOL horizontalLineDisplayed = FALSE;
    static BOOL rectangleDisplayed = FALSE;  // New flag for rectangle
    static BOOL textInRectDisplayed = FALSE; // Flag for text inside the rectangle
    static BOOL borderAnimationStarted = FALSE;
    static BOOL lineBelowRectDisplayed = FALSE; // New flag for the line below the rectangle
    static BOOL horizontalLineDisplayed1 = FALSE;
    static BOOL horizontalLineDisplayed2 = FALSE;
    static BOOL verticleLineDisplayed1 = FALSE;
    static BOOL newRectangleDisplayed = FALSE;
    static BOOL textInRectDisplayed1 = FALSE;
    static BOOL textInRectDisplayed2 = FALSE;
    static BOOL textInRectDisplayed3 = FALSE;
    static BOOL textInRectDisplayed4 = FALSE;
    static BOOL textInRectDisplayed5 = FALSE;
    static BOOL textInRectDisplayed6 = FALSE;
    static UINT_PTR newRectangleTimerId = 1004;  // Unique timer ID for the new rectangle
    static UINT_PTR newRectangleTimerId1 = 1005; // Unique timer ID for the new rectangle
    static UINT_PTR newRectangleTimerId2 = 1006; // Unique timer ID for the new rectangle
    static UINT_PTR newRectangleTimerId3 = 1007; // Unique timer ID for the new rectangle
    static UINT_PTR newRectangleTimerId5 = 1008; // Unique timer ID for the new rectangle
    static UINT_PTR newRectangleTimerId6 = 1009; // Unique timer ID for the new rectangle
    static BOOL verticleLineDisplayed2 = FALSE;
    static BOOL verticleLineDisplayed3 = FALSE;
    static BOOL verticleLineDisplayed4 = FALSE;
    static BOOL verticleLineDisplayed5 = FALSE;
    static BOOL verticleLineDisplayed6 = FALSE;
    static BOOL newRectangleDisplayed1 = FALSE;
    static BOOL newRectangleDisplayed2 = FALSE;
    static BOOL newRectangleDisplayed3 = FALSE;
    static BOOL newRectangleDisplayed5 = FALSE;
    static BOOL newRectangleDisplayed6 = FALSE;
    static BOOL lineBelowRectDisplayed3 = FALSE;

    static UINT_PTR textTimerId = 2, lineTimerId = 3, rectangleTimerId = 4;
    static UINT_PTR textInRectTimerId = 5; // Timer ID for text inside the rectangle
    static UINT_PTR borderTimerId = 6;
    static UINT_PTR lineBelowRectDisplayedTimerId = 7;
    static UINT_PTR horizontalLineTimerId = 8;   // Timer ID for the horizontal line
    static UINT_PTR horizontalLineTimerId1 = 18; // Timer ID for the horizontal line
    static UINT_PTR verticleLineTimerId = 9;     // Timer ID for the horizontal line
    static UINT_PTR verticleLineTimerId1 = 11;   // Timer ID for the horizontal line
    static UINT_PTR verticleLineTimerId2 = 13;   // Timer ID for the horizontal line
    static UINT_PTR verticleLineTimerId3 = 15;   // Timer ID for the horizontal line
    static UINT_PTR verticleLineTimerId5 = 19;   // Timer ID for the horizontal line
    static UINT_PTR verticleLineTimerId6 = 22;   // Timer ID for the horizontal line
    static UINT_PTR textInRectTimerId1 = 10;
    static UINT_PTR textInRectTimerId2 = 12;
    static UINT_PTR textInRectTimerId3 = 14;
    static UINT_PTR textInRectTimerId4 = 16;
    static UINT_PTR textInRectTimerId5 = 21;
    static UINT_PTR textInRectTimerId6 = 31;
    static UINT_PTR lineBelowRectDisplayedTimerId1 = 17;
    static int borderStep = 0;               // Step counter for the border animation
    static int borderX = 550, borderY = 250; // Starting position of the rectangle
    static int borderWidth = 250, borderHeight = 100;
    static HBITMAP hBitmap = NULL;
    static HDC hMemDC = NULL;

    HDC hdc;
    PAINTSTRUCT ps;

    switch (uMsg)
    {
    case WM_CREATE:
        PlaySound(TEXT("song.wav"), NULL, SND_FILENAME | SND_ASYNC);

        SetTimer(hwnd, TIMER_ID, 20, NULL);
        break;

    case WM_SIZE:
        cxScreen = LOWORD(lParam);
        cyScreen = HIWORD(lParam);

        if (hBitmap)
            DeleteObject(hBitmap);
        if (hMemDC)
            DeleteDC(hMemDC);

        hdc = GetDC(hwnd);
        hMemDC = CreateCompatibleDC(hdc);
        hBitmap = CreateCompatibleBitmap(hdc, cxScreen, cyScreen);
        SelectObject(hMemDC, hBitmap);
        ReleaseDC(hwnd, hdc);
        break;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);

        // Fill background
        HBRUSH hBrush = CreateSolidBrush(RGB(r, g, b));
        FillRect(hMemDC, &ps.rcPaint, hBrush);
        DeleteObject(hBrush);

        // Draw expanding rectangle
        HBRUSH rectBrush = CreateSolidBrush(RGB(255 - r, 255 - g, 255 - b));
        RECT movingRect = {0, 0, rectWidth, rectHeight};
        FillRect(hMemDC, &movingRect, rectBrush);
        DeleteObject(rectBrush);

        // Draw particles
        for (int i = 0; i < NUM_PARTICLES; i++)
        {
            HBRUSH particleBrush = CreateSolidBrush(particles[i].color);
            RECT rect = {particles[i].x, particles[i].y, particles[i].x + PARTICLE_SIZE, particles[i].y + PARTICLE_SIZE};
            FillRect(hMemDC, &rect, particleBrush);
            DeleteObject(particleBrush);
        }

        // Display text
        if (textDisplayed)
        {
            HFONT hFont = CreateFont(62, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
            SelectObject(hMemDC, hFont);
            SetBkMode(hMemDC, TRANSPARENT);

            int textX = rectWidth / 2;
            int textY = rectHeight / 2 - 24;

            SetTextColor(hMemDC, RGB(255, 255, 255));
            TextOut(hMemDC, textX - 220, textY, TEXT("WHAT"), 4);
            TextOut(hMemDC, textX - 40, textY, TEXT("IS"), 2);
            TextOut(hMemDC, textX + 35, textY, TEXT("COMPUTER"), 8);

            DeleteObject(hFont);
        }

        // Draw vertical and horizontal lines
        if (lineDisplayed)
        {
            HPEN hPen = CreatePen(PS_SOLID, 5, RGB(50, 50, 50));
            HPEN hOldPen = (HPEN)SelectObject(hMemDC, hPen);

            MoveToEx(hMemDC, rectWidth / 1.4, rectHeight, NULL);
            LineTo(hMemDC, rectWidth / 1.4, cyScreen);

            MoveToEx(hMemDC, 0, rectHeight, NULL);
            LineTo(hMemDC, cxScreen, rectHeight);

            SelectObject(hMemDC, hOldPen);
            DeleteObject(hPen);
        }

        if (rectangleDisplayed)
        {

            // Coordinates for the rectangle border (top, right, bottom, left)
            RECT borderRect = {550, 250, 550 + 250, 250 + 100};
            // Fill the rectangle with a dark color
            HBRUSH fillBrush = CreateSolidBrush(RGB(50, 50, 50)); // Dark gray color for filling
            FillRect(hMemDC, &borderRect, fillBrush);
            DeleteObject(fillBrush);

            // Draw the permanent rectangle border using a pen
            HPEN borderPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 255)); // White pen for the border
            HPEN hOldPen = (HPEN)SelectObject(hMemDC, borderPen);

            // Draw top side
            MoveToEx(hMemDC, borderRect.left, borderRect.top, NULL);
            LineTo(hMemDC, borderRect.right, borderRect.top);

            // Draw right side
            MoveToEx(hMemDC, borderRect.right, borderRect.top, NULL);
            LineTo(hMemDC, borderRect.right, borderRect.bottom);

            // Draw bottom side
            MoveToEx(hMemDC, borderRect.right, borderRect.bottom, NULL);
            LineTo(hMemDC, borderRect.left, borderRect.bottom);

            // Draw left side
            MoveToEx(hMemDC, borderRect.left, borderRect.bottom, NULL);
            LineTo(hMemDC, borderRect.left, borderRect.top);

            // Clean up
            SelectObject(hMemDC, hOldPen);
            DeleteObject(borderPen);

            if (textInRectDisplayed)
            {
                HFONT rectFont = CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
                SelectObject(hMemDC, rectFont);
                SetBkMode(hMemDC, TRANSPARENT);

                SetTextColor(hMemDC, RGB(255, 255, 255));
                DrawText(hMemDC, TEXT("COMPUTER"), -1, &borderRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

                DeleteObject(rectFont);
            }

        if (lineBelowRectDisplayed)
        {
                HPEN linePen = CreatePen(PS_SOLID, 5, RGB(139, 69, 19)); // Dark brown pen for the line
                HPEN hOldPen = (HPEN)SelectObject(hMemDC, linePen);

                // Start position of the line (center of the rectangle)
                int lineStartX = borderRect.left + borderWidth / 2;
                int lineStartY = borderRect.bottom;

                // End position of the line (100px below the bottom of the rectangle)
                int lineEndY = lineStartY + 100;

                // Draw the line
                MoveToEx(hMemDC, lineStartX, lineStartY, NULL);
                LineTo(hMemDC, lineStartX, lineEndY);

                SelectObject(hMemDC, hOldPen);
                DeleteObject(linePen);
        }
        if (horizontalLineDisplayed1)
            {
                HPEN hPen = CreatePen(PS_SOLID, 5, RGB(139, 69, 19)); // Same color as the vertical line
                HPEN hOldPen = (HPEN)SelectObject(hMemDC, hPen);

                // Draw the horizontal line at the bottom of the rectangle
                MoveToEx(hMemDC, borderRect.left - 400, borderRect.bottom + 100, NULL); // Starting point
                LineTo(hMemDC, borderRect.right + 400, borderRect.bottom + 100);        // Ending point (width 600)

                SelectObject(hMemDC, hOldPen);
                DeleteObject(hPen);
            }

            // Now for the vertical line from the left endpoint of the horizontal line
            if (verticleLineDisplayed1 && horizontalLineDisplayed1)
            {
                HPEN linePen = CreatePen(PS_SOLID, 5, RGB(139, 69, 19)); // Dark brown pen for the line
                HPEN hOldPen = (HPEN)SelectObject(hMemDC, linePen);

                // Left endpoint of the horizontal line (where the vertical line will start)
                int lineStartX = borderRect.left - 400;   // X position where the horizontal line starts (left end)
                int lineStartY = borderRect.bottom + 100; // Y position where the horizontal line ends (bottom + 100px)

                // The vertical line should go down 100px
                int lineEndY = lineStartY + 100;

                // Draw the vertical line
                MoveToEx(hMemDC, lineStartX, lineStartY, NULL);
                LineTo(hMemDC, lineStartX, lineEndY);

                SelectObject(hMemDC, hOldPen);
                DeleteObject(linePen);
            }

            if (newRectangleDisplayed)
            {
                // Rectangle coordinates
                RECT newRect = {50, 550, 50 + 250, 550 + 100};

                // Fill rectangle
                HBRUSH fillBrush1 = CreateSolidBrush(RGB(0, 0, 139)); // Orange color
                FillRect(hMemDC, &newRect, fillBrush1);
                DeleteObject(fillBrush1);

                // Draw border
                HPEN newBorderPen1 = CreatePen(PS_SOLID, 5, RGB(0,102,102)); // White border
                HPEN hOldPen1 = (HPEN)SelectObject(hMemDC, newBorderPen1);
                MoveToEx(hMemDC, newRect.left, newRect.top, NULL);
                LineTo(hMemDC, newRect.right, newRect.top);
                LineTo(hMemDC, newRect.right, newRect.bottom);
                LineTo(hMemDC, newRect.left, newRect.bottom);
                LineTo(hMemDC, newRect.left, newRect.top);
                SelectObject(hMemDC, hOldPen1);
                DeleteObject(newBorderPen1);

                if (textInRectDisplayed1)
                {
                    // Adjust RECT for text
                    RECT textRect = newRect;
                    InflateRect(&textRect, -10, -10); // Add padding for text

                    // Create and select font
                    HFONT rectFont1 = CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                                 DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                                                 CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                                                 VARIABLE_PITCH, TEXT("Arial"));
                    HFONT oldFont = (HFONT)SelectObject(hMemDC, rectFont1);

                    // Set text properties
                    SetBkMode(hMemDC, TRANSPARENT);
                    SetTextColor(hMemDC, RGB(206, 206, 206));

                    // Draw text
                    int result = DrawText(hMemDC, TEXT("PROCESSOR"), -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    if (result == 0)
                    {
                        MessageBox(hwnd, TEXT("Failed to draw text!"), TEXT("Error"), MB_OK);
                    }

                    // Clean up font
                    SelectObject(hMemDC, oldFont);
                    DeleteObject(rectFont1);
                }
                // Now for the vertical line from the left endpoint of the horizontal line
            }

            if (verticleLineDisplayed2 && horizontalLineDisplayed1)
            {
                HPEN linePen = CreatePen(PS_SOLID, 5, RGB(139, 69, 19)); // Dark brown pen for the line
                HPEN hOldPen = (HPEN)SelectObject(hMemDC, linePen);

                // Left endpoint of the horizontal line (where the vertical line will start)
                int lineStartX = borderRect.left - 50;    // X position where the horizontal line starts (left end)
                int lineStartY = borderRect.bottom + 100; // Y position where the horizontal line ends (bottom + 100px)

                // The vertical line should go down 100px
                int lineEndY = lineStartY + 100;

                // Draw the vertical line
                MoveToEx(hMemDC, lineStartX, lineStartY, NULL);
                LineTo(hMemDC, lineStartX, lineEndY);

                SelectObject(hMemDC, hOldPen);
                DeleteObject(linePen);
            }

            if (newRectangleDisplayed1)
            {
                // Rectangle coordinates
                RECT newRect1 = {400, 550, 400 + 250, 550 + 100};

                // Fill rectangle
                HBRUSH fillBrush1 = CreateSolidBrush(RGB(128, 0, 128)); // purple color
                FillRect(hMemDC, &newRect1, fillBrush1);
                DeleteObject(fillBrush1);

                // Draw border
                HPEN newBorderPen2 = CreatePen(PS_SOLID, 5, RGB(172, 115, 101)); // White border
                HPEN hOldPen2 = (HPEN)SelectObject(hMemDC, newBorderPen2);
                MoveToEx(hMemDC, newRect1.left, newRect1.top, NULL);
                LineTo(hMemDC, newRect1.right, newRect1.top);
                LineTo(hMemDC, newRect1.right, newRect1.bottom);
                LineTo(hMemDC, newRect1.left, newRect1.bottom);
                LineTo(hMemDC, newRect1.left, newRect1.top);
                SelectObject(hMemDC, hOldPen2);
                DeleteObject(newBorderPen2);

                if (textInRectDisplayed2)
                {
                    // Adjust RECT for text
                    RECT textRect = newRect1;
                    InflateRect(&textRect, -10, -10); // Add padding for text

                    // Create and select font
                    HFONT rectFont1 = CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                                 DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                                                 CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                                                 VARIABLE_PITCH, TEXT("Arial"));
                    HFONT oldFont = (HFONT)SelectObject(hMemDC, rectFont1);

                    // Set text properties
                    SetBkMode(hMemDC, TRANSPARENT);
                    SetTextColor(hMemDC, RGB(255, 215, 0));

                    // Draw text
                    int result = DrawText(hMemDC, TEXT("MAIN MEMORY"), -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    if (result == 0)
                    {
                        MessageBox(hwnd, TEXT("Failed to draw text!"), TEXT("Error"), MB_OK);
                    }

                    // Clean up font
                    SelectObject(hMemDC, oldFont);
                    DeleteObject(rectFont1);
                }
                // Now for the vertical line from the left endpoint of the horizontal line
            }

            if (verticleLineDisplayed3 && horizontalLineDisplayed1)
            {
                HPEN linePen = CreatePen(PS_SOLID, 5, RGB(139, 69, 19)); // Dark brown pen for the line
                HPEN hOldPen = (HPEN)SelectObject(hMemDC, linePen);

                // Left endpoint of the horizontal line (where the vertical line will start)
                int lineStartX = borderRect.right + 50;   // X position where the horizontal line starts (left end)
                int lineStartY = borderRect.bottom + 100; // Y position where the horizontal line ends (bottom + 100px)

                // The vertical line should go down 100px
                int lineEndY = lineStartY + 100;

                // Draw the vertical line
                MoveToEx(hMemDC, lineStartX, lineStartY, NULL);
                LineTo(hMemDC, lineStartX, lineEndY);

                SelectObject(hMemDC, hOldPen);
                DeleteObject(linePen);
            }

            if (newRectangleDisplayed2)
            {
                // Rectangle coordinates
                RECT newRect2 = {750, 550, 750 + 250, 550 + 100};

                // Fill rectangle
                HBRUSH fillBrush2 = CreateSolidBrush(RGB(92, 54, 22)); // Orange color
                FillRect(hMemDC, &newRect2, fillBrush2);
                DeleteObject(fillBrush2);

                // Draw border
                HPEN newBorderPen3 = CreatePen(PS_SOLID, 5, RGB(185, 182, 179)); // White border
                HPEN hOldPen3 = (HPEN)SelectObject(hMemDC, newBorderPen3);
                MoveToEx(hMemDC, newRect2.left, newRect2.top, NULL);
                LineTo(hMemDC, newRect2.right, newRect2.top);
                LineTo(hMemDC, newRect2.right, newRect2.bottom);
                LineTo(hMemDC, newRect2.left, newRect2.bottom);
                LineTo(hMemDC, newRect2.left, newRect2.top);
                SelectObject(hMemDC, hOldPen3);
                DeleteObject(newBorderPen3);

                if (textInRectDisplayed3)
                {
                    // Adjust RECT for text
                    RECT textRect = newRect2;
                    InflateRect(&textRect, -10, -10); // Add padding for text

                    // Create and select font
                    HFONT rectFont1 = CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                                 DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                                                 CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                                                 VARIABLE_PITCH, TEXT("Arial"));
                    HFONT oldFont = (HFONT)SelectObject(hMemDC, rectFont1);

                    // Set text properties
                    SetBkMode(hMemDC, TRANSPARENT);
                    SetTextColor(hMemDC, RGB(40, 224, 224));

                    // Draw text
                    int result = DrawText(hMemDC, TEXT("INPUT SUBSYSTEM"), -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    if (result == 0)
                    {
                        MessageBox(hwnd, TEXT("Failed to draw text!"), TEXT("Error"), MB_OK);
                    }

                    // Clean up font
                    SelectObject(hMemDC, oldFont);
                    DeleteObject(rectFont1);
                }
                // Now for the vertical line from the left endpoint of the horizontal line
            }

            // Now for the vertical line from the left endpoint of the horizontal line
            if (verticleLineDisplayed4 && horizontalLineDisplayed1)
            {
                HPEN linePen = CreatePen(PS_SOLID, 5, RGB(139, 69, 19)); // Dark brown pen for the line
                HPEN hOldPen = (HPEN)SelectObject(hMemDC, linePen);

                // Left endpoint of the horizontal line (where the vertical line will start)
                int lineStartX = borderRect.right + 400;  // X position where the horizontal line starts (left end)
                int lineStartY = borderRect.bottom + 100; // Y position where the horizontal line ends (bottom + 100px)

                // The vertical line should go down 100px
                int lineEndY = lineStartY + 100;

                // Draw the vertical line
                MoveToEx(hMemDC, lineStartX, lineStartY, NULL);
                LineTo(hMemDC, lineStartX, lineEndY);

                SelectObject(hMemDC, hOldPen);
                DeleteObject(linePen);
            }

            if (newRectangleDisplayed3)
            {
                // Rectangle coordinates
                RECT newRect3 = {1100, 550, 1110 + 250, 550 + 100};

                // Fill rectangle
                HBRUSH fillBrush3 = CreateSolidBrush(RGB(66, 23, 23)); // Orange color
                FillRect(hMemDC, &newRect3, fillBrush3);
                DeleteObject(fillBrush3);

                // Draw border
                HPEN newBorderPen4 = CreatePen(PS_SOLID, 5, RGB(157, 169, 229)); // White border
                HPEN hOldPen4 = (HPEN)SelectObject(hMemDC, newBorderPen4);
                MoveToEx(hMemDC, newRect3.left, newRect3.top, NULL);
                LineTo(hMemDC, newRect3.right, newRect3.top);
                LineTo(hMemDC, newRect3.right, newRect3.bottom);
                LineTo(hMemDC, newRect3.left, newRect3.bottom);
                LineTo(hMemDC, newRect3.left, newRect3.top);
                SelectObject(hMemDC, hOldPen4);
                DeleteObject(newBorderPen4);

                if (textInRectDisplayed4)
                {
                    // Adjust RECT for text
                    RECT textRect = newRect3;
                    InflateRect(&textRect, -10, -10); // Add padding for text

                    // Create and select font
                    HFONT rectFont1 = CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                                 DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                                                 CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                                                 VARIABLE_PITCH, TEXT("Arial"));
                    HFONT oldFont = (HFONT)SelectObject(hMemDC, rectFont1);

                    // Set text properties
                    SetBkMode(hMemDC, TRANSPARENT);
                    SetTextColor(hMemDC, RGB(237, 185, 173));

                    // Draw text
                    int result = DrawText(hMemDC, TEXT("OUTPUT SUBSYSTEM"), -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    if (result == 0)
                    {
                        MessageBox(hwnd, TEXT("Failed to draw text!"), TEXT("Error"), MB_OK);
                    }

                    // Clean up font
                    SelectObject(hMemDC, oldFont);
                    DeleteObject(rectFont1);
                }
                // Now for the vertical line from the left endpoint of the horizontal line
            }

            if (lineBelowRectDisplayed3)
            {
                HPEN linePen1 = CreatePen(PS_SOLID, 5, RGB(139, 69, 19)); // Dark brown pen for the line
                HPEN hOldPen1 = (HPEN)SelectObject(hMemDC, linePen1);

                // Left endpoint of the horizontal line (where the vertical line will start)
                int lineStartX = borderRect.left - 400;   // X position where the horizontal line starts (left end)
                int lineStartY = borderRect.bottom + 300; // Y position where the horizontal line ends (bottom + 100px)

                // The vertical line should go down 100px
                int lineEndY = lineStartY + 100;

                // Draw the line
                MoveToEx(hMemDC, lineStartX, lineStartY, NULL);
                LineTo(hMemDC, lineStartX, lineEndY);

                SelectObject(hMemDC, hOldPen1);
                DeleteObject(linePen1);
            }

            if (horizontalLineDisplayed2)
            {
                // Create a pen for the horizontal line
                HPEN hPen1 = CreatePen(PS_SOLID, 5, RGB(139, 69, 19)); // Dark brown color
                HPEN hOldPen1 = (HPEN)SelectObject(hMemDC, hPen1);

                // Draw the horizontal line
                MoveToEx(hMemDC, borderRect.left - 450, borderRect.bottom + 400, NULL); // Starting point
                LineTo(hMemDC, borderRect.right - 300, borderRect.bottom + 400);        // Ending point

                SelectObject(hMemDC, hOldPen1);
                DeleteObject(hPen1);
            }

            if (verticleLineDisplayed5 && horizontalLineDisplayed2)
            {
                // Create a pen for the vertical line
                HPEN linePen1 = CreatePen(PS_SOLID, 5, RGB(139, 69, 19)); // Dark brown color
                HPEN hOldPen1 = (HPEN)SelectObject(hMemDC, linePen1);

                // Define the starting point of the vertical line
                int lineStartX = borderRect.left - 450;   // Same as the starting X of the horizontal line
                int lineStartY = borderRect.bottom + 400; // Same as the Y of the horizontal line

                // Define the ending Y coordinate of the vertical line (100px below the starting point)
                int lineEndY = lineStartY + 100;

                // Draw the vertical line
                MoveToEx(hMemDC, lineStartX, lineStartY, NULL);
                LineTo(hMemDC, lineStartX, lineEndY);

                SelectObject(hMemDC, hOldPen1);
                DeleteObject(linePen1);
            }

            if (newRectangleDisplayed5)
            {
                // Rectangle coordinates
                RECT newRect = {50, 850, 50 + 250, 850 + 100};

                // Fill rectangle
                HBRUSH fillBrush1 = CreateSolidBrush(RGB(204,255,51)); // Orange color
                FillRect(hMemDC, &newRect, fillBrush1);
                DeleteObject(fillBrush1);

                // Draw border
                HPEN newBorderPen1 = CreatePen(PS_SOLID, 5, RGB(51,102,204)); // White border
                HPEN hOldPen1 = (HPEN)SelectObject(hMemDC, newBorderPen1);
                MoveToEx(hMemDC, newRect.left, newRect.top, NULL);
                LineTo(hMemDC, newRect.right, newRect.top);
                LineTo(hMemDC, newRect.right, newRect.bottom);
                LineTo(hMemDC, newRect.left, newRect.bottom);
                LineTo(hMemDC, newRect.left, newRect.top);
                SelectObject(hMemDC, hOldPen1);
                DeleteObject(newBorderPen1);

                if (textInRectDisplayed5)
                {
                    // Adjust RECT for text
                    RECT textRect = newRect;
                    InflateRect(&textRect, -10, -10); // Add padding for text

                    // Create and select font
                    HFONT rectFont1 = CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                                 DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                                                 CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                                                 VARIABLE_PITCH, TEXT("Arial"));
                    HFONT oldFont = (HFONT)SelectObject(hMemDC, rectFont1);

                    // Set text properties
                    SetBkMode(hMemDC, TRANSPARENT);
                    SetTextColor(hMemDC, RGB(0,0,102));

                    // Draw text
                    int result = DrawText(hMemDC, TEXT("DATA PATH"), -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    if (result == 0)
                    {
                        MessageBox(hwnd, TEXT("Failed to draw text!"), TEXT("Error"), MB_OK);
                    }

                    // Clean up font
                    SelectObject(hMemDC, oldFont);
                    DeleteObject(rectFont1);
                }
                // Now for the vertical line from the left endpoint of the horizontal line
            }

            if (verticleLineDisplayed5 && horizontalLineDisplayed2)
            {
                // Create a pen for the vertical line
                HPEN linePen1 = CreatePen(PS_SOLID, 5, RGB(139, 69, 19)); // Dark brown color
                HPEN hOldPen1 = (HPEN)SelectObject(hMemDC, linePen1);

                // Define the starting point of the vertical line (right endpoint of the horizontal line)
                int lineStartX = borderRect.right - 300;  // Same as the ending X of the horizontal line
                int lineStartY = borderRect.bottom + 400; // Same as the Y of the horizontal line

                // Define the ending Y coordinate of the vertical line (100px below the starting point)
                int lineEndY = lineStartY + 100;

                // Draw the vertical line
                MoveToEx(hMemDC, lineStartX, lineStartY, NULL);
                LineTo(hMemDC, lineStartX, lineEndY);

                SelectObject(hMemDC, hOldPen1);
                DeleteObject(linePen1);
            }

            if (newRectangleDisplayed6)
            {
                // Rectangle coordinates
                RECT newRect1 = {400, 850, 400 + 250, 850 + 100};

                // Fill rectangle
                HBRUSH fillBrush1 = CreateSolidBrush(RGB(0,153,153)); // purple color
                FillRect(hMemDC, &newRect1, fillBrush1);
                DeleteObject(fillBrush1);

                // Draw border
                HPEN newBorderPen2 = CreatePen(PS_SOLID, 5, RGB(172, 115, 101)); // White border
                HPEN hOldPen2 = (HPEN)SelectObject(hMemDC, newBorderPen2);
                MoveToEx(hMemDC, newRect1.left, newRect1.top, NULL);
                LineTo(hMemDC, newRect1.right, newRect1.top);
                LineTo(hMemDC, newRect1.right, newRect1.bottom);
                LineTo(hMemDC, newRect1.left, newRect1.bottom);
                LineTo(hMemDC, newRect1.left, newRect1.top);
                SelectObject(hMemDC, hOldPen2);
                DeleteObject(newBorderPen2);

                if (textInRectDisplayed6)
                {
                    // Adjust RECT for text
                    RECT textRect = newRect1;
                    InflateRect(&textRect, -10, -10); // Add padding for text

                    // Create and select font
                    HFONT rectFont1 = CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                                 DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                                                 CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                                                 VARIABLE_PITCH, TEXT("Arial"));
                    HFONT oldFont = (HFONT)SelectObject(hMemDC, rectFont1);

                    // Set text properties
                    SetBkMode(hMemDC, TRANSPARENT);
                    SetTextColor(hMemDC, RGB(128,0,0));

                    // Draw text
                    int result = DrawText(hMemDC, TEXT("CONTROL PATH"), -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    if (result == 0)
                    {
                        MessageBox(hwnd, TEXT("Failed to draw text!"), TEXT("Error"), MB_OK);
                    }

                    // Clean up font
                    SelectObject(hMemDC, oldFont);
                    DeleteObject(rectFont1);
                }
                // Now for the vertical line from the left endpoint of the horizontal line
            }

            // Perform BitBlt operation after all drawing
            BitBlt(hdc, 0, 0, cxScreen, cyScreen, hMemDC, 0, 0, SRCCOPY);
            EndPaint(hwnd, &ps);

            BitBlt(hdc, 0, 0, cxScreen, cyScreen, hMemDC, 0, 0, SRCCOPY);
            EndPaint(hwnd, &ps);
            break;
        }

        BitBlt(hdc, 0, 0, cxScreen, cyScreen, hMemDC, 0, 0, SRCCOPY);
        EndPaint(hwnd, &ps);
        break;

        if (borderAnimationStarted)
        {
            HPEN borderPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255)); // White border
            HPEN oldPen = (HPEN)SelectObject(hMemDC, borderPen);

            // Draw based on the current border step
            if (borderStep == 0) // Top side
            {
                MoveToEx(hMemDC, borderX, borderY, NULL);
                LineTo(hMemDC, borderX + borderWidth, borderY);
            }
            else if (borderStep == 1) // Right side
            {
                MoveToEx(hMemDC, borderX + borderWidth, borderY, NULL);
                LineTo(hMemDC, borderX + borderWidth, borderY + borderHeight);
            }
            else if (borderStep == 2) // Bottom side
            {
                MoveToEx(hMemDC, borderX + borderWidth, borderY + borderHeight, NULL);
                LineTo(hMemDC, borderX, borderY + borderHeight);
            }
            else if (borderStep == 3) // Left side
            {
                MoveToEx(hMemDC, borderX, borderY + borderHeight, NULL);
                LineTo(hMemDC, borderX, borderY);
            }

            SelectObject(hMemDC, oldPen);
            DeleteObject(borderPen);
        }

        BitBlt(hdc, 0, 0, cxScreen, cyScreen, hMemDC, 0, 0, SRCCOPY);
        EndPaint(hwnd, &ps);
        break;

    case WM_TIMER:
        if (wParam == textTimerId)
        {
            textDisplayed = TRUE;
            KillTimer(hwnd, textTimerId);
            SetTimer(hwnd, lineTimerId, 3000, NULL);
        }
        else if (wParam == lineTimerId)
        {
            lineDisplayed = TRUE;
            KillTimer(hwnd, lineTimerId);
            SetTimer(hwnd, rectangleTimerId, 2000, NULL);
        }
        else if (wParam == rectangleTimerId)
        {
            rectangleDisplayed = TRUE;
            KillTimer(hwnd, rectangleTimerId);
            SetTimer(hwnd, textInRectTimerId, 3000, NULL); // Start timer for text in the rectangle
        }
        else if (wParam == textInRectTimerId)
        {
            textInRectDisplayed = TRUE; // Display the text inside the rectangle
            KillTimer(hwnd, textInRectTimerId);
            // Start border animation
            borderAnimationStarted = TRUE;
            SetTimer(hwnd, borderTimerId, 500, NULL); // 500ms for each border step

            // Start the timer for the line below the rectangle
            SetTimer(hwnd, lineBelowRectDisplayedTimerId, 2000, NULL); // 2 seconds delay
        }
        else if (wParam == borderTimerId)
        {
            borderStep++;

            // If all sides are drawn, stop the animation
            if (borderStep > 3)
            {
                KillTimer(hwnd, borderTimerId);
                borderAnimationStarted = FALSE;
            }

            InvalidateRect(hwnd, NULL, FALSE); // Redraw the window
        }
        else if (wParam == lineBelowRectDisplayedTimerId)
        {
            lineBelowRectDisplayed = TRUE; // Display the line below the rectangle
            KillTimer(hwnd, lineBelowRectDisplayedTimerId);

            // Start the timer for the horizontal line (after 3 seconds)
            SetTimer(hwnd, horizontalLineTimerId, 3000, NULL); // 3 seconds delay
            InvalidateRect(hwnd, NULL, FALSE);                 // Trigger window redraw
        }
        else if (wParam == horizontalLineTimerId)
        {
            horizontalLineDisplayed1 = TRUE; // Set the flag to display the horizontal line
            KillTimer(hwnd, horizontalLineTimerId);
            SetTimer(hwnd, verticleLineTimerId, 3000, NULL);
            InvalidateRect(hwnd, NULL, FALSE); // Trigger window redraw
        }
        else if (wParam == verticleLineTimerId)
        {
            verticleLineDisplayed1 = TRUE;
            KillTimer(hwnd, verticleLineTimerId);
            SetTimer(hwnd, newRectangleTimerId, 3000, NULL); // Trigger the new rectangle after 3 seconds
            InvalidateRect(hwnd, NULL, FALSE);               // Trigger window redraw
        }
        if (wParam == newRectangleTimerId)
        {
            newRectangleDisplayed = TRUE; // Display the rectangle
            KillTimer(hwnd, newRectangleTimerId);

            // Start the timer for displaying text after 3 seconds
            SetTimer(hwnd, textInRectTimerId1, 3000, NULL); // 3-second delay
            InvalidateRect(hwnd, NULL, FALSE);              // Trigger a redraw
        }
        else if (wParam == textInRectTimerId1)
        {
            textInRectDisplayed1 = TRUE; // Display the text inside the new rectangle
            KillTimer(hwnd, textInRectTimerId1);
            SetTimer(hwnd, verticleLineTimerId1, 3000, NULL); // Trigger the new rectangle after 3 seconds
            InvalidateRect(hwnd, NULL, FALSE);                // Redraw the window
        }
        else if (wParam == verticleLineTimerId1)
        {
            verticleLineDisplayed2 = TRUE;
            KillTimer(hwnd, verticleLineTimerId1);
            SetTimer(hwnd, newRectangleTimerId1, 3000, NULL);
            InvalidateRect(hwnd, NULL, FALSE); // Trigger window redraw
        }
        if (wParam == newRectangleTimerId1)
        {
            newRectangleDisplayed1 = TRUE; // Display the rectangle
            KillTimer(hwnd, newRectangleTimerId1);

            // Start the timer for displaying text after 3 seconds
            SetTimer(hwnd, textInRectTimerId2, 3000, NULL); // 3-second delay
            InvalidateRect(hwnd, NULL, FALSE);              // Trigger a redraw
        }
        else if (wParam == textInRectTimerId2)
        {
            textInRectDisplayed2 = TRUE; // Display the text inside the new rectangle
            KillTimer(hwnd, textInRectTimerId2);
            SetTimer(hwnd, verticleLineTimerId2, 3000, NULL); // Trigger the new rectangle after 3 seconds
            InvalidateRect(hwnd, NULL, FALSE);                // Redraw the window
        }
        else if (wParam == verticleLineTimerId2)
        {
            verticleLineDisplayed3 = TRUE;
            KillTimer(hwnd, verticleLineTimerId2);
            SetTimer(hwnd, newRectangleTimerId2, 3000, NULL);
            InvalidateRect(hwnd, NULL, FALSE); // Trigger window redraw
        }
        if (wParam == newRectangleTimerId2)
        {
            newRectangleDisplayed2 = TRUE; // Display the rectangle
            KillTimer(hwnd, newRectangleTimerId2);

            // Start the timer for displaying text after 3 seconds
            SetTimer(hwnd, textInRectTimerId3, 3000, NULL); // 3-second delay
            InvalidateRect(hwnd, NULL, FALSE);              // Trigger a redraw
        }
        else if (wParam == textInRectTimerId3)
        {
            textInRectDisplayed3 = TRUE; // Display the text inside the new rectangle
            KillTimer(hwnd, textInRectTimerId3);
            SetTimer(hwnd, verticleLineTimerId3, 3000, NULL); // Trigger the new rectangle after 3 seconds
            InvalidateRect(hwnd, NULL, FALSE);                // Redraw the window
        }
        else if (wParam == verticleLineTimerId3)
        {
            verticleLineDisplayed4 = TRUE;
            KillTimer(hwnd, verticleLineTimerId3);
            SetTimer(hwnd, newRectangleTimerId3, 3000, NULL);
            InvalidateRect(hwnd, NULL, FALSE); // Trigger window redraw
        }

        if (wParam == newRectangleTimerId3)
        {
            newRectangleDisplayed3 = TRUE; // Display the rectangle
            KillTimer(hwnd, newRectangleTimerId3);

            // Start the timer for displaying text after 3 seconds
            SetTimer(hwnd, textInRectTimerId4, 3000, NULL); // 3-second delay
            InvalidateRect(hwnd, NULL, FALSE);              // Trigger a redraw
        }
        else if (wParam == textInRectTimerId4)
        {
            textInRectDisplayed4 = TRUE; // Display the text inside the new rectangle
            KillTimer(hwnd, textInRectTimerId4);
            SetTimer(hwnd, lineBelowRectDisplayedTimerId1, 3000, NULL); // Trigger the new rectangle after 3 seconds
            InvalidateRect(hwnd, NULL, FALSE);                          // Redraw the window
        }
        else if (wParam == lineBelowRectDisplayedTimerId1)
        {
            lineBelowRectDisplayed3 = TRUE; // Display the line below the rectangle
            KillTimer(hwnd, lineBelowRectDisplayedTimerId1);

            // Start the timer for the horizontal line (after 3 seconds)
            SetTimer(hwnd, horizontalLineTimerId1, 3000, NULL); // 3 seconds delay
            InvalidateRect(hwnd, NULL, FALSE);                  // Trigger window redraw
        }
        else if (wParam == horizontalLineTimerId1)
        {
            horizontalLineDisplayed2 = TRUE; // Set the flag to display the horizontal line
            KillTimer(hwnd, horizontalLineTimerId1);
            // SetTimer(hwnd, verticleLineTimerId, 3000, NULL);
            SetTimer(hwnd, verticleLineTimerId5, 3000, NULL);
            InvalidateRect(hwnd, NULL, FALSE); // Trigger window redraw
        }
        else if (wParam == verticleLineTimerId5)
        {
            verticleLineDisplayed5 = TRUE;
            KillTimer(hwnd, verticleLineTimerId5);
            SetTimer(hwnd, newRectangleTimerId5, 3000, NULL); // Trigger the new rectangle after 3 seconds
            InvalidateRect(hwnd, NULL, FALSE);                // Trigger window redraw
        }
        if (wParam == newRectangleTimerId5)
        {
            newRectangleDisplayed5 = TRUE; // Display the rectangle
            KillTimer(hwnd, newRectangleTimerId5);

            // Start the timer for displaying text after 3 seconds
            SetTimer(hwnd, textInRectTimerId5, 3000, NULL); // 3-second delay
            InvalidateRect(hwnd, NULL, FALSE);              // Trigger a redraw
        }
        else if (wParam == textInRectTimerId5)
        {
            textInRectDisplayed5 = TRUE; // Display the text inside the new rectangle
            KillTimer(hwnd, textInRectTimerId5);
            SetTimer(hwnd, verticleLineTimerId6, 3000, NULL); // Trigger the new rectangle after 3 seconds
            InvalidateRect(hwnd, NULL, FALSE);                // Redraw the window
        }
        else if (wParam == verticleLineTimerId6)
        {
            verticleLineDisplayed6 = TRUE;
            KillTimer(hwnd, verticleLineTimerId6);
            SetTimer(hwnd, newRectangleTimerId6, 3000, NULL);
            InvalidateRect(hwnd, NULL, FALSE); // Trigger window redraw
        }
        if (wParam == newRectangleTimerId6)
        {
            newRectangleDisplayed6 = TRUE; // Display the rectangle
            KillTimer(hwnd, newRectangleTimerId6);

            // Start the timer for displaying text after 3 seconds
            SetTimer(hwnd, textInRectTimerId6, 3000, NULL); // 3-second delay
            InvalidateRect(hwnd, NULL, FALSE);              // Trigger a redraw
        }
        else if (wParam == textInRectTimerId6)
        {
            textInRectDisplayed6 = TRUE; // Display the text inside the new rectangle
            KillTimer(hwnd, textInRectTimerId6);
            // SetTimer(hwnd, verticleLineTimerId6, 3000, NULL); // Trigger the new rectangle after 3 seconds
            InvalidateRect(hwnd, NULL, FALSE);                // Redraw the window
        }


        else if (wParam == TIMER_ID)
        {
            // Update background color
            r += r_increment;
            g += g_increment;
            b += b_increment;

            if (r >= 240 || r <= 100)
                r_increment = -r_increment;
            if (g >= 240 || g <= 100)
                g_increment = -g_increment;
            if (b >= 240 || b <= 100)
                b_increment = -b_increment;

            if (rectWidth < cxScreen)
            {
                rectWidth += rectSpeed;
            }
            else if (!rectExpanded)
            {
                rectExpanded = TRUE;
                SetTimer(hwnd, textTimerId, 3000, NULL);
            }

            UpdateParticles(particles, cxScreen, cyScreen);
            InvalidateRect(hwnd, NULL, FALSE);
        }
        break;

    case WM_DESTROY:
        KillTimer(hwnd, TIMER_ID);
        KillTimer(hwnd, textTimerId);
        KillTimer(hwnd, lineTimerId);
        KillTimer(hwnd, rectangleTimerId);
        KillTimer(hwnd, lineBelowRectDisplayedTimerId);
        KillTimer(hwnd, horizontalLineTimerId);
        KillTimer(hwnd, verticleLineTimerId);
        KillTimer(hwnd, newRectangleTimerId);
        KillTimer(hwnd, newRectangleTimerId1);
        KillTimer(hwnd, newRectangleTimerId2);
        KillTimer(hwnd, verticleLineTimerId1);
        KillTimer(hwnd, verticleLineTimerId2);
        KillTimer(hwnd, verticleLineTimerId3);
        KillTimer(hwnd, lineBelowRectDisplayedTimerId1);
        KillTimer(hwnd, horizontalLineTimerId1);
        KillTimer(hwnd, verticleLineTimerId5);
        KillTimer(hwnd, newRectangleTimerId5);
        KillTimer(hwnd, verticleLineTimerId6);

        if (hBitmap)
            DeleteObject(hBitmap);
        if (hMemDC)
            DeleteDC(hMemDC);

        PostQuitMessage(EXIT_SUCCESS);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}
void UpdateParticles(Particle particles[], int screenWidth, int screenHeight)
{
    for (int i = 0; i < NUM_PARTICLES; i++)
    {
        particles[i].x += particles[i].dx;
        particles[i].y += particles[i].dy;

        if (particles[i].x < 0 || particles[i].x >= screenWidth)
        {
            particles[i].dx = -particles[i].dx;
        }

        if (particles[i].y < 0 || particles[i].y >= screenHeight)
        {
            particles[i].dy = -particles[i].dy;
        }
    }
}
