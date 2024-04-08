#include <tchar.h>
#include "nwpwin.h"
#include <vector>
#include <algorithm>

class main_window : public vsite::nwp::window
{
private:
	POINT point;
	std::vector<POINT> points;
	int dx = 0;
	int dy = 0;

protected:
	void on_paint(HDC hdc) override  
	{ 
	// TODO: iterate over points in container and draw polyline
		if (!points.empty())
			MoveToEx(hdc, points.front().x + dx, points.front().y + dy, nullptr);
		for (auto p : points) {
			LineTo(hdc, p.x + dx, p.y + dy);
		}
	}
	void on_left_button_down(POINT p) override
	{
	// TODO: add point to container
		points.push_back(p);
		::InvalidateRect(*this, nullptr, true);
	}
	void on_key_down(int vk) override
	{
	// TODO: Esc - empty container
	// TODO: Backspace - remove last point
		switch (vk) {
		case VK_BACK:
			if(!points.empty())
				points.pop_back();
			break;
		case VK_ESCAPE:
			points.clear();			
			break;
		case VK_UP:
			dy--;
			break;
		case VK_DOWN:
			dy++;
			break;
		case VK_LEFT:
			dx--;
			break;
		case VK_RIGHT:
			dx++;
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
