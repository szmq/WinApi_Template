#include <Windows.h>

// DECLARATIONS
//////////////////////////////////////////////////
ATOM RegisterWndClass(char* pszClassName, WNDPROC fpWndProc);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HWND CreateAppWindow(int iPosX, int iPosY, int iWidth, int iHeight, 
					 char* gc_pszClassName, char* gc_pszWindowName, bool bAdjust,
					 unsigned long ulWndStyle, unsigned long ulExWndStyle);

// DEFINITIONS
//////////////////////////////////////////////////
char* const gc_pszClassName = "AppWindow";
char* const gc_pszWindowTitle = "WindowTitle";

// WinMain
//////////////////////////////////////////////////
int WINAPI WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR pCmdLine, int iCmdShow)
{
	/* MessageBox(NULL, "Welcome Windows! \n"
					 "WinApi, yea!.", "Information :)", MB_OK); */ 

	RegisterWndClass(gc_pszClassName, WndProc);
	
	HWND hWnd = NULL;
	hWnd = CreateAppWindow( 100, 100, 640, 480, gc_pszClassName,
		gc_pszWindowTitle, false, WS_OVERLAPPEDWINDOW, 0);

	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);
	
	MSG Msg = {0};
   for(;;)
   {
      if(GetMessage(&Msg, NULL, 0, 0) != 0)
      {
         TranslateMessage(&Msg);
         DispatchMessage(&Msg);
      } else break;
   } // end for

   UnregisterClass(gc_pszClassName, hInstance);
   return (int)Msg.wParam;
}

// REGISTER CLASS
ATOM RegisterWndClass(char* pszClassName, WNDPROC fpWndProc)
{
	WNDCLASSEX WndClassEx = {0};

	WndClassEx.cbSize = sizeof(WNDCLASSEX);
	WndClassEx.hInstance = GetModuleHandle(NULL);
	WndClassEx.lpszClassName = pszClassName;
	WndClassEx.lpfnWndProc = fpWndProc;
	WndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	WndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClassEx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WndClassEx.lpszMenuName = NULL;
    WndClassEx.cbClsExtra = 0;
    WndClassEx.cbWndExtra = 0;
    WndClassEx.hIconSm = NULL;
	
	return RegisterClassEx(&WndClassEx); 
}

// CREATE WINDOW
HWND CreateAppWindow(int iPosX, int iPosY, int iWidth, int iHeight, 
					 char* gc_pszClassName, char* gc_pszWindowName, bool bAdjust,
					 unsigned long ulWndStyle, unsigned long ulExWndStyle)
{
	RECT WndRect = {0, 0, iWidth, iHeight};
	if(bAdjust)
		AdjustWindowRectEx(&WndRect, ulWndStyle, false, ulExWndStyle);

	HWND hWnd = NULL;
	hWnd = CreateWindowEx( ulExWndStyle, gc_pszClassName, gc_pszWindowName,
		ulWndStyle, iPosX, iPosY,
		WndRect.right - WndRect.left, WndRect.bottom - WndRect.top,
		NULL, NULL, GetModuleHandle(NULL), NULL);
	
	return hWnd;
}

// LRESULT CALLBACK 
LRESULT CALLBACK WndProc(
   HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   // REMEMBER STATIC = GOOD CODE //

   switch(message)
   {
      case WM_CLOSE:
         if(IDYES == MessageBox(hWnd,
            "Do you really want to exit?", "REALLY?!",
            MB_YESNO | MB_ICONQUESTION))
            return DefWindowProc(hWnd, message, wParam, lParam);
         else return 0;
     
     case WM_DESTROY:
         PostQuitMessage(0);
         return 0;
   }
   return DefWindowProc(hWnd, message, wParam, lParam);
   }

