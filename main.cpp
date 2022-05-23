#include <tchar.h>
#include "nwpwin.h"
#include <list>

class main_window : public vsite::nwp::window
{
protected:
	std::list<POINT> pointList;
	void on_paint(HDC hdc) override  
	{ 
	//iterate over points in container and draw polyline
		if (!pointList.empty()) {
			MoveToEx(hdc, pointList.front().x, pointList.front().y, 0);
		}
		for (std::list<POINT>::iterator it = pointList.begin(); it != pointList.end(); ++it)
		{
			LineTo(hdc, it->x, it->y);
		}
	}
	void on_left_button_down(POINT p) override
	{
	//add point to container
		pointList.push_back(p);
		InvalidateRect(*this, nullptr, TRUE);
	}
	void on_key_down(int vk) override
	{
	
	//Backspace - remove last point
		if(vk == VK_BACK)
		{
			if (!pointList.empty())
				pointList.pop_back();
		}
	//Esc - empty container
		else if (vk == VK_ESCAPE)
		{
		pointList.clear();
		}
		else
		return;

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
