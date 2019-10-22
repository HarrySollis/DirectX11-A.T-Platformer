#include "App.h"
#include "App.h"
#include <sstream>
#include <iomanip>
#include "Box.h"
#include <memory>

App::App()
	:
	wnd(800, 600, "Test Window")
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (auto i = 0; i < 80; i++)
	{
		boxes.push_back(std::make_unique<Box>(
			wnd.Gfx(), rng, adist,
			ddist, odist, rdist
			));
	}
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

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

App::~App()
{}

void App::DoFrame()
{
	//const float t = timer.Peek();
	//std::ostringstream oss;
	//oss << "Time Elapsed: " << std::setprecision(1) << std::fixed << t << "s";
	//wnd.SetTitle(oss.str());

	//wnd.Gfx().ClearBuffer(1.0f, 1.0f, 1.0f);
	/*wnd.Gfx().DrawTriangle(
		-timer.Peek(),
		0.0f,
		0.0f
	);
	wnd.Gfx().DrawTriangle(
		timer.Peek(), 
		wnd.mouse.GetPosX() / 400.0f - 1.0f,
		-wnd.mouse.GetPosY() / 300.0f + 1.0f
	);*/

	auto dt = timer.Mark();
	wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
	for (auto& b : boxes)
	{
		b->Update(dt);
		b->Draw(wnd.Gfx());
	}
	wnd.Gfx().EndFrame();
}
