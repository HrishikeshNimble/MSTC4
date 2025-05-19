static int cxClient, cyClient, cxChar, cyChar;

static int timer_flag = 0;
static int end_flag = 0;
static int display_flag[20];

static char str[] = TEXT("To Be Continued ...");
static char substr[20];

HFONT hFont; 

HDC hdc = NULL;
TEXTMETRIC tm;
PAINTSTRUCT ps;
int i;