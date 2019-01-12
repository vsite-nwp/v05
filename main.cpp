#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>
#include <iterator>

class MainWindow : public Window
{
	std::list<POINT> points;

protected:
	void OnPaint(HDC hdc)  
	{
		int i = 0;
		for (std::list<POINT>::const_iterator it = points.begin(); it != points.end(); ++it) {
			if (i == 0) {
				MoveToEx(hdc, it->x, it->y, nullptr);
			}
			else {
				LineTo(hdc, it->x, it->y);
			}
			++i;
		}
	}
	void OnLButtonDown(POINT p) 
	{
		points.push_back(p);
		InvalidateRect(nullptr, nullptr, true);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk) {
		case VK_ESCAPE:
			points.clear();
			InvalidateRect(nullptr, nullptr, true);
			break;
		case VK_BACK:
			if (!points.empty())
			{
				points.pop_back();
			}
			InvalidateRect(nullptr, nullptr, true);
			break;
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
