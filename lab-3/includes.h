#include <windows.h>
#include <windowsx.h>

#define ALL_TOOLS 100
#define PENCIL_T 101
#define ELLIPSE_T 102
#define RECTANGLE_T 103
#define LINE_T 104
#define ERASER_T 105
#define FILL_COLOR_CHECKER 106

#define IDB_EXERCISING 109

void updateColorControls(HDC, COLORREF, int, int);
int getFromInput(HWND);
POINT getCurrentPointPosition(int, int, RECT, int);

