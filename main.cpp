#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>
#include<algorithm>

class MainWindow : public Window
{
	std::list<POINT> pts;
protected:
	void OnPaint(HDC hdc)  
	{ 
		if (pts.empty())
			return;
		::MoveToEx(hdc, pts.front().x, pts.front().y, nullptr);
		for (const auto& p : pts) {
			::LineTo(hdc, p.x, p.y);
		}
	}
	void OnLButtonDown(POINT p) 
	{
		pts.push_back(p);
		::InvalidateRect(*this, nullptr, false);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk) {

		case VK_ESCAPE:pts.clear();
			::InvalidateRect(*this, nullptr, true);
			break;
		case VK_BACK:
			if (!pts.empty()) {
				pts.pop_back();
				::InvalidateRect(*this, nullptr, true);
			}
			break;
		default:
			return;
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
