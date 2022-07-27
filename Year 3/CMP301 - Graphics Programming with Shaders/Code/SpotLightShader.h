#pragma once

#include "DXF.h"

using namespace std;
using namespace DirectX;

class SpotLightShader : public BaseShader
{
private:
	struct LightBufferType
	{
		XMFLOAT4 specular;
		XMFLOAT4 diffuse;
		XMFLOAT4 ambient;

		XMFLOAT3 direction;
		float padding;

		XMFLOAT3 position;
		float cutOff;
	};

public:
	SpotLightShader(ID3D11Device* device, HWND hwnd);
	~SpotLightShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& projection, ID3D11ShaderResourceView* texture, Light* light, float spotLightCutoff);

private:
	void initShader(const wchar_t* cs, const wchar_t* ps);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11SamplerState* sampleState;
	ID3D11Buffer* lightBuffer;
};

