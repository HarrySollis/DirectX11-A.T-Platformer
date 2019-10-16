#pragma once

#include "Win.h"
#include "ExceptionCheck.h"
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <vector>


#pragma comment(lib, "D3DCompiler.lib")

class Graphics
{
public:
	//class Exception : public ExceptionCheck
	//{
	//	using ExceptionCheck::ExceptionCheck;
	//};
	//class HrException : public Exception
	//{
	//public:
	//	HrException(int line, const char* file, HRESULT hr) noexcept;
	//	const char* what() const noexcept override;
	//	const char* GetType() const noexcept override;
	//	HRESULT GetErrorCode() const noexcept;
	//	std::string GetErrorString() const noexcept;
	//	std::string GetErrorDescription() const noexcept;
	//private:
	//	HRESULT hr;
	//class DeviceRemovedException : public HrException
	//{
	//	using HrException::HrException;
	//};
	//};


	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator = (const Graphics&) = delete;
	~Graphics() = default;
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
	void DrawTriangle(float angle, float x, float y);
	
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
};
