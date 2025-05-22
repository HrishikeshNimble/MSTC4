// 
// ############# MSTC GROUP PROJECT SPLASH SCREEN Drwaing  ##########//

#include <windows.h>
#include <stdio.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "..\include\Splash_Screen.h"
#include "..\include\global.h"

// libpath 
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "Winmm.lib")

#define TIMER_ID 8
#define TIMER_ID1 1
#define TIMER_ID2 2
#define TIMER_ID3 3
#define TIMER_ID4 4
#define TIMER_ID5 5
#define TIMER_ID6 6
#define TIMER_ID7 7
#define INTRO_TIMER_ID1 11
#define INTRO_TIMER_ID2 12
#define INTRO_TIMER_ID3 13
#define NUM_POINTS 8

HPEN choosePenColor(int, BRUSH_SIZE);
void ToggleFullScreen(void);
void uninitialize(void);
void display(void);
/******************************************/
void refPoints(void);
void linesBackground(HPEN);
void linesBackground2(void);
void sceneIntro(void);
void sceneIntro1(void);
void sceneOne(void);
void sceneTwo(void);
void sceneThree(void);
void sceneFour(void);
void sceneFive(void);
void sceneSix(void);
void sceneSeven(void);
void sceneEight(void);
void mpreProcessor(HBRUSH);
void dMMovingLine(HDC, HGDIOBJ, int, int, int);
void dCircle(HDC, HGDIOBJ, int, int, int);
void xIncreRenderPoints(HPEN, int, int, int,int*);
void xDecreRenderPoints(HPEN, int, int, int, int*);
void yDecreRenderPoints(HPEN, int, int, int, int*);
void finalRenderPoints(HPEN, int, int, int, int*);
/********************************************/
HWND ghwnd = NULL;
HDC ghdc = NULL;
BOOL gbFullScreen = FALSE;
FILE* gpFile = NULL;
HBITMAP hBitmap = NULL;
HDC hMemDC = NULL;
HDC hdc;
PAINTSTRUCT ps;
HBITMAP hBitmap4 = NULL;

int gcxScreen, gcyScreen;
int sceneCounter = 0;
int introSceneCounter = 1;
int pointsCounter = 1;
int increment = 2;

HPEN selectedBrush;
typedef struct
{
	int initialVal;
	int finalVal;
	int initPoints;
	int renderSpeed;
	HPEN burshColor;
}RenderPoints;

RenderPoints renderPoints_struct[8];
RenderPoints xdrenderPoints_struct[8];
RenderPoints ydrenderPoints_struct[4];
RenderPoints frenderPoints_struct[22];
RenderPoints ffrenderPoints_struct[3];
int xz = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) //ncmwindow show the window on how it should be shown e.g. maximized minimized or hidden etc.
{
	void initialize(void);
	void uninitialize(void);

	//4. Data
	WNDCLASSEX wndclass; //  style
	HWND hwnd;	// Handle == Pointer to Window
	//MSG msg;
	MSG msg={};	//Current msg
	
	TCHAR szAppName[] = TEXT("MSTC"); // name of class 
    TCHAR szWindowCaption[] = TEXT("MSTC GROUP DEMO");

	if (fopen_s(&gpFile, "Log.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("Creation Of Log File Failed. Exitting..."), TEXT("File I/O Error"), MB_OK);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "Log File Created Successfully.\n");
	}
	// Initialization of WNDCLASSEX Structure
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// Register WNDCLASSEX
	RegisterClassEx(&wndclass);
	// Create the windowex
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, 
		szAppName, 
		szWindowCaption, 
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		(GetSystemMetrics(SM_CXSCREEN) - GetSystemMetrics(SM_CXSCREEN) / 2) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - GetSystemMetrics(SM_CYSCREEN) / 2) / 2,
		800,
		600,
		NULL,
		NULL,
		hInstance,
		NULL);
	ghwnd = hwnd;
	ToggleFullScreen();

	initialize();

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd); // VIMP

	SetTimer(hwnd, TIMER_ID, 50, NULL);
	SetTimer(hwnd, INTRO_TIMER_ID1, 9000, NULL);
	SetTimer(hwnd, INTRO_TIMER_ID2, 24000, NULL);
	SetTimer(hwnd, TIMER_ID1, 28000, NULL);
	SetTimer(hwnd, TIMER_ID2, 32000, NULL);
	SetTimer(hwnd, TIMER_ID3, 36000, NULL);
	SetTimer(hwnd, TIMER_ID4, 40000, NULL);
	SetTimer(hwnd, TIMER_ID5, 44000, NULL);
	SetTimer(hwnd, TIMER_ID6, 48000, NULL);
	SetTimer(hwnd, TIMER_ID7, 52000, NULL);

	PlaySound(MAKEINTRESOURCE(MYAUDIO), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);

	// 9. Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	uninitialize();

	return((int)msg.wParam);
}
 
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// 11 b
	
    
	static int cxClient;
	static int cyClient;
	
    switch (iMsg)
	{
		// very 1st Msg
	case WM_CREATE:
		
    	break;

        case WM_SIZE: 
            cxClient = LOWORD(lParam); 
            cyClient = HIWORD(lParam); 
			gcxScreen = cxClient;
			gcyScreen = cyClient;
            break; 
		case WM_CHAR:
			switch (wParam)
			{
			case 'F':
			case 'f':
				ToggleFullScreen();
				break;
			case 'N':
			case 'n':
				sceneCounter++;
				break;
			case 'P':
			case 'p':
				sceneCounter--;
				break;
			default:
				break;
			}
			break;

		case WM_KEYDOWN:	
			if(wParam == VK_ESCAPE )
			{
				PostQuitMessage(0);
			}
		break;

		case WM_ERASEBKGND:
			return (0);
			
        case WM_PAINT: 
			display();
		break;

     case WM_TIMER:

		 if (wParam == TIMER_ID)
		 {
			 InvalidateRect(hwnd, NULL, FALSE);
		 }
		 if (wParam == INTRO_TIMER_ID1)
		 {
			 introSceneCounter = 2; //intro scene 2
			 InvalidateRect(hwnd, NULL, FALSE);
		 }
		 if (wParam == INTRO_TIMER_ID2)
		 {
			KillTimer(ghwnd, INTRO_TIMER_ID1);
			introSceneCounter = -1; //scene 1
			sceneCounter = 1;
			InvalidateRect(hwnd, NULL, FALSE);
			
		 }
		 if (wParam == TIMER_ID1)
		 {
			 KillTimer(ghwnd, INTRO_TIMER_ID2);
			 sceneCounter++; //scene 2
			 InvalidateRect(hwnd, NULL, FALSE);
		 }

		if (wParam == TIMER_ID2)
		{
		 sceneCounter++; //scene 3
		 KillTimer(ghwnd, TIMER_ID1);
		 InvalidateRect(hwnd, NULL, FALSE);
		}

		if (wParam == TIMER_ID3)
		{
		 sceneCounter++; //scene 4
		 KillTimer(ghwnd, TIMER_ID2);
		 InvalidateRect(hwnd, NULL, FALSE);
		}
		if (wParam == TIMER_ID4)
		{
		 sceneCounter++; //scene 5
		 KillTimer(ghwnd, TIMER_ID3);
		 InvalidateRect(hwnd, NULL, FALSE);
		}
		if (wParam == TIMER_ID5)
		{
		 sceneCounter++; //scene 6
		 KillTimer(ghwnd, TIMER_ID4);
		 InvalidateRect(hwnd, NULL, FALSE);
		}
		if (wParam == TIMER_ID6)
		{
		 KillTimer(ghwnd, TIMER_ID5);
		 sceneCounter++; //scene 7
		 
		 InvalidateRect(hwnd, NULL, FALSE);
		}
		if (wParam == TIMER_ID7)
		{
		 KillTimer(ghwnd, TIMER_ID6);
		 sceneCounter++; //scene 8

		 InvalidateRect(hwnd, NULL, FALSE);
		}
			break;
	 case WM_CLOSE:
		 DestroyWindow(hwnd);
		 break;
	 case WM_DESTROY:
		 uninitialize();
		 PostQuitMessage(0);
		 break;
	}

	// 12
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullScreen(void)
{
	// Variable Declaration

	static DWORD dwStyle;
	static WINDOWPLACEMENT wp;
	MONITORINFO mi;

	// Code

	wp.length = sizeof(WINDOWPLACEMENT);

	if (gbFullScreen == FALSE)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			mi.cbSize = sizeof(MONITORINFO);
			if (GetWindowPlacement(ghwnd, &wp) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
			ShowCursor(FALSE);
			gbFullScreen = TRUE;
		}
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPED);
		SetWindowPlacement(ghwnd, &wp);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
		gbFullScreen = FALSE;
	}
}

HPEN choosePenColor(int penColor, BRUSH_SIZE brushSize)
{
		
	COLORREF textColor;
	HPEN hLinePen;
	PAINTSTRUCT ps;


	switch(penColor)
	{
	case VISULIZER_WHITE_PEN:
		hLinePen = CreatePen(PS_SOLID, brushSize, white);
		textColor = white;
		break;
		case VISULIZER_RED_PEN :  
			hLinePen=CreatePen(PS_SOLID, brushSize , red);
			textColor=red;
			break;
		case VISULIZER_GREEN_PEN :
			hLinePen=CreatePen(PS_SOLID, brushSize , green);
			textColor=green;
			break;
		case VISULIZER_BLUE_PEN :
			hLinePen=CreatePen(PS_SOLID, brushSize , blue);
			textColor=blue;
			break;
		case VISULIZER_ORAGNE_PEN :
			hLinePen=CreatePen(PS_SOLID, brushSize , orange);
			textColor=orange;
			break;
		case VISULIZER_CYAN_PEN :
			hLinePen=CreatePen(PS_SOLID, brushSize , cyan);
			textColor=cyan;
			break;
		case VISULIZER_MGENTA_PEN :
			hLinePen=CreatePen(PS_SOLID, brushSize , magenta);
			textColor=magenta;
			break;
		case VISULIZER_YELLOW_PEN:
			hLinePen=CreatePen(PS_SOLID, brushSize , yellow);
			textColor=yellow;
			break;
		case VISULIZER_SKYBLUE_PEN :
			hLinePen=CreatePen(PS_SOLID, brushSize , skyblue);
			textColor=skyblue;
			break;
		case VISULIZER_COBALTBLUE_PEN:
			hLinePen = CreatePen(PS_SOLID, brushSize, cobaltBlue);
			textColor = cobaltBlue;
			break;
		case VISULIZER_OLIVEGREEN_PEN:
			hLinePen = CreatePen(PS_SOLID, brushSize, olivegreen);
			textColor = olivegreen;
			break;
		case VISULIZER_BLACK_PEN:
			hLinePen = CreatePen(PS_SOLID, brushSize, black);
			textColor = black;
			break;
		default:
			hLinePen=CreatePen(PS_SOLID, brushSize , orange);
			textColor=orange;	
			break;
	}
	return(hLinePen);
}

