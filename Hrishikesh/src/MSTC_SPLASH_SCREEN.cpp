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

#define TIMER_ID 1
#define TIMER_ID2 2
#define MAX_POSITION 780
#define INCREMENT 10
#define NUM_POINTS 8


HPEN choosePenColor(int, BRUSH_SIZE);
void hvnDrawLines(HPEN, int, int, int, int, POINT*, HWND);
int* setVerticesRect(int, int , int , int , int );
int* setPointParam(int, int, int, int, int);
void ToggleFullScreen(void);
void uninitialize(void);
void display(void);
void hvnDrawRect(HPEN, HWND);
int* setCirclePointsParam(int cRadius);

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
void mpreProcessor(HBRUSH);
void gDataPoints(void);
void dataPoints(void);
void dataPointsY(void);
void dataPointsNeg(int*, int);
/********************************************/
HWND ghwnd = NULL;
HDC ghdc = NULL;
BOOL gbFullScreen = FALSE;
int *apt = NULL;
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
int sceneCounter = -1;
FILE* gpFile = NULL;

int rectSpeed = 1;
//3
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) //ncmwindow show the window on how it should be shown e.g. maximized minimized or hidden etc.
{
	void initialize(void);

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
	
	ToggleFullScreen();

	//remove all window styles
	//SetWindowLong(hwnd,GWL_STYLE,0);
	//SetWindowPos(hwnd, HWND_TOP , 330, 180, 888, 550, SWP_FRAMECHANGED);
	//SetWindowPos(hwnd, HWND_TOP , 330, 180, 950, 650, SWP_FRAMECHANGED);
	initialize();


	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd); // VIMP
	SetTimer(hwnd, TIMER_ID, 20, NULL);
	SetTimer(hwnd, TIMER_ID2, 2000, NULL);

	// 9. Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}


// 11 a 
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

	ghwnd = hwnd;

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
			
        case WM_PAINT: 
			display();
		break;

     case WM_TIMER:
		 if (wParam == TIMER_ID) {
			 sceneCounter = 1;
		
			 InvalidateRect(hwnd, NULL, FALSE);
		 }
		 if (wParam == TIMER_ID2) {
			 KillTimer(ghwnd, TIMER_ID);
			 sceneCounter++;
			/* for (int i = 0; i < MAX_POSITION; i++)
			 {
				 for (int j = 0; j < NUM_POINTS; j++)
				 {
					 InvalidateRect(hwnd, NULL, FALSE);
				 }
			 }*/
			 InvalidateRect(hwnd, NULL, FALSE);
			 if (sceneCounter > 6)
			 {
				 KillTimer(ghwnd, TIMER_ID2);
			 }
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
		default:
			hLinePen=CreatePen(PS_SOLID, brushSize , orange);
			textColor=orange;	
			break;
	}
	return(hLinePen);
}

void hvnDrawRect(HPEN hPen, HWND hwnd)
{

	HDC hdc;
	HDC hMemDC;
	HBITMAP hBitmap;
	PAINTSTRUCT ps;
	RECT movingrect;
	HBRUSH rectBrush = CreateSolidBrush(RGB(255, 0 , 0));
	movingrect = { 100, 200, 100, 200 };
	GetClientRect(hwnd, &movingrect);
	hdc = GetDC(hwnd);
	hdc = BeginPaint(hwnd, &ps);
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, gcxScreen, gcyScreen);
	ghdc = hdc;
	SelectObject(hMemDC, hBitmap);
	ReleaseDC(hwnd, hdc);
	SelectObject(hMemDC, rectBrush);
	Rectangle(hMemDC, 50, 50, 380, 150);

	Rectangle(hMemDC, 50, 200, 380, 300);

	Rectangle(hMemDC, 50, 350, 380, 450);

	Rectangle(hMemDC, 50, 500, 380, 600);

	Rectangle(hMemDC, 50, 650, 380, 750);

	Rectangle(hMemDC, 500, 50, 830, 150);

	Rectangle(hMemDC, 500, 200, 830, 300);
					 			
	Rectangle(hMemDC, 500, 350, 830, 450);
					 			
	Rectangle(hMemDC, 500, 500, 830, 600);
					  			
	Rectangle(hMemDC, 500, 650, 830, 750);



	//FillRect(hMemDC, &movingrect, rectBrush);
	//BitBlt(hdc, 0, 0, cxClient, cyClient, hMemDC, 0, 0, SRCPAINT);
	//MoveToEx(hMemDC, xWidth, yHeight, pointRef);
	//LineTo(hMemDC, lineToWidth, lineToHeight);

	BitBlt(hdc, 0, 0, gcxScreen, gcyScreen, hMemDC, 0, 0, SRCCOPY);
	EndPaint(hwnd, &ps);
	DeleteObject(hPen);
	InvalidateRect(hwnd, NULL, NULL);
}

