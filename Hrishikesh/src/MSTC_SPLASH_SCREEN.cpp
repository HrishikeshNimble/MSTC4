// 
// ############# MSTC GROUP PROJECT SPLASH SCREEN Drwaing  ##########//

#include <windows.h>
#include <stdio.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "..\include\Splash_Screen.h"
#include "..\include\global.h"
#include "..\include\hvnGlobal.h"
// libpath 
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "Winmm.lib")

#define TIMER_ID 8
#define TIMER_ID9 9
#define TIMER_ID1 1
#define TIMER_ID2 2
#define TIMER_ID3 3
#define TIMER_ID4 4
#define TIMER_ID5 5
#define TIMER_ID6 6
#define TIMER_ID7 7
#define INCREMENT 10
#define NUM_POINTS 8


HPEN choosePenColor(int, BRUSH_SIZE);
void ToggleFullScreen(void);
void uninitialize(void);
void display(void);
/******************************************/
void refPoints(void);
void linesBackground(void);
void linesBackground2(void);
void sceneOne(void);
void sceneTwo(void);
void sceneThree(void);
void sceneFour(void);
void sceneFive(void);
void sceneSix(void);
void sceneSeven(void);
void mpreProcessor(HBRUSH);
void xIncreRenderPoints(HPEN, int, int, int,int*);
void xDecreRenderPoints(HPEN, int, int, int, int*);
void yDecreRenderPoints(HPEN, int, int, int, int*);
void finalRenderPoints(HPEN, int, int, int, int*);
/********************************************/
HWND ghwnd = NULL;
HDC ghdc = NULL;
BOOL gbFullScreen = FALSE;
int* apt = NULL;
int dmax = 0;
int* rightPoints = NULL;
int* botPoints = NULL;
WPARAM gwParam;
int* circleApt = NULL;
int temp1, temp2;
int gi = 0;
int j = 0;
int k = 0;
HBITMAP hBitmap = NULL;
HDC hMemDC = NULL;
int gcxScreen, gcyScreen;
int sceneCounter = 1;
int pointsCounter = 1;
FILE* gpFile = NULL;
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

