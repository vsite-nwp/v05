#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>
#include <algorithm>

class MainWindow : public Window
{
private:
	std::list<POINT> ptslst;
protected:
	void OnPaint(HDC hdc)  
	{ 
		if (ptslst.empty())
			return;
		::MoveToEx(hdc, ptslst.front().x, ptslst.front().y, nullptr);
		for (const POINT& p : ptslst) {
			::LineTo(hdc, p.x, p.y);
		}
	}
	void OnLButtonDown(POINT p) 
	{
		ptslst.push_back(p);
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
