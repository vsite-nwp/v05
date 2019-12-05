#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
private:
	std::list<POINT> dots;
protected:
	void OnPaint(HDC hdc)  
	{ 
		if (dots.empty()) return;
		MoveToEx(hdc, dots.front().x, dots.front().y, nullptr);
		for (POINT dt : dots)
			::LineTo(hdc, dt.x, dt.y);
	}
	void OnLButtonDown(POINT p) 
	{
		dots.push_back(p);
		InvalidateRect(*this, nullptr, true);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk) {
		case VK_ESCAPE:
			dots.clear();
			InvalidateRect(*this, nullptr, true);
			break;
		case VK_BACK:
			if (!dots.empty()) {
				dots.pop_back();
			}
			InvalidateRect(*this, nullptr, true);
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
