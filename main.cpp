#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
	std::list<POINT> coords;
protected:
	void ClearCoords() {
		coords.clear();
		InvalidateRect(*this, nullptr, true);
	}
	void PopBack() {
		if (!coords.empty()) {
			coords.pop_back();
			InvalidateRect(*this, nullptr, true);
		}
	}
	void OnPaint(HDC hdc)  
	{ 
		for (std::list<POINT>::iterator it = coords.begin(); it != coords.end(); ++it) {
			if (it == coords.begin())
				MoveToEx(hdc, it->x, it->y, NULL);

			LineTo(hdc, it->x, it->y);
		}
	}
	void OnLButtonDown(POINT p) 
	{
		coords.push_back(p);
		InvalidateRect(*this, nullptr, true);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk) {
		case VK_ESCAPE:
			ClearCoords();
			break;
		case VK_BACK:
			PopBack();
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
