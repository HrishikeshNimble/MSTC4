#define NUM_PARTICLES 1100
#define PARTICLE_SIZE 5

#define TIMER_ID 1
#define RECT_SPEED 5

int screenWidth, screenHeight;
RECT movingRect = {0, 0, 50, 500}; // Initial rectangle height = 500px

typedef struct
{
    int x, y;
    int dx, dy;
    COLORREF color;
} Particle;
Particle particles[NUM_PARTICLES];

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void UpdateParticles(Particle particles[], int screenWidth, int screenHeight);
void DisplayImageFromResource(HDC hdc, RECT rect, HINSTANCE hInstance);

int r = 150, g = 100, b = 200; // purple
int r_increment = 1;
int g_increment = 1;
int b_increment = -1;

static BOOL rectExpanded = FALSE;
static BOOL textDisplayed = FALSE;
static UINT_PTR textTimerId = 2; // Timer ID for text display

// Global variables for image handling
HBITMAP hBitmap = NULL;
BOOL imageDisplayed1 = FALSE; // Set to FALSE initially to ensure the image is not displayed at the start
HINSTANCE hInstance;
