#include "scene_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <graphics/mesh.h>
#include <maths/math_utils.h>
#include <input/sony_controller_input_manager.h>
#include <graphics/sprite.h>
#include "load_texture.h"

SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform)
{
	Init();
}

void SceneApp::Init()
{
	//sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
//	InitFont();

	// initialise input manager
	//input_manager_ = gef::InputManager::Create(platform_);
	state_manager_ = new StateManager(platform_);
	//level_ = new Level(platform_);
	//level_->Init();
}

void SceneApp::CleanUp()
{

}

bool SceneApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;


	//input_manager_->Update();

	state_manager_->StateUpdate(frame_time);
	//level_->Update(frame_time);

	return true;
}




void SceneApp::Render()
{
	state_manager_->StateRender();
	//level_->Render();
}

