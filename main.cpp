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
	// TODO: iterate over points in container and draw polyline
		 if(points.size()) MoveToEx(hdc, points.front().x, points.front().y, NULL);
		for (std::list<POINT>::iterator it = points.begin(); it != points.end(); it++)
		
			LineTo(hdc, it->x, it->y);
		
	}
	void OnLButtonDown(POINT p) 
	{
	// TODO: add point to container
		points.push_back(p);
		InvalidateRect(*this, NULL, TRUE);
	}
	void OnKeyDown(int vk) 
	{
	// TODO: Esc - empty container
	//TODO: Backspace - remove last point
		if (points.size())
		{
			switch (vk)
			{
			case VK_BACK:
				points.pop_back();
				break;
			case VK_ESCAPE:
				points.clear();

			}
			InvalidateRect(*this, NULL, TRUE);
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
