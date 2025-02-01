#define UNICODE
#define _UNICODE

#include <Windows.h>
#include "resource.h"
#include <mmsystem.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "winmm.lib")

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc2(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
    wnd.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
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

/*
#---------------------------------------1----------------------------------------------------
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND hwnd2 = NULL;  
    static HBITMAP hBitmap1, hBitmap2, hBitmap3;
    static int currentImage = 0;          
    static int currentLetter = 0;         
    static int currentRepublicLetter = 0; 
    static int currentDayLetter = 0;      
    static UINT_PTR timerID;              
    static HFONT hFont;                  

    switch (uMsg)
    {
        
    case WM_CREATE:
    // Play the music file 
       PlaySound(TEXT("s1.wav"), NULL, SND_FILENAME | SND_ASYNC  );
        hBitmap1 = (HBITMAP)LoadImageW(
            GetModuleHandle(NULL),
            MAKEINTRESOURCE(IDB_BITMAP1),
            IMAGE_BITMAP,
            0,
            0,
            LR_DEFAULTCOLOR);

        hBitmap2 = (HBITMAP)LoadImageW(
            GetModuleHandle(NULL),
            MAKEINTRESOURCE(IDB_BITMAP2),
            IMAGE_BITMAP,
            0,
            0,
            LR_DEFAULTCOLOR);

        hBitmap3 = (HBITMAP)LoadImageW(
            GetModuleHandle(NULL),
            MAKEINTRESOURCE(IDB_BITMAP3),
            IMAGE_BITMAP,
            0,
            0,
            LR_DEFAULTCOLOR);

    
        hFont = CreateFontW(
            130, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,
            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, L"Arial");

   
        timerID = SetTimer(hwnd, 1, 2000, NULL);
        break;

    case WM_TIMER:
        if (wParam == 1)
        {
            if (currentImage < 3)
                currentImage++; 
            else if (currentLetter < 5)
                currentLetter++; 
            else if (currentRepublicLetter < 8)
                currentRepublicLetter++; 
            else if (currentDayLetter < 3)
                currentDayLetter++; 

            if (currentImage >= 3 && currentLetter >= 5 && currentRepublicLetter >= 8 && currentDayLetter >= 3)
            {
                KillTimer(hwnd, timerID); 
            }

            InvalidateRect(hwnd, NULL, TRUE); 
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);


        HDC hdcMem = CreateCompatibleDC(hdc);

        
        for (int i = 1; i <= currentImage; ++i)
        {
            HBITMAP hBitmap = NULL;

            if (i == 1)
                hBitmap = hBitmap1;
            else if (i == 2)
                hBitmap = hBitmap2;
            else if (i == 3)
                hBitmap = hBitmap3;

            if (hBitmap)
            {
                SelectObject(hdcMem, hBitmap);

               
                StretchBlt(
                    hdc, (i - 1) * 700, 0, 700, 430, 
                    hdcMem, 0, 0, 700, 430,        
                    SRCCOPY);
            }
        }

        DeleteDC(hdcMem);

        
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(255, 165, 0)); 
        SelectObject(hdc, hFont);

        wchar_t textHappy[] = L"HAPPY";
        for (int i = 0; i < currentLetter; ++i)
        {
            TextOutW(hdc, 90 + i * 90, 500, &textHappy[i], 1); 
        }

       
        SetTextColor(hdc, RGB(255, 255, 255));

        wchar_t textRepublic[] = L"REPUBLIC";
        int republicStartX = 470; 
        int republicGap = 90;     

       
        for (int i = 0; i < currentRepublicLetter; ++i)
        {
            int adjustedGap = (i >= 7) ? 85 : republicGap;                             
            TextOutW(hdc, republicStartX + i * adjustedGap, 650, &textRepublic[i], 1); 
        }
      
        SetTextColor(hdc, RGB(19, 136, 8)); 

        wchar_t textDay[] = L"DAY";
        for (int i = 0; i < currentDayLetter; ++i)
        {
            TextOutW(hdc, 1065 + i * 90, 840, &textDay[i], 1); 
        }

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_RBUTTONDOWN: 
    {
        if (hwnd2 == NULL) 
        {
            static TCHAR szClassName2[] = TEXT("Second Window");

            WNDCLASSEX wnd2;
            ZeroMemory(&wnd2, sizeof(WNDCLASSEX));

            wnd2.cbSize = sizeof(WNDCLASSEX);
            wnd2.cbClsExtra = 0;
            wnd2.cbWndExtra = 0;
            wnd2.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); 
            wnd2.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
            wnd2.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            wnd2.hIconSm = wnd2.hIcon;
            wnd2.hInstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
            wnd2.lpfnWndProc = WndProc2; 
            wnd2.lpszClassName = szClassName2;
            wnd2.style = CS_HREDRAW | CS_VREDRAW;

            RegisterClassEx(&wnd2);

            int screenWidth = GetSystemMetrics(SM_CXSCREEN);
            int screenHeight = GetSystemMetrics(SM_CYSCREEN);

            hwnd2 = CreateWindowEx(
                WS_EX_APPWINDOW,
                szClassName2,
                TEXT("Second Window"),
                WS_POPUP,
                0, 0,
                screenWidth,
                screenHeight,
                (HWND)NULL,
                (HMENU)NULL,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL);

            if (hwnd2)
            {
                ShowWindow(hwnd2, SW_SHOW);
                UpdateWindow(hwnd2);
            }
        }
    }
    break;

    case WM_DESTROY:
        if (hBitmap1)
            DeleteObject(hBitmap1);
        if (hBitmap2)
            DeleteObject(hBitmap2);
        if (hBitmap3)
            DeleteObject(hBitmap3);

        if (hFont)
            DeleteObject(hFont);

        KillTimer(hwnd, timerID); 
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

/*
#---------------------------------------2----------------------------------------------------
*/
LRESULT CALLBACK WndProc2(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int partHeight = 0; 
    static int orangeWidth = 0; 
    static int greenWidth = 0;  
    static UINT_PTR timerID;    
    static UINT_PTR greenTimerID; 
    static UINT_PTR imageTimerID; 
    static boolean orangeDone = FALSE; 
    static boolean greenDone = FALSE;  

    switch (uMsg)
    {
    case WM_CREATE:
    {
  
        RECT rect;
        GetClientRect(hwnd, &rect);
        partHeight = (rect.bottom - rect.top) / 3;

        
        timerID = SetTimer(hwnd, 1, 30, NULL);
    }
    break;

    case WM_TIMER:
    {
        if (wParam == 1) 
        {
            RECT rect;
            GetClientRect(hwnd, &rect);

         
            int step = rect.right / (3000 / 30); 
            orangeWidth += step;

            if (orangeWidth >= rect.right)
            {
                orangeWidth = rect.right; 
                KillTimer(hwnd, timerID); 
                orangeDone = TRUE;        
                
                
                greenTimerID = SetTimer(hwnd, 2, 30, NULL); 
            }

            InvalidateRect(hwnd, NULL, TRUE); 
        }
        else if (wParam == 2) 
        {
            RECT rect;
            GetClientRect(hwnd, &rect);

            
            int step = rect.right / (3000 / 30); 
            greenWidth += step;

            if (greenWidth >= rect.right)
            {
                greenWidth = rect.right; 
                KillTimer(hwnd, greenTimerID); 
                greenDone = TRUE;  
                
                
                imageTimerID = SetTimer(hwnd, 3, 3000, NULL); 
            }

            InvalidateRect(hwnd, NULL, TRUE); 
        }
        else if (wParam == 3) 
        {
            InvalidateRect(hwnd, NULL, TRUE); 
            KillTimer(hwnd, imageTimerID); 
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT rect;
        GetClientRect(hwnd, &rect);

     
        HBRUSH hBrushOrange = CreateSolidBrush(RGB(255, 165, 0)); 
        RECT orangeRect = {rect.right - orangeWidth, 0, rect.right, partHeight}; 
        FillRect(hdc, &orangeRect, hBrushOrange);
        DeleteObject(hBrushOrange);

       
        HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255)); 
        RECT whiteRect = {0, partHeight, rect.right, 2 * partHeight};
        FillRect(hdc, &whiteRect, hBrushWhite);
        DeleteObject(hBrushWhite);

      
        RECT thirdPartRect = {0, 2 * partHeight, rect.right, rect.bottom};
        FillRect(hdc, &thirdPartRect, hBrushWhite);

        
        if (orangeDone)
        {
            HBRUSH hBrushGreen = CreateSolidBrush(RGB(19, 136, 8)); 
            RECT greenRect = {0, 2 * partHeight, greenWidth, rect.bottom}; 
            FillRect(hdc, &greenRect, hBrushGreen);
            DeleteObject(hBrushGreen);
        }

      
       
if (greenDone)  
{
    HBITMAP hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP4));
    if (hBitmap)
    {
      
        BITMAP bm;
        GetObject(hBitmap, sizeof(bm), &bm);

        
        int newWidth = bm.bmWidth + 50;
        int newHeight = bm.bmHeight + 50;

    
        int xPos = (rect.right - newWidth) / 2;
        int yPos = partHeight + (partHeight - newHeight) / 2;

     
        HDC memDC = CreateCompatibleDC(hdc);
        SelectObject(memDC, hBitmap);

     
        StretchBlt(hdc, xPos, yPos, newWidth, newHeight, memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

        DeleteDC(memDC);
        DeleteObject(hBitmap);
    }
}

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        KillTimer(hwnd, timerID); 
        KillTimer(hwnd, greenTimerID); 
        KillTimer(hwnd, imageTimerID); 
        PostQuitMessage(EXIT_SUCCESS);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}



