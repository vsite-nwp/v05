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
		if (!points.empty()) {
			MoveToEx(hdc, points.front().x, points.front().y, NULL);
			for (std::list<POINT>::iterator i = points.begin(); i != points.end(); i++) {
				LineTo(hdc, i->x, i->y);
			}
		}
	}
	void OnLButtonDown(POINT p) 
	{
		points.push_back(p);
		InvalidateRect(*this, NULL, FALSE);
	}
	void OnKeyDown(int vk)
	{
			switch (vk) {
			case VK_ESCAPE:
				points.clear();
				break;
			case VK_BACK:
				if (!points.empty())
					points.pop_back();
				break;
			}
			InvalidateRect(*this, NULL, TRUE);
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
