#include <tchar.h>
#include "nwpwin.h"
#include <vector>
#include <algorithm>
#include "gdi.h"

namespace {
	class sel_obj {
		HDC hdc;
		HGDIOBJ hOld;
	public:
		sel_obj(HDC hdc, HGDIOBJ hObj) : hdc(hdc), hOld(::SelectObject(hdc, hObj)) { }
		~sel_obj() { ::SelectObject(hdc, hOld); }
	};

	class main_window : public vsite::nwp::window
	{
	private:
		std::vector<POINT> points;
		int dx = 0;
		int dy = 0;

	protected:
		void on_paint(HDC hdc) override
		{
			using namespace vsite::nwp::gdi;
			pen pencil(RGB(0, 0, 0), 5, PS_SOLID);
			sel_obj sp(hdc, pencil);
			brush brushie(RGB(0, 0, 0));
			sel_obj sb(hdc, brushie);
			// DID_IT: iterate over points in container and draw polyline
			if (!points.empty()) {
				MoveToEx(hdc, points.front().x + dx, points.front().y + dy, nullptr);
				//::Ellipse(hdc, points.front().x - 5 + dx, points.front().y - 5 + dy, points.front().x + 5 + dx, points.front().y + 5 + dy);
			}
			for (auto p : points) {
				LineTo(hdc, p.x + dx, p.y + dy);
				//::Ellipse(hdc, p.x - 5 + dx, p.y - 5 + dy, p.x + 5 + dx, p.y + 5 + dy);
			}
		}
		void on_left_button_down(POINT p) override
		{
			// DID_IT: add point to container
			points.push_back(p);
			::InvalidateRect(*this, nullptr, true);
		}
		void on_key_down(int vk) override
		{
			// DID_IT: Esc - empty container
			// DID_IT: Backspace - remove last point
			switch (vk) {
			case VK_BACK:
				if (!points.empty())
					points.pop_back();
				break;
			case VK_ESCAPE:
				points.clear();
				break;
			case VK_UP:
				dy--;
				break;
			case VK_DOWN:
				dy++;
				break;
			case VK_LEFT:
				dx--;
				break;
			case VK_RIGHT:
				dx++;
				break;
			default:
				return;
			}
			::InvalidateRect(*this, nullptr, true);
		}
		void on_destroy() override
		{
			::PostQuitMessage(0);
		}
	};
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 5");
	return app.run();
}
