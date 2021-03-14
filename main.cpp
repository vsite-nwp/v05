#include <tchar.h>
#include "nwpwin.h"

class main_window : public vsite::nwp::window
{
protected:
	void on_paint(HDC hdc) override  
	{ 
	// TODO: iterate over points in container and draw polyline
	}
	void on_left_button_down(POINT p) override
	{
	// TODO: add point to container
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