void hvnDrawLines(HPEN hLinePen, int xWidth, int yHeight, int lineToWidth, int lineToHeight, POINT* pointRef, HWND hwnd)
{

	HDC hdc;
	PAINTSTRUCT ps;

	hdc = GetDC(hwnd);
	hdc = BeginPaint(hwnd, &ps);
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, gcxScreen, gcyScreen);
	SelectObject(hMemDC, hBitmap);
	SelectObject(hMemDC, hLinePen);
	MoveToEx(hMemDC, xWidth, yHeight, pointRef);
	LineTo(hMemDC, lineToWidth, lineToHeight);
	
	EndPaint(hwnd, &ps);
	BitBlt(hdc, 0, 0, gcxScreen, gcyScreen, hMemDC, 0, 0, SRCCOPY);
	InvalidateRect(hwnd, NULL, NULL);
	DeleteObject(hLinePen);
	ReleaseDC(hwnd, hdc);
}

int* setVerticesRect(int N, int xValueOne, int xValueTwo, int yValueOne, int yValueTwo)
{
	int* apt = NULL;
	apt = (int*)malloc(sizeof(int) * N * 4);
	if (apt == NULL)
	{
		fprintf(gpFile, "setVerticesRect() -> Failed to malloc.\n");
	}
	else
	{
		fprintf(gpFile, "setVerticesRect() -> malloc Successfully.\n");
	}
	int i = 0;
	for (i = 0; i < N; i++)
	{
		apt[i] =  xValueOne;
		apt[i + 1] =  yValueOne;
			
		apt[i+2] = xValueTwo;
		apt[i+3] =  yValueOne;
			
		apt[i+4] =  xValueTwo;
		apt[i+5] =  yValueTwo;
			
		apt[i+6] =  xValueOne;
		apt[i+7] =  yValueTwo;

		apt[i+8] =  xValueOne;
		apt[i+9] =  yValueOne;

	}
	
		return(apt);
}

int* setPointParam( int choose, int N, int xValueOne, int yValueOne,int speed)
{
	int* apt = NULL;
	apt = (int*)malloc(sizeof(int) * 20);
	if (apt == NULL)
	{
		fprintf(gpFile, "setPointParam() -> Failed to malloc.\n");
	}
	else
	{
		fprintf(gpFile, "setPointParam() -> malloc Successfully.\n");
	}
	int i = 0;
	switch (choose)
	{
	case 1:
		for (i = 1; i < N; i++)
		{
			apt[i] = xValueOne + (i * speed);
			//apt[i * 2 + 1] = yValueOne;

			
		}
		break;
	case 2:
		for (i = 1; i < N; i++)
		{
			apt[i] = xValueOne - (i * speed);
			//apt[i * 2 + 1] = yValueOne;

			fprintf(gpFile, "setPointParam() -> apt[%d] = %d.\n", i , apt[i]);
		}
		break;
	}
	

	return(apt);
}

int* setCirclePointsParam(int cRadius)
{
	int* apt = NULL;
	apt = (int*)malloc(sizeof(int) * 361 * 2);
	int i;
	float angle_rad;
	for (i = 0; i <= 360; i++)
	{
		angle_rad = M_PI / 180 * i;
		apt[i * 2 + 0] = cos(angle_rad) * (cRadius);
		apt[i * 2 + 1] = sin(angle_rad) * (cRadius);

		fprintf(gpFile, "setPointParam() -> cos = apt[%d] = %d.\n", i * 2 + 0, apt[i * 2 + 0]);
		fprintf(gpFile, "setPointParam() -> sin = apt[%d] = %d.\n", i * 2 + 1, apt[i * 2 + 1]);
	}
	return(apt);
}

void initialize(void)
{
		apt = setPointParam(1, 20, 10, 435, INCREMENT);
		//rightPoints = setPointParam(2, 20, 1920, 435, INCREMENT);
	//circleApt = setCirclePointsParam(100);
}

void display(void)
{
	if (sceneCounter == 1)
	{
		sceneOne();
	}
	if (sceneCounter == 2)
	{
		sceneTwo();
	}
	if (sceneCounter == 3)
	{
		sceneThree();
	}
	if (sceneCounter == 4)
	{
		sceneFour();
	}
	if (sceneCounter == 5)
	{
		sceneFive();
	}
	if (sceneCounter == 6)
	{
		sceneSix();
	}
	//sceneOne();
	//sceneTwo();
	//sceneThree();
	//sceneFour();
	//sceneFive();
	//sceneSix();

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
	LineTo(hMemDC,200, 0);

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
	LineTo(hMemDC,800, 0);

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

	HDC hdc;
	PAINTSTRUCT ps;
	hdc = GetDC(ghwnd);
	hdc = BeginPaint(ghwnd, &ps);
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, gcxScreen, gcyScreen);
	SelectObject(hMemDC, hBitmap);
	
	
	linesBackground();

	hPenRed = choosePenColor(5, 5);
	SelectObject(hMemDC, hPenRed);
	//Rectangle(hMemDC, 320, 400, 1600, 680);
	//Rectangle(hMemDC, 400, 480, 1520, 580);

	SelectObject(hMemDC, hPenRed);
	SetPolyFillMode(hMemDC, ALTERNATE);
	//Polygon(hMemDC,aptsub, 8);
	//Polygon(hMemDC, apt, 8);
	Polygon(hMemDC, aptplane, 10);
	Polygon(hMemDC, aptplane1, 6);
	Polygon(hMemDC, aptplane2, 6);
	hPenRed = choosePenColor(4, 5);
	HFONT hFont = CreateFont(80, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	//SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 450, 500, "When Code Meets The Machine", 27);
	EndPaint(ghwnd, &ps);
	BitBlt(hdc, 0, 0, gcxScreen, gcyScreen, hMemDC, 0, 0, SRCCOPY);
	InvalidateRect(ghwnd, NULL, NULL);
	DeleteObject(hPenRed);
	ReleaseDC(ghwnd, hdc);

}

