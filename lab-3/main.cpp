#include <windows.h>
#include <windowsx.h>
#include "includes.h"

LPSTR szClassName = "Lab#3";
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;

COLORREF fillColor = RGB(139, 0, 240);
COLORREF borderColor = RGB(0, 0, 0);
COLORREF colorSelect(HWND hwnd, COLORREF color)
{
    COLORREF g_rgbCustom[16] = {0};
    CHOOSECOLOR cc = {sizeof(CHOOSECOLOR)};

    cc.Flags = CC_RGBINIT | CC_SOLIDCOLOR;
    cc.hwndOwner = hwnd;
    cc.rgbResult = color;
    cc.lpCustColors = g_rgbCustom;

    if(ChooseColor(&cc))
    {
        color = cc.rgbResult;
    }
    return color;
}

WNDPROC GroupBoxProc;
LONG CALLBACK GroupRelay(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if(msg == WM_COMMAND || msg == WM_NOTIFY){
        return SendMessage(GetParent(hwnd), msg, wParam, lParam);
    }

    return CallWindowProc(GroupBoxProc, hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
    WNDCLASSEX wnd;
    MSG msg;
    HWND hwnd;
    hInst = hInstance;

    wnd.hInstance = hInst;
    wnd.lpszClassName = szClassName;
    wnd.lpfnWndProc = WindowProcedure;
    wnd.style = CS_HREDRAW | CS_VREDRAW;
    wnd.cbSize = sizeof(WNDCLASSEX);

    wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
    wnd.lpszMenuName = NULL;
    wnd.cbClsExtra = 0;
    wnd.cbWndExtra = 0;

    wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);

    if(!RegisterClassEx(&wnd))
    {
        return 0;
    }

    hwnd = CreateWindowEx(
            (DWORD)NULL,
            szClassName,
            "Lab3",
            WS_OVERLAPPED | WS_BORDER | WS_SYSMENU,
            CW_USEDEFAULT, CW_USEDEFAULT,
            800, 600,
            NULL,
            NULL,
            hInst,
            NULL);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int widthFirstColorBox   = 281;
    int heightFirstColorBox   = 55;
    int widthSecondColorBox = 281;
    int heightSecondColorBox = 105;

    HBITMAP bmpExercising;
    HDC hDC, MemDCExercising;



    static HWND AllTools;
    static HWND lineTool;
    static HWND eraserTool;
    static HWND penTool;
    static HWND ellipseTool;
    static HWND fillColorChecker;
    static HWND brushSize;
    static HWND eraserSize;
    static HWND rectTool;
    static HWND allConfiguration;
    static HWND bezierLineTool;
    RECT rect ;
    int windowWidth;
    int windowHeight;
    PAINTSTRUCT ps;
    HDC hdc = GetDC(hwnd);
    int mouseX, mouseY;


    HDC hdcMem;
    BITMAP bitmap;
    HBITMAP hbmpDesignerImage = NULL;
    GetObject(hbmpDesignerImage, sizeof(bitmap), &bitmap);

    static RECT drawingArea = {17, 180, 780, 550};
    static RECT fillColorRect = {widthFirstColorBox, heightFirstColorBox, widthFirstColorBox + 25, heightFirstColorBox + 30};
    static RECT borderColorRect = {widthSecondColorBox, heightSecondColorBox, widthSecondColorBox + 25, heightSecondColorBox + 20};
    static RECT tempRectangle;

    HBRUSH hBrush;
    static POINT pointPen;
    POINT point;
    HPEN linePen;
    int width;

    static BOOL lineGo;
    static POINT line;
    static BOOL rectangleGo;
    static RECT rectangle;
    static BOOL ellipseGo;
    static RECT ellipse;
    static int bezierFirst = 0;
    static POINT bezierPoints[4];

    HPEN borderPen;
    HBRUSH fillBrush;

    switch(msg)
    {
        case WM_CREATE:


            AllTools = CreateWindowEx(
                    0,
                    "Button",
                    "Tools",
                    WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                    15, 10,
                    140, 150,
                    hwnd,
                    (HMENU)ALL_TOOLS,
                    hInst,
                    NULL);

            penTool = CreateWindowEx(
                    0,
                    "Button",
                    "Pencil",
                    WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                    10, 20,
                    120, 20,
                    AllTools,
                    (HMENU)PENCIL_T,
                    hInst,
                    NULL);
            Button_SetCheck(penTool, BST_CHECKED);

            ellipseTool = CreateWindowEx(
                    0,
                    "Button",
                    "Ellipse",
                    WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,

                    10, 80,
                    120, 20,

                    AllTools,
                    (HMENU)ELLIPSE_T,
                    hInst,
                    NULL);

            rectTool = CreateWindowEx(
                    0,
                    "Button",
                    "Rectangle",
                    WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                    10, 60,
                    120, 20,
                    AllTools,
                    (HMENU)RECTANGLE_T,
                    hInst,
                    NULL);

            lineTool = CreateWindowEx(
                    0,
                    "Button",
                    "Line",
                    WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,

                    10, 40,
                    120, 20,
                    AllTools,
                    (HMENU)LINE_T,
                    hInst,
                    NULL);

            bezierLineTool = CreateWindowEx(
                    0,
                    "Button",
                    "Bezier Line",
                    WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                    10, 100,
                    120, 20,
                    AllTools,
                    (HMENU)ERASER_T,
                    hInst,
                    NULL);

            eraserTool = CreateWindowEx(
                    0,
                    "Button",
                    "Eraser",
                    WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                    10, 120,
                    120, 20,
                    AllTools,
                    (HMENU)ERASER_T,
                    hInst,
                    NULL);

            allConfiguration = CreateWindowEx(
                    0,
                    "Button",
                    "Settings",
                    WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                    180, 10,
                    140, 150,
                    hwnd,
                    (HMENU)ALL_TOOLS,
                    hInst,
                    NULL);

            fillColorChecker = CreateWindowEx(
                    0,
                    "Button",
                    "Fill figure",
                    WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                    10, 20,
                    120, 20,
                    allConfiguration,
                    (HMENU)FILL_COLOR_CHECKER,
                    hInst,
                    NULL);

            CreateWindowEx(
                    0,
                    "Static",
                    "Fill color",
                    WS_VISIBLE | WS_CHILD | SS_LEFT,
                    10, 45,
                    90, 20,
                    allConfiguration,
                    (HMENU)0,
                    hInst,
                    NULL);

            CreateWindowEx(
                    0,
                    "Static",
                    "Border Size",
                    WS_VISIBLE | WS_CHILD | SS_LEFT,
                    10, 70,
                    100, 20,
                    allConfiguration,
                    (HMENU)0,
                    hInst,
                    NULL);

            brushSize = CreateWindowEx(
                    0,
                    "Edit",
                    "10",
                    WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                    100, 70,
                    25, 20,
                    allConfiguration,
                    (HMENU)0,
                    hInst,
                    NULL);

            CreateWindowEx(
                    0,
                    "Static",
                    "Border color",
                    WS_VISIBLE | WS_CHILD | SS_LEFT,
                    10, 95,
                    90, 20,
                    allConfiguration,
                    (HMENU)0,
                    hInst,
                    NULL);

            CreateWindowEx(
                    0,
                    "Static",
                    "Eraser Size",
                    WS_VISIBLE | WS_CHILD | SS_LEFT,
                    10, 120,
                    100, 20,
                    allConfiguration,
                    (HMENU)0,
                    hInst,
                    NULL);

            eraserSize = CreateWindowEx(
                    0,
                    "Edit",
                    "30",
                    WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                    100, 120,
                    25, 20,
                    allConfiguration,
                    (HMENU)0,
                    hInst,
                    NULL);

            SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(128, 128, 128)));
            InvalidateRect(hwnd, NULL, TRUE);
            UpdateWindow(hwnd);

        break;

        case WM_PAINT:

            hDC = BeginPaint(hwnd, &ps);

            // Load the bitmap from the resource
            bmpExercising = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EXERCISING));
            // Create a memory device compatible with the above DC variable
            MemDCExercising = CreateCompatibleDC(hDC);
            // Select the new bitmap
            SelectObject(MemDCExercising, bmpExercising);

            // Copy the bits from the memory DC into the current dc
            BitBlt(hDC, 10, 10, 450, 400, MemDCExercising, 0, 0, SRCCOPY);

            // Restore the old bitmap
            DeleteDC(MemDCExercising);
            DeleteObject(bmpExercising);
            EndPaint(hwnd, &ps);

            updateColorControls(hdc, fillColor, widthFirstColorBox, heightFirstColorBox);
            updateColorControls(hdc, borderColor, widthSecondColorBox, heightSecondColorBox);

            hdcMem = CreateCompatibleDC(hdc);
            SelectObject(hdcMem, hbmpDesignerImage);
            BitBlt(hdc, 15, 340, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
            DeleteDC(hdcMem);

            SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0,0,0)));
            SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
            Rectangle(hdc, drawingArea.left, drawingArea.top, drawingArea.right, drawingArea.bottom);

            EndPaint(hwnd, &ps);
            break;


        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                default:
                    DefWindowProc(hwnd, WM_COMMAND, wParam, lParam);
                    break;
            }
            break;


        case WM_LBUTTONDOWN:
            mouseX = GET_X_LPARAM(lParam);
            mouseY = GET_Y_LPARAM(lParam);

            if(mouseX >= fillColorRect.left && mouseX <= fillColorRect.right)
            {
                if(mouseY >= fillColorRect.top && mouseY <= fillColorRect.bottom)
                {
                    fillColor = colorSelect(hwnd, fillColor);
                    updateColorControls(hdc, fillColor, widthFirstColorBox, heightFirstColorBox);
                }
                else if(mouseY >= borderColorRect.top && mouseY <= borderColorRect.bottom)
                {
                    borderColor = colorSelect(hwnd, borderColor);
                    updateColorControls(hdc, borderColor, widthFirstColorBox, heightFirstColorBox);
                }
                return 0;
            }

            if( (mouseX > drawingArea.left) && (mouseX < drawingArea.right) &&
                (mouseY > drawingArea.top) && (mouseY < drawingArea.bottom) )
            {
                width = getFromInput(brushSize);
                point = getCurrentPointPosition(mouseX, mouseY, drawingArea, width);
                mouseX = point.x;
                mouseY = point.y;

                if((wParam == MK_LBUTTON) && (Button_GetCheck(bezierLineTool) == BST_CHECKED))
                {
                    if(bezierFirst == 0)
                    {
                        bezierPoints[0] = point;
                        bezierFirst = 1;
                    }
                    else
                    {
                        bezierPoints[2] = point;
                        bezierFirst = 3;
                    }
                }
                if((wParam == MK_LBUTTON) && (Button_GetCheck(penTool) == BST_CHECKED))
                {
                    pointPen.x = mouseX;
                    pointPen.y = mouseY;
                }

                if((wParam == MK_LBUTTON) && (Button_GetCheck(rectTool) == BST_CHECKED))
                {
                    rectangle.left = mouseX;
                    rectangle.top = mouseY;
                    rectangleGo = true;
                }
                if((wParam == MK_LBUTTON) && (Button_GetCheck(lineTool) == BST_CHECKED))
                {
                    line.x = mouseX;
                    line.y = mouseY;
                    lineGo = true;
                }

                if((wParam == MK_LBUTTON) && (Button_GetCheck(ellipseTool) == BST_CHECKED))
                {
                    ellipse.left = mouseX;
                    ellipse.top = mouseY;
                    ellipseGo = true;
                }
            }
            break;

        case WM_LBUTTONUP:
            mouseX = GET_X_LPARAM(lParam);
            mouseY = GET_Y_LPARAM(lParam);
            width = getFromInput(brushSize);
            point = getCurrentPointPosition(mouseX, mouseY, drawingArea, width);
            mouseX = point.x;
            mouseY = point.y;

            borderPen = CreatePen(PS_SOLID, width, borderColor);
            if(Button_GetCheck(fillColorChecker) == BST_CHECKED)
                fillBrush = CreateSolidBrush(fillColor);
            else
                fillBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

            if(lineGo)
            {
                SelectObject(hdc, borderPen);
                MoveToEx(hdc, mouseX, mouseY, NULL);
                LineTo(hdc, line.x, line.y);
                DeleteObject(borderPen);
                lineGo = false;
            }

            if(rectangleGo)
            {
                SelectObject(hdc, borderPen);
                SelectObject(hdc, fillBrush);
                Rectangle(hdc, rectangle.left, rectangle.top, mouseX, mouseY);

                DeleteObject(borderPen);
                DeleteObject(fillBrush);

                rectangleGo = false;
            }

            if(ellipseGo)
            {
                SelectObject(hdc, borderPen);
                SelectObject(hdc, fillBrush);

                Ellipse(hdc, ellipse.left, ellipse.top, mouseX, mouseY);
                DeleteObject(borderPen);
                DeleteObject(fillBrush);

                ellipseGo = false;
            }

            if(bezierFirst == 1)
            {
                bezierPoints[1] = point;
                bezierFirst = 2;
            }

            if(bezierFirst == 3)
            {
                bezierPoints[3] = point;
                bezierFirst = 0;
                SelectObject(hdc, borderPen);
                PolyBezier(hdc, bezierPoints, 4);
                DeleteObject(borderPen);
            }
            break;

        case WM_MOUSEMOVE:
            mouseX = GET_X_LPARAM(lParam);
            mouseY = GET_Y_LPARAM(lParam);
            if( (mouseX > drawingArea.left) && (mouseX < drawingArea.right) &&
                (mouseY > drawingArea.top) && (mouseY < drawingArea.bottom) )
            {
                if((wParam == MK_LBUTTON) && (Button_GetCheck(penTool) == BST_CHECKED))
                {
                    width = getFromInput(brushSize);
                    point = getCurrentPointPosition(mouseX, mouseY, drawingArea, width);
                    mouseX = point.x;
                    mouseY = point.y;
                    linePen = CreatePen(PS_SOLID, width, borderColor);
                    SelectObject(hdc, linePen);
                    MoveToEx(hdc, mouseX, mouseY, NULL);
                    LineTo(hdc, pointPen.x, pointPen.y);
                    DeleteObject(linePen);
                    pointPen.x = mouseX;
                    pointPen.y = mouseY;
                }

                if((wParam == MK_LBUTTON) && (Button_GetCheck(eraserTool) == BST_CHECKED))
                {
                    width = getFromInput(eraserSize);
                    point = getCurrentPointPosition(mouseX, mouseY, drawingArea, width);
                    mouseX = point.x;
                    mouseY = point.y;
                    rect.left = point.x - (width / 2);
                    rect.right = point.x + (width / 2);
                    rect.top = point.y - (width / 2);
                    rect.bottom = point.y + (width / 2);
                    InvalidateRect(hwnd, &rect, FALSE);
                    SendMessage(hwnd, WM_PAINT, 0, 0);
                }
            }

            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void updateColorControls(HDC hdc, COLORREF rgb, int xLeft, int yTop)
{
    HBRUSH hBrush = CreateSolidBrush(rgb);
    HPEN hPen = CreatePen(PS_INSIDEFRAME, 2, RGB(10, 40, 140));

    SelectObject(hdc, hBrush);
    SelectObject(hdc, hPen);

    Rectangle(hdc, xLeft, yTop, xLeft + 25, yTop + 20);

    hBrush = CreateSolidBrush(RGB(10, 40, 140));
    SelectObject(hdc, hBrush);

    Rectangle(hdc, xLeft+18, yTop+13, xLeft + 25, yTop + 20);

    DeleteObject(hPen);
    DeleteObject(hBrush);
}

int getFromInput(HWND input)
{
    int result, len;
    len = SendMessage(input, WM_GETTEXTLENGTH, 0, 0);

    char * temp = (char *)malloc(len + 1);
    SendMessage(input, WM_GETTEXT, len + 1, (LPARAM)temp);
    result = atoi(temp);
    free(temp);
    return result;
}

POINT getCurrentPointPosition(int mouseX, int mouseY, RECT limit, int width)
{
    POINT result;
    width = width / 2 + 1;

    if(mouseX + width > limit.right)
        result.x = limit.right - width;
    else if(mouseX - width < limit.left)
        result.x = limit.left + width;
    else
        result.x = mouseX;

    if(mouseY - width < limit.top)
        result.y = limit.top + width;
    else if(mouseY + width > limit.bottom)
        result.y = limit.bottom - width;
    else
        result.y = mouseY;

    return result;
}
