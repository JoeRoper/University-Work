// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"
#include "ManipulationShader.h"
#include "TerrainShader.h"
#include "WaterShader.h"
#include "ModelShader.h"
#include "SpotLightShader.h"

#include "VerticalBlurShader.h"
#include "HorizontalBlurShader.h"
#include "DepthOfFieldShader.h"
#include "TextureShader.h"
#include "DepthShader.h"
#include "ShadowShader.h"
#include "WaterDepthShader.h"
#include "WaterShadowShader.h"
#include "TerrainDepthShader.h"
#include "TerrainShadowShader.h"

#define LIGHT_AMOUNT 3

class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	bool frame();

protected:
	bool render();
	void gui();

	/////////Post Processing//////////////
	void firstPass();
	void downSample();
	void horizontalBlur();
	void verticalBlur();
	void depthOfFieldPass();
	void upSample();
	void finalPass();
	////////////Lights////////////////
	void updateLights();
	void guiLightsControls();
	////////Shadows///////////////
	void depthPass(Light* light);
	void shadowPass(Light* light);

	void camera2Pass();

private:

	/////Shaders/////////////
	ManipulationShader* shader;
	TerrainShader* terrainShader;
	WaterShader* waterShader;
	PlaneMesh* meshPlane;
	PlaneMesh* waterPlane;
	PlaneMesh* lavaPlane;
	CubeMesh* meshCube;

	SpotLightShader* spotLightShader;

	//////
	AModel* spotlightModel;
	ModelShader* modelShader;

	float time = 0.0f;
	float amplitude = 40.0f;
	float frequency = 0.393f;
	float speed = 4.0f;

	//////////////Post Processing/////////////////
	OrthoMesh* orthoMesh;

	RenderTexture* sceneTexture;
	RenderTexture* horizontalBlurTexture;
	RenderTexture* verticalBlurTexture;
	RenderTexture* downSampleTexture;
	RenderTexture* upSampleTexture;
	RenderTexture* depthOfFieldTexture;
	RenderTexture* cameraDepthTexture;

	VerticalBlurShader* verticalBlurShader;
	HorizontalBlurShader* horizontalBlurShader;
	DepthOfFieldShader* depthOfFieldShader;
	TextureShader* textureShader;

	float depthOfFieldRange;
	float depthOfFieldOffset;

	///////////////////Lights//////////

	Light* lights[LIGHT_AMOUNT];
	XMFLOAT4 lightsDiffuseColour[LIGHT_AMOUNT] = { { 0.6f, 0.6f, 0.6f, 1.0f}, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.9f, 0.9f, 0.9f, 0.9f } };
	XMFLOAT4 lightsAmbientColour[LIGHT_AMOUNT] = { {0.25f, 0.25f, 0.25f, 1.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.1f, 0.1f, 0.1f, 1.0f } };
	XMFLOAT3 lightsPosition[LIGHT_AMOUNT] = { { 0.0f, 10.0f, -20.0f }, { 2000.0f, 100.0f, 0.0f }, { 0.0f, -40.0f, 0.0f } };
	XMFLOAT3 lightsDirection[LIGHT_AMOUNT] = { {0.0f, -0.5f, 0.7f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f } };
	
	float light1DiffuseColour[4] = {lightsDiffuseColour[0].x, lightsDiffuseColour[0].y, lightsDiffuseColour[0].z, lightsDiffuseColour[0].w };
	float light1AmbientColour[4] = {lightsAmbientColour[0].x, lightsAmbientColour[0].y, lightsAmbientColour[0].z, lightsAmbientColour[0].w };
	float light1Position[3] = {lightsPosition[0].x, lightsPosition[0].y, lightsPosition[0].z };
	float light1Direction[3] = {lightsDirection[0].x, lightsDirection[0].y, lightsDirection[0].z };

	float light2DiffuseColour[4] = { lightsDiffuseColour[1].x, lightsDiffuseColour[1].y, lightsDiffuseColour[1].z, lightsDiffuseColour[1].w };
	float light2AmbientColour[4] = { lightsAmbientColour[1].x, lightsAmbientColour[1].y, lightsAmbientColour[1].z, lightsAmbientColour[1].w };
	float light2Position[3] = { lightsPosition[1].x, lightsPosition[1].y, lightsPosition[1].z };
	float light2Direction[3] = { lightsDirection[1].x, lightsDirection[1].y, lightsDirection[1].z };

	float light3DiffuseColour[4] = { lightsDiffuseColour[2].x, lightsDiffuseColour[2].y, lightsDiffuseColour[2].z, lightsDiffuseColour[2].w };
	float light3AmbientColour[4] = { lightsAmbientColour[2].x, lightsAmbientColour[2].y, lightsAmbientColour[2].z, lightsAmbientColour[2].w };
	float light3Position[3] = { lightsPosition[2].x, lightsPosition[2].y, lightsPosition[2].z };
	float light3Direction[3] = { lightsDirection[2].x, lightsDirection[2].y, lightsDirection[2].z };

	// Spot light angle
	float spotLightCutoff = 50.0f;

	CubeMesh* cubeMesh;
	CubeMesh* cubeMesh1;
	CubeMesh* cubeMesh2;

	////////////////////Shadows///////////////////////
	ShadowShader* shadowShader;
	DepthShader* depthShader;
	ShadowMap* shadowMap;
	WaterDepthShader* waterDepthShader;
	WaterShadowShader* waterShadowShader;

	TerrainDepthShader* terrainDepthShader;
	TerrainShadowShader* terrainShadowShader;

	RenderTexture* shadowTexture;

	///////////////////Other Scene///////////////////
	CubeMesh* cubeMesh4;
	SphereMesh* sphereMesh;
	PlaneMesh* planeMesh2;
	AModel* model;
	float rotation = 0.0f;

	FPCamera* cameraMinimap;
	OrthoMesh* orthoMeshCamera2;
	RenderTexture* camera2Texture;

	////////////////Waves///////////////////////
	XMFLOAT4 waveA = XMFLOAT4(1, 1, 0.25, 60);
	XMFLOAT4 waveB = XMFLOAT4(1, 0.6, 0.25, 31);
	XMFLOAT4 waveC = XMFLOAT4(1, 1.3, 0.25, 18);

	float waveAGui[4] = { 1, 1, 0.25, 60 };
	float waveBGui[4] = { 1, 0.6, 0.25, 31 };
	float waveCGui[4] = { 1, 1.3, 0.25, 18 };

	XMFLOAT4 lavaA = XMFLOAT4(0.3, 0.3, 0.25, 60);
	XMFLOAT4 lavaB = XMFLOAT4(0.3, 0.6, 0.25, 31);
	XMFLOAT4 lavaC = XMFLOAT4(0.3, 0.3, 0.25, 18);

	float lavaAGui[4] = { 1, 0.3, 0.25, 10 };
	float lavaBGui[4] = { 1, 0.6, 0.25, 11 };
	float lavaCGui[4] = { 1, 0.3, 0.25, 18 };
};

#endif
