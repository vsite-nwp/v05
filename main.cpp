#include <windows.h>
#include <tchar.h>
#include <list>
#include <algorithm>
#include <iterator>
#include "nwpwin.h"

class MainWindow : public Window
{
	std::list<POINT> draw_cords;
protected:

	void OnPaint(HDC hdc)  
	{ 
		if (draw_cords.empty())
			return;

		MoveToEx(hdc, draw_cords.front().x, draw_cords.front().y, 0);

		for (std::list<POINT>::iterator it = draw_cords.begin(); it != draw_cords.end(); ++it) 
			LineTo(hdc, it->x, it->y);
	}
	void OnLButtonDown(POINT p) 
	{
		draw_cords.push_back(p);
		InvalidateRect(*this, 0, TRUE);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk) {
		case VK_ESCAPE:
			draw_cords.clear();
			break;
		case VK_BACK:
			if (draw_cords.empty())
				return;
			draw_cords.pop_back();
			break;
		}
		InvalidateRect(*this, 0, TRUE);
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
