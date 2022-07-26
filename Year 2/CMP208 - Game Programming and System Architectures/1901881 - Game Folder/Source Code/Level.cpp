#include "Level.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <graphics/mesh.h>
#include <maths/math_utils.h>
#include <box2d/box2d.h>
#include <input/input_manager.h>
#include <graphics/sprite.h>
#include "load_texture.h"

Level::Level(gef::Platform& platform) :
	sprite_renderer_(NULL),
	primitive_builder_(NULL),
	font_(NULL),
	world_(NULL),
	floor_body_(NULL),
	borderLeft_body_(NULL),
	borderRight_body_(NULL),
	input_manager_(NULL),
	platform_(platform)
{
	Init();
}

void Level::Init()
{
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	// create the renderer for draw 3D geometry
	renderer_3d_ = gef::Renderer3D::Create(platform_);

	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(platform_);
	//initializes input manager ofr block movement
	input_manager_ = gef::InputManager::Create(platform_);
	
	// initialise the physics world
	b2Vec2 gravity(0.0f, -9.81f);
	world_ = new b2World(gravity);

	InitFont();
	InitFloor();
	InitBorders();
	SetupLights();

	//Creates a new block and adds it to a vector
	Block newBlock;
	newBlock.setBlockDimensions(b2Vec2(1.0f, 1.0f));
	newBlock.Init(world_, b2Vec2(0.0f, 15.0f), platform_);
	active_block_vector_.push_back(newBlock);

}

void Level::CleanUp()
{
	// destroying the physics world also destroys all the objects within it
	delete world_;
	world_ = NULL;

	CleanUpFont();

	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;

	delete sprite_renderer_;
	sprite_renderer_ = NULL;

	delete input_manager_;
	input_manager_ = NULL;
}

bool Level::Update(float frame_time, Block block_)
{
	fps_ = 1.0f / frame_time;
	input_manager_->Update();

	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	//updates the physics world
	world_->Step(timeStep, velocityIterations, positionIterations);

	//updates all the blocks in the active vector
	for (auto& b : active_block_vector_)
	{
		b.Update();
	}

	// collision detection
	// get the head of the contact list
	b2Contact* contact = world_->GetContactList();
	// get contact count
	int contact_count = world_->GetContactCount();

	for (int contact_num = 0; contact_num < contact_count; ++contact_num)
	{
		if (contact->IsTouching())
		{
			// get the colliding bodies
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();

			if (bodyA && bodyB)
			{
				//if the block hits the border it stops the collision check
				if (bodyA == borderLeft_body_ || bodyB == borderLeft_body_ || bodyA == borderRight_body_ || bodyB == borderRight_body_)
				{
					break;
				}

				//if the block hits the floor it adds bonus points
				if (bodyA == active_block_vector_.front().getBody() && bodyB == floor_body_ || bodyB == active_block_vector_.front().getBody() && bodyA == floor_body_)
				{
					addScore(20);
				}
				//if the collision is with a block it spawns a new block
				if (bodyA == active_block_vector_.front().getBody() || bodyB == active_block_vector_.front().getBody())
				{
					//adds old block to the inactive vector then deletes the old block from the active vector
					blocks_remaining_ -= 1;
					inactive_block_vector_.push_back(active_block_vector_.front());
					active_block_vector_.pop_back();

					//creates a small block
					if (block_.getDifficulty() == Difficulty::easy)
					{
						Block newBlock;
						newBlock.setCollision(bool(true));
						newBlock.setScaleValues(1, 1);
						newBlock.setScaleBool(bool(true));
						newBlock.setBlockDimensions(b2Vec2(1.0f, 1.0f));
						newBlock.Init(world_, b2Vec2(0.0f, 15.0f), platform_);
						active_block_vector_.push_back(newBlock);

						newBlock.getBody()->SetGravityScale(1.3f);
						addScore(10 * score_scale_);
					}


					//creates a big or small block 
					if (block_.getDifficulty() == Difficulty::normal)
					{
						int rand = random(0, 2);
						Block newBlock;
						newBlock.setCollision(bool(true));
						newBlock.setScaleValues(rand, rand);
						newBlock.setScaleBool(bool(true));

						newBlock.setBlockDimensions(b2Vec2(rand, rand));
						newBlock.Init(world_, b2Vec2(0.0f, 15.0f), platform_);

						newBlock.getBody()->SetGravityScale(1.7f);
						active_block_vector_.push_back(newBlock);

						addScore(10 * score_scale_);
					}

					//creates a random sized block
					if (block_.getDifficulty() == Difficulty::hard)
					{
						int randX = random(0, 2);
						int randY = random(0, 2);
						Block newBlock;
						newBlock.setCollision(bool(true));
						newBlock.setScaleValues(randX, randY);
						newBlock.setScaleBool(bool(true));

						newBlock.setBlockDimensions(b2Vec2(randX, randY));
						newBlock.Init(world_, b2Vec2(0.0f, 15.0f), platform_);
						active_block_vector_.push_back(newBlock);
						newBlock.getBody()->SetGravityScale(2.0f);
						addScore(10 * score_scale_);
					}


				}
			}
		}

		// Get next contact point
		contact = contact->GetNext();
	}

	//sets state to game over once all the blocks have been used
	if (inactive_block_vector_.size() == block_amount_)
	{
		GameOverBool = true;
		Restart();

	}
	return true;
}

void Level::Restart()
{
	//deletes all the blocks on the level and resets the blocks remaing variable
	while (!inactive_block_vector_.empty())
	{

		world_->DestroyBody(inactive_block_vector_.back().getBody());
		inactive_block_vector_.pop_back();
	}
	//inactive_block_vector_.clear();
	blocks_remaining_ = block_amount_;
}

