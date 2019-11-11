#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
	std::list<POINT> lista;
protected:
	void OnPaint(HDC hdc)  
	{ 
		for (auto it = lista.begin(); it != lista.end(); ++it) 
		{
			if (lista.begin() == it) {
				MoveToEx(hdc,it->x, it->y, nullptr);
			}
			else {
				LineTo(hdc, it->x, it->y);
			}
		}
	}
	void OnLButtonDown(POINT p) 
	{
		lista.push_back(p);
		InvalidateRect(*this, nullptr, true);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk) 
		{
		case VK_ESCAPE:
		{
			lista.clear();
			break;
		}
		case VK_BACK: 
		{
			lista.pop_back();
			break;
		}
		default: {
			return;
		}
		}
		InvalidateRect(*this, nullptr, true);
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
