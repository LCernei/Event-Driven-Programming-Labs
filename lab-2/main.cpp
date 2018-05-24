#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include "includes.h"

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

UINT bgBrush = WHITE_BRUSH;

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("WindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = (HICON) LoadImage(
      NULL,
      "./Mario.ico",
      IMAGE_ICON,
      0,
      0,
      LR_LOADFROMFILE| LR_DEFAULTSIZE | LR_SHARED
    );
    wincl.hIconSm = NULL;
    wincl.hCursor = LoadCursorFromFile("./Mario.cur");//LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
    wincl.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
		   0,                   /* Extended possibilites for variation */
		   szClassName,         /* Classname */
		   _T("Lab#2"),       /* Title Text */
		   WS_OVERLAPPEDWINDOW, /* default window */
		   0,       /* Windows decides the position */
		   0,       /* where the window ends up on the screen */
		   420,                 /* The programs width */
		   280,                 /* and height in pixels */
		   HWND_DESKTOP,        /* The window is a child-window to desktop */
		   NULL,                /* No menu */
		   hThisInstance,       /* Program Instance handler */
		   NULL                 /* No Window Creation data */
		);

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT Ps;
    HWND handle;
    int xNewPos;
    RECT window;
    int screenWidth = GetDeviceCaps(GetDC(NULL), HORZRES);
    int screenHeight = GetDeviceCaps(GetDC(NULL), VERTRES);
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            HMENU hMenu, hSubMenu;
            hMenu = CreateMenu();

            hSubMenu = CreatePopupMenu();
            AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

            hSubMenu = CreatePopupMenu();
            AppendMenu(hSubMenu, MF_STRING, ID_GO, "&Go");
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Go");
            SetMenu(hwnd, hMenu);

            GetWindowRect(hwnd, &window);

            handle = CreateWindowEx(
                    0,"scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
                    20, 50, 150, 20, hwnd, (HMENU)ID_RED, NULL, NULL);
            SetScrollRange(handle, SB_CTL, 0, 254, TRUE);
            SetScrollPos(handle, SB_CTL, 212, TRUE);

            handle = CreateWindowEx(
                    0,"scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
                    20, 115, 150, 20, hwnd, (HMENU)ID_GREEN, NULL, NULL);
            SetScrollRange(handle, SB_CTL, 0, 254, TRUE);
            SetScrollPos(handle, SB_CTL, 207, TRUE);

            handle = CreateWindowEx(
                    0,"scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
                    20, 180, 150, 20, hwnd, (HMENU)ID_BLUE, NULL, NULL);
            SetScrollRange(handle, SB_CTL, 0, 254, TRUE);
            SetScrollPos(handle, SB_CTL, 201, TRUE);

            handle = CreateWindowEx(
                    0, "scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
                    20, 10, 330, 30, hwnd, (HMENU)ID_WIDTH, NULL, NULL);
            SetScrollRange(handle, SB_CTL, 420*100/screenWidth, 100, TRUE);
            SetScrollPos(handle, SB_CTL, 0, TRUE);

            handle = CreateWindowEx(
                    0, "scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_VERT,
                    360, 50, 30, 150, hwnd, (HMENU)ID_HEIGHTH, NULL, NULL);
            SetScrollRange(handle, SB_CTL, 265*100/screenHeight, 100, TRUE);
            SetScrollPos(handle, SB_CTL, 0, TRUE);

            handle = CreateWindow("LISTBOX", NULL,
                                    WS_CHILD | WS_VISIBLE,
                                    200, 80, 150, 70,
                                    hwnd,(HMENU) LIST_BOX, NULL, NULL);

            handle = CreateWindow("EDIT",NULL,
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    200, 50, 100, 25,
                                    hwnd, (HMENU) EDIT, NULL, NULL);

            handle = CreateWindow("Button", "New",
                                  WS_VISIBLE | WS_CHILD,
                                  300, 50, 50, 25,
                                  hwnd, (HMENU) BUTTON_ADD, NULL, NULL);

            handle = CreateWindow("Button", "Clean",
                                  WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                  200, 175, 150, 25,
                                  hwnd, (HMENU) BUTTON_CLEAN, NULL, NULL);

            handle = CreateWindow("Button", "Remove",
                                  WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                  200, 150, 150, 25,
                                  hwnd, (HMENU) BUTTON_REMOVE, NULL, NULL);

            handle = CreateWindow("Static", "2",
                                  WS_VISIBLE | WS_CHILD,
                                  180, 80, 10, 15,
                                  hwnd, (HMENU) IDC_SHOWCOUNT, NULL, NULL);

            RegisterHotKey(hwnd, ALT_ENTER, MOD_ALT, VK_RETURN);
            RegisterHotKey(hwnd, CTRL_SPACE, MOD_CONTROL, ' ');
            break;

        case WM_PAINT: {
			HDC hdc = BeginPaint(hwnd, &Ps);
			RECT rect;
			SetBkMode(hdc, TRANSPARENT);
			SetRect(&rect, 5, 15, 50, 50);
			DrawText(hdc, TEXT("W"), -1,&rect, DT_NOCLIP);
			SetRect(&rect, 5, 50, 50, 50);
			DrawText(hdc, TEXT("R"), -1,&rect, DT_NOCLIP);
			SetRect(&rect, 5, 115, 50, 50);
			DrawText(hdc, TEXT("G"), -1,&rect, DT_NOCLIP);
            SetRect(&rect, 5, 180, 50, 50);
			DrawText(hdc, TEXT("B"), -1,&rect, DT_NOCLIP);
			SetRect(&rect, 367, 25, 50, 50);
			DrawText(hdc, TEXT("H"), -1,&rect, DT_NOCLIP);
			EndPaint(hwnd, &Ps);
		}
		break;

        case WM_HSCROLL:
            static int r = 212, g = 207, b = 201, newWidth = 0;
            GetWindowRect(hwnd, &window);

            handle = (HWND)lParam;
            xNewPos = GetScrollPos(handle, SB_CTL);
            switch(LOWORD(wParam))
            {
                case SB_LINELEFT:
                    xNewPos--;
                break;

                case SB_LINERIGHT:
                    xNewPos++;
                break;

                case SB_THUMBPOSITION:
                    xNewPos = HIWORD(wParam);
                break;
            }

            switch(GetDlgCtrlID((HWND)lParam))
            {
                case ID_RED:
                    r = xNewPos;
                    break;
                case ID_GREEN:
                    g = xNewPos;
                    break;
                case ID_BLUE:
                    b = xNewPos;
                    break;
                case ID_WIDTH:
                    newWidth = screenWidth * xNewPos / 100;
                    break;
            }
            MoveWindow(hwnd, 0, 0, newWidth, window.bottom - window.top, TRUE);

            SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(r, g, b)));
            InvalidateRect(hwnd, NULL, TRUE);
            UpdateWindow(hwnd);

            SetScrollPos(handle, SB_CTL, xNewPos, TRUE);
        break;

        case WM_VSCROLL:
            static int newHeight = 0;
            GetWindowRect(hwnd, &window);

            handle = (HWND)lParam;
            xNewPos = GetScrollPos(handle, SB_CTL);
            switch(LOWORD(wParam))
            {
                case SB_LINELEFT:
                    xNewPos--;
                break;

                case SB_LINERIGHT:
                    xNewPos++;
                break;

                case SB_THUMBPOSITION:
                    xNewPos = HIWORD(wParam);
                break;
            }

            switch(GetDlgCtrlID((HWND)lParam))
            {
                case ID_HEIGHTH:
                    newHeight = screenHeight * xNewPos / 100;
                    break;
            }
            MoveWindow(hwnd, 0, 0, window.right - window.left, newHeight, TRUE);
            SetScrollPos(handle, SB_CTL, xNewPos, TRUE);
        break;

        case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			    case ID_FILE_EXIT:
					PostQuitMessage (0);
				break;

				case ID_GO:
                    MessageBox(NULL, "Go", "Go", MB_OK);
                break;

                case BUTTON_ADD:
                {
                    char name[20];
                    GetDlgItemText(hwnd, EDIT, name, 10);
                    int index = SendDlgItemMessage(hwnd, LIST_BOX, LB_ADDSTRING, 0, (LPARAM)name);
                    SendDlgItemMessage(hwnd, LIST_BOX, LB_SETITEMDATA, (WPARAM)index, 0);
                }
                break;

                case BUTTON_CLEAN:
					SendDlgItemMessage(hwnd, LIST_BOX, LB_RESETCONTENT, 0, 0);
				break;

				case BUTTON_REMOVE:
                    SendDlgItemMessage(hwnd, LIST_BOX, LB_DELETESTRING, 0, 0);
                break;

                case LIST_BOX:
                switch(HIWORD(wParam))
                {
                    case LBN_SELCHANGE:
                        PostQuitMessage (0);
                        HWND hList = GetDlgItem(hwnd, LIST_BOX);
                        int index = SendMessage(hList, LB_GETCURSEL, 0, 0);
                        SetDlgItemInt(hwnd, IDC_SHOWCOUNT, index, FALSE);
                    break;
                }
                break;
			}
		break;

        case WM_HOTKEY:
            switch(wParam)
            {
                case ALT_ENTER:
                    if (!ShowWindow(hwnd, SW_HIDE))
                        ShowWindow(hwnd, SW_RESTORE);
                break;

                case CTRL_SPACE:
                    if (MessageBox(hwnd, TEXT("Do you want to exit?"), TEXT("Close"), MB_YESNO) == IDYES)
                        PostQuitMessage (0);
                break;
            }
        break;

		case WM_GETMINMAXINFO: {
			MINMAXINFO * mmiStruct;
			mmiStruct = (MINMAXINFO*)lParam;

			POINT ptPoint;

			ptPoint.x = 420;    //Minimum width of the window.
			ptPoint.y = 280;    //Minimum height of the window.
			mmiStruct->ptMinTrackSize = ptPoint;

			ptPoint.x = GetSystemMetrics(SM_CXMAXIMIZED);   //Maximum width of the window.
			ptPoint.y = GetSystemMetrics(SM_CYMAXIMIZED);   //Maximum height of the window.
			mmiStruct->ptMaxTrackSize = ptPoint;
		}
		break;

        case WM_CLOSE: {
            MessageBox(hwnd, TEXT("Okay"), TEXT("Close"), MB_OK);
            PostQuitMessage (0);
		}
		break;

        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