HDC hdc;
PAINTSTRUCT ps;
HBITMAP hBitmap4 = NULL;
RenderPoints renderPoints_struct[8];
RenderPoints xdrenderPoints_struct[8];
RenderPoints ydrenderPoints_struct[4];
RenderPoints frenderPoints_struct[22];
RenderPoints ffrenderPoints_struct[3];

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
	SetTimer(hwnd, TIMER_ID1, 4000, NULL);
	SetTimer(hwnd, TIMER_ID2, 8000, NULL);
	SetTimer(hwnd, TIMER_ID3, 12000, NULL);
	SetTimer(hwnd, TIMER_ID4, 16000, NULL);
	SetTimer(hwnd, TIMER_ID5, 20000, NULL);
	SetTimer(hwnd, TIMER_ID6, 24000, NULL);
	SetTimer(hwnd, TIMER_ID7, 35000, NULL);
	//SetTimer(hwnd, TIMER_ID9, 24000, NULL);

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
	
	HPEN HLinePen;
	HBRUSH HNewBrush;
	HFONT HSplashScreenFont;
	HFONT HOldFont;

	static HBITMAP hbmap;
	HGDIOBJ prevHGDIObj = NULL;
	BITMAP bmBuffer;
	RECT rc;
	
	static int rectWidth = 0;
	static int rectHeight = 400;
	/*POINT apt[5] = { 100, 100, 
					   200, 100, 
					   200, 200, 
					   100, 200, 
					   100, 100 };*/

    COLORREF color;
	RECT movingRect;
	TEXTMETRIC tm; 
 	int xAccel;
    int yAccel;
	int pointIndex;
	RECT rect;
	double point_distance;

	
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
		 if (wParam == TIMER_ID1)
		 {
			 sceneCounter++;
			 // KillTimer(ghwnd, TIMER_ID1);
		 }

		 if (wParam == TIMER_ID2)
		 {
			 sceneCounter++;
			 KillTimer(ghwnd, TIMER_ID1);
		 }
		 if (wParam == TIMER_ID3)
		 {
			 sceneCounter++;
			 KillTimer(ghwnd, TIMER_ID2);
			

		 }
		 if (wParam == TIMER_ID4)
		 {
			 sceneCounter++;
			 KillTimer(ghwnd, TIMER_ID3);

		 }
		 if (wParam == TIMER_ID5)
		 {
			 sceneCounter++;
			 KillTimer(ghwnd, TIMER_ID4);
			 
		 }
		 if (wParam == TIMER_ID6)
		 {
			 sceneCounter++;
			 KillTimer(ghwnd, TIMER_ID5);
		 }
		 if (wParam == TIMER_ID7)
		 {
			 //sceneCounter++;
			 if (sceneCounter >= 7)
			 {
				 sceneCounter = 7;
			 }
			 KillTimer(ghwnd, TIMER_ID6);
			 
		 }
		/* if (wParam == TIMER_ID9)
		 {
			 sceneCounter = 8;
			 KillTimer(ghwnd, TIMER_ID7);
			 if (sceneCounter > 8)
			 {
				 sceneCounter = 8;
				 KillTimer(ghwnd, TIMER_ID9);
			 }
		 }*/

		
		 InvalidateRect(hwnd, NULL, FALSE);

		/*if (wParam == TIMER_ID) {
			
			 if (sceneCounter == 2)
			 {
				
			 }
			 if (sceneCounter == 3)
			 {
				 KillTimer(ghwnd, TIMER_ID2);
				 
			 }
			 if (sceneCounter == 4)
			 {
				 KillTimer(ghwnd, TIMER_ID3);
			 }
			 if (sceneCounter == 5)
			 {
				 KillTimer(ghwnd, TIMER_ID4);
			 }
			 if (sceneCounter == 6)
			 {
				 KillTimer(ghwnd, TIMER_ID5);
			 }
			 
			 InvalidateRect(hwnd, NULL, FALSE);
			 
		 }*/
		 //if (wParam == TIMER_ID) {
			// InvalidateRect(hwnd, NULL, FALSE);

			// if (wParam == TIMER_ID1) {
			//	 SetTimer(hwnd, TIMER_ID2, 4000, NULL);
			//	 sceneCounter = 2;
			//	 InvalidateRect(hwnd, NULL, FALSE);
			// }
			// else if (wParam == TIMER_ID2) {
			//	 SetTimer(hwnd, TIMER_ID3, 4000, NULL);
			//	 KillTimer(ghwnd, TIMER_ID1);
			//	 sceneCounter = 3;
			//	 InvalidateRect(hwnd, NULL, FALSE);
			// }
			// else if (wParam == TIMER_ID3) {
			//	 SetTimer(hwnd, TIMER_ID4, 4000, NULL);
			//	 KillTimer(ghwnd, TIMER_ID2);
			//	 sceneCounter = 4;
			//	 InvalidateRect(hwnd, NULL, FALSE);
			// }
			// else if (wParam == TIMER_ID4) {
			//	 SetTimer(hwnd, TIMER_ID5, 4000, NULL);
			//	 KillTimer(ghwnd, TIMER_ID3);
			//	 sceneCounter = 5;
			//	 InvalidateRect(hwnd, NULL, FALSE);
			// }
			// else if (wParam == TIMER_ID5) {
			//	 SetTimer(hwnd, TIMER_ID6, 4000, NULL);
			//	 KillTimer(ghwnd, TIMER_ID4);
			//	 sceneCounter = 6;
			//	 InvalidateRect(hwnd, NULL, FALSE);
			// }
			// else if (wParam == TIMER_ID6) {
			//	 SetTimer(hwnd, TIMER_ID7, 4000, NULL);
			//	 KillTimer(ghwnd, TIMER_ID5);
			//	 sceneCounter = 7;

			//	 InvalidateRect(hwnd, NULL, FALSE);
			// }
			// else if (wParam == TIMER_ID7) {
			//	 //SetTimer(hwnd, TIMER_ID1, 4000, NULL);
			//	 if (sceneCounter >= 7)
			//	 {

			//		 sceneCounter = 7;
			//		 KillTimer(ghwnd, TIMER_ID6);
			//		 //KillTimer(ghwnd, TIMER_ID);
			//		 KillTimer(ghwnd, TIMER_ID7);
			//	 }
			//	 //sceneCounter++;
			//	 InvalidateRect(hwnd, NULL, FALSE);
			// }
		 //}
		 //
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

	/*renderPoints_struct[0].initialVal = 0;
	renderPoints_struct[0].finalVal = 100;
	renderPoints_struct[0].initPoints = 0;
	renderPoints_struct[0].renderSpeed = increment;

	renderPoints_struct[1].initialVal = 100;
	renderPoints_struct[1].finalVal = 200;
	renderPoints_struct[1].initPoints = 100;
	renderPoints_struct[1].renderSpeed = increment;

	renderPoints_struct[2].initialVal = 200;
	renderPoints_struct[2].finalVal = 300;
	renderPoints_struct[2].initPoints = 200;
	renderPoints_struct[2].renderSpeed = increment;

	renderPoints_struct[3].initialVal = 300;
	renderPoints_struct[3].finalVal = 400;
	renderPoints_struct[3].initPoints = 300;
	renderPoints_struct[3].renderSpeed = increment;

	renderPoints_struct[4].initialVal = 400;
	renderPoints_struct[4].finalVal = 500;
	renderPoints_struct[4].initPoints = 400;
	renderPoints_struct[4].renderSpeed = increment;

	renderPoints_struct[5].initialVal = 500;
	renderPoints_struct[5].finalVal = 600;
	renderPoints_struct[5].initPoints = 500;
	renderPoints_struct[5].renderSpeed = increment;

	renderPoints_struct[6].initialVal = 600;
	renderPoints_struct[6].finalVal = 700;
	renderPoints_struct[6].initPoints = 600;
	renderPoints_struct[6].renderSpeed = increment;

	renderPoints_struct[7].initialVal = 700;
	renderPoints_struct[7].finalVal = 800;
	renderPoints_struct[7].initPoints = 700;
	renderPoints_struct[7].renderSpeed = increment;*/

	//X-Decrementing Points
	for (int i = 0; i < 8; i++)
	{
		xdrenderPoints_struct[i].initialVal = 1920 - (i * 100);
		xdrenderPoints_struct[i].finalVal = 1820 - (i * 100);
		xdrenderPoints_struct[i].initPoints = 1920 - (i * 100);
		xdrenderPoints_struct[i].renderSpeed = increment;
	}

	//xdrenderPoints_struct[0].initialVal = 1920;
	//xdrenderPoints_struct[0].finalVal = 1820;
	//xdrenderPoints_struct[0].initPoints = 1920;
	//xdrenderPoints_struct[0].renderSpeed = increment;

	//xdrenderPoints_struct[1].initialVal = 1820;
	//xdrenderPoints_struct[1].finalVal = 1720;
	//xdrenderPoints_struct[1].initPoints = 1820;
	//xdrenderPoints_struct[1].renderSpeed = increment;

	//xdrenderPoints_struct[2].initialVal = 1720;
	//xdrenderPoints_struct[2].finalVal = 1620;
	//xdrenderPoints_struct[2].initPoints = 1720;
	//xdrenderPoints_struct[2].renderSpeed = increment;

	//xdrenderPoints_struct[3].initialVal = 1620;
	//xdrenderPoints_struct[3].finalVal = 1520;
	//xdrenderPoints_struct[3].initPoints = 1620;
	//xdrenderPoints_struct[3].renderSpeed = increment;

	//xdrenderPoints_struct[4].initialVal = 1520;
	//xdrenderPoints_struct[4].finalVal = 1420;
	//xdrenderPoints_struct[4].initPoints = 1520;
	//xdrenderPoints_struct[4].renderSpeed = increment;

	//xdrenderPoints_struct[5].initialVal = 1420;
	//xdrenderPoints_struct[5].finalVal = 1320;
	//xdrenderPoints_struct[5].initPoints = 1420;
	//xdrenderPoints_struct[5].renderSpeed = increment;

	//xdrenderPoints_struct[6].initialVal = 1320;
	//xdrenderPoints_struct[6].finalVal = 1220;
	//xdrenderPoints_struct[6].initPoints = 1320;
	//xdrenderPoints_struct[6].renderSpeed = increment;

	//xdrenderPoints_struct[7].initialVal = 1220;
	//xdrenderPoints_struct[7].finalVal = 1120;
	//xdrenderPoints_struct[7].initPoints = 1220;
	//xdrenderPoints_struct[7].renderSpeed = increment;

	// Y-Decrementing Points
	for (int i = 0; i < 4; i++)
	{
		ydrenderPoints_struct[i].initialVal = (i * 100) + 680;
		ydrenderPoints_struct[i].finalVal = (i * 100) + 780;
		ydrenderPoints_struct[i].initPoints = (i * 100) + 680;
		ydrenderPoints_struct[i].renderSpeed = increment;

	}

	/*ydrenderPoints_struct[0].initialVal = 680;
	ydrenderPoints_struct[0].finalVal = 780;
	ydrenderPoints_struct[0].initPoints = 680;
	ydrenderPoints_struct[0].renderSpeed = increment;
	
	ydrenderPoints_struct[1].initialVal = 780;
	ydrenderPoints_struct[1].finalVal = 880;
	ydrenderPoints_struct[1].initPoints = 780;
	ydrenderPoints_struct[1].renderSpeed = increment;
	
	ydrenderPoints_struct[2].initialVal = 880;
	ydrenderPoints_struct[2].finalVal = 980;
	ydrenderPoints_struct[2].initPoints = 880;
	ydrenderPoints_struct[2].renderSpeed = increment;
	
	ydrenderPoints_struct[3].initialVal = 980;
	ydrenderPoints_struct[3].finalVal = 1080;
	ydrenderPoints_struct[3].initPoints = 980;
	ydrenderPoints_struct[3].renderSpeed = increment;*/
	
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

	/*frenderPoints_struct[0].initialVal = 0;
	frenderPoints_struct[0].finalVal = 50;
	frenderPoints_struct[0].initPoints = 0;
	frenderPoints_struct[0].renderSpeed = increment;

	frenderPoints_struct[1].initialVal = 50;
	frenderPoints_struct[1].finalVal = 100;
	frenderPoints_struct[1].initPoints = 50;
	frenderPoints_struct[1].renderSpeed = increment;

	frenderPoints_struct[2].initialVal = 100;
	frenderPoints_struct[2].finalVal = 150;
	frenderPoints_struct[2].initPoints = 100;
	frenderPoints_struct[2].renderSpeed = increment;

	frenderPoints_struct[3].initialVal = 150;
	frenderPoints_struct[3].finalVal = 200;
	frenderPoints_struct[3].initPoints = 150;
	frenderPoints_struct[3].renderSpeed = increment;

	frenderPoints_struct[4].initialVal = 200;
	frenderPoints_struct[4].finalVal = 250;
	frenderPoints_struct[4].initPoints = 200;
	frenderPoints_struct[4].renderSpeed = increment;
	
	frenderPoints_struct[5].initialVal = 250;
	frenderPoints_struct[5].finalVal = 300;
	frenderPoints_struct[5].initPoints = 250;
	frenderPoints_struct[5].renderSpeed = increment;
	
	frenderPoints_struct[6].initialVal = 300;
	frenderPoints_struct[6].finalVal = 350;
	frenderPoints_struct[6].initPoints = 300;
	frenderPoints_struct[6].renderSpeed = increment;*/

	

}