void sceneTwo(void)
{
	HPEN hPenRed;
	HPEN hLinePen;
	POINT scene2Poly [4] = { 800, 420, 1120, 420,
							 1120, 660, 800, 660};
	POINT FileI[5] = { 915, 170, 915, 270,
					   1005, 270, 1005, 180,
					   995, 170 };

	/*
	600, 840, 600, 940,
	690, 940, 690, 850,
	680, 840 };
*/
	
	
	HBRUSH orange = CreateSolidBrush(RGB(255, 165, 0));
	HBRUSH orangePoly = CreateSolidBrush(RGB(255, 165, 0));
	HDC hdc;
	PAINTSTRUCT ps;
	hdc = GetDC(ghwnd);
	hdc = BeginPaint(ghwnd, &ps);
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, gcxScreen, gcyScreen);
	SelectObject(hMemDC, hBitmap);
	linesBackground();
	//refPoints();

	hPenRed = choosePenColor(0, 5);
	SelectObject(hMemDC, hPenRed);
	//SelectObject(hMemDC, hPenRed);
	//SetPolyFillMode(hMemDC, WINDING);
	
	//Polygon(hMemDC, scene2Poly, 4);
	RECT rgn = { 630, 840, 720, 940 };
	//Rectangle(hMemDC, 800, 420, 1120, 660);
	//FillRect(hMemDC, &rgn, orange);
	//Polygon(hMemDC, upperRect, 4);

	mpreProcessor(orange);

	HFONT hFont = CreateFont(70, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	//SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 755, 55, "Pre-Processor", 13);
	
	HFONT hFont1 = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont1);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 576, 310, "Include Header Files & Expand Macros", 36);

	// .i File
	hPenRed = choosePenColor(4, 5);
	SelectObject(hMemDC, hPenRed);
	//FillRect(hMemDC, &rgn, orange);
	Polygon(hMemDC, FileI, 5);

	HFONT hFontII = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontII);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 940, 180, ".ii", 3);

	HFONT hFontI = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontI);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 940, 225, ".i", 2);

	//Arrows

	
	HPEN hPenArrows;
	//

	/*hPenArrows = choosePenColor(4, 5);
	SelectObject(hMemDC, hPenArrows);

	MoveToEx(hMemDC, 690, 890, NULL);
	LineTo(hMemDC, 750, 890);*/

	/*MoveToEx(hMemDC, 750, 890, NULL);
	LineTo(hMemDC, 730, 870);

	MoveToEx(hMemDC, 750, 890, NULL);
	LineTo(hMemDC, 730, 910);*/


	/*POINT triangleOrange[3] = { 750, 890, 740, 880,
								740, 900 };

	hPenRed = choosePenColor(4, 4);
	SelectObject(hMemDC, hPenRed);
	SelectObject(hMemDC, orangePoly);
	Polygon(hMemDC, triangleOrange, 3);
	DeleteObject(orangePoly);

	hPenRed = choosePenColor(4, 10);
	SelectObject(hMemDC, hPenRed);*/
	/*gDataPoints();
	dataPoints();
	dataPointsY();*/
	/*dataPoints(apt,465);
	dataPoints(apt,495);
	dataPoints(apt,525);
	dataPoints(apt,555);
	dataPoints(apt,585);
	dataPoints(apt,615);
	dataPoints(apt,645);*/

	/*dataPointsNeg(rightPoints, 435);
	dataPointsNeg(rightPoints, 465);
	dataPointsNeg(rightPoints, 495);
	dataPointsNeg(rightPoints, 525);
	dataPointsNeg(rightPoints, 555);
	dataPointsNeg(rightPoints, 585);
	dataPointsNeg(rightPoints, 615);
	dataPointsNeg(rightPoints, 645);*/
	//dataPoints(rightPoints, 100);
	
	EndPaint(ghwnd, &ps);
	BitBlt(hdc, 0, 0, gcxScreen, gcyScreen, hMemDC, 0, 0, SRCCOPY);
	InvalidateRect(ghwnd, NULL, NULL);
	DeleteObject(hPenRed);
	ReleaseDC(ghwnd, hdc);



}

void gDataPoints(void)
{
	HPEN hPenRed = choosePenColor(4, 10);
	SelectObject(hMemDC, hPenRed);
	int dmax = MAX_POSITION;
	int* apt = NULL;
	apt = (int*)malloc(sizeof(int) * dmax * NUM_POINTS);

	for (int i = 0; i < dmax; i++)
	{
		for (int j = 0; j < NUM_POINTS; j++)
		{
			apt[(i * NUM_POINTS) + j + 0] = i;
			apt[(i * NUM_POINTS) + j + 1] = 435 + (j*30);

			if (apt[i] < MAX_POSITION)
			{
				MoveToEx(hMemDC, apt[(i * NUM_POINTS) + j + 0], apt[(i * NUM_POINTS) + j + 1], NULL);
				LineTo(hMemDC, apt[(i * NUM_POINTS) + j + 0], apt[(i * NUM_POINTS) + j + 1]);
			}
			
		}
	}

	free(apt);
	apt = NULL;
}

