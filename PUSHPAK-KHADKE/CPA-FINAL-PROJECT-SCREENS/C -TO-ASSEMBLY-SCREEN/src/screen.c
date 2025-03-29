#include <Windows.h>
#include <time.h>
#include <math.h>
#include "..\include\global.h"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    static TCHAR szClassName[] = TEXT("FirecrackerWindow");
    static TCHAR szWindowTitle[] = TEXT("C TO ASSEMBLY CONVERSION SCREEN");

    HWND hwnd = NULL;
    WNDCLASSEX wnd;
    MSG msg;

    ZeroMemory(&wnd, sizeof(WNDCLASSEX));
    ZeroMemory(&msg, sizeof(MSG));

    wnd.cbSize = sizeof(WNDCLASSEX);
    wnd.cbClsExtra = 0;
    wnd.cbWndExtra = 0;

    wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // Initial background color
    wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
    wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wnd.hInstance = hInstance;
    wnd.lpfnWndProc = WndProc;
    wnd.lpszClassName = szClassName;
    wnd.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&wnd))
    {
        MessageBox(NULL, TEXT("Failed to register window class"), TEXT("Error"), MB_ICONERROR | MB_OK);
        return 0;
    }

    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);

    hwnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        szClassName,
        szWindowTitle,
        WS_POPUP,
        0, 0,
        screenWidth,
        screenHeight,
        (HWND)NULL,
        (HMENU)NULL,
        hInstance,
        (LPVOID)NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, TEXT("Failed to create window"), TEXT("Error"), MB_ICONERROR | MB_OK);
        return 0;
    }

    // Initialize background colors
    currentBgColor = bgColors[0];
    nextBgColor = bgColors[1];

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    // Set a timer to trigger every 50 milliseconds for animation
    SetTimer(hwnd, TIMER_ID, 50, NULL);

    // Set a timer to trigger every 2 minutes for background color change
    SetTimer(hwnd, COLOR_CHANGE_TIMER_ID, COLOR_CHANGE_INTERVAL, NULL);

    srand((unsigned int)time(NULL)); 

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        GetClientRect(hwnd, &rect);

        // Brush for the rocket
        hBrushRocket = CreateSolidBrush(RGB(255, 255, 255));

        // Initialize rockets
        for (int i = 0; i < MAX_ROCKETS; i++)
        {
            rockets[i].active = 0;
        }

        // Set a timer
        SetTimer(hwnd, LINE_TIMER_ID, 5000, NULL); 

       
        SetTimer(hwnd, CODE_TIMER_ID, 12000, NULL); // 30000 milliseconds = 30 seconds

        // Set a timer to trigger after C code is fully displayed for assembly code
        SetTimer(hwnd, ASSEMBLY_TIMER_ID, 63000 + (sizeof(codeLines) / sizeof(codeLines[0])) * 1000, NULL);
        break;

    case WM_ERASEBKGND:
        // Return TRUE to prevent background erasing (reduces flickering)
        return TRUE;

    case WM_TIMER:
        if (wParam == TIMER_ID)
        {
            // Launch rockets simultaneously
            for (int i = 0; i < MAX_ROCKETS; i++)
            {
                if (!rockets[i].active)
                {
                    // Assign rockets to left or right based on index
                    LaunchRocket(&rockets[i], i < MAX_ROCKETS / 2, i);
                }
            }

            for (int i = 0; i < MAX_ROCKETS; i++)
            {
                if (rockets[i].active)
                {
                    if (!rockets[i].explosionTriggered)
                    {
                        // Move the rocket upward
                        rockets[i].y -= 10;

                        // Trigger explosion when the rocket reaches a certain height
                        if (rockets[i].y < rect.bottom / 2)
                        {
                            rockets[i].explosionTriggered = 1;
                            InitializeParticles(&rockets[i]);
                        }
                    }
                    else
                    {
                        // Update particles
                        int activeParticles = 0;
                        for (int j = 0; j < PARTICLE_COUNT; j++)
                        {
                            if (rockets[i].particles[j].lifetime > 0)
                            {
                                rockets[i].particles[j].x += rockets[i].particles[j].dx;
                                rockets[i].particles[j].y += rockets[i].particles[j].dy;
                                rockets[i].particles[j].lifetime--;
                                activeParticles++;
                            }
                        }

                        // Reset rocket after particles disappear
                        if (activeParticles == 0)
                            rockets[i].active = 0;
                    }
                }
            }

            // Force the window to redraw
            InvalidateRect(hwnd, NULL, FALSE); // FALSE to avoid erasing the background
        }
        else if (wParam == COLOR_CHANGE_TIMER_ID)
        {
            // Change background color
            currentColorIndex = (currentColorIndex + 1) % NUM_COLORS;
            nextBgColor = bgColors[currentColorIndex];
            colorTransitionProgress = 0.0f;

            // Force the window to redraw
            InvalidateRect(hwnd, NULL, FALSE); // FALSE to avoid erasing the background
        }
        else if (wParam == LINE_TIMER_ID)
        {
            // Enable drawing of lines after 2 seconds
            drawLines = true;

            // Force the window to redraw
            InvalidateRect(hwnd, NULL, FALSE); // FALSE to avoid erasing the background

            
            KillTimer(hwnd, LINE_TIMER_ID);

            // Set a timer to show the first line of code after 3 seconds
            SetTimer(hwnd, FIRST_LINE_TIMER_ID, 3000, NULL);
        }
        else if (wParam == FIRST_LINE_TIMER_ID)
        {
            // Show the first line of code
            currentCodeLine = 0;

            // Force the window to redraw
            InvalidateRect(hwnd, NULL, FALSE); 

       
            KillTimer(hwnd, FIRST_LINE_TIMER_ID);
        }
        else if (wParam == CODE_TIMER_ID)
        {
            // Increment the current code line until all C code lines are displayed
            if (currentCodeLine < (sizeof(codeLines) / sizeof(codeLines[0]) - 1))
            {
                currentCodeLine++;
            }
            else
            {
                // When all C code lines are displayed, start showing assembly code
                KillTimer(hwnd, CODE_TIMER_ID);
                SetTimer(hwnd, ASSEMBLY_TIMER_ID, 10000, NULL); 
            }

            InvalidateRect(hwnd, NULL, FALSE);
        }
        else if (wParam == ASSEMBLY_TIMER_ID)
        {
            // Start showing assembly code
            currentAssemblyLine = 0;

            InvalidateRect(hwnd, NULL, FALSE);

            // Stop the assembly timer and start the assembly line timer
            KillTimer(hwnd, ASSEMBLY_TIMER_ID);
            SetTimer(hwnd, ASSEMBLY_LINE_TIMER_ID, 8000, NULL);
        }
        else if (wParam == ASSEMBLY_LINE_TIMER_ID)
        {
            // Increment the current assembly line until all lines are displayed
            if (currentAssemblyLine < (sizeof(assemblyCodeLines) / sizeof(assemblyCodeLines[0]) - 1))
            {
                currentAssemblyLine++;
            }
            else
            {
                // Stop the timer when all assembly lines are displayed
                KillTimer(hwnd, ASSEMBLY_LINE_TIMER_ID);
            }

            // Force the window to redraw
            InvalidateRect(hwnd, NULL, FALSE);
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Create a memory device context for double buffering
        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hbmMem = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
        HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);

        // Update background color transition
        if (colorTransitionProgress < 1.0f)
        {
            colorTransitionProgress += 0.01f; // Adjust this value for smoother or faster transition
            if (colorTransitionProgress > 1.0f)
                colorTransitionProgress = 1.0f;

            currentBgColor = InterpolateColor(currentBgColor, nextBgColor, colorTransitionProgress);
        }

        // Set the new background color
        HBRUSH hBrushBg = CreateSolidBrush(currentBgColor);
        FillRect(hdcMem, &rect, hBrushBg);
        DeleteObject(hBrushBg);

        // Draw the white rectangle at the top
        RECT topRect;
        topRect.left = 0;
        topRect.top = 0;
        topRect.right = rect.right;
        topRect.bottom = 200; // Height of 200px

        HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255)); // White brush
        FillRect(hdcMem, &topRect, hBrushWhite);
        DeleteObject(hBrushWhite);

        // Create a bold font
        HFONT hFont = CreateFont(
            75,      
            0,       
            0,      
            0,       
            FW_BOLD, 
            FALSE,   
            FALSE,   
            FALSE,   
            DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_DONTCARE,
            TEXT("Arial") 
        );

        // Select the font into the memory device context
        HFONT hOldFont = (HFONT)SelectObject(hdcMem, hFont);

        // Set text color to black
        SetTextColor(hdcMem, RGB(0, 0, 0));

        // Set background mode to transparent
        SetBkMode(hdcMem, TRANSPARENT);

        // Draw the text centered in the rectangle
        DrawText(
            hdcMem,
            TEXT("C TO ASSEMBLY CONVERSION"),
            -1, // Length of the string (-1 for null-terminated)
            &topRect,
            DT_CENTER | DT_VCENTER | DT_SINGLELINE // Center the text
        );

        // Restore the old font
        SelectObject(hdcMem, hOldFont);
        DeleteObject(hFont);

        // Draw rockets and particles
        for (int i = 0; i < MAX_ROCKETS; i++)
        {
            if (rockets[i].active)
            {
                if (!rockets[i].explosionTriggered)
                {
                    // Draw the rocket
                    SelectObject(hdcMem, hBrushRocket);
                    Ellipse(hdcMem, rockets[i].x - 5, rockets[i].y - 20, rockets[i].x + 5, rockets[i].y); // Rocket body
                }
                else
                {
                    // Draw particles
                    for (int j = 0; j < PARTICLE_COUNT; j++)
                    {
                        if (rockets[i].particles[j].lifetime > 0)
                        {
                            HBRUSH hBrush = CreateSolidBrush(rockets[i].particles[j].color);
                            SelectObject(hdcMem, hBrush);
                            Ellipse(hdcMem, rockets[i].particles[j].x - 4, rockets[i].particles[j].y - 4, rockets[i].particles[j].x + 4, rockets[i].particles[j].y + 4);
                            DeleteObject(hBrush);
                        }
                    }
                }
            }
        }

        // Draw the lines after 2 seconds
        if (drawLines)
        {
            // Draw a horizontal line at the bottom of the white rectangle
            HPEN hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0)); // Red pen, 5px width
            HPEN hOldPen = (HPEN)SelectObject(hdcMem, hPen);

            int bottomY = topRect.bottom;        // Bottom of the white rectangle
            MoveToEx(hdcMem, 0, bottomY, NULL);  // Start point
            LineTo(hdcMem, rect.right, bottomY); // End point

            // Draw a vertical line from the center of the horizontal line
            int centerX = rect.right / 2;             // Center of the screen
            MoveToEx(hdcMem, centerX, bottomY, NULL); // Start point
            LineTo(hdcMem, centerX, rect.bottom);     // End point

            // Restore the old pen
            SelectObject(hdcMem, hOldPen);
            DeleteObject(hPen);

            // Draw the code lines
            HFONT hCodeFont = CreateFont(
                40,        
                0,         
                0,         
                0,         
                FW_NORMAL, 
                FALSE,     
                FALSE,     
                FALSE,    
                DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_DONTCARE,
                TEXT("Courier New") 
            );

            // Select the code font into the memory device context
            HFONT hOldCodeFont = (HFONT)SelectObject(hdcMem, hCodeFont);

            // Set text color to RGB(173, 216, 230)
            SetTextColor(hdcMem, RGB(173, 216, 230));

            // Draw all lines up to currentCodeLine
            for (int i = 0; i <= currentCodeLine; i++)
            {
                RECT codeRect;
                codeRect.left = 10;                     // 10px from the left edge
                codeRect.top = bottomY + 10 + (i * 50); // 10px below the horizontal line, 50px spacing
                codeRect.right = centerX - 10;          // Stop before the vertical line
                codeRect.bottom = codeRect.top + 40;    // Height of the text

                DrawText(
                    hdcMem,
                    codeLines[i],
                    -1, // Length of the string (-1 for null-terminated)
                    &codeRect,
                    DT_LEFT | DT_TOP // Align text to the left and top
                );
            }

            // Draw all assembly lines up to currentAssemblyLine
            for (int i = 0; i <= currentAssemblyLine; i++)
            {
                RECT assemblyRect;
                assemblyRect.left = centerX + 10;            // Start after the vertical line
                assemblyRect.top = bottomY + 10 + (i * 50);  // 10px below the horizontal line, 50px spacing
                assemblyRect.right = rect.right - 10;        // 10px from the right edge
                assemblyRect.bottom = assemblyRect.top + 40; // Height of the text

                DrawText(
                    hdcMem,
                    assemblyCodeLines[i],
                    -1, // Length of the string (-1 for null-terminated)
                    &assemblyRect,
                    DT_LEFT | DT_TOP // Align text to the left and top
                );
            }

            // Restore the old font
            SelectObject(hdcMem, hOldCodeFont);
            DeleteObject(hCodeFont);
        }

        // Copy the off-screen buffer to the screen
        BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcMem, 0, 0, SRCCOPY);

        // Clean up
        SelectObject(hdcMem, hbmOld);
        DeleteObject(hbmMem);
        DeleteDC(hdcMem);

        EndPaint(hwnd, &ps);
    }
    break;
    case WM_DESTROY:
        KillTimer(hwnd, TIMER_ID);               
        KillTimer(hwnd, COLOR_CHANGE_TIMER_ID);  
        KillTimer(hwnd, LINE_TIMER_ID);          
        KillTimer(hwnd, CODE_TIMER_ID);          
        KillTimer(hwnd, FIRST_LINE_TIMER_ID);   
        KillTimer(hwnd, ASSEMBLY_TIMER_ID);     
        KillTimer(hwnd, ASSEMBLY_LINE_TIMER_ID); 
        DeleteObject(hBrushRocket);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void InitializeParticles(Rocket *rocket)
{
    for (int i = 0; i < PARTICLE_COUNT; i++)
    {
        rocket->particles[i].x = rocket->x;
        rocket->particles[i].y = rocket->y;

        // Position particles in a circular pattern
        double angle = (2 * PI / PARTICLE_COUNT) * i;
        rocket->particles[i].dx = (int)(cos(angle) * (rand() % 10 + 5)); // X velocity
        rocket->particles[i].dy = (int)(sin(angle) * (rand() % 10 + 5)); // Y velocity

        // Random colors for particles
        rocket->particles[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);

        // Random lifetime
        rocket->particles[i].lifetime = rand() % 50 + 50;
    }
}

void LaunchRocket(Rocket *rocket, int left, int index)
{
    if (left)
    {
        // Launch rocket on the left half of the screen
        rocket->x = rand() % (rect.right / 2);
    }
    else
    {
        // Launch rocket on the right half of the screen
        rocket->x = (rect.right / 2) + (rand() % (rect.right / 2));
    }
    rocket->y = rect.bottom;
    rocket->active = 1;
    rocket->explosionTriggered = 0;
}

COLORREF InterpolateColor(COLORREF color1, COLORREF color2, float fraction)
{
    int r1 = GetRValue(color1);
    int g1 = GetGValue(color1);
    int b1 = GetBValue(color1);

    int r2 = GetRValue(color2);
    int g2 = GetGValue(color2);
    int b2 = GetBValue(color2);

    int r = (int)(r1 + (r2 - r1) * fraction);
    int g = (int)(g1 + (g2 - g1) * fraction);
    int b = (int)(b1 + (b2 - b1) * fraction);

    return RGB(r, g, b);
}