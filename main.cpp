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
		if (points.empty()) return;

		MoveToEx(hdc, points.front().x, points.front().y, nullptr);

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
		switch (vk) {
			case VK_ESCAPE:
				points.clear();
				InvalidateRect(*this, nullptr, TRUE);
				break;
			case VK_BACK:
				if(!points.empty()) {
					points.pop_back();
					InvalidateRect(*this, nullptr, TRUE);
				}
				break;
			default:
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
