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
	void OnPaint(HDC hd)
	{
		if (!pnt.empty()) {
			Obj pen(hd, GetStockObject(DC_PEN));
			SetDCPenColor(hd, RGB(255, 0, 0));
			MoveToEx(hd, pnt.front().x, pnt.front().y, 0);
		}
		for (auto it = pnt.begin(); it != pnt.end(); ++it)
		{
			LineTo(hd, (int)it->x, (int)it->y);
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
			InvalidateRect(*this, NULL, true);
		}

		else	if (vk == VK_ESCAPE)
		{
			if (!pnt.empty())
			{
				pnt.clear();
				InvalidateRect(*this, NULL, true);
			}
		}
		else
		{
			InvalidateRect(*this, NULL, true);
			return;
		}

	};


	void OnDestroy()
	{
		return;
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
