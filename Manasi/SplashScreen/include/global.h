///////COMMON FOR ALL START/////////////

//Coloring scheme values
#define MONO_COLOR      0
#define MULTI_COLOR     1

#define VISULIZER_RED_PEN     1
#define VISULIZER_GREEN_PEN   2
#define VISULIZER_BLUE_PEN    3
#define VISULIZER_ORAGNE_PEN  4
#define VISULIZER_CYAN_PEN    5
#define VISULIZER_MGENTA_PEN  6
#define VISULIZER_YELLOW_PEN  7
#define VISULIZER_SKYBLUE_PEN 8

#ifndef size_t
#define size_t long int
#endif

typedef int BRUSH_SIZE;

typedef struct tagmyPoint
{
    int xPosition;
    int yPosition;
    int xVelocity;
    int yVelocity;
    //int xAcceleration;
    //int yAcceleration;
    int dead;  //by default when myPoint spawns it is not dead  
    COLORREF * color; 
}TJ_POINT,*PTJ_POINT,**PPTJ_POINT;

typedef struct tagVector
{
    PPTJ_POINT list;
	int count;
}VECTOR,*PVECTOR;



COLORREF red=RGB(255,0,0); 
COLORREF green=RGB(0,255,0); 
COLORREF blue=RGB(0,0,255); 
COLORREF orange=RGB(255,165,0); 
COLORREF light_orange=RGB(240,173,33);
COLORREF cyan=RGB(0,255,255); 
COLORREF magenta=RGB(255,0,255); 
COLORREF yellow=RGB(255,215,0); 
COLORREF skyblue=RGB(0,191,255); 
COLORREF darkgrey=RGB(105,105,105);
COLORREF grey    =RGB(128,128,128);


int CLIENT_XArea,CLIENT_YArea;
int CLIENT_XMouse,CLIENT_YMouse;


///////SPLASH SCREEN SPECIFIC GLOBAL VAR START /////////////

int SPLASH_SCREEN_X_SHIFT_OUTER=0; 
int SPLASH_SCREEN_Y_SHIFT_OUTER=0;
int SPLASH_SCREEN_X_SHIFT_INNER=0; 
int SPLASH_SCREEN_Y_SHIFT_INNER=0;


int SPLASH_SCREEN_POINTS_PLOTED=0;
int MUSIC_PLAY_STATUS=TRUE;
int COLOR_SCHEME=MONO_COLOR;
int SPLASH_SCREEN_RUN_STATUS=TRUE;
int SPLASH_SCREEN_CIRCLE_RADIUS=200;
PVECTOR pVec_Splash_Screen_outer;  //Global vecor pointer for splash screen


///////SPLASH SCREEN SPECIFIC GLOBAL VAR END /////////////


///////COMMON FOR ALL START /////////////

PVECTOR CreateVector(void);
int PushElement(PVECTOR pVector,PTJ_POINT pPoint);
void DestroyVector(PVECTOR * pVector);
void PopElement(PVECTOR pVector,int index);
int mygetline(char **line ,size_t * char_cnt, FILE * fp);
void RandomPen(HPEN * out_hpen,COLORREF * out_color,BRUSH_SIZE brushSize);
PTJ_POINT CreatePoint(int xPos,int yPos, int xVel, int yVel);
double getDistance(int x1,int y1, int x2,int y2 );
void GenerateCricleOffsets(PVECTOR pVector,int iRadius);
bool MyCircle(int iXCenter,int iYCenter,int radius,HDC hdc);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void UpdateTextColor(void);

///////COMMON FOR ALL END /////////////