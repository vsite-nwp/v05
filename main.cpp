#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>


class MainWindow : public Window
{
private:
	std::list<POINT> point_list;
	std::list<POINT>::iterator iterate;
protected:
	void OnPaint(HDC hdc)  
	{ 
	// iterate over points in container and draw polyline
		if (point_list.size() != 0) MoveToEx(hdc, point_list.front().x, point_list.front().y, NULL);
		for (iterate = point_list.begin(); iterate != point_list.end(); ++iterate)
			LineTo(hdc, iterate->x, iterate->y);
	}
	void OnLButtonDown(POINT p) 
	{
	// add point to container
		point_list.push_back(p);
		InvalidateRect(*this, NULL, true);
	}
	void OnKeyDown(int vk) 
	{
	// Esc - empty container
	// Backspace - remove last point
		switch (vk) {
		case VK_ESCAPE: point_list.clear(); break;
		case VK_BACK: if (point_list.size() == 0) return; point_list.pop_back(); break;
		default: break;
		}
		InvalidateRect(*this, NULL, true);
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
