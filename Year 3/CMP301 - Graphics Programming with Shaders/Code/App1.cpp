// Lab1.cpp
// Lab 1 example, simple coloured triangle mesh
#include "App1.h"

App1::App1()
{
	meshPlane = nullptr;
	shader = nullptr;
	terrainShader = nullptr;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);

	// Initalise scene variables.
	// Load texture.
	textureMgr->loadTexture(L"brick", L"res/brick1.dds");
	textureMgr->loadTexture(L"heightMap", L"res/volcano-height-map.gif");
	textureMgr->loadTexture(L"water", L"res/water-texture.jpg");
	textureMgr->loadTexture(L"lava", L"res/lava-texture.jpg");
	textureMgr->loadTexture(L"rock", L"res/rock-texture.jpg");

	// Create Mesh object and shader object
	meshPlane = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext(), 100);
	waterPlane = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext(), 200);
	lavaPlane = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext(), 25);
	meshCube = new CubeMesh(renderer->getDevice(), renderer->getDeviceContext());

	cubeMesh = new CubeMesh(renderer->getDevice(), renderer->getDeviceContext());
	cubeMesh1 = new CubeMesh(renderer->getDevice(), renderer->getDeviceContext());
	cubeMesh2 = new CubeMesh(renderer->getDevice(), renderer->getDeviceContext());

	cubeMesh4 = new CubeMesh(renderer->getDevice(), renderer->getDeviceContext());
	sphereMesh = new SphereMesh(renderer->getDevice(), renderer->getDeviceContext());
	planeMesh2 = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext());
	model = new AModel(renderer->getDevice(), "res/teapot.obj");

	// This is your shadow map
	int shadowmapWidth = 4096;
	int shadowmapHeight = 4096;
	shadowMap = new ShadowMap(renderer->getDevice(), shadowmapWidth, shadowmapHeight);

	orthoMesh = new OrthoMesh(renderer->getDevice(), renderer->getDeviceContext(), screenWidth, screenHeight);	// Full screen size
	orthoMeshCamera2 = new OrthoMesh(renderer->getDevice(), renderer->getDeviceContext(), screenWidth / 4, screenHeight / 4, -screenWidth / 2.7, screenHeight / 2.7);

	spotlightModel = new AModel(renderer->getDevice(), "res/teapot.obj");

	shader = new ManipulationShader(renderer->getDevice(), hwnd);
	terrainShader = new TerrainShader(renderer->getDevice(), hwnd);
	waterShader = new WaterShader(renderer->getDevice(), hwnd);
	spotLightShader = new SpotLightShader(renderer->getDevice(), hwnd);
	textureShader = new TextureShader(renderer->getDevice(), hwnd);
	horizontalBlurShader = new HorizontalBlurShader(renderer->getDevice(), hwnd);
	verticalBlurShader = new VerticalBlurShader(renderer->getDevice(), hwnd);
	depthOfFieldShader = new DepthOfFieldShader(renderer->getDevice(), hwnd);
	depthShader = new DepthShader(renderer->getDevice(), hwnd);
	shadowShader = new ShadowShader(renderer->getDevice(), hwnd);
	waterDepthShader = new WaterDepthShader(renderer->getDevice(), hwnd);
	waterShadowShader = new WaterShadowShader(renderer->getDevice(), hwnd);
	terrainDepthShader = new TerrainDepthShader(renderer->getDevice(), hwnd);
	terrainShadowShader = new TerrainShadowShader(renderer->getDevice(), hwnd);

	//Initialise required render textures. We need a RT for the first pass at the scene (unblurred), one to store the horizontal blur, and one to store the combination of horiontal and vertical blur.
	horizontalBlurTexture = new RenderTexture(renderer->getDevice(), screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);
	verticalBlurTexture = new RenderTexture(renderer->getDevice(), screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);
	downSampleTexture = new RenderTexture(renderer->getDevice(), screenWidth / 2, screenHeight / 2, SCREEN_NEAR, SCREEN_DEPTH);
	upSampleTexture = new RenderTexture(renderer->getDevice(), screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);
	depthOfFieldTexture = new RenderTexture(renderer->getDevice(), screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);
	cameraDepthTexture = new RenderTexture(renderer->getDevice(), screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);
	sceneTexture = new RenderTexture(renderer->getDevice(), screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);
	camera2Texture = new RenderTexture(renderer->getDevice(), screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);

	int sceneWidth = 400;
	int sceneHeight = 400;

	for (int i = 0; i < 3; i++)
	{
		lights[i] = new Light;
		lights[i]->generateOrthoMatrix((float)sceneWidth, (float)sceneHeight, 0.1f, 100.f);
	}

	camera->setPosition(0.0f, 10.0f, -80.0f);

	// Depth of field initial range
	depthOfFieldRange = 1.0f;
	depthOfFieldOffset = 0.0f;

	// Create the camera object and set to default position.
	cameraMinimap = new FPCamera(input, sWidth, sHeight, wnd);
	cameraMinimap->setPosition(0.0f, -20.0f, -40.0f);
	cameraMinimap->setRotation(40.0f, 0.0f, 0.0f);

}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	// Release the Direct3D object.
	if (meshPlane)
	{
		delete meshPlane;
		meshPlane = 0;
	}

	if (shader)
	{
		delete shader;
		shader = 0;
	}

	if (terrainShader)
	{
		delete terrainShader;
		terrainShader = 0;
	}

	if (waterShader)
	{
		delete waterShader;
		waterShader = 0;
	}
}


