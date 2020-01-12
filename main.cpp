#include <windows.h>
#include <tchar.h>
#include <list>
#include "nwpwin.h"

class MainWindow : public Window
{
	std::list<POINT> points;
protected:
	void OnPaint(HDC hdc)  
	{ 
		int cntr = 0;
		for (POINT p : points)
		{
			if (!cntr) {
				::MoveToEx(hdc, points.front().x, points.front().y, nullptr);
				++cntr;
			}
			else
			{
				::LineTo(hdc,p.x,p.y);
			}
		}
	}
	void OnLButtonDown(POINT p) 
	{
		points.push_back(p);
		InvalidateRect(*this, NULL, TRUE);
	}
	void OnKeyDown(int vk) 
	{
		if (vk == VK_ESCAPE) {
			points.clear();
			InvalidateRect(*this, NULL, TRUE);
		}
		if (vk == VK_BACK && !points.empty()) {
			points.pop_back();
			InvalidateRect(*this, NULL, TRUE);
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