void initialize(void)
{
	//X-Incrementing Points
	for (int i = 0; i < 8; i++)
	{
		renderPoints_struct[i].initialVal = i * 100;
		renderPoints_struct[i].finalVal = (i * 100) + 100;
		renderPoints_struct[i].initPoints = i * 100;
		renderPoints_struct[i].renderSpeed = increment;
		renderPoints_struct[i].burshColor = choosePenColor(0, 10);
	}

	if (renderPoints_struct == NULL)
	{
		fprintf(gpFile, "initialize() -> Failed to initialize renderPoints_struct...\n");
	}
	else
	{
		fprintf(gpFile, "initialize() -> renderPoints_struct initialized successfully...\n");
	}

	//X-Decrementing Points
	for (int i = 0; i < 8; i++)
	{
		xdrenderPoints_struct[i].initialVal = 1920 - (i * 100);
		xdrenderPoints_struct[i].finalVal = 1820 - (i * 100);
		xdrenderPoints_struct[i].initPoints = 1920 - (i * 100);
		xdrenderPoints_struct[i].renderSpeed = increment;
	}

	if (xdrenderPoints_struct == NULL)
	{
		fprintf(gpFile, "initialize() -> Failed to initialize xdrenderPoints_struct...\n");
	}
	else
	{
		fprintf(gpFile, "initialize() -> xdrenderPoints_struct initialized successfully...\n");
	}

	// Y-Decrementing Points
	for (int i = 0; i < 4; i++)
	{
		ydrenderPoints_struct[i].initialVal = (i * 100) + 680;
		ydrenderPoints_struct[i].finalVal = (i * 100) + 780;
		ydrenderPoints_struct[i].initPoints = (i * 100) + 680;
		ydrenderPoints_struct[i].renderSpeed = increment;

	}

	if (ydrenderPoints_struct == NULL)
	{
		fprintf(gpFile, "initialize() -> Failed to initialize ydrenderPoints_struct...\n");
	}
	else
	{
		fprintf(gpFile, "initialize() -> ydrenderPoints_struct initialized successfully...\n");
	}

	// Final Render Points
	for (int i = 0; i < 7; i++)//7
	{
		frenderPoints_struct[i].initialVal = i * 50;
		frenderPoints_struct[i].finalVal = (i * 50) + 50;
		frenderPoints_struct[i].initPoints = i * 50;
		frenderPoints_struct[i].renderSpeed = increment;
	}

	for (int i = 7; i < 10; i++)//3
	{
		frenderPoints_struct[i].initialVal = 100 + (i * 50);
		frenderPoints_struct[i].finalVal = (i * 50) + 150;
		frenderPoints_struct[i].initPoints = 100 + (i * 50);
		frenderPoints_struct[i].renderSpeed = increment;
	}

	for (int i = 0; i < 3; i++)//3
	{
		frenderPoints_struct[10 + i].initialVal = 700 + (i * 50);
		frenderPoints_struct[10 + i].finalVal = (i * 50) + 750;
		frenderPoints_struct[10 + i].initPoints = 700 + (i * 50);
		frenderPoints_struct[10 + i].renderSpeed = increment;
	}
	for (int i = 0; i < 3; i++)//9
	{
		frenderPoints_struct[13 + i].initialVal = 940 + (i * 50);
		frenderPoints_struct[13 + i].finalVal = (i * 50) + 990;
		frenderPoints_struct[13 + i].initPoints = 940 + (i * 50);
		frenderPoints_struct[13 + i].renderSpeed = increment;

		frenderPoints_struct[16 + i].initialVal = 1180 + (i * 50);
		frenderPoints_struct[16 + i].finalVal = (i * 50) + 1230;
		frenderPoints_struct[16 + i].initPoints = 1180 + (i * 50);
		frenderPoints_struct[16 + i].renderSpeed = increment;

		frenderPoints_struct[19 + i].initialVal = 1420 + (i * 50);
		frenderPoints_struct[19 + i].finalVal = (i * 50) + 1470;
		frenderPoints_struct[19 + i].initPoints = 1420 + (i * 50);
		frenderPoints_struct[19 + i].renderSpeed = increment;
	}
	
	if (frenderPoints_struct == NULL)
	{
		fprintf(gpFile, "initialize() -> Failed to initialize frenderPoints_struct...\n");
	}
	else
	{
		fprintf(gpFile, "initialize() -> frenderPoints_struct initialized successfully...\n");
	}

	hBitmap4 = LoadBitmap((HINSTANCE)GetWindowLongPtr(ghwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(MY_WINDOW));
	if (hBitmap4 == NULL)
	{
		MessageBox(ghwnd, TEXT("Failed to load bitmap4!"), TEXT("Error"), MB_ICONERROR);
	}
	else
	{
		fprintf(gpFile, "hBitmap4 -> Texture loaded successfully.\n");
	}
}

void display(void)
{
	hdc = GetDC(ghwnd);
	hdc = BeginPaint(ghwnd, &ps);
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, gcxScreen, gcyScreen);
	HBITMAP hBitMDC = (HBITMAP)SelectObject(hMemDC, hBitmap);
	
	if (introSceneCounter == 1)
	{
		sceneIntro();
	}
	if (introSceneCounter == 2)
	{
		sceneIntro1();
	}
	fprintf(gpFile, "IntroSceneCounter %d\n", introSceneCounter);

	if (sceneCounter == 1)
	{
		sceneOne();
	}
	if (sceneCounter == 2)
	{
		sceneTwo();
		for (int i = 0; i < 8; i++) {
			xIncreRenderPoints(choosePenColor(0, 10), renderPoints_struct[i].initialVal, renderPoints_struct[i].finalVal, renderPoints_struct[i].renderSpeed, &renderPoints_struct[i].initPoints);
			xDecreRenderPoints(choosePenColor(0, 10), xdrenderPoints_struct[i].initialVal, xdrenderPoints_struct[i].finalVal, xdrenderPoints_struct[i].renderSpeed, &xdrenderPoints_struct[i].initPoints);
		}

		for (int i = 0; i < 4; i++) {
			yDecreRenderPoints(choosePenColor(4, 10), ydrenderPoints_struct[i].initialVal, ydrenderPoints_struct[i].finalVal, ydrenderPoints_struct[i].renderSpeed, &ydrenderPoints_struct[i].initPoints);
		}
	}

	if (sceneCounter == 3)
	{
		
		sceneThree();
		for (int i = 0; i < 8; i++) {
			xIncreRenderPoints(choosePenColor(4, 10), renderPoints_struct[i].initialVal, renderPoints_struct[i].finalVal, renderPoints_struct[i].renderSpeed, &renderPoints_struct[i].initPoints);
			xDecreRenderPoints(choosePenColor(4, 10), xdrenderPoints_struct[i].initialVal, xdrenderPoints_struct[i].finalVal, xdrenderPoints_struct[i].renderSpeed, &xdrenderPoints_struct[i].initPoints);
		}

		for (int i = 0; i < 4; i++) {
			yDecreRenderPoints(choosePenColor(8, 10), ydrenderPoints_struct[i].initialVal, ydrenderPoints_struct[i].finalVal, ydrenderPoints_struct[i].renderSpeed, &ydrenderPoints_struct[i].initPoints);
		}

	}
	if (sceneCounter == 4)
	{
		sceneFour();
		for (int i = 0; i < 8; i++) {
			xIncreRenderPoints(choosePenColor(8, 10), renderPoints_struct[i].initialVal, renderPoints_struct[i].finalVal, renderPoints_struct[i].renderSpeed, &renderPoints_struct[i].initPoints);
			xDecreRenderPoints(choosePenColor(8, 10), xdrenderPoints_struct[i].initialVal, xdrenderPoints_struct[i].finalVal, xdrenderPoints_struct[i].renderSpeed, &xdrenderPoints_struct[i].initPoints);
		}

		for (int i = 0; i < 4; i++) {
			yDecreRenderPoints(choosePenColor(10, 10), ydrenderPoints_struct[i].initialVal, ydrenderPoints_struct[i].finalVal, ydrenderPoints_struct[i].renderSpeed, &ydrenderPoints_struct[i].initPoints);
		}
	}
	if (sceneCounter == 5)
	{
		sceneFive();
		for (int i = 0; i < 8; i++) {
			xIncreRenderPoints(choosePenColor(10, 10), renderPoints_struct[i].initialVal, renderPoints_struct[i].finalVal, renderPoints_struct[i].renderSpeed, &renderPoints_struct[i].initPoints);
			xDecreRenderPoints(choosePenColor(10, 10), xdrenderPoints_struct[i].initialVal, xdrenderPoints_struct[i].finalVal, xdrenderPoints_struct[i].renderSpeed, &xdrenderPoints_struct[i].initPoints);
		}

		for (int i = 0; i < 4; i++) {
			yDecreRenderPoints(choosePenColor(6, 10), ydrenderPoints_struct[i].initialVal, ydrenderPoints_struct[i].finalVal, ydrenderPoints_struct[i].renderSpeed, &ydrenderPoints_struct[i].initPoints);
		}
	}
	if (sceneCounter == 6)
	{
		sceneSix();
		for (int i = 0; i < 8; i++) {
			xIncreRenderPoints(choosePenColor(6, 10), renderPoints_struct[i].initialVal, renderPoints_struct[i].finalVal, renderPoints_struct[i].renderSpeed, &renderPoints_struct[i].initPoints);
			xDecreRenderPoints(choosePenColor(6, 10), xdrenderPoints_struct[i].initialVal, xdrenderPoints_struct[i].finalVal, xdrenderPoints_struct[i].renderSpeed, &xdrenderPoints_struct[i].initPoints);
		}

		for (int i = 0; i < 4; i++) {
			yDecreRenderPoints(choosePenColor(8, 10), ydrenderPoints_struct[i].initialVal, ydrenderPoints_struct[i].finalVal, ydrenderPoints_struct[i].renderSpeed, &ydrenderPoints_struct[i].initPoints);
		}
	}
	if (sceneCounter == 7)
	{

		
		sceneSeven();
		for (int i = 0; i < 7; i++) {
			finalRenderPoints(choosePenColor(0, 10), frenderPoints_struct[i].initialVal, frenderPoints_struct[i].finalVal, frenderPoints_struct[i].renderSpeed, &frenderPoints_struct[i].initPoints);
		}

		for (int i = 7; i < 10; i++)
		{
			finalRenderPoints(choosePenColor(4, 10), frenderPoints_struct[i].initialVal, frenderPoints_struct[i].finalVal, frenderPoints_struct[i].renderSpeed, &frenderPoints_struct[i].initPoints);
		}

		for (int i = 10; i < 13; i++)
		{
			finalRenderPoints(choosePenColor(8, 10), frenderPoints_struct[i].initialVal, frenderPoints_struct[i].finalVal, frenderPoints_struct[i].renderSpeed, &frenderPoints_struct[i].initPoints);
		}

		for (int i = 13; i < 16; i++)
		{
			finalRenderPoints(choosePenColor(10, 10), frenderPoints_struct[i].initialVal, frenderPoints_struct[i].finalVal, frenderPoints_struct[i].renderSpeed, &frenderPoints_struct[i].initPoints);
		}
		for (int i = 16; i < 19; i++)
		{
			finalRenderPoints(choosePenColor(6, 10), frenderPoints_struct[i].initialVal, frenderPoints_struct[i].finalVal, frenderPoints_struct[i].renderSpeed, &frenderPoints_struct[i].initPoints);
		}
		for (int i = 19; i < 22; i++)
		{
			finalRenderPoints(choosePenColor(8, 10), frenderPoints_struct[i].initialVal, frenderPoints_struct[i].finalVal, frenderPoints_struct[i].renderSpeed, &frenderPoints_struct[i].initPoints);
		}


		BITMAP bitmap5;
		GetObject(hBitmap4, sizeof(BITMAP), &bitmap5);

		HDC hdcMem1 = CreateCompatibleDC(hMemDC);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem1, hBitmap4);

		// position & size
		int destX = 1570;
		int destY = 415;
		int destWidth = 340;
		int destHeight = 250;

		// Draw the bitmap
		StretchBlt(hMemDC, destX, destY, destWidth, destHeight,
			hdcMem1, 0, 0, bitmap5.bmWidth, bitmap5.bmHeight, SRCCOPY);

		// Cleanup
		SelectObject(hdcMem1, hBitmap4);
		DeleteObject(hOldBitmap);
		DeleteDC(hdcMem1);
		//ReleaseDC(ghwnd, hdcMem1);
		
	}
	if (sceneCounter == 8)
	{
		sceneEight();
	}
	if (sceneCounter >= 8)
	{
		sceneCounter = 8;
	}
	
	BitBlt(hdc, 0, 0, gcxScreen, gcyScreen, hMemDC, 0, 0, SRCCOPY);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	EndPaint(ghwnd, &ps);
}

void sceneIntro(void)
{
	HPEN hPenRed;
	//refPoints();
	static int i = 0;
	POINT aptplane1[6] = { 960 - i, 440, 1030 - i, 440,
						   930 - i, 540, 1030 - i, 640,
						   960 - i,640, 860 - i, 540, };

	POINT aptplane2[6] = { 960 + i, 440, 890 + i, 440,
						   990 + i, 540, 890 + i, 640,
						   960 + i,640, 1060 + i, 540, };


	POINT blackScreen[5] = { 960 - i, 440, 860 - i ,540, 960 - i, 640,
							 300 - i, 640, 300 - i, 440};

	POINT blackScreen1[5] = { 960 + i, 440, 990 + i ,540, 960 + i, 640,
							 1620 + i, 640, 1620 + i, 440 };

	HFONT hFont = CreateFont(150, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	//SetTextAlign(hMemDC, TA_CENTER);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 365, 470, "DECIMALS GROUP", 14);
	//SetBkMode(hMemDC, OPAQUE);
	DeleteObject(hFont);

	
	HBRUSH orange = CreateSolidBrush(RGB(0, 0, 0));
	hPenRed = choosePenColor(5, 5);
	SelectObject(hMemDC, orange);
	SetPolyFillMode(hMemDC, ALTERNATE);
	Polygon(hMemDC, blackScreen, 5);
	Polygon(hMemDC, blackScreen1, 5);
	DeleteObject(orange);
	hPenRed = choosePenColor(5, 5);
	SelectObject(hMemDC, hPenRed);
	DeleteObject(hPenRed);

	hPenRed = choosePenColor(5, 5);
	SelectObject(hMemDC, hPenRed);
	SetPolyFillMode(hMemDC, ALTERNATE);
	Polygon(hMemDC, aptplane1, 6);
	Polygon(hMemDC, aptplane2, 6);
	DeleteObject(hPenRed);

	i+=6;
	if (i > 790)
	{
		i = 790;
	}

}

void sceneIntro1(void)
{
	//refPoints();

	int a = 540;
	int b = 540;
	HPEN hPen;
	static int i = 0;
	HFONT hFont = CreateFont(100, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 210, 490, "Welcome To The Journey of MSTC-4", 32);
	DeleteObject(hFont);

	POINT blackScreen[4] = { -100 + i, 440, 1920 + i, 440,
							 1920 + i, 640, -100 + i, 640 };

	HBRUSH orange = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hMemDC, orange);
	SetPolyFillMode(hMemDC, ALTERNATE);
	Polygon(hMemDC, blackScreen, 4);
	DeleteObject(orange);

	i += 10;
	
	if (i > 1920)
	{
		i = 1920;
	}

	hPen = choosePenColor(0, 5);
	dCircle(hMemDC, hPen, xz + b - a, b , 100);

	hPen = choosePenColor(8, 3);
	dMMovingLine(hMemDC, hPen, xz + b - a, b, 100);

	xz += 10;
	if (xz > 1815)
	{
		xz = 1815;
	}

	SetBkMode(hMemDC, OPAQUE);
	

}