bool App1::frame()
{
	bool result;

	result = BaseApplication::frame();
	if (!result)
	{
		return false;
	}
	
	time += timer->getTime();

	// Render the graphics.
	result = render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool App1::render()
{
	updateLights();

	//// Render scene
	
	depthPass(lights[0]);
	

	camera2Pass();

	firstPass();

	downSample();

	// Apply horizontal blur stage
	horizontalBlur();

	// Apply vertical blur to the horizontal blur stage
	verticalBlur();

	depthOfFieldPass();

	upSample();

	// Render final pass to frame buffer
	finalPass();

	

	return true;
}

void App1::firstPass()
{
	// Set the render target to be the render to texture and clear it
	sceneTexture->setRenderTarget(renderer->getDeviceContext());
	sceneTexture->clearRenderTarget(renderer->getDeviceContext(), 0.0f, 0.0f, 1.0f, 1.0f);

	// Get matrices
	camera->update();

	XMMATRIX worldMatrix = renderer->getWorldMatrix();
	XMMATRIX viewMatrix = camera->getViewMatrix();
	XMMATRIX projectionMatrix = renderer->getProjectionMatrix();

	worldMatrix = XMMatrixTranslation(-50.0, -4.0, -50.0);
	meshPlane->sendData(renderer->getDeviceContext());
	terrainShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"rock"), textureMgr->getTexture(L"heightMap"), lights[0], amplitude);
	terrainShader->render(renderer->getDeviceContext(), meshPlane->getIndexCount());

	worldMatrix = XMMatrixTranslation(-10.0, amplitude - 26, -17.0);
	lavaPlane->sendData(renderer->getDeviceContext());
	waterShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"lava"), textureMgr->getTexture(L""), lights[0], time, amplitude, frequency, speed, lavaA, lavaB, lavaC);
	waterShader->render(renderer->getDeviceContext(), lavaPlane->getIndexCount());

	//Render shape with simple lighting shader set.
	worldMatrix = XMMatrixTranslation(lights[0]->getPosition().x, lights[0]->getPosition().y, lights[0]->getPosition().z);
	cubeMesh->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"brick"));
	textureShader->render(renderer->getDeviceContext(), cubeMesh->getIndexCount());

	worldMatrix = XMMatrixTranslation(lights[1]->getPosition().x, lights[1]->getPosition().y, lights[1]->getPosition().z);
	cubeMesh1->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"water"));
	textureShader->render(renderer->getDeviceContext(), cubeMesh1->getIndexCount());

	worldMatrix = XMMatrixTranslation(lights[2]->getPosition().x, lights[2]->getPosition().y, lights[2]->getPosition().z);
	cubeMesh2->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"rock"));
	textureShader->render(renderer->getDeviceContext(), cubeMesh2->getIndexCount());

	shadowPass(lights[0]);


	// Reset the render target back to the original back buffer and not the render to texture anymore.
	renderer->setBackBufferRenderTarget();
}

