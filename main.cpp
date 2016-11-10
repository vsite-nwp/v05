#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
protected:
	void OnPaint(HDC hdc)  
	{
		for (auto iter = buffer.begin(); iter != buffer.end(); iter++)
		{
			if (iter == buffer.begin())
				MoveToEx(hdc,iter->x,iter->y,nullptr);
			else
			LineTo(hdc, iter->x, iter->y);
		}

	}
	void OnLButtonDown(POINT p) 
	{
		buffer.push_back(p);
		InvalidateRect(*this, nullptr, TRUE);
	}
	void OnKeyDown(int vk) 
	{
		
		if (vk == VK_ESCAPE) {
			buffer.clear();
			draw();
		}
		if (vk == VK_BACK) {
			auto iter = buffer.begin();
			if (iter != buffer.end())
			{
				buffer.pop_back();
				draw();
			}
		}
	}
	void OnDestroy()
	{
		::PostQuitMessage(0);
	}
private:
	std::list <POINT> buffer;
	POINT end;
	void draw() { InvalidateRect(*this, nullptr, TRUE); }
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP 5"));
	return app.Run();
}
