#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
protected:
	void OnPaint(HDC hdc)  
	{ 
		for (std::list<POINT>::const_iterator it = lista.begin(); it != lista.end(); ++it) {
			if (it == lista.begin())
				MoveToEx(hdc, it->x, it->y, NULL);
			else 
			LineTo(hdc, it->x, it->y);
		}
		InvalidateRect(*this, NULL, NULL);
	}
	void OnLButtonDown(POINT p) 
	{
		position = p;
		lista.push_back(position);
		UpdateWindow(*this);
	}
	void OnKeyDown(int vk) 
	{
	// TODO: Esc - empty container
		switch (vk) {
		case VK_ESCAPE: lista.clear(); break;
		case VK_BACK: lista.pop_back(); break;
		}
	// TODO: Backspace - remove last point
	}
	void OnDestroy()
	{
		::PostQuitMessage(0);
	}
private:
	std::list<POINT> lista;
	POINT position;
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP 5"));
	return app.Run();
}
