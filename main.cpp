#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
	std::list<POINT> lista;
	std::list<POINT>::iterator it;
protected:
	void OnPaint(HDC hdc)  
	{ 
		if (lista.size())
			MoveToEx(hdc, lista.front().x, lista.front().y, NULL);
		for (it = lista.begin(); it != lista.end(); it++){
			LineTo(hdc, it->x, it->y);
		}
	}
	void OnLButtonDown(POINT p) 
	{
		lista.push_back(p);
		InvalidateRect(*this, NULL, TRUE);
	}
	void OnKeyDown(int vk){
		if (lista.size()){
			switch (vk){
			case VK_ESCAPE:
				lista.clear();
				break;
			case VK_BACK:
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
