#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include<list>
using namespace std;
class MainWindow : public Window
{
	list<POINT>lista;
	list<POINT>::iterator it;
protected:
	void OnPaint(HDC hdc)  
	{ 
	// TODO: iterate over points in container and draw polyline
		for (it = lista.begin(); it != lista.end(); it++){
			if (it == lista.begin()){
				MoveToEx(hdc, it->x, it->y, 0);
			}
			else{

				LineTo(hdc, it->x, it->y);
			}
		}
		
	}
	void OnLButtonDown(POINT p) 
	{
	// TODO: add point to container
		lista.push_back(p);
		InvalidateRect(*this, 0, TRUE);
	}
	void OnKeyDown(int vk) 
	{
	// TODO: Esc - empty container
	// TODO: Backspace - remove last point
		switch (vk){
		case VK_ESCAPE: lista.clear(); InvalidateRect(*this, 0, TRUE);
			break;
		case VK_BACK:
			if (lista.empty()){
				break;
			}
			lista.pop_back(); InvalidateRect(*this, 0, TRUE);
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
