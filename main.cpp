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
		//version 1) range for
		for (POINT p : points)
		{
			if (p.x==points.front().x && p.y==points.front().y)
				::MoveToEx(hdc, points.front().x, points.front().y, nullptr);
			else
			{
				::LineTo(hdc,p.x,p.y);
			}
		}
		//version 2) iterator
		/*for (auto it = points.begin(); it != points.end(); ++it)
			if (it==points.begin())
				::MoveToEx(hdc, points.front().x, points.front().y, nullptr);
			else
			{
				::LineTo(hdc,it->x,it->y);
			}*/
	}
	void OnLButtonDown(POINT p) 
	{
		points.push_back(p);
		InvalidateRect(*this, NULL, TRUE);
	}
	void OnKeyDown(int vk) 
	{
		if (vk == VK_ESCAPE)
			points.erase(points.begin(),points.end());
		if (vk == VK_BACK)
			points.pop_back();
		InvalidateRect(*this,NULL,TRUE);
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