void sceneOne(void)
{
	HPEN hPenRed;

	POINT aptplane[10] = { 270, 450, 330, 390,
						   1580, 390, 1640, 450,
						   1730,540, 1640, 630,
						   1580, 690,  330, 690,
						   270, 630, 180 ,540 };

	POINT aptplane1[6] = { 170, 440, 240, 440,
						   140, 540, 240, 640,
						   170,640, 70, 540, };

	POINT aptplane2[6] = { 1750, 440, 1680, 440,
						   1780, 540, 1680, 640,
						   1750,640, 1850, 540, };

	linesBackground(choosePenColor(0, 4));

	hPenRed = choosePenColor(5, 5);
	SelectObject(hMemDC, hPenRed);
	SetPolyFillMode(hMemDC, ALTERNATE);
	Polygon(hMemDC, aptplane, 10);
	Polygon(hMemDC, aptplane1, 6);
	Polygon(hMemDC, aptplane2, 6);
	DeleteObject(hPenRed);
	HFONT hFont = CreateFont(80, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 450, 500, "When Code Meets The Machine", 27);
	DeleteObject(hFont);

}

void sceneTwo(void)
{
	HPEN hPenRed;
	POINT FileI[5] = { 915, 170, 915, 270,
					   1005, 270, 1005, 180,
					   995, 170 };
	
	

	
	linesBackground(choosePenColor(4,4));
	HBRUSH orange = CreateSolidBrush(RGB(255, 165, 0));
	mpreProcessor(orange);
	DeleteObject(orange);

	HFONT hFont = CreateFont(70, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 755, 55, "Pre-Processor", 13);
	DeleteObject(hFont);

	HFONT hFont1 = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont1);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 576, 310, "Include Header Files & Expand Macros", 36);
	DeleteObject(hFont1);

	// .i File
	hPenRed = choosePenColor(4, 5);
	SelectObject(hMemDC, hPenRed);
	Polygon(hMemDC, FileI, 5);
	DeleteObject(hPenRed);

	HFONT hFontData = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontData);
	SetBkMode(hMemDC, OPAQUE);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 917, 480, "Data", 4);
	DeleteObject(hFontData);

	HFONT hFontProcess = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontProcess);
	SetBkMode(hMemDC, OPAQUE);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 850, 540, "Processing", 10);
	DeleteObject(hFontProcess);

	HFONT hFontII = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontII);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 940, 180, ".ii", 3);
	DeleteObject(hFontII);

	HFONT hFontI = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontI);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 940, 225, ".i", 2);
	DeleteObject(hFontI);

}

void sceneThree(void)
{

	HPEN hPenRed;
	POINT FileAsm[5] = { 915, 170, 915, 270,
					   1005, 270, 1005, 180,
					   995, 170 };

	HBRUSH orange = CreateSolidBrush(RGB(2, 151, 255));
	mpreProcessor(orange);
	DeleteObject(orange);
	linesBackground(choosePenColor(8, 4));
	hPenRed = choosePenColor(8, 5);

	HFONT hFont = CreateFont(70, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 830, 55, "Compiler", 8);
	DeleteObject(hFont);

	
	HFONT hFont1 = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont1);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 706, 310, "Generate Assembly Code",22);
	DeleteObject(hFont1);

	// .asm File
	hPenRed = choosePenColor(8, 5);
	SelectObject(hMemDC, hPenRed);
	Polygon(hMemDC, FileAsm, 5);
	DeleteObject(hPenRed);

	HFONT hFontData = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontData);
	SetBkMode(hMemDC, OPAQUE);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 917, 480, "Data", 4);
	DeleteObject(hFontData);

	HFONT hFontProcess = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontProcess);
	SetBkMode(hMemDC, OPAQUE);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 850, 540, "Processing", 10);
	DeleteObject(hFontProcess);

	HFONT hFontAsm = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontAsm);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 920, 180, ".asm", 4);
	DeleteObject(hFontAsm);


	HFONT hFontS = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontS);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 942, 225, ".s", 2);
	DeleteObject(hFontS);
}

void sceneFour(void)
{
	HPEN hPenRed;
	HPEN hLinePen;
	POINT FileObj[5] = { 915, 170, 915, 270,
					   1005, 270, 1005, 180,
					   995, 170 };

	HBRUSH orange = CreateSolidBrush(RGB(13, 190, 17));

	linesBackground(choosePenColor(10, 4));
	mpreProcessor(orange);

	hPenRed = choosePenColor(0, 5);
	SelectObject(hMemDC, hPenRed);

	HFONT hFont = CreateFont(70, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(13, 190, 17));
	TextOut(hMemDC, 810, 55, "Assembler", 9);
	DeleteObject(hFont);


	HFONT hFont1 = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont1);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(13, 190, 17));
	TextOut(hMemDC, 730, 310, "Generate Machine Code", 21);
	DeleteObject(hFont1);

	//obj
	hPenRed = choosePenColor(10, 5);
	SelectObject(hMemDC, hPenRed);
	Polygon(hMemDC, FileObj, 5);

	HFONT hFontData = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontData);
	SetBkMode(hMemDC, OPAQUE);
	SetTextColor(hMemDC, RGB(13, 190, 17));
	TextOut(hMemDC, 917, 480, "Data", 4);
	DeleteObject(hFontData);

	HFONT hFontProcess = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontProcess);
	SetBkMode(hMemDC, OPAQUE);
	SetTextColor(hMemDC, RGB(13, 190, 17));
	TextOut(hMemDC, 850, 540, "Processing", 10);
	DeleteObject(hFontProcess);

	HFONT hFontObj = CreateFont(38, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontObj);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(13, 190, 17));
	TextOut(hMemDC, 927, 180, ".obj", 4);
	DeleteObject(hFontObj);

	HFONT hFontO = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontO);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(13, 190, 17));
	TextOut(hMemDC, 945, 225, ".o", 2);
	DeleteObject(hFontO);
	DeleteObject(hPenRed);
}

void sceneFive(void)
{

	HPEN hPenRed;
	HPEN hLinePen;
	POINT FileLib[5] = { 915, 170, 915, 270,
					   1005, 270, 1005, 180,
					   995, 170 };

	
	HBRUSH orange = CreateSolidBrush(RGB(255, 0, 255));

	linesBackground(choosePenColor(6, 4));
	mpreProcessor(orange);

	hPenRed = choosePenColor(0, 5);
	SelectObject(hMemDC, hPenRed);

	HFONT hFont = CreateFont(70, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 0, 255));
	TextOut(hMemDC, 865, 55, "Linker", 6);
	DeleteObject(hFont);

	HFONT hFont1 = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont1);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 0, 255));
	TextOut(hMemDC, 670, 310, "Linking Static Library .lib & .a", 32);
	DeleteObject(hFont1);

	// .i File
	hPenRed = choosePenColor(4, 5);
	SelectObject(hMemDC, hPenRed);
	Polygon(hMemDC, FileLib, 5);

	HFONT hFontData = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontData);
	SetBkMode(hMemDC, OPAQUE);
	SetTextColor(hMemDC, RGB(255, 0, 255));
	TextOut(hMemDC, 917, 480, "Data", 4);
	DeleteObject(hFontData);

	HFONT hFontProcess = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontProcess);
	SetBkMode(hMemDC, OPAQUE);
	SetTextColor(hMemDC, RGB(255, 0, 255));
	TextOut(hMemDC, 850, 540, "Processing", 10);
	DeleteObject(hFontProcess);

	// .lib
	hPenRed = choosePenColor(6, 5);
	SelectObject(hMemDC, hPenRed);
	Polygon(hMemDC, FileLib, 5);

	HFONT hFontLib = CreateFont(38, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontLib);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 0, 255));
	TextOut(hMemDC, 935, 180, ".lib", 4);
	DeleteObject(hFontLib);

	HFONT hFontA = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontA);
	SetBkMode(hMemDC, TRANSPARENT);

	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 0, 255));
	TextOut(hMemDC, 935, 225, ".a", 2);
	DeleteObject(hFontA);
	DeleteObject(hPenRed);
}

void sceneSix(void)
{

	HPEN hPenRed;
	HPEN hLinePen;
	POINT FileExe[5] = { 915, 170, 915, 270,
					   1005, 270, 1005, 180,
					   995, 170 };

	linesBackground(choosePenColor(8, 4));
	HBRUSH orange = CreateSolidBrush(RGB(0, 191, 255));
	mpreProcessor(orange);

	hPenRed = choosePenColor(0, 5);
	SelectObject(hMemDC, hPenRed);

	//Executable
	hPenRed = choosePenColor(8, 5);
	SelectObject(hMemDC, hPenRed);

	HFONT hFontExeFile = CreateFont(70, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontExeFile);
	SetBkMode(hMemDC, OPAQUE);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(0, 191, 255));
	TextOut(hMemDC, 745, 55, "Executable File", 15);
	DeleteObject(hFontExeFile);

	//Executable
	hPenRed = choosePenColor(8, 5);
	SelectObject(hMemDC, hPenRed);
	Polygon(hMemDC, FileExe, 5);

	HFONT hFontData = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontData);
	SetBkMode(hMemDC, OPAQUE);
	SetTextColor(hMemDC, RGB(0, 191, 255));
	TextOut(hMemDC, 917, 480, "Data", 4);
	DeleteObject(hFontData);

	HFONT hFontProcess = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontProcess);
	SetBkMode(hMemDC, OPAQUE);
	SetTextColor(hMemDC, RGB(0, 191, 255));
	TextOut(hMemDC, 850, 540, "Processing", 10);
	DeleteObject(hFontProcess);

	//.exe File
	HFONT hFontExe = CreateFont(38, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontExe);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(0, 191, 255));
	TextOut(hMemDC, 928, 195, ".exe", 4);
	DeleteObject(hFontExe);
	HFONT hFont1 = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont1);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(0, 191, 255));
	TextOut(hMemDC, 660, 310, "Executable Machine Code .exe", 28);

	DeleteObject(hFont1);
	DeleteObject(hPenRed);	
}

