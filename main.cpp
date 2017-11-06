#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>


class MainWindow : public Window
{
	std::list<POINT> tocke;
protected:
	void OnPaint(HDC hdc)  
	{ 
		for (auto it = tocke.begin(); it != tocke.end(); ++it) {
			if(it == tocke.begin())
			{ 
				MoveToEx(hdc, it->x, it->y, NULL); }
			LineTo(hdc, it->x, it->y);
		}
	}
	void OnLButtonDown(POINT p) 
	{
		tocke.push_back(p);
		InvalidateRect(*this, NULL, TRUE);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk)
		{
		case(VK_BACK):
			if (!tocke.empty()) {
				tocke.pop_back();
				InvalidateRect(*this, NULL, TRUE);
			}
			break;
		case(VK_ESCAPE):
			tocke.clear();
			InvalidateRect(*this, NULL, TRUE);
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
