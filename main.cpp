#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>
class Obj {
	HDC handleDc;
	HGDIOBJ hGetObj;
public:
	Obj(HDC hd, HGDIOBJ hGo) {
		handleDc = hd;
		hGetObj = hGo;
	}
	~Obj() {
		SelectObject(handleDc, hGetObj);
	}
};
class MainWindow : public Window
{
	std::list<POINT> pnt;
protected:
	void OnPaint(HDC hdc)
	{
		if (!pnt.empty()) {

			SetDCPenColor(hdc, RGB(255, 0, 0));
			MoveToEx(hdc, pnt.front().x, pnt.front().y, 0);
		}
		for (auto it = pnt.begin(); it != pnt.end(); ++it)
		{
			LineTo(hdc, (int)it->x, (int)it->y);
		}
	}
	void OnLButtonDown(POINT p) 
	{
		pnt.push_back(p);
		InvalidateRect(*this, NULL, true);
	}
	void OnKeyDown(int vk) 
	{
		if (vk == VK_BACK)
		{
			if (!pnt.empty())
				pnt.pop_back();
		}

		else if (vk == VK_ESCAPE)
		{
			if (!pnt.empty())
				pnt.clear();
		}
		else
		{
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
