#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include<list>
typedef std::list<POINT>list;
typedef list::const_iterator iterator;

class MainWindow : public Window
{
	list points;
protected:
	void OnPaint(HDC hdc)  
	{ 
	// iterate over points in container and draw polyline
		for (iterator iter = points.begin(); iter != points.end();++iter)
		{
			if (iter == points.begin())
				MoveToEx(hdc, iter->x, iter->y, 0);
			else
				LineTo(hdc, iter->x, iter->y);
		}
			
	}
	void OnLButtonDown(POINT p) 
	{
	// add point to container
		points.push_back(p);
		InvalidateRect(*this, 0, true);
	}
	void OnKeyDown(int vk) 
	{
	//  Esc - empty container
	//  Backspace - remove last point

		if (vk == VK_CONTROL)
		{
			
			while (points.size())
				points.pop_back();
		}
		else if (vk == VK_BACK) 
		{
			if(points.size())
			points.pop_back();
		
		}
		else return;
		InvalidateRect(*this, 0, true);

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
