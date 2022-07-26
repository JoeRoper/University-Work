#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include <system/application.h>
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <input/input_manager.h>
#include <box2d/Box2D.h>
#include "game_object.h"
#include "StateManager.h"
#include "Level.h"
#include "Block.h"



// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}

class SceneApp : public gef::Application
{
public:
	SceneApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();
private:

    
	gef::Renderer3D* renderer_3d_;

	StateManager* state_manager_;
	gef::InputManager* input_manager_;
	//
	
	// audio variables
	int sfx_id_;
	int sfx_voice_id_;

	float fps_;

	Level* level_;
};

#endif // _SCENE_APP_H