void App1::downSample()
{
	// Set the render target to be the render to texture and clear it
	downSampleTexture->setRenderTarget(renderer->getDeviceContext());
	downSampleTexture->clearRenderTarget(renderer->getDeviceContext(), 0.0f, 1.0f, 0.0f, 1.0f);

	XMMATRIX worldMatrix, baseViewMatrix, orthoMatrix;

	worldMatrix = renderer->getWorldMatrix();
	baseViewMatrix = camera->getOrthoViewMatrix();
	orthoMatrix = horizontalBlurTexture->getOrthoMatrix();

	// Render for Horizontal Blur
	renderer->setZBuffer(false);
	orthoMesh->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, sceneTexture->getShaderResourceView());
	textureShader->render(renderer->getDeviceContext(), orthoMesh->getIndexCount());
	renderer->setZBuffer(true);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	renderer->setBackBufferRenderTarget();
}

void App1::horizontalBlur()
{
	XMMATRIX worldMatrix, baseViewMatrix, orthoMatrix;

	float screenSizeX = (float)horizontalBlurTexture->getTextureWidth();
	horizontalBlurTexture->setRenderTarget(renderer->getDeviceContext());
	horizontalBlurTexture->clearRenderTarget(renderer->getDeviceContext(), 1.0f, 1.0f, 0.0f, 1.0f);

	worldMatrix = renderer->getWorldMatrix();
	baseViewMatrix = camera->getOrthoViewMatrix();
	orthoMatrix = horizontalBlurTexture->getOrthoMatrix();

	// Render for Horizontal Blur
	renderer->setZBuffer(false);
	orthoMesh->sendData(renderer->getDeviceContext());
	horizontalBlurShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, downSampleTexture->getShaderResourceView(), screenSizeX);
	horizontalBlurShader->render(renderer->getDeviceContext(), orthoMesh->getIndexCount());
	renderer->setZBuffer(true);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	renderer->setBackBufferRenderTarget();
}

void App1::verticalBlur()
{
	XMMATRIX worldMatrix, baseViewMatrix, orthoMatrix;

	float screenSizeY = (float)verticalBlurTexture->getTextureHeight();
	verticalBlurTexture->setRenderTarget(renderer->getDeviceContext());
	verticalBlurTexture->clearRenderTarget(renderer->getDeviceContext(), 0.0f, 1.0f, 1.0f, 1.0f);

	worldMatrix = renderer->getWorldMatrix();
	baseViewMatrix = camera->getOrthoViewMatrix();
	// Get the ortho matrix from the render to texture since texture has different dimensions being that it is smaller.
	orthoMatrix = verticalBlurTexture->getOrthoMatrix();

	// Render for Vertical Blur
	renderer->setZBuffer(false);
	orthoMesh->sendData(renderer->getDeviceContext());
	verticalBlurShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, horizontalBlurTexture->getShaderResourceView(), screenSizeY);
	verticalBlurShader->render(renderer->getDeviceContext(), orthoMesh->getIndexCount());
	renderer->setZBuffer(true);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	renderer->setBackBufferRenderTarget();
}

