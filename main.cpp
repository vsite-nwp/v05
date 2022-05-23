#include <tchar.h>
#include <list>
#include "nwpwin.h"


class main_window : public vsite::nwp::window
{
private:
	std::list <POINT> l;
protected:
	void on_paint(HDC hdc) override  
	{ 
		if (!l.empty())
			MoveToEx(hdc, l.front().x, l.front().y, 0);
		for (POINT point : l) {
			::LineTo(hdc, point.x, point.y);
		}
	
	}
	void on_left_button_down(POINT p) override
	{
		l.push_back(p);
		::InvalidateRect(*this, 0, true);
	
	}
	void on_key_down(int vk) override
	{
		switch (vk) {
		case VK_ESCAPE:
			
			l.clear();
			::InvalidateRect(*this, 0, true);
			break;
		case VK_BACK:
			if (!l.empty())
				l.pop_back();
			::InvalidateRect(*this, 0, true);
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
