#pragma once

#include "Win.h"
#include "ExceptionCheck.h"
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <memory>
#include <random>
#include <vector>
#include "DxgiInfoManager.h"


#pragma comment(lib, "D3DCompiler.lib")

class Graphics
{
	//class Exception : public ExceptionCheck
	//{
	//	using ExceptionCheck::ExceptionCheck;
	//};
	//class HrException : public Exception
	//{
	//public:
	//	HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;
	//	const char* what() const noexcept override;
	//	const char* GetType() const noexcept override;
	//	HRESULT GetErrorCode() const noexcept;
	//	std::string GetErrorString() const noexcept;
	//	std::string GetErrorDescription() const noexcept;
	//	std::string GetErrorInfo() const noexcept;
	//private:
	//	HRESULT hr;
	//	std::string info;
	//};
	//class InfoException : public Exception
	//{
	//public:
	//	InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept;
	//	const char* what() const noexcept override;
	//	const char* GetType() const noexcept override;
	//	std::string GetErrorInfo() const noexcept;
	//private:
	//	std::string info;
	//};
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator = (const Graphics&) = delete;
	~Graphics() = default;
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
	void DrawIndexed(UINT count) noexcept;
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void DrawTriangle(float angle, float x, float y);
	
public:
	DirectX::XMMATRIX projection;
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
//#ifndef NDEBUG
//	DxgiInfoManager infoManager;
//#endif
};
