int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Timer ID
#define TIMER_ID 1

// Global variables for flags
static BOOL showLine1 = FALSE;
static BOOL showPinkRect = FALSE;
static BOOL showLine2 = FALSE;
static BOOL showBlueRect = FALSE;
static BOOL showLine3 = FALSE;
static BOOL showorangeRect = FALSE;
static BOOL showLine4 = FALSE;
static BOOL showaorangeRect = FALSE;

// Handle to the parent window (WndProc7 window)
static HWND hwndParent;
static int lineX1 = 150; // Initial X position of the first line
static int lineY1 = 150;
// Initial Y position of the first line
static int lineX2 = 750; // Initial X position of the second line
static int lineY2 = 150;
// Initial Y position of the second line
static int lineX3 = 1310; // Initial X position of the third line
static int lineY3 = 150;
// // Initial Y position of the second line
static int lineX4 = 1610; // Initial X position of the third line
static int lineY4 = 150;  // // Initial Y position of the second line

// Light pink rectangle position and dimensions
static int rectX = 50;       // X position of the light pink rectangle
static int rectY = 352;      // Y position of the light pink rectangle
static int rectHeight = 100; // Height of the pink rectangle
static int rectWidth = 600;  // Width of the pink rectangle

// Light blue rectangle position and dimensions
static int blueRectX = 550;      // X position of the light blue rectangle
static int blueRectY = 500;      // Y position of the light blue rectangle
static int blueRectHeight = 100; // Height of the blue rectangle
static int blueRectWidth = 600;
// Width of the blue rectangle
static int orangeRectX = 800;      // X position of the light blue rectangle
static int orangeRectY = 700;      // Y position of the light blue rectangle
static int orangeRectHeight = 100; // Height of the blue rectangle
static int orangeRectWidth = 600;
// Width of the blue rectangle
static int aorangeRectX = 1100;     // X position of the light blue rectangle
static int aorangeRectY = 870;      // Y position of the light blue rectangle
static int aorangeRectHeight = 100; // Height of the blue rectangle
static int aorangeRectWidth = 700;  // Width of the blue rectangle

/*
Rainfall
*/
#define DROP_COUNT 600 // पानी की बूंदों की संख्या
#define MIN_SPEED 8    // न्यूनतम गति
#define MAX_SPEED 20   // अधिकतम गति
#define MIN_SIZE 8     // न्यूनतम लंबाई
#define MAX_SIZE 25    // अधिकतम लंबाई
typedef struct
{
    int x, y, speed, size, alpha;
} Raindrop;

Raindrop raindrops[DROP_COUNT];
int screenWidth, screenHeight;

#define TIMER_ID_RAIN 1
#define TIMER_ID_QUOTE 2
void DrawQuoteBox(HDC hdcDest, int x, int y, int width, int height, COLORREF color, LPCWSTR text, int alpha);