#include <windows.h>
#include <tchar.h>
#include <list>
#include "nwpwin.h"

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
		InvalidateRect(*this, nullptr, TRUE);
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
