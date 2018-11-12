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
	}
	void OnLButtonDown(POINT p) 
	{
		lista.push_back(p);
		InvalidateRect(*this, NULL, false);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk) {
		case VK_ESCAPE: 
			lista.clear();
			InvalidateRect(*this, NULL, true); 
			break;
		case VK_BACK: 
			if (!lista.empty()) {
				lista.pop_back();
				InvalidateRect(*this, NULL, true);
				break;
			}
		}
	}
	void OnDestroy()
	{
		::PostQuitMessage(0);
	}
private:
	std::list<POINT> lista;
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP 5"));
	return app.Run();
}
