#include <tchar.h>
#include "nwpwin.h"
#include <list>

class main_window : public vsite::nwp::window
{
private:
	std::list<POINT> ps;
protected:
	void on_paint(HDC hdc) override  
	{ 
		if (!ps.empty()) //baca error ako se ne provjeri
		{
			::MoveToEx(hdc, ps.front().x, ps.front().y, 0);
		}

		for (POINT p : ps)
		{
			::LineTo(hdc, p.x, p.y);
		}
	}
	void on_left_button_down(POINT p) override
	{
		ps.push_back(p);
		InvalidateRect(*this, 0, true);
	}
	void on_key_down(int vk) override
	{
	// TODO: Esc - empty container 
	// TODO: Backspace - remove last point
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
