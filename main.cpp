#include <tchar.h>
#include "nwpwin.h"
#include <list>

class main_window : public vsite::nwp::window
{
	std::list<POINT> points;

protected:
	void on_paint(HDC hdc) override  
	{ 
	// Iterate over points in container and draw polyline
		if (points.empty()) {
			return;
		}
		
		::MoveToEx(hdc, points.front().x, points.front().y, 0);

		auto it = points.begin();

		for (++it; it != points.end(); ++it) {
			::LineTo(hdc, it->x, it->y);
		}
	}
	void on_left_button_down(POINT p) override
	{
	// Add point to container
		points.push_back(p);
		::InvalidateRect(*this, 0, 0);
	}
	void on_key_down(int vk) override
	{
	// Esc - empty container
	// Backspace - remove last point
		switch (vk) {
		case VK_ESCAPE:
			points.clear();
			::InvalidateRect(*this, 0, TRUE);
			break;
		case VK_BACK:
			if (!points.empty()) {
				points.pop_back();
			}
			::InvalidateRect(*this, 0, TRUE);
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
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 5", 0, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300);
	return app.run();
}
