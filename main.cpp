#include <windows.h>
#include <tchar.h>
#include <list>
#include "nwpwin.h"
#define AREA 10

class MainWindow : public Window
{
private:
	std::list<POINT> points;
protected:
	void OnPaint(HDC hdc)  
	{ 
		if (points.empty())
			return;
		::MoveToEx(hdc, points.front().x, points.front().y, nullptr);
		for (POINT p : points) {
			::LineTo(hdc, p.x, p.y);
		}
	}

	void OnLButtonDown(POINT p) 
	{
		points.push_back(p);
		if (points.size() > 1)
		{
			std::list<POINT>::const_iterator it;
			it =  --(--(points.end()));
			RECT rc = { min(it->x,p.x)-AREA, min(it->y, p.y)-AREA, max(it->x,p.x)+AREA, max(it->y, p.y)+AREA };
			InvalidateRect(*this, &rc, TRUE);
		}
		else 
		{
			InvalidateRect(*this, nullptr, TRUE);
		}
		
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
