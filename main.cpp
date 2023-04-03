#include <tchar.h>
#include <list>
#include <algorithm>
#include "nwpwin.h"

class main_window : public vsite::nwp::window
{
private:
	std::list<POINT> toDraw;
protected:
	void on_paint(HDC hdc) override  
	{ 
	// TODO: iterate over points in container and draw polyline
		if (toDraw.empty()) return;
		::MoveToEx(hdc, toDraw.front().x, toDraw.front().y, nullptr);
		
		std::for_each(toDraw.begin()++, toDraw.end(), [&hdc](const POINT& p) {
			::LineTo(hdc, p.x, p.y);
			});
	}
	void on_left_button_down(POINT p) override
	{
		toDraw.push_back(p);
		::InvalidateRect(*this, nullptr, true);
	}
	void on_key_down(int vk) override
	{
	// TODO: Esc - empty container
	// TODO: Backspace - remove last point
		switch (vk)
		{
		case VK_ESCAPE:
			toDraw.clear();
			::InvalidateRect(*this, nullptr, true);
			break;
		case VK_BACK:
			if(toDraw.empty())
			 toDraw.pop_back();
			::InvalidateRect(*this, nullptr, true);
			break;
		default:
			break;
		}
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