void dataPoints(void)
{
	HPEN hPenRed = choosePenColor(4, 10);
	SelectObject(hMemDC, hPenRed);
	int dmax = MAX_POSITION;
	int xNeg = 1140;
	int* apt = NULL;
	apt = (int*)malloc(sizeof(int) * dmax * NUM_POINTS);

	for (int i = 0; i < dmax; i++)
	{
		for (int j = 0; j < NUM_POINTS; j++)
		{
			apt[(i * NUM_POINTS) + j + 0] = 1920 - i;
			apt[(i * NUM_POINTS) + j + 1] = 435 + (j * 30);

				MoveToEx(hMemDC, apt[(i * NUM_POINTS) + j + 0], apt[(i * NUM_POINTS) + j + 1], NULL);
				LineTo(hMemDC, apt[(i * NUM_POINTS) + j + 0], apt[(i * NUM_POINTS) + j + 1]);
		}
	}

	free(apt);
	apt = NULL;
}

void dataPointsY(void)
{

	HPEN hPenRed = choosePenColor(5, 10);
	SelectObject(hMemDC, hPenRed);
	int dmax = 400;
	int xNeg = 11;
	int* apt = NULL;
	apt = (int*)malloc(sizeof(int) * dmax * 11);

	for (int i = 0; i < dmax; i++)
	{
		for (int j = 0; j < xNeg; j++)
		{
			apt[(i * xNeg) + j + 0] = 810 + (j * 30);
			apt[(i * xNeg) + j + 1] = 680 + i;

			MoveToEx(hMemDC, apt[(i * xNeg) + j + 0], apt[(i * xNeg) + j + 1], NULL);
			LineTo(hMemDC, apt[(i * xNeg) + j + 0], apt[(i * xNeg) + j + 1]);
		}
	}

	free(apt);
	apt = NULL;

	//HPEN hPenRed = choosePenColor(4, 10);
	//SelectObject(hMemDC, hPenRed);
	//int j = 0;
	//if (j <= 500)
	//{
	//	for (int i = 0; i < NUM_POINTS; i++) {
	//		int x = apt[i];
	//		int y = yConst;
	//		MoveToEx(hMemDC, x, y, NULL);
	//		LineTo(hMemDC, x, y);
	//		// Increment point positions and reset if max is exceeded
	//		apt[i] += INCREMENT;
	//		if (apt[i] > MAX_POSITION) {
	//			apt[i] = i * INCREMENT;  // Reset to the initial position


	//		}
	//	}

	//	j++;
	//	if (j == 500)
	//	{
	//		fprintf(gpFile, "dataPoints() -> j = %d.\n", j);
	//		j = 500;
	//		for (int i = 0; i < NUM_POINTS; i++) {
	//			apt[i] = 0;
	//		}

	//	}
	//}

}

void dataPointsNeg(int*apt, int yConst)
{
	HPEN hPenRed = choosePenColor(4, 10);
	SelectObject(hMemDC, hPenRed);

	if (k <= 500)
	{
		for (int i = 0; i < NUM_POINTS; i++) {
			int x = apt[i];
			int y = yConst;
			MoveToEx(hMemDC, x, y, NULL);
			LineTo(hMemDC, x, y);
			// Increment point positions and reset if max is exceeded
			apt[i] -= INCREMENT;
			if (apt[i] < MAX_POSITION) {
				apt[i] = 1920;  // Reset to the initial position
			}
		}

		k++;
		if (k == 500)
		{
			fprintf(gpFile, "dataPoints() -> j = %d.\n", j);
			k = 500;
			for (int i = 0; i < NUM_POINTS; i++) {
				apt[i] = 0;
			}

		}
	}

}

void sceneThree(void)
{

	HPEN hPenRed;
	HPEN hLinePen;
	POINT scene2Poly[4] = { 800, 420, 1120, 420,
							 1120, 660, 800, 660 };
	POINT FileAsm[5] = { 905, 170, 905, 270,
					   995, 270, 995, 180,
					   985, 170 };

	/*
	600, 840, 600, 940,
	690, 940, 690, 850,
	680, 840 };
*/


	HBRUSH orange = CreateSolidBrush(RGB(2, 151, 255));
	HBRUSH orangePoly = CreateSolidBrush(RGB(2, 151, 255));
	HDC hdc;
	PAINTSTRUCT ps;
	hdc = GetDC(ghwnd);
	hdc = BeginPaint(ghwnd, &ps);
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, gcxScreen, gcyScreen);
	SelectObject(hMemDC, hBitmap);
	linesBackground();
	//refPoints();

	hPenRed = choosePenColor(8, 5);
	SelectObject(hMemDC, hPenRed);
	//SelectObject(hMemDC, hPenRed);
	//SetPolyFillMode(hMemDC, WINDING);

	//Polygon(hMemDC, scene2Poly, 4);
	RECT rgn = { 630, 840, 720, 940 };
	//Rectangle(hMemDC, 800, 420, 1120, 660);
	//FillRect(hMemDC, &rgn, orange);
	//Polygon(hMemDC, upperRect, 4);

	mpreProcessor(orange);

	HFONT hFont = CreateFont(70, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	//SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 820, 55, "Compiler", 8);

	HFONT hFont1 = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont1);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 706, 310, "Generate Assembly Code",22);

	// .asm File
	hPenRed = choosePenColor(8, 5);
	SelectObject(hMemDC, hPenRed);
	Polygon(hMemDC, FileAsm, 5);

	HFONT hFontAsm = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontAsm);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 910, 180, ".asm", 4);

	HFONT hFontS = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontS);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 940, 225, ".s", 2);


	EndPaint(ghwnd, &ps);
	BitBlt(hdc, 0, 0, gcxScreen, gcyScreen, hMemDC, 0, 0, SRCCOPY);
	InvalidateRect(ghwnd, NULL, NULL);
	DeleteObject(hPenRed);
	ReleaseDC(ghwnd, hdc);
	
}

