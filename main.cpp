#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <algorithm>
#include <list>

class MainWindow : public Window
{
    std::list<POINT> points;
protected:
	void OnPaint(HDC hdc)  
	{ 
	// TODO: iterate over points in container and draw polyline
		if (points.empty())
			return;
		POINT s = points.front();
		MoveToEx(hdc,s.x,s.y, nullptr);
		for (const auto& p : points) {
			LineTo(hdc, p.x, p.y);
		}
	}
	void OnLButtonDown(POINT p) 
	{
	// TODO: add point to container
		points.push_back(p);
		InvalidateRect(*this, nullptr, true);
	}
	void OnKeyDown(int vk) 
	{
	// TODO: Esc - empty container
	// TODO: Backspace - remove last point
		switch(vk) {
			case VK_ESCAPE:
				points.clear();
				break;
			case VK_BACK:
				points.pop_back();
				break;
			default:
				return;
		}
		InvalidateRect(*this, nullptr, true);
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
