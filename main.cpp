#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
private:
	std::list<POINT> list_points;

protected:
	void OnPaint(HDC hdc)  
	{ 
		std::list<POINT>::iterator iterator;

		if (!list_points.empty())
		{
			MoveToEx(hdc, list_points.front().x, list_points.front().y, NULL);
		}

		for (iterator=list_points.begin();iterator!=list_points.end(); ++iterator)
		{
			LineTo(hdc, iterator->x, iterator->y);
		}
	}
	void OnLButtonDown(POINT p) 
	{
		list_points.push_back(p);
		InvalidateRect(*this, NULL, true);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk)
		{
		case VK_ESCAPE: list_points.clear(); break;
		case VK_BACK:if (list_points.empty()) return;
			list_points.pop_back(); break;
		default: return;
			
		}
		InvalidateRect(*this, NULL, true);
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
