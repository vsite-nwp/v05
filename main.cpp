#include <tchar.h>
#include "nwpwin.h"
#include <list>

class main_window : public vsite::nwp::window
{
	std::list<POINT> points;

protected:
	void on_paint(HDC hdc) override  
	{ 
	// TODO: iterate over points in container and draw polyline
		if (points.empty()) {
			return;
		}
		
		POINT firstPoint = points.front();
		::MoveToEx(hdc, firstPoint.x, firstPoint.y, 0);

		typedef std::list<POINT>::iterator iter;
		iter it = points.begin();

		for (++it; it != points.end(); ++it) {
			POINT endPoint = *it;
			::LineTo(hdc, endPoint.x, endPoint.y);
		}
	}
	void on_left_button_down(POINT p) override
	{
	// TODO: add point to container
		points.push_back(p);
		::InvalidateRect(*this, 0, 0);
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
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 5", 0, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300);
	return app.run();
}
