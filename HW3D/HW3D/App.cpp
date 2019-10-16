#include "App.h"
#include "App.h"
#include <sstream>
#include <iomanip>

App::App()
	:
	wnd(800, 600, "Test Window")
{}

int App::Go()
{
	MSG msg;
	BOOL gResult;
	while (true)
	{
		while (/*(gResult = */PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))/* > 0*/
		{
			if (msg.message == WM_QUIT)
			{
				return msg.wParam;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);

			//while (!wnd.mouse.IsEmpty())
			//{
			//	const auto e = wnd.mouse.Read();
			//	if (e.GetType() == Mouse::Event::Type::Move)
			//	{
			//		std::ostringstream oss;
			//		oss << "Mouse Position: (" << e.GetPosX() << "," << e.GetPosY();
			//		wnd.SetTitle(oss.str());
			//	}
			//}

		}
		DoFrame();
	}	

	return {};
}

void App::DoFrame()
{
	//const float t = timer.Peek();
	//std::ostringstream oss;
	//oss << "Time Elapsed: " << std::setprecision(1) << std::fixed << t << "s";
	//wnd.SetTitle(oss.str());

	wnd.Gfx().ClearBuffer(1.0f, 1.0f, 1.0f);
	wnd.Gfx().DrawTriangle(
		-timer.Peek(),
		0.0f,
		0.0f
	);
	wnd.Gfx().DrawTriangle(
		timer.Peek(), 
		wnd.mouse.GetPosX() / 400.0f - 1.0f,
		-wnd.mouse.GetPosY() / 300.0f + 1.0f
	);
	wnd.Gfx().EndFrame();
}
