#include <tchar.h>
#include "nwpwin.h"
#include <list>   
#include<algorithm>

class main_window : public vsite::nwp::window
{
private:
	std::list<POINT> cords;
protected:
	
	void on_paint(HDC hdc) override  
	{ 


		if (!cords.empty())
		{
			
			MoveToEx(hdc, cords.begin()->x, cords.begin()->y, nullptr);
			for (POINT j : cords) LineTo(hdc, j.x, j.y);
		}
		
	}
	void on_left_button_down(POINT p) override
	{
	
		cords.push_back(p);
		InvalidateRect(*this, nullptr, true);
	}
	void on_key_down(int vk) override
	{
		switch (vk)
		{
		case VK_ESCAPE:
		{
			cords.clear();
			InvalidateRect(*this, nullptr, true);
			break;
		}
		case VK_BACK:
		{
			if (!cords.empty()) {
			cords.pop_back();
			InvalidateRect(*this, nullptr, true);
			}
			break;
		}
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
