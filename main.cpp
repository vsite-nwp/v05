#include <tchar.h>
#include "nwpwin.h"
#include <vector>
#include <algorithm>


class main_window : public vsite::nwp::window
{
	std::vector<POINT> points;

protected:
	void on_paint(HDC hdc) override  
	{ 
		if (points.empty())
			return;

		MoveToEx(hdc, points[0].x, points[0].y, nullptr);

		// iterate over points in container and draw polyline
		for (size_t i = 1; i < points.size(); i++)
		{
			LineTo(hdc, points[i].x, points[i].y);
		}
	}
	void on_left_button_down(POINT p) override
	{
	// add point to container
		points.push_back(p);
		::InvalidateRect(*this, 0, true);
	}
	void on_key_down(int vk) override
	{
		if (points.empty())
			return;

		switch (vk)
		{
		// Esc - empty container
		case VK_ESCAPE:
			points.clear();
			InvalidateRect(*this, NULL, true);
			break;

		// Backspace - remove last point
		case VK_BACK:
			points.pop_back();
			InvalidateRect(*this, NULL, true);
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
