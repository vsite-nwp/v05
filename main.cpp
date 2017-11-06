#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>;

class MainWindow : public Window
{
	std::list<POINT>point;
	typedef std::list<POINT>::const_iterator iter;
protected:
	void OnPaint(HDC hdc)  
	{ 
	
		for (iter it=point.begin(); it != point.end(); it++) {
			
			if (it == point.begin())
				MoveToEx(hdc, it->x , it->y,NULL);
				LineTo(hdc, it->x , it->y);
		}

	}
	void OnLButtonDown(POINT p) 
	{
		point.push_back(p);
		InvalidateRect(*this, 0, TRUE);

	
	}
	void OnKeyDown(int vk) 
	{
	
		switch (vk)
		{
		case VK_ESCAPE:
			point.clear();
			break;
		case VK_BACK:
			point.pop_back();
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
