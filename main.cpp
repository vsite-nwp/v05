#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
	std::list<POINT> point;
protected:
	void OnPaint(HDC hdc)
	{
		if (point.empty())

			return;
		else

		MoveToEx(hdc, point.front().x, point.front().y, 0);
		for (auto it = point.begin(); it != point.end(); ++it)
		{
			LineTo(hdc, (int)it->x, (int)it->y);
		}
	}
	

	void OnLButtonDown(POINT p) 
	{
		point.push_back(p);
		InvalidateRect(*this, NULL, true);
	}
	void OnKeyDown(int vk)
	{
		switch (vk) {
		case VK_BACK:

			point.pop_back();
			InvalidateRect(*this, nullptr, true);
			break;
		case VK_ESCAPE:

			point.clear();
			InvalidateRect(*this, nullptr, true);
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
