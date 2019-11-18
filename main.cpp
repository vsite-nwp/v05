#include <algorithm>
#include <list>
#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"

class MainWindow : public Window
{
	std::list<POINT> listaPointova;

protected:
	void OnPaint(HDC hdc)  
	{ 
		if (listaPointova.empty() == false)
		{
			MoveToEx(hdc, listaPointova.front().x, listaPointova.front().y, NULL);
		}
		for (POINT pt : listaPointova)
		{
			::LineTo(hdc, pt.x, pt.y);
		}
	}
	void OnLButtonDown(POINT p) 
	{
		listaPointova.push_back(p);
		InvalidateRect(*this, 0, true);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk)
		{
		case VK_BACK:
		{
			if (listaPointova.empty() == false) {
				listaPointova.pop_back();
				InvalidateRect(*this, 0, true);
				break;
			}
		}
		case VK_ESCAPE:
		{
			listaPointova.clear();
			InvalidateRect(*this, 0, true);
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
