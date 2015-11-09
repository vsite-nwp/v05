#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <iostream>
#include <list>

class SelObj {
	HDC hdc;
	HGDIOBJ hOld;
public:
	SelObj(HDC hdc, HGDIOBJ hObj) : hdc(hdc), hOld(::SelectObject(hdc, hObj)) { }
	~SelObj() { ::SelectObject(hdc, hOld); }
};


class MainWindow : public Window
{
public:
	std::list<POINT> points;
protected:
	void OnPaint(HDC hdc)  
	{ 
		if(points.size()) MoveToEx(hdc, points.front().x, points.front().y, NULL);
		for (std::list<POINT>::iterator it = points.begin(); it != points.end(); it++)
		{
			LineTo(hdc, it->x, it-> y);
		}
			
	// TODO: iterate over points in container and draw polyline

	}
	void OnLButtonDown(POINT p) 
	{
		points.push_back(p);		
		InvalidateRect(*this, NULL, TRUE);
	}
	void OnKeyDown(int vk) 
	{
		if (vk == VK_ESCAPE)
		{
			points.clear();
			InvalidateRect(*this, NULL, TRUE);
		}
		if (vk == VK_BACK)
		{
			points.pop_back();
			InvalidateRect(*this, NULL, TRUE);
		}
		if (vk == VK_SPACE)
		{

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
