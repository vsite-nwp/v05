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
		::LineTo(hdc, points.front().x, points.front().y);
	}
	void on_left_button_down(POINT p) override
	{
	// add point to container
		points.push_back(p);
		InvalidateRect(*this, nullptr, true);
	}
	void on_key_down(int vk) override
	{
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
