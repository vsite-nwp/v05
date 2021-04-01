#include <tchar.h>
#include "nwpwin.h"
#include <list>

class main_window : public vsite::nwp::window
{
protected:
	std::list<POINT> points;
	void on_paint(HDC hdc) override  
	{ 
		if (points.empty())  return;
		MoveToEx(hdc, points.front().x, points.front().y, 0);
		for (auto el : points) {
			LineTo(hdc, el.x, el.y);
		}
	}
	void on_left_button_down(POINT p) override
	{
		points.push_back(p);
		InvalidateRect(*this, 0, true);
	}
	void on_key_down(int vk) override
	{
		switch (vk)
		{
		case VK_ESCAPE:
			points.clear();
			InvalidateRect(*this, NULL, true);
			break;
		case VK_BACK:
			if (!points.empty()) { points.pop_back(); InvalidateRect(*this, NULL, true); }
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
