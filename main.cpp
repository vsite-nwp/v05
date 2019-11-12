#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
	std::list<POINT> list;
public:
	void Move() { InvalidateRect(*this, NULL, true); }
protected:
	void OnPaint(HDC hdc)  
	{ 
		for (auto iter = list.begin(); iter != list.end(); ++iter) {
			if (iter == list.begin())
				MoveToEx(hdc, list.front().x, list.front().y, NULL);
			else
				LineTo(hdc, iter->x, iter->y);
		}
	}
	void OnLButtonDown(POINT p) 
	{
		list.push_back(p);
		Move();
	}
	void OnKeyDown(int vk) 
	{
		switch (vk)
		{
		case VK_BACK:
			list.pop_back();
			Move();
			break;
		case VK_ESCAPE:
			list.clear();
			Move();
			break;
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
