#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
protected:
	void OnPaint(HDC hdc)  
	{ 
	// TODO: iterate over points in container and draw polyline
	
	}
	void OnLButtonDown(POINT p) 
	{
	//add point to container
		list.push_back(p);
	}
	void OnKeyDown(int vk) 
	{
	
		switch (vk){
		case VK_ESCAPE:		//Esc - empty container
			list.clear();
			break;
		case VK_BACK:		//Backspace - remove last point
			list.pop_back();
			break;
		default:
			return;
		}
	
	}
	void OnDestroy()
	{
		::PostQuitMessage(0);
	}
private:
	std::list<POINT> list;
	POINT cords;
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP 5"));
	return app.Run();
}
