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
		if (!points.empty())
		{
			MoveToEx(hdc, points.front().x, points.front().y, 0);

			for (auto it = points.begin(); it != points.end(); ++it)
			{
				LineTo(hdc, (int)it->x, (int)it->y);
			}
		}
	}
	void OnLButtonDown(POINT p) 
	{
		points.push_back(p);
		InvalidateRect(*this, NULL, true);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk) {
		case VK_ESCAPE:
			points.clear();
			InvalidateRect(*this, NULL, true);
			break;
		case VK_BACK:
			points.pop_back();
			InvalidateRect(*this, NULL, true);
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
