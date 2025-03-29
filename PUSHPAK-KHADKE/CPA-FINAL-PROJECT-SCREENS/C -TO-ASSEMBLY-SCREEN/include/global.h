/*
Fire Effect
*/

/*
Effect Code
*/
#define TIMER_ID 1
#define PARTICLE_COUNT 150 // Increased particle count
#define MAX_ROCKETS 12      // Maximum rockets launched at once
#define PI 3.14159265

int screenWidth, screenHeight;

// Particle structure
typedef struct
{
    int x, y;            // Position
    int dx, dy;          // Velocity
    COLORREF color;      // Color
    int lifetime;        // Lifetime of the particle
} Particle;

typedef struct
{
    int x, y;                 // Rocket position
    int active;               // Rocket state
    int explosionTriggered;   // Explosion state
    Particle particles[PARTICLE_COUNT];
} Rocket;

Rocket rockets[MAX_ROCKETS];
RECT rect;
HBRUSH hBrushRocket;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void InitializeParticles(Rocket* rocket);
void LaunchRocket(Rocket* rocket, int left, int index);
COLORREF InterpolateColor(COLORREF color1, COLORREF color2, float fraction);


// ------------------------------ color change
#define COLOR_CHANGE_INTERVAL 3000 
#define NUM_COLORS 6
#define COLOR_CHANGE_TIMER_ID 2 

// 5 dark colors for background cycling
COLORREF bgColors[NUM_COLORS] = {
    RGB(51, 25, 0),   // Dark Brown
    RGB(0, 0, 102),   // Dark Blue
    RGB(45, 10, 45),  // Dark Purple-Brown
    RGB(33, 33, 33),  // Dark Black
    RGB(51, 0, 0),    // Dark Red
    RGB(25, 0, 51)    // Dark Purple
};

int currentColorIndex = 0;
COLORREF currentBgColor;
COLORREF nextBgColor;
float colorTransitionProgress = 0.0f;

//----------------------------- lines
#include <stdbool.h>
#define LINE_TIMER_ID 3 
bool drawLines = false; // Flag to control drawing of lines

//---------------- c code display lines
#define CODE_TIMER_ID 4 
#define FIRST_LINE_TIMER_ID 5
// Add a new state variable
bool allLinesPrinted = false;
int currentCodeLine = 0; // Index of the current line to display
const char* codeLines[] = {
    "#include <stdio.h>",
    "#include <stdlib.h>",
    "int main(void) {",
    "    printf(\"Hello, World!\\n\");",
    "    exit(0);",
    "}"
};

//----------------------- assembly code display lines

#define ASSEMBLY_LINE_TIMER_ID 8
#define ASSEMBLY_TIMER_ID 9
int currentAssemblyLine = -1; // -1 means no assembly code is being displayed
const char* assemblyCodeLines[] = {
    ".section .data",
    "msg1:",
    "    .string \"Hello, World!\\n\"",
    "",
    ".section .text",
    ".globl main",
    ".type   main, @function",
    "",
    "main:",
    "    pushl   %ebp",
    "    movl    %esp, %ebp",
    "    pushl   $msg1",
    "    call    printf",
    "    addl    $4, %esp",
    "    pushl   $0",
    "    call    exit"
};