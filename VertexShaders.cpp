#include "VertexShaders.h"

VertexShaders::VertexShaders(Graphics& gfx, const std::wstring& path)
{
	D3DReadFileToBlob(path.c_str(), &pBytecodeBlob);
	GetDevice(gfx)->CreateVertexShader(
		pBytecodeBlob->GetBufferPointer(),
		pBytecodeBlob->GetBufferSize(),
		nullptr,
		&pVertexShader
	);
}

void VertexShaders::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}

ID3DBlob* VertexShaders::GetBytecode() const noexcept
{
	return pBytecodeBlob.Get();
}