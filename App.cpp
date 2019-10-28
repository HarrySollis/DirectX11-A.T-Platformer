#include "App.h"
#include <sstream>
#include <iomanip>
#include "Sheet.h"
#include "Melon.h"
#include "Pyramid.h"
#include "Box.h"
#include <memory>
#include <algorithm>
#include "ObjMath.h"
#include "Surface.h"
//#include "GDIPlusManager.h"

//GDIPlusManager gdipm;

App::App()
	:
	wnd(800, 600, "Test Window")
{
	class Factory
	{
	public:
		Factory(Graphics& gfx)
			:
			gfx(gfx)
		{}
		std::unique_ptr<Drawable> operator()()
		{
			//return std::make_unique<Box>(
			//					gfx, rng, adist, ddist,
			//					odist, rdist, bdist
			//					);
			switch (typedist(rng))
			{
			case 0:
				return std::make_unique<Pyramid>(
					gfx, rng, adist, ddist,
					odist, rdist
					);
			case 1:
				return std::make_unique<Box>(
					gfx, rng, adist, ddist,
					odist, rdist, bdist
					);
			case 2:
				return std::make_unique<Melon>(
					gfx, rng, adist, ddist,
					odist, rdist, longdist, latdist
					);
			default:
				assert(false && "bad drawable type in factory");
				return {};
			}
		}
	private:
		Graphics& gfx;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_real_distribution<float> adist{ 0.0f,PI * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f,PI * 0.5f };
		std::uniform_real_distribution<float> odist{ 0.0f,PI * 0.08f };
		std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
		std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
		std::uniform_int_distribution<int> latdist{ 5,20 };
		std::uniform_int_distribution<int> longdist{ 10,40 };
		std::uniform_int_distribution<int> typedist{ 0,2 };
	};

	Factory f(wnd.Gfx());
	//drawables.reserve(nDrawables);
	std::generate_n(std::back_inserter(drawables), nDrawables, f);
	

	/*std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 1.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.08f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (auto i = 0; i < 180; i++)
	{
		boxes.push_back(std::make_unique<Box>(
			wnd.Gfx(), rng, adist,
			ddist, odist, rdist
			));
	}*/

	//const auto s = Surface::FromFile("Images\\Diamond-Ore-BlockTexture.png");

	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

App::~App()
{}

void App::DoFrame()
{
	auto dt = timer.Mark();
	wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
	for (auto& d : drawables)
	{
		d->Update(dt);
		d->Draw(wnd.Gfx());
	}
	wnd.Gfx().EndFrame();
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
		}
		DoFrame();
	}	

	//return {};
}