#include <tchar.h>
#include "nwpwin.h"

#include <list>
#include <algorithm>

class main_window : public vsite::nwp::window
{
	std::list<POINT> points;
protected:
	void on_paint(HDC hdc) override  
	{ 
		if (points.empty())
			return;
	// TODO: iterate over points in container and draw polyline
		MoveToEx(hdc, points.front().x, points.front().y, nullptr);
		std::for_each(points.begin(), points.end(), [hdc](POINT p) {::LineTo(hdc,p.x,p.y);});
	}
	void on_left_button_down(POINT p) override
	{
		points.push_back(p);
		::InvalidateRect(*this, nullptr, true);

	// TODO: add point to container
	}
	void on_key_down(int vk) override
	{
		if (vk == VK_ESCAPE)
		{
			points.clear();
			::InvalidateRect(*this, nullptr, true);
		}
		if (vk = VK_BACK) {
			points.pop_back();
			::InvalidateRect(*this, nullptr, true);
		}
	// TODO: Esc - empty container
	// TODO: Backspace - remove last point
		
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
