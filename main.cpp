#include <tchar.h>
#include "nwpwin.h"
#include <list>

class main_window : public vsite::nwp::window
{
protected:
	void on_paint(HDC hdc) override  
	{ 
	// iterate over points in container and draw polyline
		if (points.empty()) return;
		::MoveToEx(hdc, points.front().x, points.front().y, nullptr);
		for (auto const& x : points) {
			::LineTo(hdc, x.x, x.y);
		}
	}
	void on_left_button_down(POINT p) override
	{
	// add point to container
		points.push_back(p);
		InvalidateRect(*this, NULL, false);
	}
	void on_key_down(int vk) override
	{
	// Esc - empty container
	// Backspace - remove last point
		if (points.empty()) return;
		switch (vk) {
		case VK_ESCAPE:
			points.clear();
			break;
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
private:
	std::list<POINT> points;
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 5");
	return app.run();
}