void sceneFour(void)
{


	HPEN hPenRed;
	HPEN hLinePen;
	POINT scene2Poly[4] = { 800, 420, 1120, 420,
							 1120, 660, 800, 660 };
	POINT FileObj[5] = { 915, 170, 915, 270,
					   1005, 270, 1005, 180,
					   995, 170 };

	/*
	600, 840, 600, 940,
	690, 940, 690, 850,
	680, 840 };
*/


	HBRUSH orange = CreateSolidBrush(RGB(13, 190, 17));
	HBRUSH orangePoly = CreateSolidBrush(RGB(13, 190, 17));
	HDC hdc;
	PAINTSTRUCT ps;
	hdc = GetDC(ghwnd);
	hdc = BeginPaint(ghwnd, &ps);
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, gcxScreen, gcyScreen);
	SelectObject(hMemDC, hBitmap);
	linesBackground();
	//refPoints();

	hPenRed = choosePenColor(0, 5);
	SelectObject(hMemDC, hPenRed);
	//SelectObject(hMemDC, hPenRed);
	//SetPolyFillMode(hMemDC, WINDING);

	//Polygon(hMemDC, scene2Poly, 4);
	RECT rgn = { 630, 840, 720, 940 };
	//Rectangle(hMemDC, 800, 420, 1120, 660);
	//FillRect(hMemDC, &rgn, orange);
	//Polygon(hMemDC, upperRect, 4);

	mpreProcessor(orange);

	HFONT hFont = CreateFont(70, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	//SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(13, 190, 17));
	TextOut(hMemDC, 810, 55, "Assembler", 9);

	HFONT hFont1 = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont1);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(13, 190, 17));
	TextOut(hMemDC, 750, 310, "Generate Machine Code", 21);

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

	HFONT hFontO = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontO);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(13, 190, 17));
	TextOut(hMemDC, 945, 225, ".o", 2);

	EndPaint(ghwnd, &ps);
	BitBlt(hdc, 0, 0, gcxScreen, gcyScreen, hMemDC, 0, 0, SRCCOPY);
	InvalidateRect(ghwnd, NULL, NULL);
	DeleteObject(hPenRed);
	ReleaseDC(ghwnd, hdc);
}

void sceneFive(void)
{

	HPEN hPenRed;
	HPEN hLinePen;
	POINT scene2Poly[4] = { 800, 420, 1120, 420,
							 1120, 660, 800, 660 };
	POINT FileLib[5] = { 915, 170, 915, 270,
					   1005, 270, 1005, 180,
					   995, 170 };

	/*
	600, 840, 600, 940,
	690, 940, 690, 850,
	680, 840 };
*/


	HBRUSH orange = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH orangePoly = CreateSolidBrush(RGB(255, 0, 255));
	HDC hdc;
	PAINTSTRUCT ps;
	hdc = GetDC(ghwnd);
	hdc = BeginPaint(ghwnd, &ps);
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, gcxScreen, gcyScreen);
	SelectObject(hMemDC, hBitmap);
	linesBackground();
	//refPoints();

	hPenRed = choosePenColor(0, 5);
	SelectObject(hMemDC, hPenRed);

	//Polygon(hMemDC, scene2Poly, 4);
	RECT rgn = { 630, 840, 720, 940 };

	mpreProcessor(orange);



	HFONT hFont = CreateFont(70, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	//SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 0, 255));
	TextOut(hMemDC, 865, 55, "Linker", 6);

	HFONT hFont1 = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont1);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 0, 255));
	TextOut(hMemDC, 670, 310, "Linking Static Library .lib & .a", 32);

	// .i File
	hPenRed = choosePenColor(4, 5);
	SelectObject(hMemDC, hPenRed);
	//FillRect(hMemDC, &rgn, orange);
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
	TextOut(hMemDC, 940, 180, ".lib", 4);

	HFONT hFontA = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontA);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 0, 255));
	TextOut(hMemDC, 940, 225, ".a", 2);

	

	EndPaint(ghwnd, &ps);
	BitBlt(hdc, 0, 0, gcxScreen, gcyScreen, hMemDC, 0, 0, SRCCOPY);
	InvalidateRect(ghwnd, NULL, NULL);
	DeleteObject(hPenRed);
	ReleaseDC(ghwnd, hdc);
}

