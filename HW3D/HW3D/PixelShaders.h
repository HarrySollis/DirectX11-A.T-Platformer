#pragma once
#include "Bindable.h"

class PixelShaders : public Bindable
{
public:
	PixelShaders(Graphics& gfx, const std::wstring& path);
	void Bind(Graphics& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
};