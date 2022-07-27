// Colour shader.h
// Simple shader example.
#pragma once

#include "DXF.h"

using namespace std;
using namespace DirectX;


class TerrainDepthShader : public BaseShader
{
	struct TimeBufferType
	{
		float time;//should be based on delta time from the timer class
		float amplitude;
		float frequency;
		float speed;
	};

	struct TerrainBufferType
	{
		float amplitude;
		XMFLOAT3 padding;
	};

public:

	TerrainDepthShader(ID3D11Device* device, HWND hwnd);
	~TerrainDepthShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& projection, ID3D11ShaderResourceView* texture, float amplitude);

private:
	void initShader(const wchar_t* vs, const wchar_t* ps);

private:
	ID3D11Buffer* matrixBuffer;

	ID3D11SamplerState* sampleState;

	ID3D11Buffer* timeBuffer;
	ID3D11Buffer* terrainBuffer;
};