void sceneSeven(void)
{
	HPEN hPenRed;
	HPEN hLinePen;
	POINT FileI[5] = { 360, 500, 360, 600,
					   450, 600, 450, 510,
					   440, 500 };

	linesBackground2();
	HFONT hFont = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	SetTextColor(hMemDC, (0, 191, 255));
	TextOut(hMemDC, 647, 740, "When Code Meets The Machine", 27);
	DeleteObject(hFont);

	HFONT hFontPre = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontPre);
	SetBkMode(hMemDC, OPAQUE);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 310, 370, "Pre-Processor", 13);
	DeleteObject(hFontPre);
	
	// .i File
	hPenRed = choosePenColor(4, 5);
	SelectObject(hMemDC, hPenRed);
	Polygon(hMemDC, FileI, 5);
	DeleteObject(hPenRed);

	HFONT hFontII = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontII);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 385, 510, ".ii", 3);
	DeleteObject(hFontII);

	HFONT hFontI = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontI);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 385, 550, ".i", 2);
	DeleteObject(hFontI);

	//Compiler
	POINT FileAsm[5] = { 600, 500, 600, 600,
					   690, 600, 690, 510,
					   680, 500 };
	hPenRed = choosePenColor(8, 5);
	SelectObject(hMemDC, hPenRed);
	Polygon(hMemDC, FileAsm, 5);
	DeleteObject(hPenRed);

	HFONT hFontAsm = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontAsm);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 605, 510, ".asm", 4);
	DeleteObject(hFontAsm);
	
	HFONT hFontS = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontS);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 605, 550, ".s", 2);
	DeleteObject(hFontS);

	HFONT hFontComp = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontComp);
	SetBkMode(hMemDC, OPAQUE);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 585, 370, "Compiler", 8);
	DeleteObject(hFontComp);

	//Assembler
	POINT FileObj[5] = {850, 500, 850, 600,
					   940, 600, 940, 510,
					   930, 500 };
	hPenRed = choosePenColor(10, 5);
	SelectObject(hMemDC, hPenRed);
	Polygon(hMemDC, FileObj, 5);
	DeleteObject(hPenRed);

	HFONT hFontObj = CreateFont(38, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontObj);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(13, 190, 17));
	TextOut(hMemDC, 865, 510, ".obj", 4);
	DeleteObject(hFontObj);

	HFONT hFontO = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontO);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(13, 190, 17));
	TextOut(hMemDC, 865, 550, ".o", 2);
	DeleteObject(hFontO);

	HFONT hFontAsmb = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontAsmb);
	SetBkMode(hMemDC, OPAQUE);
	SetTextColor(hMemDC, RGB(13, 190, 17));
	TextOut(hMemDC, 820, 370, "Assembler", 9);
	DeleteObject(hFontAsmb);

	//Linker
	POINT FileLib[5] = { 1090, 500, 1090, 600,
					   1180, 600, 1180, 510,
					   1170, 500 };
	hPenRed = choosePenColor(6, 5);
	SelectObject(hMemDC, hPenRed);
	Polygon(hMemDC, FileLib, 5);
	DeleteObject(hPenRed);

	HFONT hFontLib = CreateFont(38, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontLib);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(255, 0, 255));
	TextOut(hMemDC, 1110, 510, ".lib", 4);
	DeleteObject(hFontLib);
	
	HFONT hFontA = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontA);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(255, 0, 255));
	TextOut(hMemDC, 1110, 550, ".a", 2);
	DeleteObject(hFontA);

	HFONT hFontLink = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontLink);
	SetBkMode(hMemDC, OPAQUE);
	SetTextColor(hMemDC, RGB(255, 0, 255));
	TextOut(hMemDC, 1090, 370, "Linker", 6);
	DeleteObject(hFontLink);

	//Executable
	HFONT hFontExeFile = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontExeFile);
	SetBkMode(hMemDC, OPAQUE);
	SetTextColor(hMemDC, RGB(0, 191, 255));
	TextOut(hMemDC, 1290, 370, "Executable", 10);
	DeleteObject(hFontExeFile);

	//Executable
	POINT FileExe[5] = { 1330, 500, 1330, 600,
					  1420, 600, 1420, 510,
					   1410, 500 };

	hPenRed = choosePenColor(8, 5);
	SelectObject(hMemDC, hPenRed);
	Polygon(hMemDC, FileExe, 5);
	DeleteObject(hPenRed);

	HFONT hFontExe = CreateFont(38, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontExe);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(0, 191, 255));
	TextOut(hMemDC, 1342, 528, ".exe", 4);
	DeleteObject(hFontExe);
}

void sceneEight(void)
{
	BITMAP bitmap5;
	GetObject(hBitmap4, sizeof(BITMAP), &bitmap5);

	HDC hdcMem1 = CreateCompatibleDC(hMemDC);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem1, hBitmap4);
	static int i = 0;
	static int j = 0;
	static int destX = 0;
	static int destY = 0;
	static int destWidth = 0;	
	static int destHeight = 0;
	
	if (i < 780)
	{
		destX = 1570 - i;
		destY = 415;
		destWidth = 340;
		destHeight = 250;
		// Draw the bitmap
		StretchBlt(hMemDC, destX, destY, destWidth, destHeight,
			hdcMem1, 0, 0, bitmap5.bmWidth, bitmap5.bmHeight, SRCCOPY);
		i+=5;
	}
	else if(i > 780)
	{
		i = 780;

		destX = 1570 - i;
		destY = 415;
		destWidth = 340;
		destHeight = 250;
		// Draw the bitmap
		StretchBlt(hMemDC, destX, destY, destWidth, destHeight,
			hdcMem1, 0, 0, bitmap5.bmWidth, bitmap5.bmHeight, SRCCOPY);
	}
	else if (j < 700 || i == 780)
	{
		destX = 790 - (j * 4);
		destY = 415 - (j * 3);
		destWidth = 340 + (j * 8);
		destHeight = 250 + (j * 6);
		// Draw the bitmap
		StretchBlt(hMemDC, destX, destY, destWidth, destHeight,
			hdcMem1, 0, 0, bitmap5.bmWidth, bitmap5.bmHeight, SRCCOPY);
		j+=3;

		if (j >= 700)
		{
			j = 700;
		}
	}

	DeleteObject(hOldBitmap);
	DeleteDC(hdcMem1);
}

void xIncreRenderPoints(HPEN brushColor,int initialVal,int finalVal,int speed, int* pointsVal)
{
	SelectObject(hMemDC, brushColor);


	if (pointsVal == NULL || *pointsVal >= finalVal)
	{
		fprintf(gpFile, "xIncreRenderPoints() -> Render Points either NULL or Not in Range.\n");
		return;
	}
	else
	{
		//fprintf(gpFile, "xIncreRenderPoints() -> Render Points in Range to render.\n");
	}

	for (int j = 0; j < NUM_POINTS; j++)
	{
		int x = *pointsVal;
		int y = 435 + (j * 30);

		MoveToEx(hMemDC, x, y, NULL);
		LineTo(hMemDC, x, y);
	}

	*pointsVal = *pointsVal + speed;
	if (*pointsVal >= finalVal)
	{
		*pointsVal = initialVal;
	}

	DeleteObject(brushColor);
}

void xDecreRenderPoints(HPEN brushColor, int initialVal, int finalVal, int speed, int* pointsVal)
{
	SelectObject(hMemDC, brushColor);


	if (pointsVal == NULL || *pointsVal <= finalVal)
	{
		fprintf(gpFile, "xDecreRenderPoints() -> Render Points either NULL or Not in Range.\n");
		return;
	}
	else
	{
		//fprintf(gpFile, "xDecreRenderPoints() -> Render Points in Range to render.\n");
	}

	for (int j = 0; j < NUM_POINTS; j++)
	{
		int x = *pointsVal;
		int y = 435 + (j * 30);

		MoveToEx(hMemDC, x, y, NULL);
		LineTo(hMemDC, x, y);
	}

	*pointsVal = *pointsVal - speed;
	if (*pointsVal <= finalVal)
	{
		*pointsVal = initialVal;
	}
	DeleteObject(brushColor);
}

void yDecreRenderPoints(HPEN brushColor, int initialVal, int finalVal, int speed, int* pointsVal)
{
	SelectObject(hMemDC, brushColor);


	if (pointsVal == NULL || *pointsVal >= finalVal)
	{
		fprintf(gpFile, "yDecreRenderPoints() -> Render Points either NULL or Not in Range.\n");
		return;
	}
	else
	{
		//fprintf(gpFile, "yDecreRenderPoints() -> Render Points in Range to render.\n");
	}

	for (int j = 0; j < 11; j++)
	{
		int x = 810 + (j * 30);
		int y = *pointsVal;

		MoveToEx(hMemDC, x, y, NULL);
		LineTo(hMemDC, x, y);
	}

	*pointsVal = *pointsVal + speed;
	if (*pointsVal >= finalVal)
	{
		*pointsVal = initialVal;
	}
	DeleteObject(brushColor);
}

void finalRenderPoints(HPEN brushColor, int initialVal, int finalVal, int speed, int* pointsVal)
{
	SelectObject(hMemDC, brushColor);


	if (pointsVal == NULL || *pointsVal >= finalVal)
	{
		fprintf(gpFile, "finalRenderPoints() -> Render Points either NULL or Not in Range.\n");
		return;
	}
	else
	{
	//	fprintf(gpFile, "finalRenderPoints() -> Render Points in Range to render.\n");
	}

	for (int j = 0; j < 3; j++)
	{
		int x = *pointsVal;
		int y = 520 + (j * 30);

		MoveToEx(hMemDC, x, y, NULL);
		LineTo(hMemDC, x, y);
	}

	*pointsVal = *pointsVal + speed;
	if (*pointsVal >= finalVal)
	{
		*pointsVal = initialVal;
	}
	DeleteObject(brushColor);
}

void mpreProcessor(HBRUSH colorBrush)
{
	HPEN hLinePen;
	hLinePen = choosePenColor(0, 7);
	HPEN hPenRed;
	hPenRed = choosePenColor(0, 5);

	SelectObject(hMemDC, hPenRed);
	RECT rgn = { 800, 420, 1120, 660 };
	
	Rectangle(hMemDC, 800, 420, 1120, 660);
	FillRect(hMemDC, &rgn, colorBrush);
	DeleteObject(hPenRed);
	//Pins
	SelectObject(hMemDC, hLinePen);

	MoveToEx(hMemDC, 800, 435, NULL);
	LineTo(hMemDC, 780, 435);

	MoveToEx(hMemDC, 800, 465, NULL);
	LineTo(hMemDC, 780, 465);

	MoveToEx(hMemDC, 800, 495, NULL);
	LineTo(hMemDC, 780, 495);

	MoveToEx(hMemDC, 800, 525, NULL);
	LineTo(hMemDC, 780, 525);

	MoveToEx(hMemDC, 800, 555, NULL);
	LineTo(hMemDC, 780, 555);

	MoveToEx(hMemDC, 800, 585, NULL);
	LineTo(hMemDC, 780, 585);

	MoveToEx(hMemDC, 800, 615, NULL);
	LineTo(hMemDC, 780, 615);

	MoveToEx(hMemDC, 800, 645, NULL);
	LineTo(hMemDC, 780, 645);

	//Reverse

	MoveToEx(hMemDC, 1119, 435, NULL);
	LineTo(hMemDC, 1138, 435);

	MoveToEx(hMemDC, 1119, 465, NULL);
	LineTo(hMemDC, 1138, 465);

	MoveToEx(hMemDC, 1119, 495, NULL);
	LineTo(hMemDC, 1138, 495);

	MoveToEx(hMemDC, 1119, 525, NULL);
	LineTo(hMemDC, 1138, 525);

	MoveToEx(hMemDC, 1119, 555, NULL);
	LineTo(hMemDC, 1138, 555);

	MoveToEx(hMemDC, 1119, 585, NULL);
	LineTo(hMemDC, 1138, 585);

	MoveToEx(hMemDC, 1119, 615, NULL);
	LineTo(hMemDC, 1138, 615);

	MoveToEx(hMemDC, 1119, 645, NULL);
	LineTo(hMemDC, 1138, 645);

	// Uplines
	MoveToEx(hMemDC, 810, 420, NULL);
	LineTo(hMemDC, 810, 400);

	MoveToEx(hMemDC, 840, 420, NULL);
	LineTo(hMemDC, 840, 400);

	MoveToEx(hMemDC, 870, 420, NULL);
	LineTo(hMemDC, 870, 400);

	MoveToEx(hMemDC, 900, 420, NULL);
	LineTo(hMemDC, 900, 400);

	MoveToEx(hMemDC, 930, 420, NULL);
	LineTo(hMemDC, 930, 400);

	MoveToEx(hMemDC, 960, 420, NULL);
	LineTo(hMemDC, 960, 400);

	MoveToEx(hMemDC, 990, 420, NULL);
	LineTo(hMemDC, 990, 400);

	MoveToEx(hMemDC, 1020, 420, NULL);
	LineTo(hMemDC, 1020, 400);

	MoveToEx(hMemDC, 1050, 420, NULL);
	LineTo(hMemDC, 1050, 400);

	MoveToEx(hMemDC, 1080, 420, NULL);
	LineTo(hMemDC, 1080, 400);

	MoveToEx(hMemDC, 1110, 420, NULL);
	LineTo(hMemDC, 1110, 400);

	//Reverse

	MoveToEx(hMemDC, 810, 660, NULL);
	LineTo(hMemDC, 810, 680);

	MoveToEx(hMemDC, 840, 660, NULL);
	LineTo(hMemDC, 840, 680);

	MoveToEx(hMemDC, 870, 660, NULL);
	LineTo(hMemDC, 870, 680);

	MoveToEx(hMemDC, 900, 660, NULL);
	LineTo(hMemDC, 900, 680);

	MoveToEx(hMemDC, 930, 660, NULL);
	LineTo(hMemDC, 930, 680);

	MoveToEx(hMemDC, 960, 660, NULL);
	LineTo(hMemDC, 960, 680);

	MoveToEx(hMemDC, 990, 660, NULL);
	LineTo(hMemDC, 990, 680);

	MoveToEx(hMemDC, 1020, 660, NULL);
	LineTo(hMemDC, 1020, 680);

	MoveToEx(hMemDC, 1050, 660, NULL);
	LineTo(hMemDC, 1050, 680);

	MoveToEx(hMemDC, 1080, 660, NULL);
	LineTo(hMemDC, 1080, 680);

	MoveToEx(hMemDC, 1110, 660, NULL);
	LineTo(hMemDC, 1110, 680);

	
	DeleteObject(hLinePen);
}

