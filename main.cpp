#include <tchar.h>
#include "nwpwin.h"
#include <list>

class main_window : public vsite::nwp::window
{
	std::list<POINT> points;

protected:
	void on_paint(HDC hdc) override
	{
		//iterate over points in container and draw polyline
		if (!points.empty()) {
			MoveToEx(hdc, points.front().x, points.front().y, nullptr);
			for (auto& p : points) {
				LineTo(hdc, p.x, p.y);
			}
		}
	}
	void on_left_button_down(POINT p) override
	{
		//add point to container
		points.push_back(p);
		::InvalidateRect(*this, NULL, TRUE);
	}
	void on_key_down(int vk) override
	{
		//Esc - empty container
		if (vk == VK_ESCAPE)
		{
			points.clear();
			::InvalidateRect(*this, NULL, TRUE);
		}
		//Backspace - remove last point
		if (vk == VK_BACK)
		{
			if (!points.empty())
			{
				points.pop_back();
				::InvalidateRect(*this, NULL, TRUE);
			}
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