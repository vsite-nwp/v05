 #include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <algorithm>
#include <list>

class MainWindow : public Window
{
	std::list<POINT> points;
protected:
	void OnPaint(HDC hdc)  
	{ 
		if (!points.empty()) 
		{
			MoveToEx(hdc, points.front().x,points.front().y,0);
		}
		
		for (POINT p : points) 
		{
			LineTo(hdc, p.x, p.y);
		}
	}
	void OnLButtonDown(POINT p) 
	{
		points.push_back(p);
		InvalidateRect(*this, 0, false);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk)
		{
		case VK_ESCAPE:
			points.clear();
			InvalidateRect(*this, 0, true);
			break;
		case VK_BACK:
			if (!points.empty())
			{
				points.pop_back();
				InvalidateRect(*this, 0, true);
			}
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
