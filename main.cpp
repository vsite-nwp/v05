#include <tchar.h>
#include "nwpwin.h"
#include <list>

class main_window : public vsite::nwp::window
{

private:
	std::list<POINT> lista;

protected:
	void on_paint(HDC hdc) override  
	{ 

	if (lista.empty()) { return; }
	MoveToEx(hdc, lista.front().x, lista.front().y, NULL);
	for (POINT i : lista) {LineTo(hdc, i.x, i.y);}

	}

	void on_left_button_down(POINT p) override
	{
	lista.push_back(p);
	InvalidateRect(*this, NULL, TRUE);
	}

	void on_key_down(int vk) override
	{

	if (lista.empty()) {return;}

		switch (vk) {
		case VK_ESCAPE:
			lista.clear();
			break;

		case VK_BACK:
			lista.pop_back();
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
