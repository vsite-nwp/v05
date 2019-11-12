#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
	std::list<POINT> list;
protected:
	void OnPaint(HDC hdc)  
	{ 
	// TODO: iterate over points in container and draw polyline
	}
	void OnLButtonDown(POINT p) 
	{
		list.push_back(p);
		InvalidateRect(*this, NULL, true);
	}
	void OnKeyDown(int vk) 
	{
	// TODO: Esc - empty container
	// TODO: Backspace - remove last point
	}
	void OnDestroy()
	{
		::PostQuitMessage(0);
	}
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP 5"));
	return app.Run();
}
