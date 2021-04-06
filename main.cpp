#include <tchar.h>
#include "nwpwin.h"
#include <list>

class main_window : public vsite::nwp::window
{

protected:

	void on_paint(HDC hdc) override{
		if (!pointList.empty()) {
			::MoveToEx(hdc, pointList.front().x, pointList.front().y, 0);
		}

		for (POINT points : pointList){
			::LineTo(hdc, points.x, points.y);
		}
	}

	void on_left_button_down(POINT points) override	{
		pointList.push_back(points);
		InvalidateRect(*this, 0, true);
	}

	void on_key_down(int vk) override{
		switch (vk){
		case VK_ESCAPE:
			pointList.clear();
			::InvalidateRect(*this, nullptr, true);


			break;
		case VK_BACK:
			if (pointList.empty()){
				return;
			}
			else {
				pointList.pop_back();
				::InvalidateRect(*this, nullptr, true);
			}
			
			break;
		default:
			return;
		}
	}
private:
	std::list<POINT> pointList;


	void on_destroy() override	{
		::PostQuitMessage(0);
	}
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int){
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 5 lab");
	return app.run();
}