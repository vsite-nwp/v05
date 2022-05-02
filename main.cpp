#include <tchar.h>
#include "nwpwin.h"
#include<list>

class main_window : public vsite::nwp::window
{
	POINT p;
	std::list<POINT> list_p;

protected:
	void on_paint(HDC hdc) override  
	{ 
	// TODO: iterate over points in container and draw polyline
		for (auto point = list_p.begin(); point != list_p.end(); ++point) {

			if (point == list_p.begin()) {
				MoveToEx(hdc, point->x, point->y, NULL);
			}
			LineTo(hdc, point->x, point->y);
		}
	}
	void on_left_button_down(POINT p) override
	{
	// TODO: add point to container
		list_p.push_back(p);
		//RedrawWindow(HDC,)
		//UpdateWindow(GetDlgItem(hdc,GetActiveWindow());
		//UpdateWindow(GetActiveWindow());
		InvalidateRect(*this, nullptr, true);
	
	}
	void on_key_down(int vk) override
	{
	// TODO: Esc - empty container
		short esc_press = GetAsyncKeyState(VK_ESCAPE);
		if (esc_press) {
			list_p.clear();
			InvalidateRect(*this, nullptr, true);
		}
	// TODO: Backspace - remove last point
		short backspace_press = GetAsyncKeyState(VK_BACK);
		if (backspace_press) {
			if (!list_p.empty())
				list_p.pop_back();
			InvalidateRect(*this, nullptr, true);
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