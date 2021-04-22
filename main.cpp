#include <tchar.h>
#include "nwpwin.h"
#include <list>

class main_window : public vsite::nwp::window
{
protected:
	std::list<POINT> pl;

	void on_paint(HDC hdc) override  
	{ 
		if (!pl.empty()) {
			MoveToEx(hdc, pl.front().x, pl.front().y, 0);
			for (const POINT& p : pl) {
				LineTo(hdc, p.x, p.y);
			}
		}
	}

	void on_left_button_down(POINT p) override
	{
		pl.push_back(p);
		InvalidateRect(*this, 0, true);
	}

	void on_key_down(int vk) override
	{
		switch (vk) {
		case VK_ESCAPE:
			pl.clear();
			InvalidateRect(*this, 0, true);
			break;
		case VK_BACK:
			if (!pl.empty()) {
				pl.pop_back();
				InvalidateRect(*this, 0, true);
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