void linesBackground(HPEN selectedDrawTool)
{

	HPEN hPenWhiteline;
	HPEN hPenWhitedot;
	HPEN hPenWhitedotbig;
	//
	
	hPenWhiteline = selectedDrawTool;
	SelectObject(hMemDC, hPenWhiteline);
	
	MoveToEx(hMemDC, 0, 400, NULL);
	LineTo(hMemDC, 250, 400);
	MoveToEx(hMemDC, 250, 400, NULL);
	LineTo(hMemDC, 300, 350);
	MoveToEx(hMemDC, 300, 350, NULL);
	LineTo(hMemDC, 500, 350);

	MoveToEx(hMemDC, 0, 300, NULL);
	LineTo(hMemDC, 80, 300);
	MoveToEx(hMemDC, 80, 300, NULL);
	LineTo(hMemDC, 80, 350);
	
	MoveToEx(hMemDC, 0, 280, NULL);
	LineTo(hMemDC, 110, 280);

	MoveToEx(hMemDC, 150, 340, NULL);
	LineTo(hMemDC, 200, 300);
	MoveToEx(hMemDC, 200, 300, NULL);
	LineTo(hMemDC, 380, 300);
	MoveToEx(hMemDC, 380, 300, NULL);
	LineTo(hMemDC, 430, 260);

	MoveToEx(hMemDC, 30, 230, NULL);
	LineTo(hMemDC, 100, 230);
	MoveToEx(hMemDC, 100, 230, NULL);
	LineTo(hMemDC, 100, 250);
	MoveToEx(hMemDC, 100, 250, NULL);
	LineTo(hMemDC, 350, 250);

	MoveToEx(hMemDC, 0, 170, NULL);
	LineTo(hMemDC, 70, 170);
	MoveToEx(hMemDC, 70, 170, NULL);
	LineTo(hMemDC, 90, 200);
	MoveToEx(hMemDC, 90, 200, NULL);
	LineTo(hMemDC, 200, 200);

	MoveToEx(hMemDC, 250, 180, NULL);
	LineTo(hMemDC, 460, 180);
	MoveToEx(hMemDC, 460, 180, NULL);
	LineTo(hMemDC, 500, 250);
	MoveToEx(hMemDC, 500, 250, NULL);
	LineTo(hMemDC, 570, 250);

	MoveToEx(hMemDC, 0, 80, NULL);
	LineTo(hMemDC, 200, 80);
	MoveToEx(hMemDC, 200, 80, NULL);
	LineTo(hMemDC, 250, 130);
	MoveToEx(hMemDC, 250, 130, NULL);
	LineTo(hMemDC, 500, 130);

	MoveToEx(hMemDC, 50, 120, NULL);
	LineTo(hMemDC, 150, 120);

	MoveToEx(hMemDC, 300, 0, NULL);
	LineTo(hMemDC, 300, 80);
	MoveToEx(hMemDC, 300, 80, NULL);
	LineTo(hMemDC, 600, 80);

	MoveToEx(hMemDC, 40, 40, NULL);
	LineTo(hMemDC, 200, 40);
	MoveToEx(hMemDC, 200, 0, NULL);
	LineTo(hMemDC, 200, 40);

	MoveToEx(hMemDC, 500, 0, NULL);
	LineTo(hMemDC, 500, 50);
	MoveToEx(hMemDC, 500, 50, NULL);
	LineTo(hMemDC, 700, 50);
	MoveToEx(hMemDC, 700, 50, NULL);
	LineTo(hMemDC, 700, 120);

	//Reverse

	MoveToEx(hMemDC, 0, 680, NULL);
	LineTo(hMemDC, 250, 680);
	MoveToEx(hMemDC, 250, 680, NULL);
	LineTo(hMemDC, 300, 730);
	MoveToEx(hMemDC, 300, 730, NULL);
	LineTo(hMemDC, 500, 730);

	MoveToEx(hMemDC, 0, 780, NULL);
	LineTo(hMemDC, 80, 780);
	MoveToEx(hMemDC, 80, 780, NULL);
	LineTo(hMemDC, 80, 730);

	MoveToEx(hMemDC, 0, 800, NULL);
	LineTo(hMemDC, 110, 800);

	MoveToEx(hMemDC, 150, 740, NULL);
	LineTo(hMemDC, 200, 780);
	MoveToEx(hMemDC, 200, 780, NULL);
	LineTo(hMemDC, 380, 780);
	MoveToEx(hMemDC, 380, 780, NULL);
	LineTo(hMemDC, 430, 820);

	MoveToEx(hMemDC, 30, 850, NULL);
	LineTo(hMemDC, 100, 850);
	MoveToEx(hMemDC, 100, 850, NULL);
	LineTo(hMemDC, 100, 830);
	MoveToEx(hMemDC, 100, 830, NULL);
	LineTo(hMemDC, 350, 830);

	MoveToEx(hMemDC, 0, 908, NULL);
	LineTo(hMemDC, 70, 908);
	MoveToEx(hMemDC, 70, 908, NULL);
	LineTo(hMemDC, 90, 880);
	MoveToEx(hMemDC, 90, 880, NULL);
	LineTo(hMemDC, 200, 880);

	MoveToEx(hMemDC, 250, 900, NULL);
	LineTo(hMemDC, 460, 900);
	MoveToEx(hMemDC, 460, 900, NULL);
	LineTo(hMemDC, 500, 830);
	MoveToEx(hMemDC, 500, 830, NULL);
	LineTo(hMemDC, 570, 830);

	MoveToEx(hMemDC, 0, 1000, NULL);
	LineTo(hMemDC, 200, 1000);
	MoveToEx(hMemDC, 200, 1000, NULL);
	LineTo(hMemDC, 250, 950);
	MoveToEx(hMemDC, 250, 950, NULL);
	LineTo(hMemDC, 500, 950);

	MoveToEx(hMemDC, 50, 960, NULL);
	LineTo(hMemDC, 150, 960);

	MoveToEx(hMemDC, 300, 1080, NULL);
	LineTo(hMemDC, 300, 1000);
	MoveToEx(hMemDC, 300, 1000, NULL);
	LineTo(hMemDC, 600, 1000);

	MoveToEx(hMemDC, 40, 1040, NULL);
	LineTo(hMemDC, 200, 1040);
	MoveToEx(hMemDC, 200, 1080, NULL);
	LineTo(hMemDC, 200, 1040);

	MoveToEx(hMemDC, 500, 1080, NULL);
	LineTo(hMemDC, 500, 1030);
	MoveToEx(hMemDC, 500, 1030, NULL);
	LineTo(hMemDC, 700, 1030);
	MoveToEx(hMemDC, 700, 1030, NULL);
	LineTo(hMemDC, 700, 960);
	DeleteObject(hPenWhiteline);

	hPenWhiteline = selectedDrawTool;
	SelectObject(hMemDC, hPenWhiteline);

	MoveToEx(hMemDC, 1920, 400, NULL);
	LineTo(hMemDC, 1670, 400);
	MoveToEx(hMemDC, 1670, 400, NULL);
	LineTo(hMemDC, 1620, 350);
	MoveToEx(hMemDC, 1620, 350, NULL);
	LineTo(hMemDC, 1420, 350);

	MoveToEx(hMemDC, 1920, 300, NULL);
	LineTo(hMemDC, 1840, 300);
	MoveToEx(hMemDC, 1840, 300, NULL);
	LineTo(hMemDC, 1840, 350);

	MoveToEx(hMemDC, 1920, 280, NULL);
	LineTo(hMemDC, 1810, 280);

	MoveToEx(hMemDC, 1770, 340, NULL);
	LineTo(hMemDC, 1720, 300);
	MoveToEx(hMemDC, 1720, 300, NULL);
	LineTo(hMemDC, 1540, 300);
	MoveToEx(hMemDC, 1540, 300, NULL);
	LineTo(hMemDC, 1490, 260);

	MoveToEx(hMemDC, 1890, 230, NULL);
	LineTo(hMemDC, 1820, 230);
	MoveToEx(hMemDC, 1820, 230, NULL);
	LineTo(hMemDC, 1820, 250);
	MoveToEx(hMemDC, 1820, 250, NULL);
	LineTo(hMemDC, 1570, 250);

	MoveToEx(hMemDC, 1920, 170, NULL);
	LineTo(hMemDC, 1850, 170);
	MoveToEx(hMemDC, 1850, 170, NULL);
	LineTo(hMemDC, 1830, 200);
	MoveToEx(hMemDC, 1830, 200, NULL);
	LineTo(hMemDC, 1720, 200);

	MoveToEx(hMemDC, 1670, 180, NULL);
	LineTo(hMemDC, 1460, 180);
	MoveToEx(hMemDC, 1460, 180, NULL);
	LineTo(hMemDC, 1420, 250);
	MoveToEx(hMemDC, 1420, 250, NULL);
	LineTo(hMemDC, 1350, 250);

	MoveToEx(hMemDC, 1920, 80, NULL);
	LineTo(hMemDC, 1720, 80);
	MoveToEx(hMemDC, 1720, 80, NULL);
	LineTo(hMemDC, 1670, 130);
	MoveToEx(hMemDC, 1670, 130, NULL);
	LineTo(hMemDC, 1420, 130);

	MoveToEx(hMemDC, 1870, 120, NULL);
	LineTo(hMemDC, 1770, 120);

	MoveToEx(hMemDC, 1620, 0, NULL);
	LineTo(hMemDC, 1620, 80);
	MoveToEx(hMemDC, 1620, 80, NULL);
	LineTo(hMemDC, 1320, 80);

	MoveToEx(hMemDC, 1880, 40, NULL);
	LineTo(hMemDC, 1720, 40);
	MoveToEx(hMemDC, 1720, 0, NULL);
	LineTo(hMemDC, 1720, 40);

	MoveToEx(hMemDC, 1420, 0, NULL);
	LineTo(hMemDC, 1420, 50);
	MoveToEx(hMemDC, 1420, 50, NULL);
	LineTo(hMemDC, 1220, 50);
	MoveToEx(hMemDC, 1220, 50, NULL);
	LineTo(hMemDC, 1220, 120);

	//Reverse

	MoveToEx(hMemDC, 1920, 680, NULL);
	LineTo(hMemDC, 1670, 680);
	MoveToEx(hMemDC, 1670, 680, NULL);
	LineTo(hMemDC, 1620, 730);
	MoveToEx(hMemDC, 1620, 730, NULL);
	LineTo(hMemDC, 1420, 730);

	MoveToEx(hMemDC, 1920, 780, NULL);
	LineTo(hMemDC, 1840, 780);
	MoveToEx(hMemDC, 1840, 780, NULL);
	LineTo(hMemDC, 1840, 730);

	MoveToEx(hMemDC, 1920, 800, NULL);
	LineTo(hMemDC, 1810, 800);

	MoveToEx(hMemDC, 1770, 740, NULL);
	LineTo(hMemDC, 1720, 780);
	MoveToEx(hMemDC, 1720, 780, NULL);
	LineTo(hMemDC, 1540, 780);
	MoveToEx(hMemDC, 1540, 780, NULL);
	LineTo(hMemDC, 1490, 820);

	MoveToEx(hMemDC, 1890, 850, NULL);
	LineTo(hMemDC, 1820, 850);
	MoveToEx(hMemDC, 1820, 850, NULL);
	LineTo(hMemDC, 1820, 830);
	MoveToEx(hMemDC, 1820, 830, NULL);
	LineTo(hMemDC, 1570, 830);

	MoveToEx(hMemDC, 1920, 908, NULL);
	LineTo(hMemDC, 1850, 908);
	MoveToEx(hMemDC, 1850, 908, NULL);
	LineTo(hMemDC, 1830, 880);
	MoveToEx(hMemDC, 1830, 880, NULL);
	LineTo(hMemDC, 1720, 880);

	MoveToEx(hMemDC, 1670, 900, NULL);
	LineTo(hMemDC, 1460, 900);
	MoveToEx(hMemDC, 1460, 900, NULL);
	LineTo(hMemDC, 1420, 830);
	MoveToEx(hMemDC, 1420, 830, NULL);
	LineTo(hMemDC, 1350, 830);

	MoveToEx(hMemDC, 1920, 1000, NULL);
	LineTo(hMemDC, 1720, 1000);
	MoveToEx(hMemDC, 1720, 1000, NULL);
	LineTo(hMemDC, 1670, 950);
	MoveToEx(hMemDC, 1670, 950, NULL);
	LineTo(hMemDC, 1420, 950);

	MoveToEx(hMemDC, 1870, 960, NULL);
	LineTo(hMemDC, 1770, 960);

	MoveToEx(hMemDC, 1620, 1080, NULL);
	LineTo(hMemDC, 1620, 1000);
	MoveToEx(hMemDC, 1620, 1000, NULL);
	LineTo(hMemDC, 1320, 1000);

	MoveToEx(hMemDC, 1880, 1040, NULL);
	LineTo(hMemDC, 1720, 1040);
	MoveToEx(hMemDC, 1720, 1080, NULL);
	LineTo(hMemDC, 1720, 1040);

	MoveToEx(hMemDC, 1420, 1080, NULL);
	LineTo(hMemDC, 1420, 1030);
	MoveToEx(hMemDC, 1420, 1030, NULL);
	LineTo(hMemDC, 1220, 1030);
	MoveToEx(hMemDC, 1220, 1030, NULL);
	LineTo(hMemDC, 1220, 960);
	DeleteObject(hPenWhiteline);

	//
	hPenWhitedot = choosePenColor(0, 12);
	SelectObject(hMemDC, hPenWhitedot);
	
	MoveToEx(hMemDC, 500, 350, NULL);
	LineTo(hMemDC, 500, 350);

	MoveToEx(hMemDC, 80, 350, NULL);
	LineTo(hMemDC, 80, 350);

	MoveToEx(hMemDC, 110, 280, NULL);
	LineTo(hMemDC, 110, 280);

	MoveToEx(hMemDC, 30, 230, NULL);
	LineTo(hMemDC, 30, 230);

	MoveToEx(hMemDC, 350, 250, NULL);
	LineTo(hMemDC, 350, 250);

	MoveToEx(hMemDC, 250, 180, NULL);
	LineTo(hMemDC, 250, 180);
	MoveToEx(hMemDC, 570, 250, NULL);
	LineTo(hMemDC, 570, 250);

	MoveToEx(hMemDC, 50, 120, NULL);
	LineTo(hMemDC, 50, 120);

	MoveToEx(hMemDC, 150, 120, NULL);
	LineTo(hMemDC, 150, 120);

	MoveToEx(hMemDC, 600, 80, NULL);
	LineTo(hMemDC, 600, 80);

	MoveToEx(hMemDC, 40, 40, NULL);
	LineTo(hMemDC, 40, 40);

	//Reverse
	MoveToEx(hMemDC, 500, 730, NULL);
	LineTo(hMemDC, 500, 730);

	MoveToEx(hMemDC, 80, 730, NULL);
	LineTo(hMemDC, 80, 730);

	MoveToEx(hMemDC, 110, 800, NULL);
	LineTo(hMemDC, 110, 800);

	MoveToEx(hMemDC, 30, 850, NULL);
	LineTo(hMemDC, 30, 850);

	MoveToEx(hMemDC, 350, 830, NULL);
	LineTo(hMemDC, 350, 830);

	MoveToEx(hMemDC, 250, 900, NULL);
	LineTo(hMemDC, 250, 900);
	MoveToEx(hMemDC, 570, 830, NULL);
	LineTo(hMemDC, 570, 830);

	MoveToEx(hMemDC, 50, 960, NULL);
	LineTo(hMemDC, 50, 960);

	MoveToEx(hMemDC, 150, 960, NULL);
	LineTo(hMemDC, 150, 960);

	MoveToEx(hMemDC, 600, 1000, NULL);
	LineTo(hMemDC, 600, 1000);

	MoveToEx(hMemDC, 40, 1040, NULL);
	LineTo(hMemDC, 40, 1040);
	DeleteObject(hPenWhitedot);

	//
	hPenWhitedotbig = choosePenColor(0, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 150, 340, NULL);
	LineTo(hMemDC, 150, 340);

	MoveToEx(hMemDC, 430, 260, NULL);
	LineTo(hMemDC, 430, 260);

	MoveToEx(hMemDC, 200, 200, NULL);
	LineTo(hMemDC, 200, 200);

	MoveToEx(hMemDC, 500, 130, NULL);
	LineTo(hMemDC, 500, 130);

	MoveToEx(hMemDC, 700, 120, NULL);
	LineTo(hMemDC, 700, 120);

	//Reverse

	MoveToEx(hMemDC, 150, 740, NULL);
	LineTo(hMemDC, 150, 740);

	MoveToEx(hMemDC, 430, 820, NULL);
	LineTo(hMemDC, 430, 820);

	MoveToEx(hMemDC, 200, 880, NULL);
	LineTo(hMemDC, 200, 880);

	MoveToEx(hMemDC, 500, 950, NULL);
	LineTo(hMemDC, 500, 950);

	MoveToEx(hMemDC, 700, 960, NULL);
	LineTo(hMemDC, 700, 960);
	DeleteObject(hPenWhitedotbig);
/********Right side Lines*******************************************************************************/ 

	

	//
	hPenWhitedot = choosePenColor(0, 12);
	SelectObject(hMemDC, hPenWhitedot);

	MoveToEx(hMemDC, 1420, 350, NULL);
	LineTo(hMemDC, 1420, 350);

	MoveToEx(hMemDC, 1840, 350, NULL);
	LineTo(hMemDC, 1840, 350);

	MoveToEx(hMemDC, 1810, 280, NULL);
	LineTo(hMemDC, 1810, 280);

	MoveToEx(hMemDC, 1890, 230, NULL);
	LineTo(hMemDC, 1890, 230);

	MoveToEx(hMemDC, 1570, 250, NULL);
	LineTo(hMemDC, 1570, 250);

	MoveToEx(hMemDC, 1670, 180, NULL);
	LineTo(hMemDC, 1670, 180);
	MoveToEx(hMemDC, 1350, 250, NULL);
	LineTo(hMemDC, 1350, 250);

	MoveToEx(hMemDC, 1870, 120, NULL);
	LineTo(hMemDC, 1870, 120);

	MoveToEx(hMemDC, 1770, 120, NULL);
	LineTo(hMemDC, 1770, 120);

	MoveToEx(hMemDC, 1320, 80, NULL);
	LineTo(hMemDC, 1320, 80);

	MoveToEx(hMemDC, 1880, 40, NULL);
	LineTo(hMemDC, 1880, 40);

	//Reverse
	MoveToEx(hMemDC, 1420, 730, NULL);
	LineTo(hMemDC, 1420, 730);

	MoveToEx(hMemDC, 1840, 730, NULL);
	LineTo(hMemDC, 1840, 730);

	MoveToEx(hMemDC, 1810, 800, NULL);
	LineTo(hMemDC, 1810, 800);

	MoveToEx(hMemDC, 1890, 850, NULL);
	LineTo(hMemDC, 1890, 850);

	MoveToEx(hMemDC, 1570, 830, NULL);
	LineTo(hMemDC, 1570, 830);

	MoveToEx(hMemDC, 1670, 900, NULL);
	LineTo(hMemDC, 1670, 900);
	MoveToEx(hMemDC, 1350, 830, NULL);
	LineTo(hMemDC, 1350, 830);

	MoveToEx(hMemDC, 1870, 960, NULL);
	LineTo(hMemDC, 1870, 960);

	MoveToEx(hMemDC, 1770, 960, NULL);
	LineTo(hMemDC, 1770, 960);

	MoveToEx(hMemDC, 1320, 1000, NULL);
	LineTo(hMemDC, 1320, 1000);

	MoveToEx(hMemDC, 1880, 1040, NULL);
	LineTo(hMemDC, 1880, 1040);
	DeleteObject(hPenWhitedot);

	//
	hPenWhitedotbig = choosePenColor(0, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1770, 340, NULL);
	LineTo(hMemDC, 1770, 340);

	MoveToEx(hMemDC, 1490, 260, NULL);
	LineTo(hMemDC, 1490, 260);

	MoveToEx(hMemDC, 1720, 200, NULL);
	LineTo(hMemDC, 1720, 200);

	MoveToEx(hMemDC, 1420, 130, NULL);
	LineTo(hMemDC, 1420, 130);

	MoveToEx(hMemDC, 1220, 120, NULL);
	LineTo(hMemDC, 1220, 120);

	//Reverse

	MoveToEx(hMemDC, 1770, 740, NULL);
	LineTo(hMemDC, 1770, 740);

	MoveToEx(hMemDC, 1490, 820, NULL);
	LineTo(hMemDC, 1490, 820);

	MoveToEx(hMemDC, 1720, 880, NULL);
	LineTo(hMemDC, 1720, 880);

	MoveToEx(hMemDC, 1420, 950, NULL);
	LineTo(hMemDC, 1420, 950);

	MoveToEx(hMemDC, 1220, 960, NULL);
	LineTo(hMemDC, 1220, 960);

	
	DeleteObject(hPenWhitedotbig);
	
}

