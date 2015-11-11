#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
protected:
	void OnPaint(HDC hdc)  
	{ 
	//iterate over points in container and draw polyline
		
		for (std::list<POINT>::iterator iter = list.begin(); iter != list.end(); iter++){
			if (iter->x == jump.x && iter->y == jump.y){
				iter++;
				if(iter != list.end())
					MoveToEx(hdc, iter->x, iter->y, nullptr);
			}
			else if (iter == list.begin()){
				MoveToEx(hdc, iter->x, iter->y, nullptr);	//nullptr ili 0
			}
			else{
				LineTo(hdc, iter->x, iter->y);
			}
		}
	}
	void OnLButtonDown(POINT p) 
	{
	//add point to container
		list.push_back(p);

		InvalidateRect(*this, 0, TRUE);
	}
	void OnKeyDown(int vk) 
	{
		switch (vk){
		case VK_ESCAPE:		//Esc - empty container
			list.clear();
			InvalidateRect(*this, 0, TRUE);
			break;
		case VK_BACK:		//Backspace - remove last point
			if (list.empty()) return;

			list.pop_back();
			InvalidateRect(*this, 0, TRUE);
			break;
		case VK_SPACE:
			jump.x = -1;
			jump.y = -1;
			list.push_back(jump);
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
	POINT jump;
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP 5"));
	return app.Run();
}
