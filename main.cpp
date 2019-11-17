#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include <list>

class MainWindow : public Window
{
	std::list<POINT> pt;
protected:
		void OnPaint(HDC hdc)
		{
			if (!pt.empty())
			{
				MoveToEx(hdc, pt.front().x, pt.front().y, nullptr);
				for (auto it : pt)
					LineTo(hdc, it.x, it.y);
			}
		}
			void OnLButtonDown(POINT p)
		{
			pt.push_back(p);
			InvalidateRect(*this, nullptr, true);
		}
			void OnKeyDown(int vk)
		{
			switch (vk)
			{
			case VK_ESCAPE:
				pt.clear();
				InvalidateRect(*this, nullptr, true);
				break;
			case VK_BACK:
				if (!pt.empty())
					pt.pop_back();
				InvalidateRect(*this, nullptr, true);
				break;
			default:
				break;
			}
		}
		void OnDestroy()
		{
			::PostQuitMessage(0);
		}
	};
	int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
	{
		Application app;
		MainWindow wnd;
		wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP 5"));
		return app.Run();
	}