#include <tchar.h>
#include "nwpwin.h"
#include <list>
#include <algorithm>


class main_window : public vsite::nwp::window
{
protected:
	std::list<POINT> pointsList;

	void on_paint(HDC hdc) override  
	{ 
		if (pointsList.empty())
			return;

		MoveToEx(hdc, pointsList.front().x, pointsList.front().y, (LPPOINT) NULL);

		for (POINT& point : pointsList) {
			LineTo(hdc, point.x, point.y);
		}
	}

	void on_left_button_down(POINT p) override
	{	
		pointsList.push_back(p);
		InvalidateRect(*this, NULL, TRUE);
	}

	void on_key_down(int vk) override
	{
		switch (vk)
		{
		case VK_ESCAPE:
			pointsList.clear();
			InvalidateRect(*this, NULL, TRUE);
			break;
		case VK_BACK:
			if (!pointsList.empty())
			{
				pointsList.pop_back();
				InvalidateRect(*this, NULL, TRUE);
			}
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
