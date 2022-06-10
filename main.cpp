#include <tchar.h>
#include "nwpwin.h"
#include <list>
#include <iterator>

class main_window : public vsite::nwp::window
{
	std::list<POINT> listp;
protected:
	void on_paint(HDC hdc) override  
	{ 
	// TODO: iterate over points in container and draw polyline
		if (listp.empty()) {
			return;
		}
		MoveToEx(hdc, listp.front().x, listp.front().y, NULL);
		for (std::list<POINT>::iterator it = listp.begin(); it != listp.end(); ++it)
			LineTo(hdc, it->x, it->y);

	}

	void on_left_button_down(POINT p) override {
	
		listp.push_back(p);
		InvalidateRect(*this, NULL, TRUE);
	}

	void on_key_down(int vk) override
	{
		if (listp.empty()) {
			return;
		}

		switch (vk) {
		case VK_ESCAPE:
			listp.clear();
			break;
		
		case VK_BACK:
			listp.pop_back();
			break;
		}

		InvalidateRect(*this, NULL, TRUE);
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