void Level::Render()
{
	//creates the background image
	sprite_renderer_->Begin();
	gef::Sprite background;
	gef::Texture* background_texture_ = CreateTextureFromPNG("game-level-screen.png", platform_);
	background.set_texture(background_texture_);
	background.set_position(gef::Vector4(platform_.width() * 0.5f, platform_.height() * 0.5f, 1.99f));
	background.set_height(544.0f);
	background.set_width(960.0f);
	sprite_renderer_->DrawSprite(background);

	DrawHUD(); //renders text
	sprite_renderer_->End();

	// draw 3d geometry
	renderer_3d_->Begin(false);

	//sets up camera
	// projection
	float fov = gef::DegToRad(45.0f);
	float aspect_ratio = (float)platform_.width() / (float)platform_.height();
	gef::Matrix44 projection_matrix;
	projection_matrix = platform_.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);
	renderer_3d_->set_projection_matrix(projection_matrix);

	// view
	gef::Vector4 camera_eye(0.0f, 0.0f, 47.0f);
	gef::Vector4 camera_lookat(0.0f, 0.0f, 0.0f);
	gef::Vector4 camera_up(0.0f, 1.0f, 0.0f);
	gef::Matrix44 view_matrix;
	view_matrix.LookAt(camera_eye, camera_lookat, camera_up);
	renderer_3d_->set_view_matrix(view_matrix);

	// draw ground
	renderer_3d_->DrawMesh(floor_);

	//renders blocks
	for (auto& b : active_block_vector_)
	{
		renderer_3d_->DrawMesh(b.getObject());
	}
	for (auto& b : inactive_block_vector_)
	{
		renderer_3d_->DrawMesh(b.getObject());
	}

	renderer_3d_->End();
}

void Level::InitFloor()
{
	//sets the floor model to one I created
	const char* scene_asset_filename = "big-floor.scn";
	scene_assets_ = LoadSceneAssets(platform_, scene_asset_filename);
	if (scene_assets_)
	{
		floor_.set_mesh(GetMeshFromSceneAssets(scene_assets_));
	}

	// create a physics body for the floor
	b2BodyDef floor_body_def;
	floor_body_def.type = b2_staticBody;
	floor_body_def.position = b2Vec2(0.0f, -15.0f);
	floor_body_def.userData.pointer = reinterpret_cast<uintptr_t>(&floor_);

	floor_body_ = world_->CreateBody(&floor_body_def);

	// create the shape for the floor
	b2PolygonShape floor_shape;
	floor_shape.SetAsBox(40.0f, 3.5f);

	// create the fixture
	b2FixtureDef floor_fixture_def;
	floor_fixture_def.shape = &floor_shape;
	floor_fixture_def.density = 1.0f;
	floor_fixture_def.friction = 0.5f;

	b2Fixture* floor_fixture_ = floor_body_->CreateFixture(&floor_fixture_def);

	floor_.UpdateFromSimulation(floor_body_);
}

void Level::InitBorders()
{
	//border left
	// create a physics body for the border
	b2BodyDef borderLeft_body_def;
	borderLeft_body_def.type = b2_staticBody;
	borderLeft_body_def.position = b2Vec2(-40.0f, -15.0f);

	borderLeft_body_ = world_->CreateBody(&borderLeft_body_def);

	// create the shape for the borderLeft
	b2PolygonShape borderLeft_shape;
	borderLeft_shape.SetAsBox(5.0f, 30.0f);

	// create the fixture
	b2FixtureDef borderLeft_fixture_def;
	borderLeft_fixture_def.shape = &borderLeft_shape;
	borderLeft_fixture_def.density = 1.0f;
	borderLeft_fixture_def.friction = 0.5f;

	b2Fixture* borderLeft_fixture_ = borderLeft_body_->CreateFixture(&borderLeft_fixture_def);


	//borderRight
	// create a physics body for the border
	b2BodyDef borderRight_body_def;
	borderRight_body_def.type = b2_staticBody;
	borderRight_body_def.position = b2Vec2(40.0f, -15.0f);

	borderRight_body_ = world_->CreateBody(&borderRight_body_def);

	// create the shape for the borderRight
	b2PolygonShape borderRight_shape;
	borderRight_shape.SetAsBox(5.0f, 30.5f);

	// create the fixture
	b2FixtureDef borderRight_fixture_def;
	borderRight_fixture_def.shape = &borderRight_shape;
	borderRight_fixture_def.density = 1.0f;
	borderRight_fixture_def.friction = 0.5f;

	b2Fixture* borderRight_fixture_ = borderRight_body_->CreateFixture(&borderRight_fixture_def);

}

void Level::InitFont()
{
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void Level::CleanUpFont()
{
	if (font_)  //if it not a null ptr it deletes
	{
		delete font_;
		font_ = NULL;
	}
}

void Level::DrawHUD()
{
	if (font_)
	{
		font_->RenderText(sprite_renderer_, gef::Vector4(0.0f, 5.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "Score: %.0f", getScore());
		font_->RenderText(sprite_renderer_, gef::Vector4(0.0f, 25.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "Block Amount: %.0f", blocks_remaining_);
	}
}

void Level::SetupLights()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.25f, 0.25f, 0.25f, 1.0f));

	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);
}

gef::Scene* Level::LoadSceneAssets(gef::Platform& platform, const char* filename)
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

gef::Mesh* Level::GetMeshFromSceneAssets(gef::Scene* scene)
{
	gef::Mesh* mesh = NULL;

	// if the scene data contains at least one mesh
	// return the first mesh
	if (scene && scene->meshes.size() > 0)
		mesh = scene->meshes.front();

	return mesh;
}
