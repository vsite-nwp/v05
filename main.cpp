#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
private:
	std::list<POINT> points;
protected:
	void OnPaint(HDC hdc)  
	{ 
	//  iterate over points in container and draw polyline
		if (!points.empty())
		{
			MoveToEx(hdc, points.front().x, points.front().y, NULL);
			for (std::list<POINT>::iterator it = points.begin(); it != points.end(); ++it)
			{
				LineTo(hdc, it->x, it->y);
			}
		}
	}
	void OnLButtonDown(POINT p) 
	{
	//  add point to container
		points.push_back(p);
		InvalidateRect(*this, NULL, TRUE);
	}
	void OnKeyDown(int vk) 
	{
		if (!points.empty())
		{
			switch (vk)
			{
			case VK_ESCAPE:	//  Esc - empty container
				points.clear();
				InvalidateRect(*this, NULL, TRUE);
				break;
			case VK_BACK:	//  Backspace - remove last point
				points.pop_back();
				InvalidateRect(*this, NULL, TRUE);
				break;
			default:
				break;
			}
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
