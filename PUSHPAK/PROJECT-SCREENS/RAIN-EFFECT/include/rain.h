#define TIMER_ID 1
#define DROP_COUNT 600     
#define MIN_SPEED 8        
#define MAX_SPEED 20       
#define MIN_SIZE 8         
#define MAX_SIZE 25        

typedef struct {
    int x, y, speed, size, alpha;
} Raindrop;

Raindrop raindrops[DROP_COUNT];
int screenWidth, screenHeight;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "Msimg32.lib")