void display(void)
{
	
	hdc = GetDC(ghwnd);
	hdc = BeginPaint(ghwnd, &ps);
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, gcxScreen, gcyScreen);
	HBITMAP hBitMDC = (HBITMAP)SelectObject(hMemDC, hBitmap);
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

		for (int i = 7; i < 10; i++)//7
		{
			finalRenderPoints(choosePenColor(4, 10), frenderPoints_struct[i].initialVal, frenderPoints_struct[i].finalVal, frenderPoints_struct[i].renderSpeed, &frenderPoints_struct[i].initPoints);
		}

		for (int i = 10; i < 13; i++)//3
		{
			finalRenderPoints(choosePenColor(8, 10), frenderPoints_struct[i].initialVal, frenderPoints_struct[i].finalVal, frenderPoints_struct[i].renderSpeed, &frenderPoints_struct[i].initPoints);
		}

		for (int i = 13; i < 16; i++)//3
		{
			finalRenderPoints(choosePenColor(10, 10), frenderPoints_struct[i].initialVal, frenderPoints_struct[i].finalVal, frenderPoints_struct[i].renderSpeed, &frenderPoints_struct[i].initPoints);
		}
		for (int i = 16; i < 19; i++)//9
		{
			finalRenderPoints(choosePenColor(6, 10), frenderPoints_struct[i].initialVal, frenderPoints_struct[i].finalVal, frenderPoints_struct[i].renderSpeed, &frenderPoints_struct[i].initPoints);
		}
		for (int i = 19; i < 22; i++)//9
		{
			finalRenderPoints(choosePenColor(8, 10), frenderPoints_struct[i].initialVal, frenderPoints_struct[i].finalVal, frenderPoints_struct[i].renderSpeed, &frenderPoints_struct[i].initPoints);
		}

		//static int desiredWidth4 = 400;
		//static int desiredHeight4 = 400;

		//BITMAP bitmap4;
		//GetObject(hBitmap4, sizeof(BITMAP), &bitmap4);

		//int xBitmap4 = (ps.rcPaint.right - desiredWidth4) / 2;

		////HDC hdcMem4 = CreateCompatibleDC(hdc);
		//SelectObject(hMemDC, hBitmap4);

		//StretchBlt(hdc, 1200, 620, desiredWidth4, desiredHeight4, hMemDC, 0, 0, bitmap4.bmWidth, bitmap4.bmHeight, SRCCOPY);
		//DeleteObject(hBitmap4);
		//DeleteDC(hMemDC);
	}
	
	//sceneOne();
	//sceneTwo();
	//sceneThree();
	//sceneFour();
	//sceneFive();
	//sceneSix();
	//sceneSeven();

	
	
	BitBlt(hdc, 0, 0, gcxScreen, gcyScreen, hMemDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, hBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	EndPaint(ghwnd, &ps);
	//ReleaseDC(ghwnd, hdc);
}

