#include <tchar.h>
#include "nwpwin.h"
#include <list>

class main_window : public vsite::nwp::window
{
	std::list<POINT> lp;
protected:
	void on_paint(HDC hdc) override  
	{ 
		if (!lp.empty())
			MoveToEx(hdc, lp.front().x, lp.front().y, NULL);

		for (POINT p : lp)
			::LineTo(hdc, p.x, p.y);
	}
	void on_left_button_down(POINT p) override
	{
		lp.push_back(p);
		InvalidateRect(*this, 0, true);
	}
	void on_key_down(int vk) override
	{
		switch (vk){
		case VK_BACK:
			if (!lp.empty())
				lp.pop_back();

			InvalidateRect(*this, 0, true);
			break;
		
		case VK_ESCAPE:
			lp.clear();
			InvalidateRect(*this, 0, true);
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
