#pragma once
#include <system/application.h>
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <box2d/Box2D.h>
#include "game_object.h"
#include "graphics/scene.h"
#include <input/sony_controller_input_manager.h>
#include <audio/audio_manager.h>

//used to change the difficulty in statemanager and change variables based on the difficulty in level
enum Difficulty {
	easy,
	normal,
	hard
};

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}

class Block
{
public:
	Block();

	void Init(b2World* world_, b2Vec2 position, gef::Platform& platform);//creates a block and plays the collision sound
	void Update();

	b2Body* getBody() { return block_body_; };
	b2Fixture* getFixture() { return block_fixture_; };
	GameObject getObject() { return block_; };

	void ScaleBlock();
	void BlockMovement();//Moves the block through input

	void setScaleBool(bool scale) { this->scale = scale; }
	void setScaleValues(int x, int y) { scaleValues = gef::Vector4(x, y, 1); }
	void setBlockDimensions(b2Vec2 dimensions) { this->dimensions = dimensions; }

	Difficulty getDifficulty() { return difficulty_; }
	void setDifficulty(Difficulty difficulty_) { this->difficulty_ = difficulty_; }

	bool getPlaySound() { return playSound; }
	void setPlaySound(bool playSound) { this->playSound = playSound; }

	bool getCollision() { return collision; }
	void setCollision(bool collision) { this->collision = collision; }

	gef::Scene* LoadSceneAssets(gef::Platform& platform, const char* filename);
	gef::Mesh* GetMeshFromSceneAssets(gef::Scene* scene);
private:

	//Block Varriables
	b2Body* block_body_ = nullptr;
	b2Fixture* block_fixture_ = nullptr;
	GameObject block_;
	gef::Scene* block_assets_;
	
	//sets the game to normal difficulty by default
	Difficulty difficulty_ = Difficulty::normal;
	

	gef::InputManager* input_manager_;
	gef::AudioManager* audio_manager_;
	
	b2Vec2 dimensions;
	gef::Vector4 scaleValues;

	bool collision = false;
	bool x_pressed = false;
	bool playSound = false;
	bool scale = false;

	int sound_id_ = -1;
	float rotateZ = 0;
};

