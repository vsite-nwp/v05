#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window{
	std::list<POINT> p;
protected:
	void OnPaint(HDC hdc){ 
		if (p.empty()==false)
			MoveToEx(hdc, p.front().x, p.front().y, NULL);
		for (POINT pt : p)
			::LineTo(hdc, pt.x, pt.y);
	}
	void OnLButtonDown(POINT po){
		p.push_back(po);
		InvalidateRect(*this, 0, true);
	}
	void OnKeyDown(int vk){
		if (vk == VK_ESCAPE) {
			p.clear();
			InvalidateRect(*this, 0, true);
		}
		else if (vk == VK_BACK) {
			if (p.empty() == false) {
				p.pop_back();
				InvalidateRect(*this, 0, true);
			}
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
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("Vj5"));
	return app.Run();
}