void App1::depthOfFieldPass()
{
	XMMATRIX worldMatrix, baseViewMatrix, orthoMatrix;

	depthOfFieldTexture->setRenderTarget(renderer->getDeviceContext());
	depthOfFieldTexture->clearRenderTarget(renderer->getDeviceContext(), 0.0f, 1.0f, 1.0f, 1.0f);

	worldMatrix = renderer->getWorldMatrix();
	baseViewMatrix = camera->getOrthoViewMatrix();
	// Get the ortho matrix from the render to texture since texture has different dimensions being that it is smaller.
	orthoMatrix = depthOfFieldTexture->getOrthoMatrix();

	// Render for Vertical Blur
	renderer->setZBuffer(false);
	orthoMesh->sendData(renderer->getDeviceContext());
	depthOfFieldShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, sceneTexture->getShaderResourceView(), verticalBlurTexture->getShaderResourceView(), cameraDepthTexture->getShaderResourceView(), depthOfFieldRange, SCREEN_NEAR, SCREEN_DEPTH, depthOfFieldOffset);
	depthOfFieldShader->render(renderer->getDeviceContext(), orthoMesh->getIndexCount());
	renderer->setZBuffer(true);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	renderer->setBackBufferRenderTarget();
}

void App1::upSample()
{
	//reverse the down sampling
	//render it again using another render texture 
	//and ortho mesh se to full size
	upSampleTexture->setRenderTarget(renderer->getDeviceContext());
	upSampleTexture->clearRenderTarget(renderer->getDeviceContext(), 0.0f, 0.0f, 1.0f, 1.0f);

	// RENDER THE RENDER TEXTURE SCENE
	// Requires 2D rendering and an ortho mesh.

	XMMATRIX worldMatrix = renderer->getWorldMatrix();
	XMMATRIX baseViewMatrix = camera->getOrthoViewMatrix();  // ortho matrix for 2D rendering
	XMMATRIX orthoMatrix = upSampleTexture->getOrthoMatrix();	// Default camera position for orthographic rendering

	renderer->setZBuffer(false);
	orthoMesh->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, depthOfFieldTexture->getShaderResourceView());
	textureShader->render(renderer->getDeviceContext(), orthoMesh->getIndexCount());
	renderer->setZBuffer(true);

	renderer->setBackBufferRenderTarget();
}

void App1::finalPass()
{
	// Clear the scene. (default blue colour)
	renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// RENDER THE RENDER TEXTURE SCENE
	// Requires 2D rendering and an ortho mesh.
	renderer->setZBuffer(false);


	XMMATRIX worldMatrix = renderer->getWorldMatrix();
	XMMATRIX orthoMatrix = renderer->getOrthoMatrix();  // ortho matrix for 2D rendering
	XMMATRIX orthoViewMatrix = camera->getOrthoViewMatrix();	// Default camera position for orthographic rendering

	orthoMesh->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, orthoViewMatrix, orthoMatrix, upSampleTexture->getShaderResourceView());
	textureShader->render(renderer->getDeviceContext(), orthoMesh->getIndexCount());

	renderer->setZBuffer(true);

	orthoMeshCamera2->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, orthoViewMatrix, orthoMatrix, camera2Texture->getShaderResourceView());
	textureShader->render(renderer->getDeviceContext(), orthoMeshCamera2->getIndexCount());


	// Render GUI
	gui();

	// Present the rendered scene to the screen.
	renderer->endScene();
}

void App1::updateLights()
{
	for (int i = 0; i < 3; i++)
	{
		lights[i]->setDiffuseColour(lightsDiffuseColour[i].x, lightsDiffuseColour[i].y, lightsDiffuseColour[i].z, lightsDiffuseColour[i].w);
		lights[i]->setAmbientColour(lightsAmbientColour[i].x, lightsAmbientColour[i].y, lightsAmbientColour[i].z, lightsAmbientColour[i].w);
		lights[i]->setPosition(lightsPosition[i].x, lightsPosition[i].y, lightsPosition[i].z);
		lights[i]->setDirection(lightsDirection[i].x, lightsDirection[i].y, lightsDirection[i].z);
	}
}

