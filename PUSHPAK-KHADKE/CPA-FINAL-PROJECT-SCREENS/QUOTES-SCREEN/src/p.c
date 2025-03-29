#include <Windows.h>
#include "..\include\global.h"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")

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

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch (uMsg)
    {
    case WM_CREATE:
    {
        // Store the parent window handle
        hwndParent = (HWND)((CREATESTRUCT *)lParam)->lpCreateParams;
        SetTimer(hwnd, TIMER_ID, 5000, NULL); 
    break;

    case WM_TIMER:
        // Handle timer events
        if (wParam == TIMER_ID)
        {
            // Sequentially update the flags
            static int step = 0;
            step = (step + 1) % 9; // Cycle through 8 steps (1 to 8)

            // Set the appropriate flag based on the step
            switch (step)
            {
            case 1:
                showLine1 = TRUE; // Show the first line
                break;
            case 2:
                showPinkRect = TRUE; // Show the pink rectangle
                break;
            case 3:
                showLine2 = TRUE; // Show the second line
                break;
            case 4:
                showBlueRect = TRUE; // Show the blue rectangle
                break;
            case 5:
                showLine3 = TRUE; // Show the third line
                break;
            case 6:
                showorangeRect = TRUE; // Show the orange rectangle
                break;
            case 7:
                showLine4 = TRUE; // Show the fourth line
                break;
            case 8:
                showaorangeRect = TRUE; // Show the another orange rectangle
                break;
            }

            // Redraw the window
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

   
        RECT rect;
        GetClientRect(hwnd, &rect);

        // Create a yellow-light colored brush
        HBRUSH hBrushYellow = CreateSolidBrush(RGB(255, 255, 153)); 
        RECT yellowRect = {0, 0, rect.right, 150};                  

        // Fill the yellow rectangle
        FillRect(hdc, &yellowRect, hBrushYellow);
        DeleteObject(hBrushYellow);

    
        HFONT hFontYellow = CreateFont(80, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                       DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                       CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                       DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
        HGDIOBJ oldFontYellow = SelectObject(hdc, hFontYellow);

        // Set text color and background mode
        SetTextColor(hdc, RGB(0, 0, 0)); // Black text
        SetBkMode(hdc, TRANSPARENT);

        const TCHAR *quote = TEXT("QUOTES");
        RECT textRect = {0, 0, rect.right, 150};

        // Draw the text centered in the yellow rectangle
        DrawText(hdc, quote, -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        SelectObject(hdc, oldFontYellow);
        DeleteObject(hFontYellow);

        // Check if the pink rectangle should be drawn
        if (showPinkRect)
        {
            HBRUSH hBrushPink = CreateSolidBrush(RGB(255, 182, 193)); 
            RECT pinkRect = {rectX, rectY, rectX + rectWidth, rectY + rectHeight};

      
            FillRect(hdc, &pinkRect, hBrushPink);
            DeleteObject(hBrushPink);

   
            HFONT hFontPink = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                         DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                         CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                         DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
            HGDIOBJ oldFontPink = SelectObject(hdc, hFontPink);

        
            SetTextColor(hdc, RGB(0, 0, 0)); 
            SetBkMode(hdc, TRANSPARENT);

            // The text to be displayed in the pink rectangle
            const TCHAR *text = TEXT("Basic is advanced and advanced is basic");
            RECT pinkTextRect = {rectX, rectY, rectX + rectWidth, rectY + rectHeight};

            // Draw the text centered in the pink rectangle
            DrawText(hdc, text, -1, &pinkTextRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            // Cleanup for pink text
            SelectObject(hdc, oldFontPink);
            DeleteObject(hFontPink);
        }

        if (showLine1)
        {
            HPEN hPen1 = CreatePen(PS_SOLID, 10, RGB(227, 227, 227)); // Red color for the first line
            HGDIOBJ oldPen1 = SelectObject(hdc, hPen1);

            // Move to the starting point of the first line
            MoveToEx(hdc, lineX1, lineY1, NULL);
            // Draw the vertical line
            LineTo(hdc, lineX1, lineY1 + 200); // 200px long vertical line

            // Cleanup for the first line
            SelectObject(hdc, oldPen1);
            DeleteObject(hPen1);
        }

        // Check if the second line should be drawn
        if (showLine2)
        {
            HPEN hPen2 = CreatePen(PS_SOLID, 10, RGB(247, 242, 171)); // Green color for the second line
            HGDIOBJ oldPen2 = SelectObject(hdc, hPen2);

            // Move to the starting point of the second line
            MoveToEx(hdc, lineX2, lineY2, NULL);
            // Draw the vertical line
            LineTo(hdc, lineX2, lineY2 + 350); // 350px long vertical line

            // Cleanup for the second line
            SelectObject(hdc, oldPen2);
            DeleteObject(hPen2);
        }

        if (showLine3)
        {
            HPEN hPen3 = CreatePen(PS_SOLID, 10, RGB(178, 164, 150)); // Green color for the second line
            HGDIOBJ oldPen3 = SelectObject(hdc, hPen3);

            // Move to the starting point of the second line
            MoveToEx(hdc, lineX3, lineY3, NULL);
            // Draw the vertical line
            LineTo(hdc, lineX3, lineY3 + 550); // 350px long vertical line

            // Cleanup for the second line
            SelectObject(hdc, oldPen3);
            DeleteObject(hPen3);
        }

        if (showLine4)
        {
            HPEN hPen4 = CreatePen(PS_SOLID, 10, RGB(242, 194, 238)); // Green color for the second line
            HGDIOBJ oldPen4 = SelectObject(hdc, hPen4);

            // Move to the starting point of the second line
            MoveToEx(hdc, lineX4, lineY4, NULL);
            // Draw the vertical line
            LineTo(hdc, lineX4, lineY4 + 750); // 350px long vertical line

            // Cleanup for the second line
            SelectObject(hdc, oldPen4);
            DeleteObject(hPen4);
        }

        // Check if the blue rectangle should be drawn
        if (showBlueRect)
        {
            HBRUSH hBrushBlue = CreateSolidBrush(RGB(173, 216, 230)); // Light blue color
            RECT blueRect = {blueRectX, blueRectY, blueRectX + blueRectWidth, blueRectY + blueRectHeight};

            // Fill the light blue rectangle
            FillRect(hdc, &blueRect, hBrushBlue);
            DeleteObject(hBrushBlue);

            // Set up the font for the blue rectangle text
            HFONT hFontBlue = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                         DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                         CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                         DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
            HGDIOBJ oldFontBlue = SelectObject(hdc, hFontBlue);

            // Set text color for the blue rectangle text
            SetTextColor(hdc, RGB(0, 0, 0)); // Black text
            SetBkMode(hdc, TRANSPARENT);

            // The text to be displayed in the blue rectangle
            const TCHAR *blueText = TEXT("Unix is mother of all OS");
            RECT blueTextRect = {blueRectX, blueRectY, blueRectX + blueRectWidth, blueRectY + blueRectHeight};

            // Draw the text centered in the blue rectangle
            DrawText(hdc, blueText, -1, &blueTextRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            // Cleanup for blue text
            SelectObject(hdc, oldFontBlue);
            DeleteObject(hFontBlue);
        }

        if (showorangeRect)
        {
            HBRUSH hBrushorange = CreateSolidBrush(RGB(255, 247, 8)); // Light blue color
            RECT orangeRect = {orangeRectX, orangeRectY, orangeRectX + orangeRectWidth, orangeRectY + orangeRectHeight};

            // Fill the light blue rectangle
            FillRect(hdc, &orangeRect, hBrushorange);
            DeleteObject(hBrushorange);

            // Set up the font for the blue rectangle text
            HFONT hFontorange = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                           DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                           CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                           DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
            HGDIOBJ oldFontorange = SelectObject(hdc, hFontorange);

            // Set text color for the blue rectangle text
            SetTextColor(hdc, RGB(0, 0, 0)); // Black text
            SetBkMode(hdc, TRANSPARENT);

            // The text to be displayed in the blue rectangle
            const TCHAR *orangeText = TEXT("Knowledge is inter-related");
            RECT orangeTextRect = {orangeRectX, orangeRectY, orangeRectX + orangeRectWidth, orangeRectY + orangeRectHeight};

            // Draw the text centered in the blue rectangle
            DrawText(hdc, orangeText, -1, &orangeTextRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            // Cleanup for blue text
            SelectObject(hdc, oldFontorange);
            DeleteObject(hFontorange);
        }

        if (showaorangeRect)
        {
            HBRUSH hBrushaorange = CreateSolidBrush(RGB(84, 182, 202)); // Light blue color
            RECT aorangeRect = {aorangeRectX, aorangeRectY, aorangeRectX + aorangeRectWidth, aorangeRectY + aorangeRectHeight};

            // Fill the light blue rectangle
            FillRect(hdc, &aorangeRect, hBrushaorange);
            DeleteObject(hBrushaorange);

            // Set up the font for the blue rectangle text
            HFONT hFontaorange = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                            DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
            HGDIOBJ oldFontaorange = SelectObject(hdc, hFontaorange);

            // Set text color for the blue rectangle text
            SetTextColor(hdc, RGB(0, 0, 0)); // Black text
            SetBkMode(hdc, TRANSPARENT);

            // The text to be displayed in the blue rectangle
            const TCHAR *aorangeText = TEXT("C is the mother of all programming languages.");
            RECT aorangeTextRect = {aorangeRectX, aorangeRectY, aorangeRectX + aorangeRectWidth, aorangeRectY + aorangeRectHeight};

            // Draw the text centered in the blue rectangle
            DrawText(hdc, aorangeText, -1, &aorangeTextRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            // Cleanup for blue text
            SelectObject(hdc, oldFontaorange);
            DeleteObject(hFontaorange);
        }

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        // Clean up the timer
        KillTimer(hwnd, TIMER_ID);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}