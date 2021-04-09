#include <tchar.h>
#include "nwpwin.h"
#include <list>

class main_window : public vsite::nwp::window
{
protected:
	void on_paint(HDC hdc) override  
	{ 
		if (!points.empty()) 
		{
			MoveToEx(hdc, points.front().x, points.front().y, NULL);
			for (POINT point : points) 
			{
				LineTo(hdc, point.x, point.y);
			}
		}
		return;
	}
	void on_left_button_down(POINT p) override
	{
		points.push_back(p);
		InvalidateRect(*this, NULL, true);
	}
	void on_key_down(int vk) override
	{
		switch (vk) 
		{
		case VK_BACK:
			if (!points.empty()) 
			{
				points.pop_back();
				InvalidateRect(*this, NULL, true);
			}
			break;
		case VK_ESCAPE:
			points.clear();
			InvalidateRect(*this, NULL, true);
			break;
		}
	}
	void on_destroy() override
	{
		::PostQuitMessage(0);
	}

	std::list<POINT> points;
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 5");
	return app.run();
}
