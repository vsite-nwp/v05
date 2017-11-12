#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>
#include <algorithm>

class MainWindow : public Window
{
	std::list<POINT> pointL;
protected:
	void OnPaint(HDC hdc)  
	{ 
		if (!pointL.empty()) {
			MoveToEx(hdc, pointL.front().x, pointL.front().y, 0);
			for (POINT px : pointL)LineTo(hdc, px.x, px.y);
		}
	}
	void OnLButtonDown(POINT p) 
	{
		pointL.push_back(p);
		InvalidateRect(*this,0,true);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk) {
		case VK_BACK:
			if (!pointL.empty()) {
				pointL.pop_back();
				InvalidateRect(*this, 0, true);
			}

			break;
		case VK_ESCAPE:
			if (!pointL.empty()) {
				pointL.clear();
				InvalidateRect(*this, 0, true);
			}
			break;
		default:
			InvalidateRect(*this, 0, true);
		}
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
