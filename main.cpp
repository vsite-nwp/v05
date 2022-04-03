#include <tchar.h>
#include "nwpwin.h"
#include <list>

class main_window : public vsite::nwp::window
{
protected:
	std::list<POINT> Points;
	void on_paint(HDC hdc) override  
	{ 
	// iterate over points in container and draw polyline
		if (Points.empty()) return;
		MoveToEx(hdc, Points.front().x, Points.front().y, 0);
		for (auto el : Points) {
			LineTo(hdc, el.x, el.y);
		}
	}
	void on_left_button_down(POINT p) override
	{
	// add point to container
		Points.push_back(p);
		InvalidateRect(*this, 0, true);
	}
	void on_key_down(int vk) override
	{
	// Esc - empty container
		switch (vk) {
		case VK_ESCAPE:
			Points.clear();
			InvalidateRect(*this, NULL, true);
			break;
		case VK_BACK:	// Backspace - remove last point
			if (!Points.empty()) {
				Points.pop_back();
				InvalidateRect(*this, NULL, true);
			}
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
