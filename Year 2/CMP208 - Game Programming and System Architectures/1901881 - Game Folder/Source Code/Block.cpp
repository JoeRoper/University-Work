#include "Block.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <graphics/mesh.h>
#include <maths/math_utils.h>
#include <box2d/box2d.h>
#include <input/input_manager.h>

Block::Block()
{

}

void Block::Init(b2World* world_, b2Vec2 position, gef::Platform& platform_)
{
	//sets the audio manager loads the sound file then plays in when a new block is created
	audio_manager_ = gef::AudioManager::Create();
	sound_id_ = audio_manager_->LoadSample("brick_sound.wav", platform_);
	if (collision) 
	{
		audio_manager_->PlaySample(sound_id_, false);
	}
	
	input_manager_ = gef::InputManager::Create(platform_);

	//loads 3d block model and sets it to the game object
	const char* scene_asset_filename = "block.scn";
	block_assets_ = LoadSceneAssets(platform_, scene_asset_filename);
	if (block_assets_)
	{
		block_.set_mesh(GetMeshFromSceneAssets(block_assets_));
	}

	//sets up the block physics body
	b2BodyDef block_body_def;
	block_body_def.type = b2_dynamicBody;
	block_body_def.position = position;
	block_body_def.userData.pointer = reinterpret_cast<uintptr_t>(&block_);

	block_body_ = world_->CreateBody(&block_body_def);

	b2PolygonShape block_shape;
	block_shape.SetAsBox(dimensions.x, dimensions.y);

	b2FixtureDef block_fixture_def;
	block_fixture_def.shape = &block_shape;
	block_fixture_def.density = 1.0f;
	block_fixture_def.friction = 1.0f;
	block_fixture_ = block_body_->CreateFixture(&block_fixture_def);
	
	block_.UpdateFromSimulation(block_body_);
}

void Block::BlockMovement()
{
	input_manager_->Update();

	gef::Matrix44 block_transform;
	block_transform.SetIdentity();


	const gef::SonyController* controller = input_manager_->controller_input()->GetController(0);


	if (controller->buttons_down() & gef_SONY_CTRL_LEFT)
	{
		//moves the block left
		block_body_->ApplyForce(b2Vec2(-200.0f, 0.0f), block_body_->GetWorldCenter(), true);
	}

	if (controller->buttons_down() & gef_SONY_CTRL_RIGHT)
	{
		//moves the block right
		block_body_->ApplyForce(b2Vec2(200.0f, 0.0f), block_body_->GetWorldCenter(), true);
	}

	if (controller->buttons_down() & gef_SONY_CTRL_CROSS)
	{
		//makes the block fall to gravity
		x_pressed = true;
	}
	if (controller->buttons_down() & gef_SONY_CTRL_TRIANGLE)
	{
		//makes the block fall faster
		block_body_->ApplyForce(b2Vec2(0.0f, -1000.0f), block_body_->GetWorldCenter(), true);
		x_pressed = true;
	}

	block_transform.SetTranslation(gef::Vector4(block_body_->GetPosition().x, block_body_->GetPosition().y, 0.0f));
	if (!x_pressed)
	{
		//applies a constant force pushing the block up so that it falls slowly
		block_body_->ApplyForce(b2Vec2(0.0f, 39.29f), block_body_->GetWorldCenter(), true);
	}
	block_.set_transform(block_transform);
}

void Block::ScaleBlock()
{
	//scales the block depending on the difficulty
	gef::Matrix44 block_transform;
	block_transform.SetIdentity();

	block_transform.Scale(scaleValues);
	
	block_transform.SetTranslation(gef::Vector4(block_body_->GetPosition().x, block_body_->GetPosition().y, 0.0f));

	block_.set_transform(block_transform);
}

void Block::Update()
{
	block_.UpdateFromSimulation(block_body_);
	BlockMovement();
	if (scale)
	{
		ScaleBlock();
	}

}

gef::Scene* Block::LoadSceneAssets(gef::Platform& platform, const char* filename)
{
	gef::Scene* scene = new gef::Scene();

	if (scene->ReadSceneFromFile(platform, filename))
	{
		// if scene file loads successful
		// create material and mesh resources from the scene data
		scene->CreateMaterials(platform);
		scene->CreateMeshes(platform);
	}
	else
	{
		delete scene;
		scene = NULL;
	}

	return scene;
}

gef::Mesh* Block::GetMeshFromSceneAssets(gef::Scene* scene)
{
	gef::Mesh* mesh = NULL;

	// if the scene data contains at least one mesh
	// return the first mesh
	if (scene && scene->meshes.size() > 0)
		mesh = scene->meshes.front();

	return mesh;
}