#include <tchar.h>
#include "nwpwin.h"
#include <list>

class main_window : public vsite::nwp::window
{
	std::list<POINT> points;

protected:
	void on_paint(HDC hdc) override
	{
		for (auto point = points.begin(); point != points.end(); ++point) {
			if (point == points.begin())
				MoveToEx(hdc, point->x, point->y, NULL);
			LineTo(hdc, point->x, point->y);
		}
	}

	void on_left_button_down(POINT p) override
	{
		points.push_back(p);
		InvalidateRect(*this, nullptr, true);
	}

	void on_key_down(int vk) override
	{
		if (vk == VK_ESCAPE)
			points.clear();
		if (vk == VK_BACK && !points.empty())
			points.pop_back();
		InvalidateRect(*this, nullptr, true);
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
