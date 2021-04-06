#include <tchar.h>
#include "nwpwin.h"
#include <list>
#include <iostream>

class main_window : public vsite::nwp::window
{
protected:
	std::list<POINT> pnt;
	void on_paint(HDC hdc) override  
	{ 
		if (!pnt.empty()) {
			SetDCPenColor(hdc, RGB(255, 0, 0));
			MoveToEx(hdc, pnt.front().x, pnt.front().y, 0);
		}
		for (auto it = pnt.begin(); it != pnt.end(); ++it)
		{
			LineTo(hdc, (int)it->x, (int)it->y);
		}
	}
	void on_left_button_down(POINT p) override
	{
		pnt.push_back(p);
		InvalidateRect(*this, NULL, true);
	}
	void on_key_down(int vk) override
	{
		if (vk == VK_BACK) { if (!pnt.empty()) pnt.pop_back(); }
		else	if (vk == VK_ESCAPE)
		{
			if (!pnt.empty()) { pnt.clear(); }
		}
		else { return; }
		InvalidateRect(*this, NULL, true);
	}
	void on_destroy() override
	{
		::PostQuitMessage(0);
	}
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 5");
	return app.run();
}
