// 
// ############# MSTC GROUP PROJECT SPLASH SCREEN Drawing  ##########//

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

COLORREF g_currentTextColor = RGB(255, 0, 0);
static int colorCycleCompleted = 0;  


//3
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) //ncmwindow show the window on how it should be shown e.g. maximized minimized or hidden etc.
{

    //My Addon
	
    pVec_Splash_Screen_outer=CreateVector();  //Create Point Vector
	
	GenerateCricleOffsets(pVec_Splash_Screen_outer,SPLASH_SCREEN_CIRCLE_RADIUS);  //fill the vector with circle co-ordinates

	//4. Data
	WNDCLASSEX wndclass; //  style
	HWND hwnd;	// Handle == Pointer to Window
	//MSG msg;
	MSG msg={};	//Current msg
	
	TCHAR szAppName[] = TEXT("MSTC"); // name of class 
    TCHAR szWindowCaption[] = TEXT("MSTC GROUP DEMO");

	//5. Code : Fill the struct 
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0; // additional
	wndclass.cbWndExtra = 0; // additional

	wndclass.lpfnWndProc = WndProc; // it actully funcptr
	wndclass.hInstance = hInstance; // 1st param

	//wndclass.hIcon = LoadIcon(NULL, IDI_QUESTION); // Custom icon for Taskbar
	//wndclass.hIconSm = LoadIcon(NULL, IDI_SHIELD); // minimize icon for window itself
	
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	 
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	wndclass.lpszClassName = szAppName; // Group Name ""
	wndclass.lpszMenuName = NULL; // used in project

	// 6
	RegisterClassEx(&wndclass);

	// 7  Create window and return its

	// play sound
	PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );

hwnd = CreateWindow(szAppName, // class style
        NULL,    //for Spalsh screen NO caption required
		WS_DLGFRAME,	   // Style of wnd
		CW_USEDEFAULT,				// x cord
		CW_USEDEFAULT,				// y cord
		CW_USEDEFAULT ,				// width
		CW_USEDEFAULT,				// custom height
		(HWND)NULL,                 // hWndParent
        (HMENU)NULL,				// hMenu
		hInstance,					// 1st 
		NULL);



	//remove all window styles
	SetWindowLong(hwnd,GWL_STYLE,0);
	//SetWindowPos(hwnd, HWND_TOP , 330, 180, 888, 550, SWP_FRAMECHANGED);
	SetWindowPos(hwnd, HWND_TOP , 330, 180, 950, 650, SWP_FRAMECHANGED);
	
	// 8  memset
	//ShowWindow(hwnd, nCmdShow);
	AnimateWindow(hwnd , 2000 , AW_CENTER);
	UpdateWindow(hwnd); // VIMP

	// 9. Message Loop
	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
		
	// 10
    DestroyVector(&pVec_Splash_Screen_outer); //Destroy Point Vector

	return((int)msg.wParam);
}


