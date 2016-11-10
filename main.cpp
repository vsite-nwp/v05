#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <vector>

class MainWindow : public Window
{
private:
	std::vector<POINT> polyline;
	POINT p;
	void draw() { InvalidateRect(*this, nullptr, TRUE); }
protected:
	void OnPaint(HDC hdc)
	{
		std::vector<POINT>::iterator  it = polyline.begin();

		if (polyline.size())
			MoveToEx(hdc, it->x, it->y, NULL);

		for (; it < polyline.end(); it++) {
			LineTo(hdc, it->x, it->y);
		}

	}
	void OnLButtonDown(POINT p)
	{
		polyline.push_back(p);
		draw();
	}
	void OnKeyDown(int vk)
	{
		switch (vk) {
		case VK_ESCAPE:
			polyline.clear();
			break;
		case VK_BACK:
			if (polyline.empty()) return;
			polyline.pop_back();
			break;
		}
		draw();
		return;
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
