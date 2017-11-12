#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>
#include <algorithm>

class MainWindow : public Window
{
	std::list<POINT> pointsL;

protected:
	void OnPaint(HDC hdc)  
	{ 
		if (!pointsL.empty())
			MoveToEx(hdc, pointsL.front().x, pointsL.front().y, NULL);
			
		for (POINT pt : pointsL)
			::LineTo(hdc, pt.x, pt.y);
	}
	void OnLButtonDown(POINT p) 
	{
		pointsL.push_back(p);
		InvalidateRect(*this, 0, true);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk)
		{
		case VK_ESCAPE:{
			pointsL.clear();
			InvalidateRect(*this, 0, true);
			break;
		}
		case VK_BACK:{
			if (!pointsL.empty()){
				pointsL.pop_back();
				InvalidateRect(*this, 0, true);
				break;
			}
		}
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