void sceneSix(void)
{


	HPEN hPenRed;
	HPEN hLinePen;
	POINT FileI[5] = { 350, 600, 350, 700,
					   440, 700, 440, 610,
					   430, 600 };

	/*
	600, 840, 600, 940,
	690, 940, 690, 850,
	680, 840 };
*/


	HBRUSH orange = CreateSolidBrush(RGB(255, 165, 0));
	HBRUSH orangePoly = CreateSolidBrush(RGB(255, 165, 0));
	HDC hdc;
	PAINTSTRUCT ps;
	hdc = GetDC(ghwnd);
	hdc = BeginPaint(ghwnd, &ps);
	hMemDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, gcxScreen, gcyScreen);
	SelectObject(hMemDC, hBitmap);
	linesBackground2();
	//refPoints();

	hPenRed = choosePenColor(0, 5);
	SelectObject(hMemDC, hPenRed);


	HFONT hFont = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFont);
	//SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 300, 450, "Pre-Processor", 13);


	// .i File
	hPenRed = choosePenColor(4, 5);
	SelectObject(hMemDC, hPenRed);
	//FillRect(hMemDC, &rgn, orange);
	Polygon(hMemDC, FileI, 5);

	HFONT hFontII = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontII);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 375, 610, ".ii", 3);

	HFONT hFontI = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontI);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 165, 0));
	TextOut(hMemDC, 375, 650, ".i", 2);

	//Compiler

	POINT FileAsm[5] = { 620, 600, 620, 700,
					   710, 700, 710, 610,
					   700, 600 };
	hPenRed = choosePenColor(8, 5);
	SelectObject(hMemDC, hPenRed);
	Polygon(hMemDC, FileAsm, 5);

	HFONT hFontAsm = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontAsm);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 625, 620, ".asm", 4);

	HFONT hFontS = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontS);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 625, 650, ".s", 2);

	hPenRed = choosePenColor(8, 5);
	SelectObject(hMemDC, hPenRed);

	HFONT hFontComp = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontComp);
	SetBkMode(hMemDC, OPAQUE);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(2, 151, 255));
	TextOut(hMemDC, 600, 450, "Compiler", 8);

	//Assembler
	POINT FileObj[5] = { 880, 600, 880, 700,
					   970, 700, 970, 610,
					   960, 600 };
	hPenRed = choosePenColor(10, 5);
	SelectObject(hMemDC, hPenRed);
	Polygon(hMemDC, FileObj, 5);

	HFONT hFontObj = CreateFont(38, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontObj);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(13, 190, 17));
	TextOut(hMemDC, 895, 615, ".obj", 4);

	HFONT hFontO = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontO);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(13, 190, 17));
	TextOut(hMemDC, 895, 645, ".o", 2);

	hPenRed = choosePenColor(0, 5);
	SelectObject(hMemDC, hPenRed);

	HFONT hFontAsmb = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontAsmb);
	SetBkMode(hMemDC, OPAQUE);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(13, 190, 17));
	TextOut(hMemDC, 850, 450, "Assembler", 9);


	//Linker
	POINT FileLib[5] = { 1125, 600, 1125, 700,
					   1215, 700, 1215, 610,
					   1205, 600 };
	hPenRed = choosePenColor(6, 5);
	SelectObject(hMemDC, hPenRed);
	Polygon(hMemDC, FileLib, 5);

	HFONT hFontLib = CreateFont(38, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontLib);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 0, 255));
	TextOut(hMemDC, 1145, 615, ".lib", 4);

	HFONT hFontA = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontA);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 0, 255));
	TextOut(hMemDC, 1145, 645, ".a", 2);
	

	hPenRed = choosePenColor(0, 5);
	SelectObject(hMemDC, hPenRed);

	HFONT hFontLink = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontLink);
	SetBkMode(hMemDC, OPAQUE);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(255, 0, 255));
	TextOut(hMemDC, 1125, 450, "Linker", 6);

	//Executable
	hPenRed = choosePenColor(8, 5);
	SelectObject(hMemDC, hPenRed);

	HFONT hFontExeFile = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontExeFile);
	SetBkMode(hMemDC, OPAQUE);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(0, 191, 255));
	TextOut(hMemDC, 1325, 450, "Executable", 10);


	//Executable
	POINT FileExe[5] = { 1360, 600, 1360, 700,
					  1450, 700, 1450, 610,
					   1440, 600 };

	hPenRed = choosePenColor(8, 5);
	SelectObject(hMemDC, hPenRed);
	Polygon(hMemDC, FileExe, 5);

	HFONT hFontExe = CreateFont(38, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hMemDC, hFontExe);
	SetBkMode(hMemDC, TRANSPARENT);
	SelectObject(hMemDC, hPenRed);
	SetTextColor(hMemDC, RGB(0, 191, 255));
	TextOut(hMemDC, 1374, 625, ".exe", 4);


	POINT triangleOrange[3] = { 750, 890, 730, 870,
								730, 910 };

	/*hPenRed = choosePenColor(4, 4);
	SelectObject(hMemDC, hPenRed);
	SelectObject(hMemDC, orangePoly);
	Polygon(hMemDC, triangleOrange, 3);
	DeleteObject(orangePoly);*/

	EndPaint(ghwnd, &ps);
	BitBlt(hdc, 0, 0, gcxScreen, gcyScreen, hMemDC, 0, 0, SRCCOPY);
	InvalidateRect(ghwnd, NULL, NULL);
	DeleteObject(hPenRed);
	ReleaseDC(ghwnd, hdc);
}

