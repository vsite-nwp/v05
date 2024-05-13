#include <tchar.h>
#include "nwpwin.h"
#include <list>

class main_window : public vsite::nwp::window
{
private:
	std::list<POINT> points;
protected:
	void on_paint(HDC hdc) override  
	{ 
	// iterate over points in container and draw polyline
		if (points.empty()) return;
		::MoveToEx(hdc, points.front().x, points.front().y, nullptr);
		for (auto const& x : points) {
			::LineTo(hdc, x.x, x.y);
		}
		// Connect to first point
		//::LineTo(hdc, points.front().x, points.front().y);
	}
	void on_left_button_down(POINT p) override
	{
	// add point to container
		points.push_back(p);
		InvalidateRect(*this, nullptr, true);
	}
	void on_key_down(int vk) override
	{
		if (points.empty()) return;
		switch (vk) {
		// Esc - empty container
		case VK_ESCAPE:
			points.clear();
			break;
		// Backspace - remove last point
		case VK_BACK:
			points.pop_back();
			break;
		default:
			return;
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
