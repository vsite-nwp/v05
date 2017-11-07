#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>
#include <algorithm>

class MainWindow : public Window
{
	std::list<POINT> tocke;
protected:
	void OnPaint(HDC hdc)  
	{ 
	// iterate over points in container and draw polyline
		if (tocke.empty())
			return;

		POINT begin = tocke.front();
		MoveToEx(hdc, begin.x, begin.y, 0);
		for (std::list<POINT>::iterator it = tocke.begin(); it != tocke.end();it++)
		{
			LineTo(hdc, it->x, it->y);
		}
	}
	void OnLButtonDown(POINT p) 
	{
	// add point to container
		tocke.push_back(p);
		InvalidateRect(*this, 0, TRUE);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk)
		{
		case VK_ESCAPE:
			tocke.clear();
			break;
		case VK_BACK:
			if(!tocke.empty())
				tocke.pop_back();
		default:
			break;
		}
		InvalidateRect(*this, 0, true);
	// Esc - empty container
	// Backspace - remove last point
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
