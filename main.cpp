#include <tchar.h>
#include "nwpwin.h"
#include <list>
#include <iostream>

class main_window : public vsite::nwp::window
{
protected:
	std::list<POINT> listaTocaka;
	RECT rc;
	void on_paint(HDC hdc) override  
	{ 
		POINT p;
		if (!listaTocaka.empty()) {
			MoveToEx(hdc, listaTocaka.begin()->x, listaTocaka.begin()->y, &p);
			for (auto it = listaTocaka.begin(); it != listaTocaka.end(); ++it) {
				LineTo(hdc, it -> x, it -> y);
			}
		}
	}
	void on_left_button_down(POINT p) override
	{
		listaTocaka.push_back(p);
		InvalidateRect(*this, NULL, TRUE);
	}
	void on_key_down(int vk) override
	{
		switch (vk) {
		case VK_ESCAPE: {
			listaTocaka.clear();
			InvalidateRect(*this, NULL, TRUE);
			break;
		}
		case VK_BACK: {
			if (listaTocaka.empty())
				return;
			listaTocaka.pop_back();
			InvalidateRect(*this, NULL, TRUE);
			break;
		}
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
