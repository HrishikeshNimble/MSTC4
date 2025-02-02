#include <Windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "Winmm.lib")

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 

int r = 255, g = 255, b = 0; 

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

    if(!RegisterClassEx(&wnd))
    {
        MessageBox(
            NULL, 
            TEXT("Failed to register a window class"), 
            TEXT("RegisterClassEx"), 
            MB_ICONERROR | MB_TOPMOST
        ); 
        ExitProcess(EXIT_FAILURE); 
    }

    hwnd = CreateWindowEx(
        WS_EX_APPWINDOW, 
        szClassName, 
        szWindowTitle, 
        WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        (HWND)NULL, 
        (HMENU)NULL, 
        hInstance, 
        (LPVOID)NULL
    ); 

    if(hwnd == NULL)
    {
        MessageBox(
            (HWND)NULL, 
            TEXT("Failed to create an application window"), 
            TEXT("CreateWindowEx"), 
            MB_ICONERROR | MB_TOPMOST
        ); 
        ExitProcess(EXIT_FAILURE); 
    }

    AnimateWindow(hwnd, 400, AW_SLIDE | AW_HOR_POSITIVE | AW_VER_POSITIVE);
    ShowWindow(hwnd, nShowCmd); 
    UpdateWindow(hwnd); 

    SetTimer(hwnd, 1, 200, NULL); 

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    }

    return ((int)msg.wParam); 
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int cxChar;
    static int cyChar;
    
    static int cxScreen;
    static int cyScreen;

    static TCHAR szMessage[] = TEXT("Breathless Playing!!!");
    int iLength = lstrlen(szMessage);

    HDC hdc = NULL;
    PAINTSTRUCT ps;
    TEXTMETRIC tm;
    
    HBRUSH hBrush = NULL;

    switch(uMsg)
    {   
        case WM_CREATE:

            PlaySound(TEXT("song.wav"), NULL, SND_FILENAME | SND_ASYNC  );

            hdc = GetDC(hwnd);
            GetTextMetrics(hdc, &tm);
            ReleaseDC(hwnd, hdc);
            cxChar = tm.tmAveCharWidth;
            cyChar = tm.tmHeight + tm.tmExternalLeading;
            break;

        case WM_SIZE: 
            cxScreen = LOWORD(lParam); 
            cyScreen = HIWORD(lParam); 
            break;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
        SetTextAlign(hdc, TA_TOP | TA_CENTER);
      
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
       
        int centerX = (clientRect.right - clientRect.left) / 2;
        int centerY = (clientRect.bottom - clientRect.top) / 2;

        SetTextAlign(hdc, TA_TOP | TA_CENTER);
 
        hBrush = CreateSolidBrush(RGB(r, g, b)); 
        FillRect(hdc, &ps.rcPaint, hBrush);
        DeleteObject(hBrush);

        SetTextAlign(hdc, TA_TOP | TA_CENTER);
        TextOut(hdc, centerX, centerY, szMessage, iLength);

        EndPaint(hwnd, &ps);
        break;

        case WM_TIMER:
           
          /*  if (r > 245) 
            {
                r -= 2; 
            }*/

            if (g > 0) 
            {
                g -= 2;
            }  
           /*if (b < 0) 
            {
               b += 2; 
            } 

            if (r == 0 && g == 128) 
            {
                b = 0; 
            }*/

            InvalidateRect(hwnd, NULL, TRUE); 
            break;

        case WM_DESTROY: 
            KillTimer(hwnd, 1);
            PostQuitMessage(EXIT_SUCCESS); 
            break; 
    }

    return (DefWindowProc(hwnd, uMsg, wParam, lParam)); 
}

