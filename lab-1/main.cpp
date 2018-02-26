#if defined(UNICODE) && !defined(_UNICODE)
	#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
	#define UNICODE
#endif
#include <tchar.h>
#include <windows.h>

HWND hList;
HWND hElement;

int count = 0;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("Window Class");

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
	wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
	wincl.cbSize = sizeof (WNDCLASSEX);

	/* Use default icon and mouse-pointer */
	wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;                 /* No menu */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */
	/* Use Windows's default colour as the background of the window */
	wincl.hbrBackground = (HBRUSH) COLOR_WINDOW;
	wincl.style = CS_HREDRAW | CS_VREDRAW; /* Redraw the window after it is resized */

	/* Register the window class, and if it fails quit the program */
	if (!RegisterClassEx (&wincl))
		return 0;

	/* The class is registered, let's create the program*/
	hwnd = CreateWindowEx (
		   0,                   /* Extended possibilites for variation */
		   szClassName,         /* Classname */
		   _T("To do list PRO v11"),       /* Title Text */
		   WS_OVERLAPPEDWINDOW, /* default window */
		   CW_USEDEFAULT,       /* Windows decides the position */
		   CW_USEDEFAULT,       /* where the window ends up on the screen */
		   330,                 /* The programs width */
		   265,                 /* and height in pixels */
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
	switch (message)                  /* handle the messages */
	{
		case WM_CREATE: {

			HWND hButtonAdd = CreateWindowEx(NULL,
				"BUTTON",
				"ADD",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON|BS_TOP,
				10,
				40,
				100,
				25,
				hwnd,
				(HMENU)101,
				GetModuleHandle(NULL),
				NULL);

			HFONT hFont = CreateFont(30,0,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, TEXT("Impact"));
			HWND hButtonAlert = CreateWindowEx(NULL,
				"BUTTON",
				"Alert",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON|BS_TOP,
				10,
				180,
				300,
				40,
				hwnd,
				(HMENU)102,
				GetModuleHandle(NULL),
				NULL);
			SendMessage (hButtonAlert, WM_SETFONT, WPARAM (hFont), TRUE);

			hList = CreateWindowEx(WS_EX_CLIENTEDGE,
				"EDIT",
				"",
				WS_CHILD|WS_VISIBLE|WS_VSCROLL|ES_READONLY|
				ES_MULTILINE,
				10,
				70,
				300,
				100,
				hwnd,
				(HMENU)103,
				GetModuleHandle(NULL),
				NULL);

			hFont = CreateFont(25,0,0,0,FW_DONTCARE,TRUE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, TEXT("Monotype Corsiva"));
			hElement = CreateWindowEx(
				(DWORD)NULL,
				TEXT("edit"),
				"Input",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				120,
				40,
				190,
				25,
				hwnd,
				(HMENU)104,
				GetModuleHandle(NULL),
				NULL);
			SendMessage (hElement, WM_SETFONT, WPARAM (hFont), TRUE);
		}
		break;

		case WM_PAINT: {
			HDC hdc = BeginPaint(hwnd, &Ps);
			RECT rect;
			// Second Text
			GetClientRect (hwnd, &rect) ;
			SetBkMode(hdc, TRANSPARENT);
			DrawText(hdc, TEXT("To do LIST"), -1, &rect, DT_SINGLELINE | DT_NOCLIP | DT_CENTER  ) ;

			// First Text
			HFONT hFont = CreateFont(25,0,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,NULL, VARIABLE_PITCH,TEXT("Impact"));
			SetRect(&rect, 10, 10, 50, 50);
			SelectObject(hdc, hFont);
			SetBkMode(hdc, OPAQUE);
			SetBkColor(hdc, RGB(50,100,20));
			SetTextColor(hdc, RGB(255,100,40));
			DrawText(hdc, TEXT("!sad things to do:"), -1,&rect, DT_NOCLIP);

			EndPaint(hwnd, &Ps);
		}
		break;

		case WM_COMMAND: {
			switch(LOWORD(wParam)) {
				case 101: {

					char buffer[256];
					SendMessage(hElement,
						WM_GETTEXT,
						sizeof(buffer)/sizeof(buffer[0]),
						reinterpret_cast<LPARAM>(buffer));

					if(strlen(buffer) > 0){
						char newInput[255] = "";
						char stat[30];
						strcat(newInput, itoa((count+1), stat, 10) );
						strcat(newInput, " ) ");
						strcat(newInput, buffer);
						if (!strcmp(buffer, "exit"))
							PostQuitMessage (0);
						strcat(newInput, "\r\n");

						SendMessage(hList, EM_REPLACESEL, FALSE, (LPARAM)newInput);
						SendMessage(hElement, WM_SETTEXT, NULL, (LPARAM)"");
						count++;
					}

				}
				break;

				case 102: {
					if (MessageBox(hwnd, TEXT("Destroy Window?"), TEXT("Close"), MB_YESNO) == IDYES)
						DestroyWindow(GetDlgItem(hwnd, 102));
				}
				break;
			}
		}
		break;

		case WM_SIZE: {
			INT nWidth = LOWORD(lParam);
			INT nHeight = HIWORD(lParam);
			HWND hButtonAlert = GetDlgItem(hwnd, 102);

			MoveWindow(hButtonAlert, 10, nHeight - 45, nWidth - 17, 40, TRUE);

			HWND hlist = GetDlgItem(hwnd, 103);
			HWND helement = GetDlgItem(hwnd, 104);

			MoveWindow(hlist, 10, 70, nWidth - 20, nHeight - 120, TRUE);
			MoveWindow(helement, 120, 40, nWidth - 130, 25, TRUE);
		}
		break;

		case WM_GETMINMAXINFO: {
			MINMAXINFO * mmiStruct;
			mmiStruct = (MINMAXINFO*)lParam;

			POINT ptPoint;

			ptPoint.x = 330;    //Minimum width of the window.
			ptPoint.y = 265;    //Minimum height of the window.
			mmiStruct->ptMinTrackSize = ptPoint;

			ptPoint.x = GetSystemMetrics(SM_CXMAXIMIZED);   //Maximum width of the window.
			ptPoint.y = GetSystemMetrics(SM_CYMAXIMIZED);   //Maximum height of the window.
			mmiStruct->ptMaxTrackSize = ptPoint;
		}
		break;

		case WM_CLOSE: {
			if (MessageBox(hwnd, TEXT("Do you want to exit?"), TEXT("Realy?"), MB_YESNO) == IDYES)
			{
				MessageBox(hwnd, TEXT("I don't see that in the list! ('exit')"), TEXT("You fool"), MB_OK);
			}
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
