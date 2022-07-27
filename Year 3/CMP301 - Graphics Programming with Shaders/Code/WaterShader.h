#pragma once
#include "DXF.h"

#define LIGHT_AMOUNT 3

using namespace std;
using namespace DirectX;

class WaterShader : public BaseShader
{
private:
	struct LightBufferType
	{
		XMFLOAT4 diffuse;
		XMFLOAT4 ambient;
		XMFLOAT4 direction;
	};

	struct TimeBufferType
	{
		float time;//should be based on delta time from the timer class
		float amplitude;
		float frequency;
		float speed;
	};

	struct WaveBufferType
	{
		XMFLOAT4 waveA;
		XMFLOAT4 waveB;
		XMFLOAT4 waveC;
	};

public:
	WaterShader(ID3D11Device* device, HWND hwnd);
	~WaterShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, ID3D11ShaderResourceView* texturePS, ID3D11ShaderResourceView* textureVS, Light* light, float timer, float amplitude, float frequency, float speed, XMFLOAT4 waveA, XMFLOAT4 waveB, XMFLOAT4 waveC);

private:
	void initShader(const wchar_t* cs, const wchar_t* ps);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11SamplerState* sampleState;
	ID3D11Buffer* lightBuffer;
	ID3D11Buffer* timeBuffer;
	ID3D11Buffer* waveBuffer;
};