void App1::gui()
{
	// Force turn off unnecessary shader stages.
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->HSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->DSSetShader(NULL, NULL, 0);

	// Build UI
	ImGui::Text("FPS: %.2f", timer->getFPS());
	ImGui::Checkbox("Wireframe mode", &wireframeToggle);

	if (ImGui::CollapsingHeader("Depth Of Field", 0))
	{
		ImGui::SliderFloat("Offset", &depthOfFieldOffset, -5.0f, 5.0f);
		ImGui::SliderFloat("Range", &depthOfFieldRange, 0.0f, 5.0f);
	}

	if (ImGui::CollapsingHeader("Terrain", 0))
	{
		ImGui::SliderFloat("Volcano Height", &amplitude, 0.0f, 40.0f);
	}

	if (ImGui::CollapsingHeader("Waves", 0))
	{
		if (ImGui::InputFloat4("Wave A", waveAGui)) {

			waveA = XMFLOAT4(waveAGui[0], waveAGui[1], waveAGui[2], waveAGui[3]);
		}
		if (ImGui::InputFloat4("Wave B", waveBGui)) {

			waveB = XMFLOAT4(waveBGui[0], waveBGui[1], waveBGui[2], waveBGui[3]);
		}
		if (ImGui::InputFloat4("Wave C", waveCGui)) {

			waveC = XMFLOAT4(waveCGui[0], waveCGui[1], waveCGui[2], waveCGui[3]);
		}
	}

	if (ImGui::CollapsingHeader("Lava", 0))
	{
		if (ImGui::InputFloat4("Wave A", lavaAGui)) {

			lavaA = XMFLOAT4(lavaAGui[0], lavaAGui[1], lavaAGui[2], lavaAGui[3]);
		}
		if (ImGui::InputFloat4("Wave B", lavaBGui)) {

			lavaB = XMFLOAT4(lavaBGui[0], lavaBGui[1], lavaBGui[2], lavaBGui[3]);
		}
		if (ImGui::InputFloat4("Wave C", lavaCGui)) {

			lavaC = XMFLOAT4(lavaCGui[0], lavaCGui[1], lavaCGui[2], lavaCGui[3]);
		}
	}


	guiLightsControls();

	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void App1::guiLightsControls()
{
	if (ImGui::CollapsingHeader("Lights", 0))
	{
		if (ImGui::CollapsingHeader("Light 1", 0))
		{
			// Edit a color (stored as ~4 floats)
			if (ImGui::ColorEdit4("Light Diffuse Colour", light1DiffuseColour))
			{
				lightsDiffuseColour[0].x = (light1DiffuseColour[0]);
				lightsDiffuseColour[0].y = (light1DiffuseColour[1]);
				lightsDiffuseColour[0].z = (light1DiffuseColour[2]);
				lightsDiffuseColour[0].z = (light1DiffuseColour[3]);
			}

			if (ImGui::ColorEdit4("Light Ambient Colour", light1AmbientColour))
			{
				lightsAmbientColour[0].x = (light1AmbientColour[0]);
				lightsAmbientColour[0].y = (light1AmbientColour[1]);
				lightsAmbientColour[0].z = (light1AmbientColour[2]);
				lightsAmbientColour[0].z = (light1AmbientColour[3]);
			}

			if (ImGui::InputFloat3("Light Position:", light1Position)) {
		
				lightsPosition[0].x = (light1Position[0]);
				lightsPosition[0].y = (light1Position[1]);
				lightsPosition[0].z = (light1Position[2]);
			}
			if (ImGui::InputFloat3("Light Direction:", light1Direction)) {
		
				lightsDirection[0].x = (light1Direction[0]);
				lightsDirection[0].y = (light1Direction[1]);
				lightsDirection[0].z = (light1Direction[2]);
			}
		}

		if (ImGui::CollapsingHeader("Light 2", 0))
		{
			// Edit a color (stored as ~4 floats)
			if (ImGui::ColorEdit4("Light Diffuse Colour", light2DiffuseColour))
			{
				lightsDiffuseColour[1].x = (light2DiffuseColour[0]);
				lightsDiffuseColour[1].y = (light2DiffuseColour[1]);
				lightsDiffuseColour[1].z = (light2DiffuseColour[2]);
				lightsDiffuseColour[1].z = (light2DiffuseColour[3]);
			}

			if (ImGui::ColorEdit4("Light Ambient Colour", light2AmbientColour))
			{
				lightsAmbientColour[1].x = (light2AmbientColour[0]);
				lightsAmbientColour[1].y = (light2AmbientColour[1]);
				lightsAmbientColour[1].z = (light2AmbientColour[2]);
				lightsAmbientColour[1].z = (light2AmbientColour[3]);
			}

			if (ImGui::InputFloat3("Light Position:", light2Position)) {
	
				lightsPosition[1].x = (light2Position[0]);
				lightsPosition[1].y = (light2Position[1]);
				lightsPosition[1].z = (light2Position[2]);
			}
			if (ImGui::InputFloat3("Light Direction:", light2Direction)) {
		
				lightsDirection[1].x = (light2Direction[0]);
				lightsDirection[1].y = (light2Direction[1]);
				lightsDirection[1].z = (light2Direction[2]);
			}
		}

		if (ImGui::CollapsingHeader("Spotlight", 0))
		{
			ImGui::SliderFloat("Spot Light Cutoff", &spotLightCutoff, 0.0f, 200.0f);
			// Edit a color (stored as ~4 floats)
			if (ImGui::ColorEdit4("Light Diffuse Colour", light3DiffuseColour))
			{
				lightsDiffuseColour[2].x = (light3DiffuseColour[0]);
				lightsDiffuseColour[2].y = (light3DiffuseColour[1]);
				lightsDiffuseColour[2].z = (light3DiffuseColour[2]);
				lightsDiffuseColour[2].z = (light3DiffuseColour[3]);
			}

			if (ImGui::ColorEdit4("Light Ambient Colour", light3AmbientColour))
			{
				lightsAmbientColour[2].x = (light3AmbientColour[0]);
				lightsAmbientColour[2].y = (light3AmbientColour[1]);
				lightsAmbientColour[2].z = (light3AmbientColour[2]);
				lightsAmbientColour[2].z = (light3AmbientColour[3]);
			}

			if (ImGui::InputFloat3("Light Position:", light3Position)) {

				lightsPosition[2].x = (light3Position[0]);
				lightsPosition[2].y = (light3Position[1]);
				lightsPosition[2].z = (light3Position[2]);
			}
			if (ImGui::InputFloat3("Light Direction:", light3Direction)) {
	
				lightsDirection[2].x = (light3Direction[0]);
				lightsDirection[2].y = (light3Direction[1]);
				lightsDirection[2].z = (light3Direction[2]);
			}
		}
	}
}

void App1::depthPass(Light* light)
{
	// Set the render target to be the render to texture.
	shadowMap->BindDsvAndSetNullRenderTarget(renderer->getDeviceContext());

	// get the world, view, and projection matrices from the camera and d3d objects.
	light->generateViewMatrix();
	XMMATRIX lightViewMatrix = light->getViewMatrix();
	XMMATRIX lightProjectionMatrix = light->getOrthoMatrix();
	XMMATRIX worldMatrix = renderer->getWorldMatrix();


	worldMatrix = XMMatrixTranslation(-50.0, -4.0, -50.0);
	meshPlane->sendData(renderer->getDeviceContext());
	terrainDepthShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, lightViewMatrix, lightProjectionMatrix, textureMgr->getTexture(L"heightMap"), amplitude);
	terrainDepthShader->render(renderer->getDeviceContext(), meshPlane->getIndexCount());

	worldMatrix = XMMatrixTranslation(-100.0, -0.2, -100.0);
	waterPlane->sendData(renderer->getDeviceContext());
	waterDepthShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, lightViewMatrix, lightProjectionMatrix, time, amplitude, frequency, speed, waveA, waveB, waveC);
	waterDepthShader->render(renderer->getDeviceContext(), waterPlane->getIndexCount());

	worldMatrix = XMMatrixTranslation(-10.0, amplitude - 26, -17.0);
	lavaPlane->sendData(renderer->getDeviceContext());
	waterDepthShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, lightViewMatrix, lightProjectionMatrix, time, amplitude, frequency, speed, lavaA, lavaB, lavaC);
	waterDepthShader->render(renderer->getDeviceContext(), lavaPlane->getIndexCount());


	worldMatrix = renderer->getWorldMatrix();
	worldMatrix = XMMatrixTranslation(0.f, 7.f, 5.f);
	XMMATRIX scaleMatrix = XMMatrixScaling(0.2f, 0.2f, 0.2f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleMatrix);

	// Render model
	model->sendData(renderer->getDeviceContext());
	depthShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	depthShader->render(renderer->getDeviceContext(), model->getIndexCount());

	// Set back buffer as render target and reset view port.
	renderer->setBackBufferRenderTarget();
	renderer->resetViewport();
}

