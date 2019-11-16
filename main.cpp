#include <windows.h>
#include <tchar.h>
#include <list>
#include "nwpwin.h"

class MainWindow : public Window
{
protected:
	std::list<POINT> tocke;
	std::list<POINT>::iterator it;
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	void OnPaint(HDC hdc)
	{
		POINT p;
		SelectObject(hdc, pen);
		if (tocke.begin() != tocke.end()) {
			MoveToEx(hdc, (tocke.begin())->x, (tocke.begin())->y, &p);
			for (it = ++tocke.begin(); it != tocke.end(); it++) {
				LineTo(hdc, it->x, it->y);
			}
		}


	}
	void OnLButtonDown(POINT p)
	{
		tocke.push_back(p);
		InvalidateRect(*this, NULL, TRUE);
		UpdateWindow(*this);

	}
	void OnKeyDown(int vk)
	{
		switch (vk) {
		case VK_ESCAPE:
			tocke.clear();
			InvalidateRect(*this, NULL, TRUE);
			UpdateWindow(*this);
			break;
		case VK_BACK:
			tocke.pop_back();
			InvalidateRect(*this, NULL, TRUE);
			UpdateWindow(*this);
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
