#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include<list>

class MainWindow : public Window
{
protected:
	std::list<POINT> lists;
	std::list<POINT>::iterator it;
	void OnPaint(HDC hdc)  {
		
		if (lists.size() != 0) {
			MoveToEx(hdc, lists.front().x, lists.front().y, NULL);
		}
		for (it = lists.begin(); it != lists.end(); ++it) {
				LineTo(hdc, it->x, it->y);
			}
	}
	void OnLButtonDown(POINT p) {
		
		lists.push_back(p);
		InvalidateRect(*this, NULL, true);
	
	}
	void OnKeyDown(int vk) {
		
		switch (vk) {
			case VK_ESCAPE:
				lists.clear();
				break;
			case VK_BACK:
				if (lists.size() == 0)
				return;
				lists.pop_back();
				break;
		default:
			return;
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
