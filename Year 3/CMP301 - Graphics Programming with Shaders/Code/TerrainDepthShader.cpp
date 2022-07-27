#include "TerrainDepthShader.h"

TerrainDepthShader::TerrainDepthShader(ID3D11Device* device, HWND hwnd) : BaseShader(device, hwnd)
{
	initShader(L"terrainDepth_vs.cso", L"depth_ps.cso");
}

TerrainDepthShader::~TerrainDepthShader()
{
	// Release the matrix constant buffer.
	if (matrixBuffer)
	{
		matrixBuffer->Release();
		matrixBuffer = 0;
	}

	// Release the layout.
	if (layout)
	{
		layout->Release();
		layout = 0;
	}

	//Release base shader components
	BaseShader::~BaseShader();
}

void TerrainDepthShader::initShader(const wchar_t* vsFilename, const wchar_t* psFilename)
{
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC timeBufferDesc;
	D3D11_BUFFER_DESC waveBufferDesc;
	D3D11_BUFFER_DESC terrainBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;

	// Load (+ compile) shader files
	loadVertexShader(vsFilename);
	loadPixelShader(psFilename);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;
	renderer->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer);

	// Setup time buffer
	// Setup the description of the time dynamic constant buffer that is in the pixel shader.
	// Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
	timeBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	timeBufferDesc.ByteWidth = sizeof(TimeBufferType);
	timeBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	timeBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	timeBufferDesc.MiscFlags = 0;
	timeBufferDesc.StructureByteStride = 0;
	renderer->CreateBuffer(&timeBufferDesc, NULL, &timeBuffer);

	// Setup terrain buffer
// Setup the description of the terrain dynamic constant buffer that is in the pixel shader.
// Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
	terrainBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	terrainBufferDesc.ByteWidth = sizeof(TerrainBufferType);
	terrainBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	terrainBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	terrainBufferDesc.MiscFlags = 0;
	terrainBufferDesc.StructureByteStride = 0;
	renderer->CreateBuffer(&terrainBufferDesc, NULL, &terrainBuffer);
}

void TerrainDepthShader::setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& projection, ID3D11ShaderResourceView* texture, float amplitude)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;

	// Transpose the matrices to prepare them for the shader.
	XMMATRIX tworld = XMMatrixTranspose(world);
	XMMATRIX tview = XMMatrixTranspose(view);
	XMMATRIX tproj = XMMatrixTranspose(projection);

	// Lock the constant buffer so it can be written to.
	deviceContext->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->world = tworld;// worldMatrix;
	dataPtr->view = tview;
	dataPtr->projection = tproj;
	deviceContext->Unmap(matrixBuffer, 0);
	deviceContext->VSSetConstantBuffers(0, 1, &matrixBuffer);

	//Additional
	// Send terrain data to vertex shader
	TerrainBufferType* terrainPtr;
	deviceContext->Map(terrainBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	terrainPtr = (TerrainBufferType*)mappedResource.pData;
	terrainPtr->amplitude = amplitude;
	terrainPtr->padding = XMFLOAT3(0.0f, 0.0f, 0.0f);
	deviceContext->Unmap(terrainBuffer, 0);
	deviceContext->VSSetConstantBuffers(1, 1, &terrainBuffer);
	deviceContext->VSSetShaderResources(0, 1, &texture);




}
