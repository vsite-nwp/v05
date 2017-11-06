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
		if (!lista.empty())
			MoveToEx(hdc, lista.front().x, lista.front().y, 0);
		for(POINT p : lista)
		{
			LineTo(hdc, p.x, p.y);		
		}
	}
	void OnLButtonDown(POINT p) 
	{
		lista.push_back(p);
		InvalidateRect(*this, 0, false);
	}
	void OnKeyDown(int vk) 
	{
		if (lista.empty())
			return;
		switch (vk) {
		case VK_ESCAPE: lista.clear(); break;
		case VK_BACK:  lista.pop_back(); break;
		default: return;
		}
		InvalidateRect(*this, 0, true);
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
