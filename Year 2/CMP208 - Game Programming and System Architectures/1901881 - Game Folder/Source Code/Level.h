#pragma once
#include <system/application.h>
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <box2d/Box2D.h>
#include "game_object.h"
#include "graphics/scene.h"
#include <input/sony_controller_input_manager.h>
#include "Block.h"
#include <vector>

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}
class Level 
{
public:
	Level(gef::Platform& platform);

	void Init();
	void InitBorders();
	void InitFloor();
	void InitFont();

	void CleanUp();
	void CleanUpFont();

	bool Update(float frame_time, Block block_);
	void Render();

	void DrawHUD();
	void SetupLights();

	gef::Scene* LoadSceneAssets(gef::Platform& platform, const char* filename);
	gef::Mesh* GetMeshFromSceneAssets(gef::Scene* scene);

	void addScore(int add) { score_ += add; }
	void setScore(float score_) { this->score_ = score_; }
	float getScore() { return score_; }
	void setScoreScale(float scale) { score_scale_ = scale; }

	bool getGameOverBool() { return GameOverBool; }
	void setGameOverBool(bool GameOverBool) { this->GameOverBool = GameOverBool; }

	void Restart();

	int random(int min, int max) { return rand() % (max - min) + min + 1; }//creates a random integer

private:
	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;
	gef::Renderer3D* renderer_3d_;
	gef::Platform& platform_;
	gef::MeshInstance mesh_instance_;
	gef::Scene* scene_assets_;
	gef::InputManager* input_manager_;
	PrimitiveBuilder* primitive_builder_;

	// create the physics world
	b2World* world_;

	// floor variables
	GameObject floor_;
	b2Body* floor_body_;

	//Creates border physics body
	b2Body* borderLeft_body_;
	b2Body* borderRight_body_;

	//player stuffs
	bool x_pressed = false;
	float rotateZ = 0;

	//Block Variables
	std::vector<Block> active_block_vector_;
	std::vector<Block> inactive_block_vector_;
	float block_amount_ = 30.0f;
	float blocks_remaining_ = block_amount_;

	//Score Variables
	float score_ = 0.0f;
	float score_scale_ = 1.0f;

	bool GameOverBool = false;
	float fps_;

};

