#include <tchar.h>
#include <vector>
#include <algorithm>
#include <list>
#include "nwpwin.h"

class main_window : public vsite::nwp::window
{
private:
	POINT p;
	std::list<POINT> points;

protected:
	void on_paint(HDC hdc) override  
	{ 
		if (points.empty()) return;
	//  iterate over points in container and draw polyline
		MoveToEx(hdc, points.front().x, points.front().y, nullptr);
		for (auto &p : points) {
			LineTo(hdc, p.x, p.y);
		}
	}
	void on_left_button_down(POINT p) override
	{
		//  add point to container
		points.push_back(p);
		::InvalidateRect(*this, nullptr, true);
	}
	void on_key_down(int vk) override
	{
	//  Esc - empty container
	//  Backspace - remove last point
		switch (vk)
		{
		case VK_ESCAPE:
			points.clear();
			break;
		case VK_BACK:
			if (!points.empty()) points.pop_back();
			break;
		default:
			return;
		}

		::InvalidateRect(*this, nullptr, true);
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