void sceneOne(void)
{
	HPEN hPenRed;
	POINT aptsub[8] = { 270, 450, 330, 390,
						1580, 390, 1640, 450,
						1580, 450, 1560, 430,
						350, 430, 330, 450 };
	POINT apt[8] = { 270, 630, 330, 690,
					 1580, 690, 1640, 630,
					 1580, 630, 1560, 650,
					 350, 650, 330, 630 };

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

	
	
	
	linesBackground();

	hPenRed = choosePenColor(5, 5);
	SelectObject(hMemDC, hPenRed);
	SetPolyFillMode(hMemDC, ALTERNATE);
	Polygon(hMemDC, aptplane, 10);
	Polygon(hMemDC, aptplane1, 6);
	Polygon(hMemDC, aptplane2, 6);
	hPenRed = choosePenColor(4, 5);
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
	
	


	linesBackground();
	HBRUSH orange = CreateSolidBrush(RGB(255, 165, 0));
	mpreProcessor(orange);
	DeleteObject(orange);

	HFONT hFont = CreateFont(70, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	//SetBkMode(hMemDC, TRANSPARENT);
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
	//FillRect(hMemDC, &rgn, orange);
	Polygon(hMemDC, FileI, 5);
	DeleteObject(hPenRed);

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
	linesBackground();
	hPenRed = choosePenColor(8, 5);

	HFONT hFont = CreateFont(70, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 830, 55, "Compiler", 8);
	//SelectObject(hMemDC, hFont);
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
	//SelectObject(hMemDC, hPenRed);
	DeleteObject(hPenRed);

	HFONT hFontAsm = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontAsm);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 920, 180, ".asm", 4);
	//SelectObject(hMemDC, hFontAsm);
	DeleteObject(hFontAsm);


	HFONT hFontS = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontS);
	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 942, 225, ".s", 2);
