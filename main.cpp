#include <tchar.h>
#include "nwpwin.h"
#include <list>



class main_window : public vsite::nwp::window
{
	std::list<POINT> points;
protected:
	void on_paint(HDC hdc) override
	{
		//  iterate over points in container and draw polyline
		if (points.empty()) { return; }
		MoveToEx(hdc, points.front().x, points.front().y, NULL);
		for (POINT p : points) { ::LineTo(hdc, p.x, p.y); }
	}
	void on_left_button_down(POINT p) override
	{
		//  add point to container
		points.push_back(p);
		InvalidateRect(*this, NULL, false);

	}
	void on_key_down(int vk) override
	{
		//  Esc - empty container
		//  Backspace - remove last point
		switch (vk) {
		case VK_ESCAPE:
			points.clear();
			break;

		case VK_BACK:
			if (!points.empty()) { points.pop_back(); }
			break;
		default:
			break;
		}
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
