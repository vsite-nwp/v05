#include <windows.h>i
#include <tchar.h>
#include <list>
#include <algorithm>
#include "nwpwin.h"

class MainWindow : public Window
{
protected:
	void Reset()
	{
		if (mCoords.size() > 0)
		{
			mCoords.clear();
			InvalidateRect(*this, nullptr, true);
		}
	}
	void PopBack()
	{
		if (!mCoords.empty())
		{
			mCoords.pop_back();
			InvalidateRect(*this, nullptr, true);
		}
	}
	void OnPaint(HDC hdc)  
	{ 
		if (mCoords.size())
		{
			auto i = mCoords.begin();
			MoveToEx(hdc, i->x, i->y, nullptr);
			std::for_each(std::begin(mCoords), std::end(mCoords), [&hdc](POINT& p)->void { ::LineTo(hdc, p.x, p.y); });
		}
	}
	void OnLButtonDown(POINT p) 
	{
		mCoords.push_back(p);
		InvalidateRect(*this, nullptr, true);
	}

	void OnKeyDown(int vk) 
	{
		switch (vk)
		{
			case VK_ESCAPE:
			{
				Reset();
				break;
			}
			case VK_BACK:
			{
				PopBack();
				break;
			}
			default:
				break;	
		}
	}
	void OnDestroy()
	{
		::PostQuitMessage(0);
	}
private:
	std::list<POINT> mCoords;
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP 5"));
	return app.Run();
}