void App1::shadowPass(Light* light)
{
	// get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	XMMATRIX worldMatrix = renderer->getWorldMatrix();
	XMMATRIX viewMatrix = camera->getViewMatrix();
	XMMATRIX projectionMatrix = renderer->getProjectionMatrix();

	worldMatrix = XMMatrixTranslation(-50.0, -4.0, -50.0);
	meshPlane->sendData(renderer->getDeviceContext());
	terrainShadowShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"rock"), textureMgr->getTexture(L"heightMap"), shadowMap->getDepthMapSRV(), light, amplitude);
	terrainShadowShader->render(renderer->getDeviceContext(), meshPlane->getIndexCount());


	worldMatrix = XMMatrixTranslation(-100.0, -0.2, -100.0);
	waterPlane->sendData(renderer->getDeviceContext());
	waterShadowShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"water"), shadowMap->getDepthMapSRV(), light, time, amplitude, frequency, speed, waveA, waveB, waveC);
	waterShadowShader->render(renderer->getDeviceContext(), waterPlane->getIndexCount());

	worldMatrix = XMMatrixTranslation(-10.0, amplitude - 26, -17.0);
	lavaPlane->sendData(renderer->getDeviceContext());
	waterShadowShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"lava"), shadowMap->getDepthMapSRV(), light, time, amplitude, frequency, speed, lavaA, lavaB, lavaC);
	waterShadowShader->render(renderer->getDeviceContext(), lavaPlane->getIndexCount());


	
	// Render model
	worldMatrix = renderer->getWorldMatrix();
	worldMatrix = XMMatrixTranslation(50.0f, 5.0f, 5.0f);
	XMMATRIX scaleMatrix = XMMatrixScaling(0.2f, 0.2f, 0.2f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleMatrix);

	model->sendData(renderer->getDeviceContext());
	shadowShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"brick"), shadowMap->getDepthMapSRV(), light);
	shadowShader->render(renderer->getDeviceContext(), model->getIndexCount());

}

void App1::camera2Pass()
{
	// Set the render target to be the render to texture and clear it
	camera2Texture->setRenderTarget(renderer->getDeviceContext());
	camera2Texture->clearRenderTarget(renderer->getDeviceContext(), 0.174f, 0.142f, 0.237f, 1.0f);

	// Get matrices
	cameraMinimap->update();
	XMMATRIX worldMatrix = renderer->getWorldMatrix();
	XMMATRIX viewMatrix = cameraMinimap->getViewMatrix();
	XMMATRIX projectionMatrix = renderer->getProjectionMatrix();

	// Render shape with simple lighting shader set.
	worldMatrix = XMMatrixTranslation(-50.f, -50.f, -50.f);
	planeMesh2->sendData(renderer->getDeviceContext());
	spotLightShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"brick"), lights[2], spotLightCutoff);
	spotLightShader->render(renderer->getDeviceContext(), planeMesh2->getIndexCount());


	// Reset the render target back to the original back buffer and not the render to texture anymore.
	renderer->setBackBufferRenderTarget();
}

