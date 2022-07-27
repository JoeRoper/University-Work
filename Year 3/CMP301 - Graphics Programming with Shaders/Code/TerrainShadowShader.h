// Light shader.h
// Basic single light shader setup
#ifndef _TERRAINSHADOWSHADER_H_
#define _TERRAINSHADOWSHADER_H_

#include "DXF.h"

using namespace std;
using namespace DirectX;


class TerrainShadowShader : public BaseShader
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

	struct TerrainBufferType
	{
		float amplitude;
		XMFLOAT3 padding;
	};

public:

	TerrainShadowShader(ID3D11Device* device, HWND hwnd);
	~TerrainShadowShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, ID3D11ShaderResourceView* texturePS, ID3D11ShaderResourceView* textureVS, ID3D11ShaderResourceView* depthMap, Light* light, float amplitude);

private:
	void initShader(const wchar_t* vs, const wchar_t* ps);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11SamplerState* sampleState;
	ID3D11SamplerState* sampleStateShadow;
	ID3D11Buffer* lightBuffer;
	ID3D11Buffer* terrainBuffer;
};

#endif