#include <Windows.h>
#include "to_be_continued.h"

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "winmm.lib") 


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	static TCHAR szClassName[] = TEXT("To Be Continued");
	static TCHAR szWindowCaption[] = TEXT("To Be Continued");

	HBRUSH hBrush = NULL;
	HCURSOR hCursor = NULL;
	HICON hIcon = NULL;
	HICON hIconSm = NULL;
	HWND hWnd = NULL;

	WNDCLASSEX wndEx;
	MSG msg;

	ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
	ZeroMemory(&msg, sizeof(MSG));

	hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
	if (hBrush == NULL)
	{
		MessageBox((HWND)NULL, TEXT("Could not obtain brush"), TEXT("GetStockObject"), MB_ICONERROR);
		return (EXIT_FAILURE);
	}

	hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
	if (hCursor == NULL)
	{
		MessageBox((HWND)NULL, TEXT("Could not obtain Cursor"), TEXT("LoadCursor"), MB_ICONERROR);
		return (EXIT_FAILURE);
	}

	hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
	if (hIcon == NULL)
	{
		MessageBox((HWND)NULL, TEXT("Could not load Icon"), TEXT("LoadIcon"), MB_ICONERROR);
		return (EXIT_FAILURE);
	}

	hIconSm = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
	if (hIconSm == NULL)
	{
		MessageBox((HWND)NULL, TEXT("Could not obtain small icon"), TEXT("LoadIcon"), MB_ICONERROR);
		return (EXIT_FAILURE);
	}

	wndEx.cbSize = sizeof(WNDCLASSEX);
	wndEx.cbClsExtra = 0;
	wndEx.cbWndExtra = 0;
	wndEx.hbrBackground = hBrush;
	wndEx.hCursor = hCursor;
	wndEx.hIcon = hIcon;
	wndEx.hIconSm = hIconSm;
	wndEx.hInstance = hInstance;
	wndEx.lpfnWndProc = WndProc;
	wndEx.lpszClassName = szClassName;
	wndEx.lpszMenuName = NULL;
	wndEx.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wndEx)) {
		MessageBox((HWND)NULL, TEXT("Could not register window class"), TEXT("RegisterClassEx"), MB_ICONERROR);
		return (EXIT_FAILURE);
	}

	hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		szClassName,
		szWindowCaption,
		WS_POPUP,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(HWND)NULL,
		(HMENU)NULL,
		hInstance,
		NULL);
	if (hWnd == NULL) {
		MessageBox((HWND)NULL, TEXT("Could not create application"), TEXT("CreateWindow"), MB_ICONERROR);
		return (EXIT_FAILURE);
	}

	ShowWindow(hWnd, SW_MAXIMIZE);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, (HWND)NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (0);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	
	switch (uMsg) {
		case WM_CREATE:
			SetTimer(hWnd, 1, 250, NULL);
			hdc = GetDC(hWnd);
			GetTextMetrics(hdc, &tm);
			cxChar = tm.tmAveCharWidth;
			cyChar = tm.tmHeight + tm.tmExternalLeading;
			
			PlaySound(TEXT("Type3.wav"), NULL, SND_FILENAME | SND_ASYNC);
			ReleaseDC(hWnd, hdc);
			hdc = NULL;

			break;

		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
			break;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			hFont = CreateFont(cyChar * 7, cxChar * 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Cambria")); 
			SelectObject(hdc, hFont); 
	        		
			for (i = 0; i < strlen(str); i++) {
				if (display_flag[i] == 1) {
					substr[i] = str[i];
				}
			}

			SetTextAlign(hdc, TA_CENTER); 
			SetBkColor(hdc, RGB(128, 128, 128));
			TextOut(hdc, cxClient / 2, 0.8 * cyClient / 2, substr, lstrlen(substr)); 
            
			if (end_flag == 1) {
				EndPaint(hWnd, &ps);
				break; 
			}

			break;

		case WM_TIMER:

				++timer_flag;
				for (i = 0; i < timer_flag; i++)
				{
					display_flag[i] = 1;
				}
				if (timer_flag > strlen(str))
					end_flag = 1;

				InvalidateRect(hWnd, NULL, FALSE);

			break;

		case WM_KEYDOWN:

		if(wParam == VK_ESCAPE )
				{
					PostQuitMessage(0);
				}
		break;

		case WM_DESTROY:
			PostQuitMessage(EXIT_SUCCESS);
			break;
	}

	return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}
