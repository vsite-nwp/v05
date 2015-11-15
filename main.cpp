#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include<list>

class MainWindow : public Window
{
protected:
	std::list<POINT> lists;
	std::list<POINT>::iterator it;
	void OnPaint(HDC hdc)  
	{
	
	// TODO: iterate over points in container and draw polyline
	}
	void OnLButtonDown(POINT p) 
	{
		lists.push_back(p);
	// TODO: add point to container
	}
	void OnKeyDown(int vk) 
	{
		switch (vk) {
		case VK_ESCAPE:
			lists.clear();
			break;
		case VK_BACK:
			lists.pop_back();
			break;
		default:
			return;
		}
		
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
