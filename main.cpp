#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>
#include <algorithm>
class SelObj {
	HDC hdc;
	HGDIOBJ hOld;
public:
	SelObj(HDC hdc, HGDIOBJ hObj) : hdc(hdc), hOld(::SelectObject(hdc, hObj)) { }
	~SelObj() { ::SelectObject(hdc, hOld); }
};
class draw
{
	HDC hdc;
public:
	draw(HDC hdc) : hdc(hdc) {}
	void operator()(POINT p) { Ellipse(hdc, p.x - 10, p.y - 10, p.x + 10, p.y + 10); }
};

class MainWindow : public Window
{
	
	std::list <POINT> plist;
protected:
	void OnPaint(HDC hdc)  
	{ 
		if (!plist.empty()) 
			MoveToEx(hdc, plist.front().x, plist.front().y, NULL);

		for (POINT pt : plist) 
			::LineTo(hdc, pt.x, pt.y);
		


	}
	void OnLButtonDown(POINT p) 
	{
		plist.push_back(p);
		InvalidateRect(*this, 0, true);
		
	}
	void OnKeyDown(int vk) 
	{
		switch (vk){
		case VK_ESCAPE: {
			
			plist.clear();
			InvalidateRect(*this, 0, true);
			break;
		}
		case VK_BACK: {
			if(!plist.empty())
				plist.pop_back();
			InvalidateRect(*this, 0, true);
			break;
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
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP 5"));
	return app.Run();
}
