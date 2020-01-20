#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
	std::list<POINT> plist;
protected:
	void OnPaint(HDC hdc)  
	{ 
	// iterate over points in container and draw polyline
		if (plist.empty()) return;
		MoveToEx(hdc, plist.front().x, plist.front().y, nullptr);
		for (POINT p : plist)
			LineTo(hdc, p.x, p.y);
	}
	void OnLButtonDown(POINT p) 
	{
	// add point to container
		plist.push_back(p);
		InvalidateRect(*this, nullptr, true);
	}
	void OnKeyDown(int vk) 
	{
	// Esc - empty container
	// Backspace - remove last point

		switch (vk) {
		case VK_ESCAPE:
			plist.clear();
			InvalidateRect(*this, nullptr, true);
			break;
		case VK_BACK:
			if (plist.empty()) return;
			plist.pop_back();
			InvalidateRect(*this, nullptr, true);
			break;
		default:
			return;
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