void linesBackground2(void)
{

	HPEN hPenWhiteline;
	HPEN hPenWhitedot;
	HPEN hPenWhitedotbig;
	//

	hPenWhiteline = choosePenColor(0, 4);
	SelectObject(hMemDC, hPenWhiteline);

	MoveToEx(hMemDC, 0, 400, NULL);
	LineTo(hMemDC, 250, 400);
	MoveToEx(hMemDC, 250, 400, NULL);
	LineTo(hMemDC, 300, 350);
	MoveToEx(hMemDC, 300, 350, NULL);
	LineTo(hMemDC, 500, 350);

	MoveToEx(hMemDC, 0, 300, NULL);
	LineTo(hMemDC, 80, 300);
	MoveToEx(hMemDC, 80, 300, NULL);
	LineTo(hMemDC, 80, 350);

	MoveToEx(hMemDC, 0, 280, NULL);
	LineTo(hMemDC, 110, 280);

	MoveToEx(hMemDC, 150, 340, NULL);
	LineTo(hMemDC, 200, 300);
	MoveToEx(hMemDC, 200, 300, NULL);
	LineTo(hMemDC, 380, 300);
	MoveToEx(hMemDC, 380, 300, NULL);
	LineTo(hMemDC, 430, 260);

	MoveToEx(hMemDC, 30, 230, NULL);
	LineTo(hMemDC, 100, 230);
	MoveToEx(hMemDC, 100, 230, NULL);
	LineTo(hMemDC, 100, 250);
	MoveToEx(hMemDC, 100, 250, NULL);
	LineTo(hMemDC, 350, 250);

	MoveToEx(hMemDC, 0, 170, NULL);
	LineTo(hMemDC, 70, 170);
	MoveToEx(hMemDC, 70, 170, NULL);
	LineTo(hMemDC, 90, 200);
	MoveToEx(hMemDC, 90, 200, NULL);
	LineTo(hMemDC, 200, 200);

	MoveToEx(hMemDC, 250, 180, NULL);
	LineTo(hMemDC, 460, 180);
	MoveToEx(hMemDC, 460, 180, NULL);
	LineTo(hMemDC, 500, 250);
	MoveToEx(hMemDC, 500, 250, NULL);
	LineTo(hMemDC, 570, 250);

	MoveToEx(hMemDC, 0, 80, NULL);
	LineTo(hMemDC, 200, 80);
	MoveToEx(hMemDC, 200, 80, NULL);
	LineTo(hMemDC, 250, 130);
	MoveToEx(hMemDC, 250, 130, NULL);
	LineTo(hMemDC, 500, 130);

	MoveToEx(hMemDC, 50, 120, NULL);
	LineTo(hMemDC, 150, 120);

	MoveToEx(hMemDC, 300, 0, NULL);
	LineTo(hMemDC, 300, 80);
	MoveToEx(hMemDC, 300, 80, NULL);
	LineTo(hMemDC, 600, 80);

	MoveToEx(hMemDC, 40, 40, NULL);
	LineTo(hMemDC, 200, 40);
	MoveToEx(hMemDC, 200, 0, NULL);
	LineTo(hMemDC, 200, 40);

	MoveToEx(hMemDC, 500, 0, NULL);
	LineTo(hMemDC, 500, 50);
	MoveToEx(hMemDC, 500, 50, NULL);
	LineTo(hMemDC, 700, 50);
	MoveToEx(hMemDC, 700, 50, NULL);
	LineTo(hMemDC, 700, 120);

	//Reverse

	MoveToEx(hMemDC, 0, 680, NULL);
	LineTo(hMemDC, 250, 680);
	MoveToEx(hMemDC, 250, 680, NULL);
	LineTo(hMemDC, 300, 730);
	MoveToEx(hMemDC, 300, 730, NULL);
	LineTo(hMemDC, 500, 730);

	MoveToEx(hMemDC, 0, 780, NULL);
	LineTo(hMemDC, 80, 780);
	MoveToEx(hMemDC, 80, 780, NULL);
	LineTo(hMemDC, 80, 730);

	MoveToEx(hMemDC, 0, 800, NULL);
	LineTo(hMemDC, 110, 800);

	MoveToEx(hMemDC, 150, 740, NULL);
	LineTo(hMemDC, 200, 780);
	MoveToEx(hMemDC, 200, 780, NULL);
	LineTo(hMemDC, 380, 780);
	MoveToEx(hMemDC, 380, 780, NULL);
	LineTo(hMemDC, 430, 820);

	MoveToEx(hMemDC, 30, 850, NULL);
	LineTo(hMemDC, 100, 850);
	MoveToEx(hMemDC, 100, 850, NULL);
	LineTo(hMemDC, 100, 830);
	MoveToEx(hMemDC, 100, 830, NULL);
	LineTo(hMemDC, 350, 830);

	MoveToEx(hMemDC, 0, 908, NULL);
	LineTo(hMemDC, 70, 908);
	MoveToEx(hMemDC, 70, 908, NULL);
	LineTo(hMemDC, 90, 880);
	MoveToEx(hMemDC, 90, 880, NULL);
	LineTo(hMemDC, 200, 880);

	MoveToEx(hMemDC, 250, 900, NULL);
	LineTo(hMemDC, 460, 900);
	MoveToEx(hMemDC, 460, 900, NULL);
	LineTo(hMemDC, 500, 830);
	MoveToEx(hMemDC, 500, 830, NULL);
	LineTo(hMemDC, 570, 830);

	MoveToEx(hMemDC, 0, 1000, NULL);
	LineTo(hMemDC, 200, 1000);
	MoveToEx(hMemDC, 200, 1000, NULL);
	LineTo(hMemDC, 250, 950);
	MoveToEx(hMemDC, 250, 950, NULL);
	LineTo(hMemDC, 500, 950);

	MoveToEx(hMemDC, 50, 960, NULL);
	LineTo(hMemDC, 150, 960);

	MoveToEx(hMemDC, 300, 1080, NULL);
	LineTo(hMemDC, 300, 1000);
	MoveToEx(hMemDC, 300, 1000, NULL);
	LineTo(hMemDC, 600, 1000);

	MoveToEx(hMemDC, 40, 1040, NULL);
	LineTo(hMemDC, 200, 1040);
	MoveToEx(hMemDC, 200, 1080, NULL);
	LineTo(hMemDC, 200, 1040);

	MoveToEx(hMemDC, 500, 1080, NULL);
	LineTo(hMemDC, 500, 1030);
	MoveToEx(hMemDC, 500, 1030, NULL);
	LineTo(hMemDC, 700, 1030);
	MoveToEx(hMemDC, 700, 1030, NULL);
	LineTo(hMemDC, 700, 960);

	DeleteObject(hPenWhiteline);
	

	// Dots 4,9,10,6,8
	hPenWhitedot = choosePenColor(4, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 500, 350, NULL);
	LineTo(hMemDC, 500, 350);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(9, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 80, 350, NULL);
	LineTo(hMemDC, 80, 350);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(10, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 110, 280, NULL);
	LineTo(hMemDC, 110, 280);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(6, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 30, 230, NULL);
	LineTo(hMemDC, 30, 230);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(8, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 350, 250, NULL);
	LineTo(hMemDC, 350, 250);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(9, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 250, 180, NULL);
	LineTo(hMemDC, 250, 180);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(8, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 570, 250, NULL);
	LineTo(hMemDC, 570, 250);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(10, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 50, 120, NULL);
	LineTo(hMemDC, 50, 120);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(4, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 150, 120, NULL);
	LineTo(hMemDC, 150, 120);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(6, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 600, 80, NULL);
	LineTo(hMemDC, 600, 80);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(9, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 40, 40, NULL);
	LineTo(hMemDC, 40, 40);
	DeleteObject(hPenWhitedot);

	//Reverse
	hPenWhitedot = choosePenColor(4, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 500, 730, NULL);
	LineTo(hMemDC, 500, 730);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(6, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 80, 730, NULL);
	LineTo(hMemDC, 80, 730);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(10, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 110, 800, NULL);
	LineTo(hMemDC, 110, 800);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(8, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 30, 850, NULL);
	LineTo(hMemDC, 30, 850);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(6, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 350, 830, NULL);
	LineTo(hMemDC, 350, 830);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(10, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 250, 900, NULL);
	LineTo(hMemDC, 250, 900);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(4, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 570, 830, NULL);
	LineTo(hMemDC, 570, 830);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(9, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 50, 960, NULL);
	LineTo(hMemDC, 50, 960);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(8, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 150, 960, NULL);
	LineTo(hMemDC, 150, 960);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(6, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 600, 1000, NULL);
	LineTo(hMemDC, 600, 1000);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(10, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 40, 1040, NULL);
	LineTo(hMemDC, 40, 1040);
	DeleteObject(hPenWhitedot);

	//
	hPenWhitedotbig = choosePenColor(9, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 150, 340, NULL);
	LineTo(hMemDC, 150, 340);
	DeleteObject(hPenWhitedotbig);

	hPenWhitedotbig = choosePenColor(6, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 430, 260, NULL);
	LineTo(hMemDC, 430, 260);
	DeleteObject(hPenWhitedotbig);

	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 200, 200, NULL);
	LineTo(hMemDC, 200, 200);
	DeleteObject(hPenWhitedotbig);

	hPenWhitedotbig = choosePenColor(10, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 500, 130, NULL);
	LineTo(hMemDC, 500, 130);
	DeleteObject(hPenWhitedotbig);

	hPenWhitedotbig = choosePenColor(4, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 700, 120, NULL);
	LineTo(hMemDC, 700, 120);
	DeleteObject(hPenWhitedotbig);

	//Reverse
	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 150, 740, NULL);
	LineTo(hMemDC, 150, 740);
	DeleteObject(hPenWhitedotbig);

	hPenWhitedotbig = choosePenColor(10, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 430, 820, NULL);
	LineTo(hMemDC, 430, 820);
	DeleteObject(hPenWhitedotbig);

	hPenWhitedotbig = choosePenColor(6, 15);
	SelectObject(hMemDC, hPenWhitedotbig); 
	MoveToEx(hMemDC, 200, 880, NULL);
	LineTo(hMemDC, 200, 880);
	DeleteObject(hPenWhitedotbig);

	hPenWhitedotbig = choosePenColor(9, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 500, 950, NULL);
	LineTo(hMemDC, 500, 950);
	DeleteObject(hPenWhitedotbig);

	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 700, 960, NULL);
	LineTo(hMemDC, 700, 960);
	DeleteObject(hPenWhitedotbig);

	/********Right side Lines*******************************************************************************/
	hPenWhiteline = choosePenColor(0, 4);
	SelectObject(hMemDC, hPenWhiteline);

	MoveToEx(hMemDC, 1920, 400, NULL);
	LineTo(hMemDC, 1670, 400);
	MoveToEx(hMemDC, 1670, 400, NULL);
	LineTo(hMemDC, 1620, 350);
	MoveToEx(hMemDC, 1620, 350, NULL);
	LineTo(hMemDC, 1420, 350);

	MoveToEx(hMemDC, 1920, 300, NULL);
	LineTo(hMemDC, 1840, 300);
	MoveToEx(hMemDC, 1840, 300, NULL);
	LineTo(hMemDC, 1840, 350);

	MoveToEx(hMemDC, 1920, 280, NULL);
	LineTo(hMemDC, 1810, 280);

	MoveToEx(hMemDC, 1770, 340, NULL);
	LineTo(hMemDC, 1720, 300);
	MoveToEx(hMemDC, 1720, 300, NULL);
	LineTo(hMemDC, 1540, 300);
	MoveToEx(hMemDC, 1540, 300, NULL);
	LineTo(hMemDC, 1490, 260);

	MoveToEx(hMemDC, 1890, 230, NULL);
	LineTo(hMemDC, 1820, 230);
	MoveToEx(hMemDC, 1820, 230, NULL);
	LineTo(hMemDC, 1820, 250);
	MoveToEx(hMemDC, 1820, 250, NULL);
	LineTo(hMemDC, 1570, 250);

	MoveToEx(hMemDC, 1920, 170, NULL);
	LineTo(hMemDC, 1850, 170);
	MoveToEx(hMemDC, 1850, 170, NULL);
	LineTo(hMemDC, 1830, 200);
	MoveToEx(hMemDC, 1830, 200, NULL);
	LineTo(hMemDC, 1720, 200);

	MoveToEx(hMemDC, 1670, 180, NULL);
	LineTo(hMemDC, 1460, 180);
	MoveToEx(hMemDC, 1460, 180, NULL);
	LineTo(hMemDC, 1420, 250);
	MoveToEx(hMemDC, 1420, 250, NULL);
	LineTo(hMemDC, 1350, 250);

	MoveToEx(hMemDC, 1920, 80, NULL);
	LineTo(hMemDC, 1720, 80);
	MoveToEx(hMemDC, 1720, 80, NULL);
	LineTo(hMemDC, 1670, 130);
	MoveToEx(hMemDC, 1670, 130, NULL);
	LineTo(hMemDC, 1420, 130);

	MoveToEx(hMemDC, 1870, 120, NULL);
	LineTo(hMemDC, 1770, 120);

	MoveToEx(hMemDC, 1620, 0, NULL);
	LineTo(hMemDC, 1620, 80);
	MoveToEx(hMemDC, 1620, 80, NULL);
	LineTo(hMemDC, 1320, 80);

	MoveToEx(hMemDC, 1880, 40, NULL);
	LineTo(hMemDC, 1720, 40);
	MoveToEx(hMemDC, 1720, 0, NULL);
	LineTo(hMemDC, 1720, 40);

	MoveToEx(hMemDC, 1420, 0, NULL);
	LineTo(hMemDC, 1420, 50);
	MoveToEx(hMemDC, 1420, 50, NULL);
	LineTo(hMemDC, 1220, 50);
	MoveToEx(hMemDC, 1220, 50, NULL);
	LineTo(hMemDC, 1220, 120);

	//Reverse

	MoveToEx(hMemDC, 1920, 680, NULL);
	LineTo(hMemDC, 1670, 680);
	MoveToEx(hMemDC, 1670, 680, NULL);
	LineTo(hMemDC, 1620, 730);
	MoveToEx(hMemDC, 1620, 730, NULL);
	LineTo(hMemDC, 1420, 730);

	MoveToEx(hMemDC, 1920, 780, NULL);
	LineTo(hMemDC, 1840, 780);
	MoveToEx(hMemDC, 1840, 780, NULL);
	LineTo(hMemDC, 1840, 730);

	MoveToEx(hMemDC, 1920, 800, NULL);
	LineTo(hMemDC, 1810, 800);

	MoveToEx(hMemDC, 1770, 740, NULL);
	LineTo(hMemDC, 1720, 780);
	MoveToEx(hMemDC, 1720, 780, NULL);
	LineTo(hMemDC, 1540, 780);
	MoveToEx(hMemDC, 1540, 780, NULL);
	LineTo(hMemDC, 1490, 820);

	MoveToEx(hMemDC, 1890, 850, NULL);
	LineTo(hMemDC, 1820, 850);
	MoveToEx(hMemDC, 1820, 850, NULL);
	LineTo(hMemDC, 1820, 830);
	MoveToEx(hMemDC, 1820, 830, NULL);
	LineTo(hMemDC, 1570, 830);

	MoveToEx(hMemDC, 1920, 908, NULL);
	LineTo(hMemDC, 1850, 908);
	MoveToEx(hMemDC, 1850, 908, NULL);
	LineTo(hMemDC, 1830, 880);
	MoveToEx(hMemDC, 1830, 880, NULL);
	LineTo(hMemDC, 1720, 880);

	MoveToEx(hMemDC, 1670, 900, NULL);
	LineTo(hMemDC, 1460, 900);
	MoveToEx(hMemDC, 1460, 900, NULL);
	LineTo(hMemDC, 1420, 830);
	MoveToEx(hMemDC, 1420, 830, NULL);
	LineTo(hMemDC, 1350, 830);

	MoveToEx(hMemDC, 1920, 1000, NULL);
	LineTo(hMemDC, 1720, 1000);
	MoveToEx(hMemDC, 1720, 1000, NULL);
	LineTo(hMemDC, 1670, 950);
	MoveToEx(hMemDC, 1670, 950, NULL);
	LineTo(hMemDC, 1420, 950);

	MoveToEx(hMemDC, 1870, 960, NULL);
	LineTo(hMemDC, 1770, 960);

	MoveToEx(hMemDC, 1620, 1080, NULL);
	LineTo(hMemDC, 1620, 1000);
	MoveToEx(hMemDC, 1620, 1000, NULL);
	LineTo(hMemDC, 1320, 1000);

	MoveToEx(hMemDC, 1880, 1040, NULL);
	LineTo(hMemDC, 1720, 1040);
	MoveToEx(hMemDC, 1720, 1080, NULL);
	LineTo(hMemDC, 1720, 1040);

	MoveToEx(hMemDC, 1420, 1080, NULL);
	LineTo(hMemDC, 1420, 1030);
	MoveToEx(hMemDC, 1420, 1030, NULL);
	LineTo(hMemDC, 1220, 1030);
	MoveToEx(hMemDC, 1220, 1030, NULL);
	LineTo(hMemDC, 1220, 960);
	DeleteObject(hPenWhiteline);

	//

	hPenWhitedot = choosePenColor(4, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1420, 350, NULL);
	LineTo(hMemDC, 1420, 350);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(6, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1840, 350, NULL);
	LineTo(hMemDC, 1840, 350);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1810, 280, NULL);
	LineTo(hMemDC, 1810, 280);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(10, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1890, 230, NULL);
	LineTo(hMemDC, 1890, 230);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(9, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1570, 250, NULL);
	LineTo(hMemDC, 1570, 250);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(6, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1670, 180, NULL);
	LineTo(hMemDC, 1670, 180);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(10, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1350, 250, NULL);
	LineTo(hMemDC, 1350, 250);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1870, 120, NULL);
	LineTo(hMemDC, 1870, 120);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(4, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1770, 120, NULL);
	LineTo(hMemDC, 1770, 120);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1320, 80, NULL);
	LineTo(hMemDC, 1320, 80);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(9, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1880, 40, NULL);
	LineTo(hMemDC, 1880, 40);
	DeleteObject(hPenWhitedot);

	//Reverse

	hPenWhitedot = choosePenColor(4, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1420, 730, NULL);
	LineTo(hMemDC, 1420, 730);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1840, 730, NULL);
	LineTo(hMemDC, 1840, 730);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(10, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1810, 800, NULL);
	LineTo(hMemDC, 1810, 800);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(6, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1890, 850, NULL);
	LineTo(hMemDC, 1890, 850);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(9, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1570, 830, NULL);
	LineTo(hMemDC, 1570, 830);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(10, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1670, 900, NULL);
	LineTo(hMemDC, 1670, 900);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(9, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1350, 830, NULL);
	LineTo(hMemDC, 1350, 830);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(4, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1870, 960, NULL);
	LineTo(hMemDC, 1870, 960);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1770, 960, NULL);
	LineTo(hMemDC, 1770, 960);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(6, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1320, 1000, NULL);
	LineTo(hMemDC, 1320, 1000);
	DeleteObject(hPenWhitedot);

	hPenWhitedot = choosePenColor(9, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1880, 1040, NULL);
	LineTo(hMemDC, 1880, 1040);
	DeleteObject(hPenWhitedot);

	//
	hPenWhitedotbig = choosePenColor(10, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1770, 340, NULL);
	LineTo(hMemDC, 1770, 340);
	DeleteObject(hPenWhitedotbig);

	hPenWhitedotbig = choosePenColor(6, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1490, 260, NULL);
	LineTo(hMemDC, 1490, 260);
	DeleteObject(hPenWhitedotbig);

	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1720, 200, NULL);
	LineTo(hMemDC, 1720, 200);
	DeleteObject(hPenWhitedotbig);

	hPenWhitedotbig = choosePenColor(4, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1420, 130, NULL);
	LineTo(hMemDC, 1420, 130);
	DeleteObject(hPenWhitedotbig);

	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1220, 120, NULL);
	LineTo(hMemDC, 1220, 120);
	DeleteObject(hPenWhitedotbig);

	//Reverse
	hPenWhitedotbig = choosePenColor(9, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1770, 740, NULL);
	LineTo(hMemDC, 1770, 740);
	DeleteObject(hPenWhitedotbig);

	hPenWhitedotbig = choosePenColor(4, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1490, 820, NULL);
	LineTo(hMemDC, 1490, 820);
	DeleteObject(hPenWhitedotbig);

	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1720, 880, NULL);
	LineTo(hMemDC, 1720, 880);
	DeleteObject(hPenWhitedotbig);

	hPenWhitedotbig = choosePenColor(6, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1420, 950, NULL);
	LineTo(hMemDC, 1420, 950);
	DeleteObject(hPenWhitedotbig);

	hPenWhitedotbig = choosePenColor(10, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1220, 960, NULL);
	LineTo(hMemDC, 1220, 960);
	DeleteObject(hPenWhitedotbig);
}

