#include <Windows.h> 
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 

// long long __stdcall WndProc(struct HWND__* hwnd, unsinged int uMsg, unsigned long long wParam, 
//                                 long long lParam); 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    static TCHAR szAppName[] = TEXT("Abhay Pardeshi"); 
    static TCHAR szClassName[] = TEXT("The Standard Window");  

    WNDCLASSEX wnd; 
    MSG msg; 

    HWND hwnd = NULL; 

    ZeroMemory(&wnd, sizeof(WNDCLASSEX)); 
    ZeroMemory(&msg, sizeof(MSG)); 

    wnd.cbSize = sizeof(WNDCLASSEX); 
    wnd.cbClsExtra = 0; 
    wnd.cbWndExtra = 0; 
    //wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    //wnd.hbrBackground = CreateSolidBrush(RGB(0, 0, 255)); // Blue brush
    //wnd.hbrBackground = CreateSolidBrush(RGB(0, 255, 0)); //  Green brush
    //wnd.hbrBackground = CreateSolidBrush(RGB(255, 0, 0)); //  Red brush
    //wnd.hbrBackground = CreateSolidBrush(RGB(123, 123, 123)); //  Mix brush  
    wnd.hbrBackground = CreateSolidBrush(RGB(123, 123, 0)); //  Mix brush 
    wnd.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW); 
    wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); 
    wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION); 
    wnd.hInstance = hInstance; 
    wnd.lpfnWndProc = WndProc; 
    wnd.lpszClassName = szClassName; 
    wnd.lpszMenuName = NULL; 
    wnd.style = CS_HREDRAW | CS_VREDRAW; 

    if(!RegisterClassEx(&wnd))
    {
        MessageBox((HWND)NULL, TEXT("Failed to register a window class"), TEXT("RegisterClassEx"), MB_ICONERROR | MB_TOPMOST); 
        ExitProcess(EXIT_FAILURE); 
    }
    hwnd = CreateWindowEx(WS_EX_APPWINDOW, szClassName, szAppName, WS_OVERLAPPEDWINDOW, 
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
            (HWND)NULL, (HMENU)NULL, hInstance, NULL); 
    if(hwnd == NULL)
    {
        MessageBox((HWND)NULL, TEXT("Failed to create a window"), TEXT("CreateWindowEx"), MB_ICONERROR | MB_TOPMOST); 
        ExitProcess(EXIT_FAILURE); 
    }
// Animate the window with a slide-in effect
     
     //AnimateWindow(hwnd, 1000, AW_SLIDE | AW_VER_POSITIVE);
     //AnimateWindow(hwnd, 1000, AW_SLIDE | AW_HOR_POSITIVE);
     //AnimateWindow(hwnd, 1000, AW_SLIDE | AW_VER_NEGATIVE);  
     //AnimateWindow(hwnd, 1000, AW_SLIDE | AW_HOR_NEGATIVE);                     
     AnimateWindow(hwnd, 1000, AW_SLIDE | AW_CENTER);
     
     //AnimateWindow(hwnd, 1000, AW_SLIDE | AW_CENTER | AW_HIDE);                //AW_HIDE-> Hides the window after the animation completes.

    //ShowWindow(hwnd, nCmdShow); 
    PlaySound("music.wav", NULL, SND_SYNC);

    UpdateWindow(hwnd); 
    while(GetMessage(&msg, (HWND)NULL, 0, 0))
    {
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    }
  
    return (msg.wParam); 
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_RBUTTONDOWN: 
            MessageBox(NULL, TEXT("Right button is clicked"), TEXT("EVENT HANDLER"), MB_OK | MB_TOPMOST); 
            break; 
        case WM_DESTROY: 
            PostQuitMessage(EXIT_SUCCESS); 
            break; 
    }

    return (DefWindowProc(hwnd, uMsg, wParam, lParam)); 
}



