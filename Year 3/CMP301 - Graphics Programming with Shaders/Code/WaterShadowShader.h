// Light shader.h
// Basic single light shader setup
#ifndef _WATERSHADOWSHADER_H_
#define _WATERSHADOWSHADER_H_

#include "DXF.h"

using namespace std;
using namespace DirectX;


class WaterShadowShader : public BaseShader
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
		XMMATRIX lightView;
		XMMATRIX lightProjection;
	};

	struct LightBufferType
	{
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT3 direction;
		float padding;
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

	WaterShadowShader(ID3D11Device* device, HWND hwnd);
	~WaterShadowShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMap, Light* light, float timer, float amplitude, float frequency, float speed, XMFLOAT4 waveA, XMFLOAT4 waveB, XMFLOAT4 waveC);

private:
	void initShader(const wchar_t* vs, const wchar_t* ps);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11SamplerState* sampleState;
	ID3D11SamplerState* sampleStateShadow;
	ID3D11Buffer* lightBuffer;

	ID3D11Buffer* timeBuffer;
	ID3D11Buffer* waveBuffer;
};

#endif