// 11 a 
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// 11 b
	void UpdateTextColor(void);
    
    static int cxClient, cyClient, cxChar, cyChar, cxMouse,cyMouse;
	static int SPLASH_SCREEN_BG_DRAW=0;
    static int SPALSH_SCREEN_COMPLETED=0;
	
	HDC hdc; 
	HDC hdcComp;
	HPEN HLinePen;
	HINSTANCE hInst;
	HPEN HOldPen;
	HBRUSH HNewBrush;
	HBRUSH HOldBrush;
	HFONT HSplashScreenFont;
	HFONT HOldFont;
	
	static HBITMAP hbmap;
	HGDIOBJ prevHGDIObj = NULL;
	BITMAP bmBuffer;
	RECT rc;
	
	
    COLORREF color;
	
	TEXTMETRIC tm; 
    PAINTSTRUCT ps; 
	int xAccel;
    int yAccel;
	int pointIndex;
	//RECT Cliet_Rect;
	double point_distance;
	
    switch (iMsg)
	{
		// very 1st Msg
	case WM_CREATE:
			hInst = (HINSTANCE)((LPCREATESTRUCT)lParam)->hInstance;
			hbmap = LoadBitmap(hInst, MAKEINTRESOURCE(MY_BITMAP));
			
	       	SetTimer(hwnd, 1,30, NULL); 
            hdc = GetDC(hwnd); 
            GetTextMetrics(hdc, &tm);
            cxChar = tm.tmAveCharWidth; 
            cyChar = tm.tmHeight + tm.tmExternalLeading; 
            //GetClientRect(hwnd, &Cliet_Rect);
			//SCREEN_X_SHIFT=(Cliet_Rect.right/2)-(564);
			//SCREEN_Y_SHIFT=(Cliet_Rect.bottom/2)-(393);
			
			ReleaseDC(hwnd, hdc); 
            hdc = NULL; 
    	break;

        case WM_SIZE: 
            cxClient = LOWORD(lParam); 
            cyClient = HIWORD(lParam); 
            CLIENT_XArea = cxClient;
            CLIENT_YArea = cyClient;
			
			//Maintaing Image offset to Keep drawing atthe center
		
			//SPLASH_SCREEN_X_SHIFT_INNER=(cxClient/2)-( 1228 + (1792-1228)/2);  //Images's rect's (max x ) right position was 312
			//SPLASH_SCREEN_Y_SHIFT_INNER=(cyClient/2)-(564/2) - 40;  //Images's rect's (max Y)  bottom position was 564

			
			SPLASH_SCREEN_X_SHIFT_INNER=(cxClient/2)-(564/2);  //Images's rect's (max x ) right position was 312
			SPLASH_SCREEN_Y_SHIFT_INNER=(cyClient/2)-(339/2) ;  //Images's rect's (max Y)  bottom position was 564
		
			//SPLASH_SCREEN_X_SHIFT_OUTER=(cxClient/2)-( 614 + (1178-614)/2);  //Images's rect's (max x ) right position was 312
			//SPLASH_SCREEN_Y_SHIFT_OUTER=(cyClient/2)-(614/2);  //Images's rect's (max Y)  bottom position was 564
			
			SPLASH_SCREEN_X_SHIFT_OUTER=(cxClient/2);  //Images's rect's (max x ) right position was 312
			SPLASH_SCREEN_Y_SHIFT_OUTER=(cyClient/2);  //Images's rect's (max Y)  bottom position was 564
			SPLASH_SCREEN_BG_DRAW=1;
            break; 


        case WM_MOUSEMOVE:
            cxMouse = LOWORD(lParam);
            cyMouse = HIWORD(lParam);
			CLIENT_XMouse=cxMouse;
			CLIENT_YMouse=cyMouse;
            break;

		case WM_KEYDOWN:
	
	/*
			if(wParam == 'M' || wParam == 'm')
			{
				//Togle code
				if(MUSIC_PLAY_STATUS==TRUE)
				{
					MUSIC_PLAY_STATUS=FALSE;
					PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC  );
				}
				else
				{
					MUSIC_PLAY_STATUS=TRUE;
					PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );
				}
			}
		
			*/
			
			if(wParam == 'C' || wParam == 'c')
			{
				//Togle the coloring scheme
				if( COLOR_SCHEME == MONO_COLOR )
				{
					COLOR_SCHEME = MULTI_COLOR;
				}else if(COLOR_SCHEME == MULTI_COLOR )
                
				{
					COLOR_SCHEME = MONO_COLOR;
				}
				
			}
			
			if(wParam == VK_ESCAPE )
			{
				PostQuitMessage(0);
			}
		break;
			
     
    case WM_PAINT: 
        hdc = BeginPaint(hwnd, &ps);
        
        if( SPLASH_SCREEN_RUN_STATUS == TRUE) {
            if(SPLASH_SCREEN_BG_DRAW == 1) {
                hdcComp = CreateCompatibleDC(hdc);
                prevHGDIObj = SelectObject(hdcComp, hbmap);
                GetObject(hbmap, sizeof(BITMAP), &bmBuffer);
                GetClientRect(hwnd, &rc);
                BitBlt(hdc, (rc.right - bmBuffer.bmWidth)/2, (rc.bottom - bmBuffer.bmHeight)/2, (int)bmBuffer.bmWidth , (int)bmBuffer.bmHeight, hdcComp, 0, 0, SRCCOPY); 
                SPLASH_SCREEN_BG_DRAW=0;
            }

            if( COLOR_SCHEME == MONO_COLOR ) {
                HLinePen=CreatePen(PS_SOLID, 8 , light_orange);
            } else if(COLOR_SCHEME == MULTI_COLOR) {
                RandomPen(&HLinePen,&color,8);
            }
            HOldPen=(HPEN)SelectObject(hdc,HLinePen);
            for(pointIndex=0; pointIndex < SPLASH_SCREEN_POINTS_PLOTED ; pointIndex++) {
                if(pointIndex!=0) {
                    MoveToEx(hdc,pVec_Splash_Screen_outer->list[pointIndex-1]->xPosition+SPLASH_SCREEN_X_SHIFT_OUTER,pVec_Splash_Screen_outer->list[pointIndex-1]->yPosition+SPLASH_SCREEN_Y_SHIFT_OUTER,NULL);
                    LineTo(hdc,pVec_Splash_Screen_outer->list[pointIndex]->xPosition+SPLASH_SCREEN_X_SHIFT_OUTER,pVec_Splash_Screen_outer->list[pointIndex]->yPosition+SPLASH_SCREEN_Y_SHIFT_OUTER);
                }
            }
            if( SPLASH_SCREEN_POINTS_PLOTED == pVec_Splash_Screen_outer->count ) {
                SetTextAlign(hdc, TA_CENTER | TA_TOP); 
                SetBkMode(hdc,TRANSPARENT);
                SetTextColor(hdc, g_currentTextColor); // Use the current text color
                
                HSplashScreenFont=CreateFont(40, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Cambria"));
                HOldFont=(HFONT)SelectObject(hdc, HSplashScreenFont);
                
                TextOut(hdc, SPLASH_SCREEN_X_SHIFT_OUTER, SPLASH_SCREEN_Y_SHIFT_OUTER + SPLASH_SCREEN_CIRCLE_RADIUS - 480, "CoreCode Programming Academy LLP", lstrlen("CoreCode Programming Academy LLP"));
                TextOut(hdc, SPLASH_SCREEN_X_SHIFT_OUTER, SPLASH_SCREEN_Y_SHIFT_OUTER + SPLASH_SCREEN_CIRCLE_RADIUS + 30, "Group Decimals Presents : Reinventing The Wheels", lstrlen("Group Decimals Presents : Reinventing The Wheels"));
            }
        } else {
            SetTextAlign(hdc, TA_CENTER | TA_TOP); 
            SetBkMode(hdc,TRANSPARENT);
            SetTextColor(hdc,skyblue);
            TextOut(hdc, SPLASH_SCREEN_X_SHIFT_OUTER, SPLASH_SCREEN_Y_SHIFT_OUTER + 300, "Moved to other window", lstrlen("Moved to other window"));
        }

        SelectObject(hdcComp, prevHGDIObj);
        DeleteDC(hdcComp);
        EndPaint(hwnd, &ps);
        break;

    case WM_TIMER:
        if(SPLASH_SCREEN_POINTS_PLOTED == 0 && MUSIC_PLAY_STATUS==TRUE) {
            //PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC );
        }
        
        if(SPALSH_SCREEN_COMPLETED == 1) {
            InvalidateRect(hwnd, NULL, TRUE);
            SPALSH_SCREEN_COMPLETED++;
        }
        
        if( SPLASH_SCREEN_POINTS_PLOTED != pVec_Splash_Screen_outer->count) {
            SPLASH_SCREEN_POINTS_PLOTED++;	
            InvalidateRect(hwnd, NULL, FALSE);
        } else {
            MUSIC_PLAY_STATUS=FALSE;
        }

        // Update the text color
        UpdateTextColor();
        InvalidateRect(hwnd, NULL, FALSE); // Trigger repaint to update the text color
        break;

   
		


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	// 12
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}



bool MyCircle(int iXCenter,int iYCenter,int radius,HDC hdc)
{
    return(Ellipse(hdc,(iXCenter-radius),(iYCenter-radius),(iXCenter+radius),(iYCenter+radius)));
}


int mygetline(char **line ,size_t * char_cnt, FILE * fp){

	
	long int BUFF_SIZE=64;
	long int BUFF_INCREMENT=64;
	
	long int FILE_READ_POINT=0;
	long int FILE_CHAR_COUNT=0;

	fseek(fp,0,SEEK_CUR);
	FILE_READ_POINT=ftell(fp);
	
	int i;
	int LINE_END=0;
	
	
	fseek(fp,FILE_READ_POINT,SEEK_SET);
	 

	 
	 while(LINE_END!=1)
	 {
	 	fseek(fp,FILE_READ_POINT,SEEK_SET);
	 
	 BUFF_SIZE=BUFF_SIZE+BUFF_INCREMENT;
	 
	 
	 	*line=(char *)realloc(*line, sizeof(char)*BUFF_SIZE);
       
       
    if(fgets(*line,BUFF_SIZE,fp)!=NULL)
    {
       
       for(i=0;i<(BUFF_SIZE-1) -1;i++)
       {
   
       	if((*line)[i]=='\0' )
       	{
       	       LINE_END=1;
       	       *char_cnt=BUFF_SIZE;
       	       break;
       	}
       	//puts(" Inside For Loop ");
       }
      
      //BUFF_MULTIPLIER++;
    }else  //this case handles last line in file
    {
    	  LINE_END=1;
    	  *char_cnt=0;
    }
	 }
	 
	 fseek(fp,0,SEEK_CUR);
	FILE_READ_POINT=ftell(fp);
      
      //to vheck if we reached file end
      fseek(fp,0,SEEK_END);
      FILE_CHAR_COUNT=ftell(fp);
      
      //printf(" TOTAL CHAR %ld  CURENT READ %ld\n",FILE_CHAR_COUNT,FILE_READ_POINT);
      
      if(FILE_READ_POINT==FILE_CHAR_COUNT)
      {
           return (-1);
      }else
      {
          fseek(fp,FILE_READ_POINT,SEEK_SET);
          return (0);
      }
}

void UpdateTextColor() {
    static int r = 255, g = 0, b = 0; 
    static int cycleStep = 0;

    if (colorCycleCompleted == 0) { 
        if (r > 0 && b == 0) {
            r--;
            g++;
        }
        if (g > 0 && r == 0) {
            g--;
            b++;
        }
        if (b > 0 && g == 0) {
            b--;
            r++;
        }

        g_currentTextColor = RGB(r, g, b);

       
        if (r == 255 && g == 0 && b == 0) {
            cycleStep++; 
            if (cycleStep >= 2) {  
                colorCycleCompleted = 1;  
            }
        }
    }
}

void RandomPen(HPEN * out_hpen,COLORREF * out_color,BRUSH_SIZE brushSize)
{
		
	COLORREF textColor;
	HPEN hLinePen;
	
	int iColor=rand()%9; //some random number
	switch(iColor)
	{
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
		default:
			hLinePen=CreatePen(PS_SOLID, brushSize , orange);
			textColor=orange;
	} 
	
	if(out_hpen!=NULL)
		*out_hpen=hLinePen;
	if(out_color!=NULL)
	*out_color=textColor;
}

PVECTOR CreateVector(void)
{
    PVECTOR pVector=NULL;
    pVector=(PVECTOR)malloc(sizeof(VECTOR));
    pVector->list=NULL;
    pVector->count=0;
    return pVector;
}

void DestroyVector(PVECTOR * pVector)
{
    int i=0;
    for (i=0;i<(*pVector)->count;i++)
    {
        free((*pVector)->list[i]);
		(*pVector)->list[i]=NULL;
    }
    free((*pVector)->list);
    (*pVector)->list=NULL;
    (*pVector)->count=0;
    free(*pVector);
    *pVector=NULL;
}



int PushElement(PVECTOR pVector,PTJ_POINT pPoint)
{
    pVector->count+=1;
    pVector->list=(PPTJ_POINT)realloc(pVector->list,pVector->count*sizeof(PTJ_POINT));
	
    pVector->list[pVector->count-1]=pPoint;
	
    return (EXIT_SUCCESS);
}


void PopElement(PVECTOR pVector,int index)
{
    if(index <0 || index >= pVector->count)
		return;
	
	free(pVector->list[index]);
	pVector->list[index] = NULL;
	
	int i;
	for(i=index;i< pVector->count-1 ;i++)
	{
		pVector->list[i]=pVector->list[i+1];
		pVector->list[i+1] = NULL;
	}
	
	pVector->count-=1;
}

PTJ_POINT CreatePoint(int xPos,int yPos, int xVel, int yVel)
{
    PTJ_POINT pPoint=NULL;
	pPoint=(PTJ_POINT)malloc(sizeof(TJ_POINT));
    pPoint->xPosition=xPos;
    pPoint->yPosition=yPos;
    pPoint->xVelocity=xVel;
    pPoint->yVelocity=yVel;
	pPoint->dead=0;
    return pPoint;
}

double getDistance(int x1,int y1, int x2,int y2 )
{
	//@ Return the distacne between 2 poitns using euclidian distance formula;
	double distacne;
	int delta_x=x2-x1;
	int delta_y=y2-y1;
	
	distacne = pow(pow(delta_x,2.0f) + pow(delta_y,2.0f), (0.5f));
	return (distacne);
}


//This is used to craete offset for perfect circle
void GenerateCricleOffsets(PVECTOR pVector,int iRadius)
{
	PTJ_POINT pPoint;
	int angle_deg; //0 to 360
    int iPointX,iPointY;
    float angle_rad;   
	
    for(angle_deg=0;angle_deg<=360;angle_deg+=3)
    {
        angle_rad=M_PI/180*angle_deg;
		iPointX= cos(angle_rad) * (iRadius);
		iPointY= sin(angle_rad) * (iRadius);
		
		pPoint=CreatePoint(iPointX,iPointY,0,0);    //Offset only values 
		PushElement(pVector,pPoint);
    }
}