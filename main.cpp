#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
	std::list<POINT> points;
protected:
	void OnPaint(HDC hdc)  
	{ 
		if(points.size())
			MoveToEx(hdc, points.begin()->x, points.begin()->y, 0);
		
		for (std::list<POINT>::iterator it = points.begin(); it != points.end(); it++) {
			LineTo(hdc, it->x, it->y);
		}
	}
	void OnLButtonDown(POINT p) 
	{
		InvalidateRect(*this, 0, true);
		points.push_back(p);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk) {
		case VK_ESCAPE: points.clear(); break;
		case VK_BACK:	if (points.size()) { points.pop_back(); } break;
		}
		InvalidateRect(*this, 0, true);
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