void mpreProcessor(HBRUSH colorBrush)
{
	HBRUSH orange = CreateSolidBrush(RGB(255, 165, 0));
	HPEN hLinePen;
	hLinePen = choosePenColor(0, 7);
	HPEN hPenRed;
	hPenRed = choosePenColor(0, 5);

	SelectObject(hMemDC, hPenRed);
	RECT rgn = { 800, 420, 1120, 660 };
	
	Rectangle(hMemDC, 800, 420, 1120, 660);
	FillRect(hMemDC, &rgn, colorBrush);

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

	DeleteObject(hPenRed);
	DeleteObject(hLinePen);
}

void linesBackground(void)
{

	HPEN hPenWhiteline;
	HPEN hPenWhitedot;
	HPEN hPenWhitedotbig;
	//
	
	hPenWhiteline = choosePenColor(0, 4);
	hPenWhitedot = choosePenColor(0, 12);
	hPenWhitedotbig = choosePenColor(0, 15);
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

	//
	
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

	//

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

/********Right side Lines*******************************************************************************/ 

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

	//

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

	//

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

	DeleteObject(hPenWhiteline);
	DeleteObject(hPenWhitedot);
	DeleteObject(hPenWhitedotbig);
	
}

void linesBackground2(void)
{

	HPEN hPenWhiteline;
	HPEN hPenWhitedot;
	HPEN hPenWhitedotbig;
	//

	hPenWhiteline = choosePenColor(0, 4);
	hPenWhitedot = choosePenColor(0, 12);
	hPenWhitedotbig = choosePenColor(0, 15);
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

	// Dots 4,9,10,6,8
	hPenWhitedot = choosePenColor(4, 12);
	SelectObject(hMemDC, hPenWhitedot);

	MoveToEx(hMemDC, 500, 350, NULL);
	LineTo(hMemDC, 500, 350);

	hPenWhitedot = choosePenColor(9, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 80, 350, NULL);
	LineTo(hMemDC, 80, 350);

	hPenWhitedot = choosePenColor(10, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 110, 280, NULL);
	LineTo(hMemDC, 110, 280);

	hPenWhitedot = choosePenColor(6, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 30, 230, NULL);
	LineTo(hMemDC, 30, 230);

	hPenWhitedot = choosePenColor(8, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 350, 250, NULL);
	LineTo(hMemDC, 350, 250);

	hPenWhitedot = choosePenColor(9, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 250, 180, NULL);
	LineTo(hMemDC, 250, 180);
	hPenWhitedot = choosePenColor(8, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 570, 250, NULL);
	LineTo(hMemDC, 570, 250);

	hPenWhitedot = choosePenColor(10, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 50, 120, NULL);
	LineTo(hMemDC, 50, 120);

	hPenWhitedot = choosePenColor(4, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 150, 120, NULL);
	LineTo(hMemDC, 150, 120);

	hPenWhitedot = choosePenColor(6, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 600, 80, NULL);
	LineTo(hMemDC, 600, 80);

	hPenWhitedot = choosePenColor(9, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 40, 40, NULL);
	LineTo(hMemDC, 40, 40);

	//Reverse
	hPenWhitedot = choosePenColor(4, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 500, 730, NULL);
	LineTo(hMemDC, 500, 730);

	hPenWhitedot = choosePenColor(6, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 80, 730, NULL);
	LineTo(hMemDC, 80, 730);

	hPenWhitedot = choosePenColor(10, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 110, 800, NULL);
	LineTo(hMemDC, 110, 800);

	hPenWhitedot = choosePenColor(8, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 30, 850, NULL);
	LineTo(hMemDC, 30, 850);

	hPenWhitedot = choosePenColor(6, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 350, 830, NULL);
	LineTo(hMemDC, 350, 830);

	hPenWhitedot = choosePenColor(10, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 250, 900, NULL);
	LineTo(hMemDC, 250, 900);

	hPenWhitedot = choosePenColor(4, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 570, 830, NULL);
	LineTo(hMemDC, 570, 830);

	hPenWhitedot = choosePenColor(9, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 50, 960, NULL);
	LineTo(hMemDC, 50, 960);

	hPenWhitedot = choosePenColor(8, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 150, 960, NULL);
	LineTo(hMemDC, 150, 960);

	hPenWhitedot = choosePenColor(6, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 600, 1000, NULL);
	LineTo(hMemDC, 600, 1000);

	hPenWhitedot = choosePenColor(10, 12);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 40, 1040, NULL);
	LineTo(hMemDC, 40, 1040);

	//
	hPenWhitedotbig = choosePenColor(9, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 150, 340, NULL);
	LineTo(hMemDC, 150, 340);

	hPenWhitedotbig = choosePenColor(6, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 430, 260, NULL);
	LineTo(hMemDC, 430, 260);

	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 200, 200, NULL);
	LineTo(hMemDC, 200, 200);

	hPenWhitedotbig = choosePenColor(10, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 500, 130, NULL);
	LineTo(hMemDC, 500, 130);

	hPenWhitedotbig = choosePenColor(4, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 700, 120, NULL);
	LineTo(hMemDC, 700, 120);

	//Reverse
	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 150, 740, NULL);
	LineTo(hMemDC, 150, 740);

	hPenWhitedotbig = choosePenColor(10, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 430, 820, NULL);
	LineTo(hMemDC, 430, 820);


	hPenWhitedotbig = choosePenColor(6, 15);
	SelectObject(hMemDC, hPenWhitedotbig); 
	MoveToEx(hMemDC, 200, 880, NULL);
	LineTo(hMemDC, 200, 880);

	hPenWhitedotbig = choosePenColor(9, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 500, 950, NULL);
	LineTo(hMemDC, 500, 950);

	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 700, 960, NULL);
	LineTo(hMemDC, 700, 960);

	/********Right side Lines*******************************************************************************/

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

	//

	hPenWhitedotbig = choosePenColor(4, 15);
	SelectObject(hMemDC, hPenWhitedot);

	MoveToEx(hMemDC, 1420, 350, NULL);
	LineTo(hMemDC, 1420, 350);

	hPenWhitedotbig = choosePenColor(6, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1840, 350, NULL);
	LineTo(hMemDC, 1840, 350);

	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1810, 280, NULL);
	LineTo(hMemDC, 1810, 280);

	hPenWhitedotbig = choosePenColor(10, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1890, 230, NULL);
	LineTo(hMemDC, 1890, 230);

	hPenWhitedotbig = choosePenColor(9, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1570, 250, NULL);
	LineTo(hMemDC, 1570, 250);

	hPenWhitedotbig = choosePenColor(6, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1670, 180, NULL);
	LineTo(hMemDC, 1670, 180);

	hPenWhitedotbig = choosePenColor(10, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1350, 250, NULL);
	LineTo(hMemDC, 1350, 250);

	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1870, 120, NULL);
	LineTo(hMemDC, 1870, 120);

	hPenWhitedotbig = choosePenColor(4, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1770, 120, NULL);
	LineTo(hMemDC, 1770, 120);

	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1320, 80, NULL);
	LineTo(hMemDC, 1320, 80);

	hPenWhitedotbig = choosePenColor(9, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1880, 40, NULL);
	LineTo(hMemDC, 1880, 40);

	//Reverse

	hPenWhitedotbig = choosePenColor(4, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1420, 730, NULL);
	LineTo(hMemDC, 1420, 730);

	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1840, 730, NULL);
	LineTo(hMemDC, 1840, 730);

	hPenWhitedotbig = choosePenColor(10, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1810, 800, NULL);
	LineTo(hMemDC, 1810, 800);

	hPenWhitedotbig = choosePenColor(6, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1890, 850, NULL);
	LineTo(hMemDC, 1890, 850);

	hPenWhitedotbig = choosePenColor(9, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1570, 830, NULL);
	LineTo(hMemDC, 1570, 830);

	hPenWhitedotbig = choosePenColor(10, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1670, 900, NULL);
	LineTo(hMemDC, 1670, 900);

	hPenWhitedotbig = choosePenColor(9, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1350, 830, NULL);
	LineTo(hMemDC, 1350, 830);

	hPenWhitedotbig = choosePenColor(4, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1870, 960, NULL);
	LineTo(hMemDC, 1870, 960);

	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1770, 960, NULL);
	LineTo(hMemDC, 1770, 960);

	hPenWhitedotbig = choosePenColor(6, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1320, 1000, NULL);
	LineTo(hMemDC, 1320, 1000);

	hPenWhitedotbig = choosePenColor(9, 15);
	SelectObject(hMemDC, hPenWhitedot);
	MoveToEx(hMemDC, 1880, 1040, NULL);
	LineTo(hMemDC, 1880, 1040);

	//
	hPenWhitedotbig = choosePenColor(10, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1770, 340, NULL);
	LineTo(hMemDC, 1770, 340);

	hPenWhitedotbig = choosePenColor(6, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1490, 260, NULL);
	LineTo(hMemDC, 1490, 260);

	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1720, 200, NULL);
	LineTo(hMemDC, 1720, 200);

	hPenWhitedotbig = choosePenColor(4, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1420, 130, NULL);
	LineTo(hMemDC, 1420, 130);

	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1220, 120, NULL);
	LineTo(hMemDC, 1220, 120);

	//Reverse
	hPenWhitedotbig = choosePenColor(9, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1770, 740, NULL);
	LineTo(hMemDC, 1770, 740);

	hPenWhitedotbig = choosePenColor(4, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1490, 820, NULL);
	LineTo(hMemDC, 1490, 820);

	hPenWhitedotbig = choosePenColor(8, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1720, 880, NULL);
	LineTo(hMemDC, 1720, 880);

	hPenWhitedotbig = choosePenColor(6, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1420, 950, NULL);
	LineTo(hMemDC, 1420, 950);

	hPenWhitedotbig = choosePenColor(10, 15);
	SelectObject(hMemDC, hPenWhitedotbig);
	MoveToEx(hMemDC, 1220, 960, NULL);
	LineTo(hMemDC, 1220, 960);

	DeleteObject(hPenWhiteline);
	DeleteObject(hPenWhitedot);
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
