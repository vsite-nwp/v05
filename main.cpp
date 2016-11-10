#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
	POINT p;
	std::list<POINT> lista;
	
protected:
	void OnPaint(HDC hdc)  
	{ 
		std::list<POINT>::iterator it = lista.begin();;
		if (lista.size())
			MoveToEx(hdc, it->x, it->y,NULL);
		while(it != lista.end()){ 
			LineTo(hdc, it->x, it->y);
			++it;
		}
	}
	void OnLButtonDown(POINT p)
	{
		lista.push_back(p);
		InvalidateRect(*this, NULL, TRUE);
	}

	void OnKeyDown(int vk_ID) 
	{
		if (lista.size()) {
			switch (vk_ID) {
			case VK_ESCAPE:
				lista.clear();
				break;
			case VK_BACK:
				if (lista.empty()) return;
				lista.pop_back();
				break;
			default:
				return;
			}
			InvalidateRect(*this, NULL, TRUE);
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
