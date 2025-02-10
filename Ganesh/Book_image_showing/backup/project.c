#include <Windows.h>
#include "resource.h"
#include <stdio.h>
#include <commdlg.h>
#include <math.h>
#include <stdbool.h>
#include <tchar.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "Gdi32.lib")

#define MAX_PARTICLES 1000
#define TIMER_ID 1

int x = 60;       
int y = 250;      
int width = 450;  
int height = 550; 

typedef struct
{
    float x, y;     
    float vx, vy;  
    COLORREF color; 
    int life;    
} Particle;

Particle particles[MAX_PARTICLES]; 
int numParticles = 0;              


void InitParticle(Particle *p, int width, int height)
{
    p->x = rand() % width;                                    
    p->y = rand() % height;                                   
    p->vx = (rand() % 5 - 2);                                
    p->vy = (rand() % 5 - 2);                                
    p->color = RGB(rand() % 256, rand() % 256, rand() % 256); 
    p->life = 100 + rand() % 100;                           
}

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
    wnd.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_DATA_ICON));
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
    //static HWND hwnd2 = NULL;       
    static HBITMAP hBitmap1 = NULL;  
    static HBITMAP hBitmap2 = NULL;
    static HBITMAP hBitmap3 = NULL;
    static HBITMAP hBitmap4 = NULL;

    static int desiredWidth1 = 100; 
    static int desiredHeight1 = 100; 

    static int desiredWidth2 = 200; 
    static int desiredHeight2 = 200; 

    static int desiredWidth3 = 300; 
    static int desiredHeight3 = 300; 

    static int desiredWidth4 = 400; 
    static int desiredHeight4 = 400; 
    
    static bool showImage1 = false;
    static bool showImage2 = false;
    static bool showImage3 = false;
    static bool showImage4 = false;

    static bool showCoreCode = false;
    static bool showMSTC = false;

    switch (uMsg)
    {
    case WM_CREATE:
    {
       
        hBitmap1 = LoadBitmap((HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDB_MAIN_BITMAP1));
        if (hBitmap1 == NULL)
        {
            MessageBox(hwnd, TEXT("Failed to load bitmap1!"), TEXT("Error"), MB_ICONERROR);
        }

        
        hBitmap2 = LoadBitmap((HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDB_MAIN_BITMAP2));
        if (hBitmap2 == NULL)
        {
            MessageBox(hwnd, TEXT("Failed to load bitmap2!"), TEXT("Error"), MB_ICONERROR);
        }

        hBitmap3 = LoadBitmap((HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDB_MAIN_BITMAP3));
        if (hBitmap3 == NULL)
        {
            MessageBox(hwnd, TEXT("Failed to load bitmap3!"), TEXT("Error"), MB_ICONERROR);
        }

        hBitmap4 = LoadBitmap((HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDB_MAIN_BITMAP4));
        if (hBitmap4 == NULL)
        {
            MessageBox(hwnd, TEXT("Failed to load bitmap4!"), TEXT("Error"), MB_ICONERROR);
        }


    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        
        SetTextColor(hdc, RGB(255, 165, 0)); 
        SetBkMode(hdc, TRANSPARENT);

        
        HFONT hBoldFont = CreateFont(
            60,           
            0,            
            0,          
            0,            
            FW_EXTRABOLD, 
            FALSE,        
            FALSE,        
            FALSE,        
            DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_QUALITY,
            TEXT("Arial") 
        );

        SelectObject(hdc, hBoldFont);

        
        int yBitmap = 150;         
        int textY = yBitmap - 100; 
        RECT textRect;
        GetClientRect(hwnd, &textRect);

      
        SIZE textSize;
        GetTextExtentPoint32(hdc, TEXT("|| Shree Ganeshay Namaha ||"), lstrlen(TEXT("|| Shree Ganeshay Namaha ||")), &textSize);
        int textX = (textRect.right - textRect.left - textSize.cx) / 2; 

        
        TextOut(hdc, textX, textY, TEXT("|| Shree Ganeshay Namaha ||"), lstrlen(TEXT("|| Shree Ganeshay Namaha ||")));

        DeleteObject(hBoldFont);

      
         if (showImage1 && hBitmap1)
        {
            BITMAP bitmap1;
            GetObject(hBitmap1, sizeof(BITMAP), &bitmap1);

        
            int xBitmap1 = (ps.rcPaint.right - desiredWidth1) / 2; 

           
            HDC hdcMem1 = CreateCompatibleDC(hdc);
            SelectObject(hdcMem1, hBitmap1);

       
            StretchBlt(hdc, xBitmap1, yBitmap, desiredWidth1, desiredHeight1, hdcMem1, 0, 0, bitmap1.bmWidth, bitmap1.bmHeight, SRCCOPY);

           
            DeleteDC(hdcMem1);
        }

        if(showImage2 && hBitmap2)
        {  ////
            BITMAP bitmap2;
            GetObject(hBitmap2, sizeof(BITMAP), &bitmap2);

        
            int xBitmap2 = (ps.rcPaint.right - desiredWidth2) / 2; 

           
            HDC hdcMem2 = CreateCompatibleDC(hdc);
            SelectObject(hdcMem2, hBitmap2);

       
            StretchBlt(hdc, xBitmap2, yBitmap, desiredWidth2, desiredHeight2, hdcMem2, 0, 0, bitmap2.bmWidth, bitmap2.bmHeight, SRCCOPY);

           
            DeleteDC(hdcMem2);
        }

        if(showImage3 && hBitmap3)
        {  ////
            BITMAP bitmap3;
            GetObject(hBitmap3, sizeof(BITMAP), &bitmap3);

        
            int xBitmap3 = (ps.rcPaint.right - desiredWidth3) / 2; 

           
            HDC hdcMem3 = CreateCompatibleDC(hdc);
            SelectObject(hdcMem3, hBitmap3);

       
            StretchBlt(hdc, xBitmap3, yBitmap, desiredWidth3, desiredHeight3, hdcMem3, 0, 0, bitmap3.bmWidth, bitmap3.bmHeight, SRCCOPY);

           
            DeleteDC(hdcMem3);
        }
       
        if(showImage4 && hBitmap4)
        {  ////
            BITMAP bitmap4;
            GetObject(hBitmap4, sizeof(BITMAP), &bitmap4);

        
            int xBitmap4 = (ps.rcPaint.right - desiredWidth4) / 2; 

           
            HDC hdcMem4 = CreateCompatibleDC(hdc);
            SelectObject(hdcMem4, hBitmap4);

       
            StretchBlt(hdc, xBitmap4, yBitmap, desiredWidth4, desiredHeight4, hdcMem4, 0, 0, bitmap4.bmWidth, bitmap4.bmHeight, SRCCOPY);

           
            DeleteDC(hdcMem4);
        }
        if (showCoreCode)
        {
            SetTextColor(hdc, RGB(255, 255, 255)); 
            HFONT hFont = CreateFont(
                90, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_QUALITY, TEXT("Arial"));
            SelectObject(hdc, hFont);

            RECT rc;
            GetClientRect(hwnd, &rc);

            SIZE coreTextSize;
            GetTextExtentPoint32(hdc, TEXT("CoreCode Programing Academy"), lstrlen(TEXT("CoreCode Programing Academy")), &coreTextSize);
            int x = (rc.right - rc.left - coreTextSize.cx) / 2;
            int y = 800; 

            TextOut(hdc, x, y, TEXT("CoreCode Programing Academy"), lstrlen(TEXT("CoreCode Programing Academy")));

            DeleteObject(hFont);
        }

     
        if (showMSTC)
        {
            SetTextColor(hdc, RGB(144, 238, 144)); 
            HFONT hFont = CreateFont(
                90, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_QUALITY, TEXT("Arial"));
            SelectObject(hdc, hFont);

            RECT rc;
            GetClientRect(hwnd, &rc);

            SIZE subTextSize;
            GetTextExtentPoint32(hdc, TEXT("MSTC-04/Pushpak Khadke/Calculator"), lstrlen(TEXT("MSTC-04/Pushpak Khadke/Calculator")), &subTextSize);
            int subTextY = 900; // Adjust the y position as needed
            int subTextX = (rc.right - rc.left - subTextSize.cx) / 2;

            TextOut(hdc, subTextX, subTextY, TEXT("MSTC-04/Pushpak Khadke/Calculator"), lstrlen(TEXT("MSTC-04/Pushpak Khadke/Calculator")));

            DeleteObject(hFont);
        }

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case 'A':                             
            showImage1 = true; 
            showImage2 = true;     
            showImage3 = true;
            showImage4 = true;          
            InvalidateRect(hwnd, NULL, TRUE); 
            break;
        case 'B':                             
            showCoreCode = true;              
            InvalidateRect(hwnd, NULL, TRUE); 
            break;
        case 'C':                             
            showMSTC = true;              
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        break;

 

    case WM_DESTROY:
        if (hBitmap1)
        {
            DeleteObject(hBitmap1);
        }
        if (hBitmap2)
        {
            DeleteObject(hBitmap2);
        }
        if (hBitmap3)
        {
            DeleteObject(hBitmap3);
        }
        if (hBitmap4)
        {
            DeleteObject(hBitmap4);
        }
        PostQuitMessage(EXIT_SUCCESS);
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


