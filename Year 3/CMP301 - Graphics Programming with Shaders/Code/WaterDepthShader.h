// Colour shader.h
// Simple shader example.
#pragma once

#include "DXF.h"

using namespace std;
using namespace DirectX;


class WaterDepthShader : public BaseShader
{
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

	WaterDepthShader(ID3D11Device* device, HWND hwnd);
	~WaterDepthShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& projection, float timer, float amplitude, float frequency, float speed, XMFLOAT4 waveA, XMFLOAT4 waveB, XMFLOAT4 waveC);

private:
	void initShader(const wchar_t* vs, const wchar_t* ps);

private:
	ID3D11Buffer* matrixBuffer;

	ID3D11SamplerState* sampleState;

	ID3D11Buffer* timeBuffer;
	ID3D11Buffer* waveBuffer;
};
