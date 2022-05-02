#include <tchar.h>
#include "nwpwin.h"
#include<list>

class main_window : public vsite::nwp::window
{

private:
	std::list<POINT> point;
protected:
	void on_paint(HDC hdc) override  
	{ 
	// TODO: iterate over points in container and draw polyline
		if (!point.empty()) {
			MoveToEx(hdc, point.front().x, point.front().y, 0);
		}
		for (std::list<POINT>::iterator it = point.begin(); it != point.end(); ++it)
		{
			LineTo(hdc, it->x, it->y);
		}
	}
	void on_left_button_down(POINT p) override
	{
	// TODO: add point to container
		point.push_back(p);
		InvalidateRect(*this, nullptr, TRUE);
	}
	void on_key_down(int vk) override
	{
	// TODO: Esc - empty container
	// TODO: Backspace - remove last point

		switch (vk)
		{
		case VK_ESCAPE:
			point.clear();
			::InvalidateRect(*this, nullptr, TRUE);
			break;
		case VK_BACK:
			if (!point.empty())
			{
				point.pop_back();
				::InvalidateRect(*this, nullptr, TRUE);
				break;
			}
			return;
		default:
			return;
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
