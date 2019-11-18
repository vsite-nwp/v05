#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
private:
	std::list<POINT> allPointList;
	
protected:

	void MovePoints()
	{
		InvalidateRect(*this, NULL, true);
	}

	void OnPaint(HDC hdc)  
	{ 			
			for (auto point = allPointList.begin(); point != allPointList.end(); ++point)
			{
				if (point == allPointList.begin())					
					MoveToEx(hdc, point->x, point->y, NULL);
									
				LineTo(hdc, point->x, point->y);
			}		
	}
	void OnLButtonDown(POINT p) 
	{
		allPointList.push_back(p);
		MovePoints();		
	}
	void OnKeyDown(int vk) 
	{
		switch (vk)
		{
			case VK_ESCAPE:
			{
				allPointList.clear();
				MovePoints();
				break;
			}
			case VK_BACK:
			{				
				if (!allPointList.empty())				
					allPointList.pop_back();					
				
				MovePoints();
				break;
			}
			default:
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



