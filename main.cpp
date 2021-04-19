#include <tchar.h>
#include "nwpwin.h"
#include <list>
#include <algorithm>

class main_window : public vsite::nwp::window
{
	std::list<POINT> listaTocaka;
protected:
	void on_paint(HDC hdc) override  
	{ 
	
		if (listaTocaka.empty())
			return;

		MoveToEx(hdc, listaTocaka.front().x, listaTocaka.front().y, (LPPOINT)NULL);

		for (POINT& tocka : listaTocaka) {
			LineTo(hdc, tocka.x, tocka.y);
		}
	}
	void on_left_button_down(POINT p) override
	{
	
		listaTocaka.push_back(p);
		InvalidateRect(*this, 0, TRUE);
	}
	void on_key_down(int vk) override
	{


		switch (vk) {
		case VK_BACK:
			if (!listaTocaka.empty()) {
				listaTocaka.pop_back();
				InvalidateRect(*this, 0, TRUE);
			}
			break;
		case VK_ESCAPE:
			listaTocaka.clear();
			InvalidateRect(*this, 0, TRUE);
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
