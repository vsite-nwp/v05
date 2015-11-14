#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include<list>
typedef std::list<POINT>list;
typedef list::const_iterator iterator;
class MainWindow : public Window
{
	list points;
protected:
	void OnPaint(HDC hdc)  
	{ 
	// iterate over points in container and draw polyline
		for (iterator iter = points.begin(); iter != points.end();++iter)
		{
			if (iter == points.begin())
				MoveToEx(hdc, iter->x, iter->y, 0);
			else
				LineTo(hdc, iter->x, iter->y);
		}
			
	}
	void OnLButtonDown(POINT p) 
	{
	// TODO: add point to container
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
