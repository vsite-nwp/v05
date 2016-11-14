#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <vector>
#include <algorithm>

class MainWindow : public Window
{
	std::vector<POINT> points;
protected:
	void OnPaint(HDC hdc)  
	{ 
		for (auto iter = points.begin(); iter != points.end(); ++iter)
			{
				if (iter == points.begin())
					MoveToEx(hdc, iter->x, iter->y, NULL);

					LineTo(hdc, iter->x, iter->y);
			}
	}
	void OnLButtonDown(POINT p) 
	{
		points.push_back(p);
		InvalidateRect(*this, nullptr, TRUE);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk)
		{
		case VK_ESCAPE: 
			points.clear();
			InvalidateRect(*this, nullptr, TRUE);
			break;
		case VK_BACK:
			if (points.size() > 0)
			{
				points.pop_back();
				InvalidateRect(*this, nullptr, TRUE);
			}
		default:
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
