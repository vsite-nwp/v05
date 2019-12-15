#include <windows.h>
#include <list>
#include <tchar.h>
#include "nwpwin.h"

// NoteToSelf: get HDC from main window?

class MainWindow : public Window
{
protected:
	void OnPaint(HDC hdc)  
	{ 

		DrawPolygon(hdc);

	}
	void OnLButtonDown(POINT p) 
	{

		coords.push_back(p);
		InvalidateRect(*this, nullptr, true);

	}
	void OnKeyDown(int vk) 
	{

		if (vk == VK_ESCAPE)
			coords.clear();

		if (vk == VK_BACK && !coords.empty())
			coords.pop_back();
		InvalidateRect(*this, nullptr, true);
	}
	void OnDestroy()
	{
		::PostQuitMessage(0);
	}

	void DrawPolygon(HDC hdc)
	{
		if (!coords.empty())
		{

			MoveToEx(hdc, coords.front().x, coords.front().y, nullptr);

			for each (POINT point in coords)
			{
				LineTo(hdc, point.x, point.y);
			}

		}

	}

private:

	std::list<POINT> coords;

};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP 5"));
	return app.Run();
}