//	SelectObject(hMemDC, hFontS);
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

	linesBackground();
	mpreProcessor(orange);

	hPenRed = choosePenColor(0, 5);
	SelectObject(hMemDC, hPenRed);

	HFONT hFont = CreateFont(70, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	//SetBkMode(hMemDC, TRANSPARENT);
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

	linesBackground();
	mpreProcessor(orange);

	hPenRed = choosePenColor(0, 5);
	SelectObject(hMemDC, hPenRed);

	HFONT hFont = CreateFont(70, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	//SetBkMode(hMemDC, TRANSPARENT);
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

	HBRUSH orange = CreateSolidBrush(RGB(0, 191, 255));

	linesBackground();
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
	refPoints();
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

	

	//// position & size
	//int destX = 1200;
	//int destY = 450;
	//int destWidth = 200;
	//int destHeight = 200;
	//BITMAP bitmap4;
	//HDC hdcMem1 = CreateCompatibleDC(hdc); // Using double buffer hMemDC
	//HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem1, hBitmap4);
	//hBitmap4 = LoadBitmap((HINSTANCE)GetWindowLongPtr(ghwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(MY_WINDOW));

	//GetObject(hBitmap4, sizeof(BITMAP), &bitmap4);
	//SelectObject(hMemDC, hBitmap4);

	//// Draw the bitmap
	//StretchBlt(hMemDC, destX, destY, destWidth, destHeight,
	//	hdcMem1, 0, 0, bitmap4.bmWidth, bitmap4.bmHeight, SRCCOPY);

	//DeleteObject(hOldBitmap);
	//DeleteDC(hdcMem1);



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
		fprintf(gpFile, "xIncreRenderPoints() -> Render Points in Range to render.\n");
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
		fprintf(gpFile, "xDecreRenderPoints() -> Render Points in Range to render.\n");
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
		fprintf(gpFile, "yDecreRenderPoints() -> Render Points in Range to render.\n");
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
		fprintf(gpFile, "finalRenderPoints() -> Render Points in Range to render.\n");
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

//void gDataPoints(HPEN horzPoints, HPEN vertPoints)
//{
//	SelectObject(hMemDC, horzPoints);
//	static int dmax = 0;
//	static int currVal = 0;
//	int* aptl = NULL;
//	if (dmax < 100)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = dmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		dmax++;
//		if (dmax >= 100)
//		{
//			dmax = currVal;
//		}
//	}
//
//	static int twoDmax = 100;
//	static int twoCurrVal = 100;
//
//	if (twoDmax < 200)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = twoDmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		twoDmax++;
//		if (twoDmax >= 200)
//		{
//
//			twoDmax = twoCurrVal;
//		}
//	}
//
//	static int threeDmax = 200;
//	static int threeCurrVal = 200;
//
//	if (threeDmax < 300)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = threeDmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		threeDmax++;
//		if (threeDmax >= 300)
//		{
//			threeDmax = threeCurrVal;
//		}
//	}
//
//	static int FourDmax = 300;
//	static int FourCurrVal = 300;
//
//	if (FourDmax < 400)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = FourDmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		FourDmax++;
//		if (FourDmax >= 400)
//		{
//			FourDmax = FourCurrVal;
//		}
//	}
//
//	static int fiveDmax = 400;
//	static int fiveCurrVal = 400;
//
//	if (fiveDmax < 500)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = fiveDmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		fiveDmax++;
//		if (fiveDmax >= 500)
//		{
//			fiveDmax = fiveCurrVal;
//		}
//	}
//
//	static int sixDmax = 500;
//	static int sixCurrVal = 500;
//
//	if (sixDmax < 600)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = sixDmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		sixDmax++;
//		if (sixDmax >= 600)
//		{
//			sixDmax = sixCurrVal;
//		}
//	}
//
//	static int sevenDmax = 600;
//	static int sevenCurrVal = 600;
//
//	if (sevenDmax < 700)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = sevenDmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		sevenDmax++;
//		if (sevenDmax >= 700)
//		{
//			sevenDmax = sevenCurrVal;
//		}
//	}
//
//	static int eightDmax = 700;
//	static int eightCurrVal = 700;
//
//	if (eightDmax < 800)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = eightDmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		eightDmax++;
//		if (eightDmax >= 800)
//		{
//			eightDmax = eightCurrVal;
//		}
//	}
//
//	//Negative Points
//	static int NegDmax = 1920;
//	static int NegCurrVal = 1920;
//
//	if (NegDmax > 1820)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = NegDmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		NegDmax--;
//		if (NegDmax <= 1820)
//		{
//			NegDmax = NegCurrVal;
//		}
//	}
//
//	static int twoNegDmax = 1820;
//	static int twoNegCurrVal = 1820;
//
//	if (twoNegDmax > 1720)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = twoNegDmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		twoNegDmax--;
//		if (twoNegDmax <= 1720)
//		{
//			twoNegDmax = twoNegCurrVal;
//		}
//	}
//
//	static int threeNegDmax = 1720;
//	static int threeNegCurrVal = 1720;
//
//	if (threeNegDmax > 1620)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = threeNegDmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		threeNegDmax--;
//		if (threeNegDmax <= 1620)
//		{
//			threeNegDmax = threeNegCurrVal;
//		}
//
//	}
//
//	static int fourNegDmax = 1620;
//	static int fourNegCurrVal = 1620;
//
//	if (fourNegDmax > 1520)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = fourNegDmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		fourNegDmax--;
//		if (fourNegDmax <= 1520)
//		{
//			fourNegDmax = fourNegCurrVal;
//		}
//	}
//
//	static int fiveNegDmax = 1520;
//	static int fiveNegCurrVal = 1520;
//
//	if (fiveNegDmax > 1420)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = fiveNegDmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		fiveNegDmax--;
//		if (fiveNegDmax <= 1420)
//		{
//			fiveNegDmax = fiveNegCurrVal;
//		}
//	}
//
//	static int sixNegDmax = 1420;
//	static int sixNegCurrVal = 1420;
//
//	if (sixNegDmax > 1320)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = sixNegDmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		sixNegDmax--;
//		if (sixNegDmax <= 1320)
//		{
//			sixNegDmax = sixNegCurrVal;
//		}
//	}
//
//	static int sevenNegDmax = 1320;
//	static int sevenNegCurrVal = 1320;
//
//	if (sevenNegDmax > 1220)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = sevenNegDmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		sevenNegDmax--;
//		if (sevenNegDmax <= 1220)
//		{
//			sevenNegDmax = sevenNegCurrVal;
//		}
//	}
//
//	static int eightNegDmax = 1220;
//	static int eightNegCurrVal = 1220;
//
//	if (eightNegDmax > 1120)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = eightNegDmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		eightNegDmax--;
//		if (eightNegDmax <= 1120)
//		{
//			eightNegDmax = eightNegCurrVal;
//		}
//	}
//
//	//VertPoints
//	SelectObject(hMemDC, vertPoints);
//	static int xDmax = 680;
//	static int xCurrVal = 680;
//
//	if (xDmax < 780)
//	{
//		aptl = (int*)malloc(sizeof(int) * 11 * 2);
//		for (int j = 0; j < 11; j++)
//		{
//			aptl[(j * 2) + 0] = 810 + (j * 30);
//			aptl[(j * 2) + 1] = xDmax;
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		xDmax++;
//		if (xDmax >= 780)
//		{
//			xDmax = xCurrVal;
//		}
//	}
//
//	static int xtwoDmax = 780;
//	static int xtwoCurrVal = 780;
//
//	if (xtwoDmax < 880)
//	{
//		aptl = (int*)malloc(sizeof(int) * 11 * 2);
//		for (int j = 0; j < 11; j++)
//		{
//			aptl[(j * 2) + 0] = 810 + (j * 30);
//			aptl[(j * 2) + 1] = xtwoDmax;
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		xtwoDmax++;
//		if (xtwoDmax >= 880)
//		{
//			xtwoDmax = xtwoCurrVal;
//		}
//	}
//
//	static int xthreeDmax = 880;
//	static int xthreeCurrVal = 880;
//
//	if (xthreeDmax < 980)
//	{
//		aptl = (int*)malloc(sizeof(int) * 11 * 2);
//		for (int j = 0; j < 11; j++)
//		{
//			aptl[(j * 2) + 0] = 810 + (j * 30);
//			aptl[(j * 2) + 1] = xthreeDmax;
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		xthreeDmax++;
//		if (xthreeDmax >= 980)
//		{
//			xthreeDmax = xthreeCurrVal;
//		}
//	}
//
//	static int xfourDmax = 980;
//	static int xfourCurrVal = 980;
//
//	if (xfourDmax < 1080)
//	{
//		aptl = (int*)malloc(sizeof(int) * 11 * 2);
//		for (int j = 0; j < 11; j++)
//		{
//			aptl[(j * 2) + 0] = 810 + (j * 30);
//			aptl[(j * 2) + 1] = xfourDmax;
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//		}
//		free(aptl);
//		xfourDmax++;
//		if (xfourDmax >= 1080)
//		{
//			xfourDmax = xfourCurrVal;
//		}
//	}
//
//	/*if (twoDmax < 200)
//	{
//		aptl = (int*)malloc(sizeof(int) * NUM_POINTS * 2);
//		for (int j = 0; j < NUM_POINTS; j++)
//		{
//			aptl[(j * 2) + 0] = twoDmax;
//			aptl[(j * 2) + 1] = 435 + (j * 30);
//
//
//			MoveToEx(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1], NULL);
//			LineTo(hMemDC, aptl[(j * 2) + 0], aptl[(j * 2) + 1]);
//
//
//			llp = (j * 2) + 0;
//			llpp = (j * 2) + 1;
//			fprintf(gpFile, "apt[%d] = %d\n", llp, aptl[(j * 2) + 0]);
//			fprintf(gpFile, "apt[%d] = %d\n", llpp, aptl[(j * 2) + 1]);
//		}
//		free(aptl);
//		fprintf(gpFile, "dmax = %d\n", dmax);
//		InvalidateRect(ghwnd, NULL, NULL);
//		twoDmax++;
//		if (twoDmax >= 200)
//		{
//
//			twoDmax = twoCurrVal;
//			fprintf(gpFile, " Reset dmax = %d\n", dmax);
//		}
//	}*/
//}

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

void linesBackground(void)
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
	DeleteObject(hPenWhitedot);
	MoveToEx(hMemDC, 500, 350, NULL);
	LineTo(hMemDC, 500, 350);

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

void uninitialize(void)
{
	if (apt)
	{
		free(apt);
		apt = NULL;
	}
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