void dMMovingLine(HDC fhdc, HGDIOBJ hgdiObj, int xinitVal, int yinitVal, int radius)
{
	SelectObject(fhdc, hgdiObj);
	int x = 0;
	int y = 0;
	float radians = M_PI / 180.f;

	static float i = 0.0f;
	static float j = 45.0f;
	static float k = 90.0f;
	static float l = 135.0f;
	static float m = 180.0f;
	static float n = 225.0f;
	static float o = 270.0f;
	static float p = 315.0f;
	static float q = 360.0f;

	if (i < 360.0f)
	{
		x = radius * cos(i * radians) + xinitVal;
		y = radius * sin(i * radians) + yinitVal;

		MoveToEx(fhdc, xinitVal, yinitVal, NULL);
		LineTo(fhdc, x, y);
		i += 4;
		if (i >= 360.0f)
		{
			i = 0.0f;
		}
	}

	if (j < 360.0f)
	{
		x = radius * cos(j * radians) + xinitVal;

		y = radius * sin(j * radians) + yinitVal;
		MoveToEx(fhdc, xinitVal, yinitVal, NULL);
		LineTo(fhdc, x, y);
		j += 4;
		if (j >= 360.0f)
		{
			j = 0.0f;
		}
	}

	if (k < 360.0f)
	{
		x = radius * cos(k * radians) + xinitVal;

		y = radius * sin(k * radians) + yinitVal;
		MoveToEx(fhdc, xinitVal, yinitVal, NULL);
		LineTo(fhdc, x, y);
		k += 4;
		if (k >= 360.0f)
		{
			k = 0.0f;
		}
	}

	if (l < 360.0f)
	{
		x = radius * cos(l * radians) + xinitVal;

		y = radius * sin(l * radians) + yinitVal;
		MoveToEx(fhdc, xinitVal, yinitVal, NULL);
		LineTo(fhdc, x, y);
		l += 4;
		if (l >= 360.0f)
		{
			l = 0.0f;
		}
	}

	if (m < 360.0f)
	{
		x = radius * cos(m * radians) + xinitVal;

		y = radius * sin(m * radians) + yinitVal;
		MoveToEx(fhdc, xinitVal, yinitVal, NULL);
		LineTo(fhdc, x, y);
		m += 4;
		if (m >= 360.0f)
		{
			m = 0.0f;
		}
	}

	if (n < 360.0f)
	{
		x = radius * cos(n * radians) + xinitVal;

		y = radius * sin(n * radians) + yinitVal;
		MoveToEx(fhdc, xinitVal, yinitVal, NULL);
		LineTo(fhdc, x, y);
		n += 4;
		if (n >= 360.0f)
		{
			n = 0.0f;
		}
	}

	if (o < 360.0f)
	{
		x = radius * cos(o * radians) + xinitVal;

		y = radius * sin(o * radians) + yinitVal;
		MoveToEx(fhdc, xinitVal, yinitVal, NULL);
		LineTo(fhdc, x, y);
		o += 4;
		if (o >= 360.0f)
		{
			o = 0.0f;
		}
	}

	if (p < 360.0f)
	{
		x = radius * cos(p * radians) + xinitVal;

		y = radius * sin(p * radians) + yinitVal;
		MoveToEx(fhdc, xinitVal, yinitVal, NULL);
		LineTo(fhdc, x, y);
		p += 4;
		if (p >= 360.0f)
		{
			p = 0.0f;
		}
	}

	if (q < 360.0f)
	{
		x = radius * cos(q * radians) + xinitVal;

		y = radius * sin(q * radians) + yinitVal;
		MoveToEx(fhdc, xinitVal, yinitVal, NULL);
		LineTo(fhdc, x, y);
		q += 4;
		if (q >= 360.0f)
		{
			q = 0.0f;
		}
	}
	/*HPEN hPen = choosePenColor(0, 5);
	hPen = choosePenColor(3, 15);
	SelectObject(fhdc, hPen);
	dLine(hMemDC, hPen, xz + 300, 300, xz + 300 + x, 200 + y);
	dLine(hMemDC, hPen, xz + 300, 300, xz + 230, 230);

	dLine(hMemDC, hPen, xz + 300, 300, xz + 200, 300);
	dLine(hMemDC, hPen, xz + 300, 300, xz + 230, 370);

	dLine(hMemDC, hPen, xz + 300, 300, xz + 300, 400);
	dLine(hMemDC, hPen, xz + 300, 300, xz + 370, 370);

	dLine(hMemDC, hPen, xz + 300, 300, xz + 400, 300);
	dLine(hMemDC, hPen, xz + 300, 300, xz + 370, 230);
	DeleteObject(hPen);*/


	DeleteObject(hgdiObj);
}

void dCircle(HDC fhdc, HGDIOBJ hgdiObj, int xVal, int yVal, int radius)
{
	SelectObject(fhdc, hgdiObj);
	int x = 0;
	int y = 0;
	float radians = M_PI / 180.f;
	for (int i = 0; i < 360; i++)
	{
		x = radius * cos(i * radians) + xVal;
		y = radius * sin(i * radians) + yVal;

		MoveToEx(fhdc, x, y, NULL);
		LineTo(fhdc, x, y);
	}


	DeleteObject(hgdiObj);
}

void refPoints(void)
{
	HPEN hPenRed;
	hPenRed = choosePenColor(2, 15);
	SelectObject(hMemDC, hPenRed);
	MoveToEx(hMemDC, 0, 100, NULL);
	LineTo(hMemDC, 0, 100);

	MoveToEx(hMemDC, 0, 200, NULL);
	LineTo(hMemDC, 0, 200);

	MoveToEx(hMemDC, 0, 300, NULL);
	LineTo(hMemDC, 0, 300);

	MoveToEx(hMemDC, 0, 400, NULL);
	LineTo(hMemDC, 0, 400);

	MoveToEx(hMemDC, 0, 500, NULL);
	LineTo(hMemDC, 0, 500);

	MoveToEx(hMemDC, 0, 600, NULL);
	LineTo(hMemDC, 0, 600);

	MoveToEx(hMemDC, 0, 700, NULL);
	LineTo(hMemDC, 0, 700);

	MoveToEx(hMemDC, 0, 800, NULL);
	LineTo(hMemDC, 0, 800);

	MoveToEx(hMemDC, 0, 900, NULL);
	LineTo(hMemDC, 0, 900);

	MoveToEx(hMemDC, 0, 1000, NULL);
	LineTo(hMemDC, 0, 1000);
	/************************************************************************/
	MoveToEx(hMemDC, 100, 0, NULL);
	LineTo(hMemDC, 100, 0);

	MoveToEx(hMemDC, 200, 0, NULL);
	LineTo(hMemDC, 200, 0);

	MoveToEx(hMemDC, 300, 0, NULL);
	LineTo(hMemDC, 300, 0);

	MoveToEx(hMemDC, 400, 0, NULL);
	LineTo(hMemDC, 400, 0);

	MoveToEx(hMemDC, 500, 0, NULL);
	LineTo(hMemDC, 500, 0);

	MoveToEx(hMemDC, 600, 0, NULL);
	LineTo(hMemDC, 600, 0);

	MoveToEx(hMemDC, 700, 0, NULL);
	LineTo(hMemDC, 700, 0);

	MoveToEx(hMemDC, 800, 0, NULL);
	LineTo(hMemDC, 800, 0);

	MoveToEx(hMemDC, 900, 0, NULL);
	LineTo(hMemDC, 900, 0);

	MoveToEx(hMemDC, 1000, 0, NULL);
	LineTo(hMemDC, 1000, 0);

	MoveToEx(hMemDC, 1100, 0, NULL);
	LineTo(hMemDC, 1100, 0);

	MoveToEx(hMemDC, 1200, 0, NULL);
	LineTo(hMemDC, 1200, 0);

	MoveToEx(hMemDC, 1300, 0, NULL);
	LineTo(hMemDC, 1300, 0);

	MoveToEx(hMemDC, 1400, 0, NULL);
	LineTo(hMemDC, 1400, 0);

	MoveToEx(hMemDC, 1500, 0, NULL);
	LineTo(hMemDC, 1500, 0);

	MoveToEx(hMemDC, 1600, 0, NULL);
	LineTo(hMemDC, 1600, 0);

	MoveToEx(hMemDC, 1700, 0, NULL);
	LineTo(hMemDC, 1700, 0);

	MoveToEx(hMemDC, 1800, 0, NULL);
	LineTo(hMemDC, 1800, 0);

	MoveToEx(hMemDC, 1900, 0, NULL);
	LineTo(hMemDC, 1900, 0);

	DeleteObject(hPenRed);
}

void uninitialize(void)
{
	
	if (ghwnd)
	{
		DestroyWindow(ghwnd);
		ghwnd = NULL;
	}

	if (gpFile)
	{
		fprintf(gpFile, "Log File Successfully Closed.\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}
