#include "StateManager.h"

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

StateManager::StateManager(gef::Platform& platform) :
	sprite_renderer_(NULL),
	input_manager_(NULL),
	game_state_(GameState::None),
	state_timer_(0.0f),
	platform_(platform),
	renderer_3d_(NULL),
	level_(NULL),
	font_(NULL)
{
	Init();
}

void StateManager::Init()
{
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
	level_ = new Level(platform_);
	renderer_3d_ = gef::Renderer3D::Create(platform_);
	// initialise input manager
	input_manager_ = gef::InputManager::Create(platform_);

	//Sets music file 
	audio_manager_ = gef::AudioManager::Create();
	music_id_ = audio_manager_->LoadMusic("mario-music.wav", platform_);

	//sets game state to init
	ChangeGameState(GameState::Init);
	InitFont();
}

void StateManager::StateUpdate(float frame_time)
{
	//if the game over bool in level is set to true it resets the score an changes state to game over
	if (level_->getGameOverBool())
	{
		ChangeGameState(GameState::GameOver);
		level_->setGameOverBool(bool(false));
		final_score_ = level_->getScore();
		level_->setScore(0.0f);
	}
	input_manager_->Update();

	const gef::SonyController* controller = input_manager_->controller_input()->GetController(0);
	
	state_timer_ += frame_time;
	//switch statement updates the current state
	switch (game_state_)
	{
	case GameState::Init:
		InitStateUpdate(frame_time);
		break;
	case GameState::Menu:
		MenuStateUpdate(frame_time);
		break;
	case GameState::Controls:
		ControlStateUpdate(frame_time);
		break;
	case GameState::Settings:
		SettingsStateUpdate(frame_time);
		break;
	case GameState::Pause:
		PauseStateUpdate(frame_time);
		break;
	case GameState::Level1:
		LevelStateUpdate(frame_time);
		break;
	case GameState::GameOver:
		GameOverStateUpdate(frame_time);
		break;
	default:
		break;
	}
}

void StateManager::StateRender()
{
	//switch statement renders the current state
	switch (game_state_)
	{
	case GameState::Init:
		InitStateRender();
		break;
	case GameState::Menu:
		MenuStateRender();
		break;
	case GameState::Controls:
		ControlStateRender();
		break;
	case GameState::Settings:
		SettingsStateRender();
		break;
	case GameState::Pause:
		PauseStateRender();
		break;
	case GameState::Level1:
		LevelStateRender();
		break;
	case GameState::GameOver:
		GameOverStateRender();
	default:
		break;
	}
}

void StateManager::ChangeGameState(GameState new_state)
{
	//changes gamestate and restets the timer for init
	game_state_ = new_state;
	state_timer_ = 0.0f;
}

void StateManager::InitStateUpdate(float frame_time)
{
	//plays the music
	audio_manager_->PlayMusic();
	audio_manager_->SetMasterVolume(volume_);//sets volume to user defined variable
	//resets the score and moves the text out of the way
	final_score_ = 0.0f;
	textPosition = gef::Vector4(6900.0f, 330.0f, -1.9f);
	textNumPosition = gef::Vector4(7000.0f, 220.0f, -1.9f);
	textScorePosition = gef::Vector4(7000.0f, 150.0f, -1.9f);
	//changes state to menu after a second
	if (state_timer_ > 1.0F)
	{
		ChangeGameState(GameState::Menu);
	}
}

void StateManager::InitStateRender()
{
	BackgroundRender("game-loading-screen.png");
	textPosition = gef::Vector4(6900.0f, 330.0f, -1.9f);
	textNumPosition = gef::Vector4(7000.0f, 220.0f, -1.9f);
	textScorePosition = gef::Vector4(4000.0f, 150.0f, -1.9f);
	DrawHUD();
}

void StateManager::MenuStateUpdate(float frame_time)
{
	//sets input for the buttons to change states
	const gef::SonyController* controller = input_manager_->controller_input()->GetController(0);

	if (controller && controller->buttons_released() & gef_SONY_CTRL_CROSS)
	{
		ChangeGameState(GameState::Level1);
	}
	else if (controller && controller->buttons_released() & gef_SONY_CTRL_SQUARE)
	{
		ChangeGameState(GameState::Settings);
	}
	else if (controller && controller->buttons_released() & gef_SONY_CTRL_CIRCLE)
	{
		ChangeGameState(GameState::Controls);
	}
	else if (controller && controller->buttons_released() & gef_SONY_CTRL_TRIANGLE)
	{
		exit(0);
	}
}

void StateManager::MenuStateRender()
{
	BackgroundRender("game-start-screen.png");
	textPosition = gef::Vector4(6900.0f, 330.0f, -1.9f);
	textNumPosition = gef::Vector4(7000.0f, 220.0f, -1.9f);
	textScorePosition = gef::Vector4(4000.0f, 150.0f, -1.9f);
	DrawHUD();
}

void StateManager::ControlStateUpdate(float frame_time)
{
	const gef::SonyController* controller = input_manager_->controller_input()->GetController(0);

	if (controller && controller->buttons_released() & gef_SONY_CTRL_SQUARE)
	{
		ChangeGameState(GameState::Menu);
	}
	else if (controller && controller->buttons_released() & gef_SONY_CTRL_CIRCLE)
	{
		ChangeGameState(GameState::Level1);
	}
}

void StateManager::ControlStateRender()
{
	BackgroundRender("game-control-screen.png");
	textPosition = gef::Vector4(6900.0f, 330.0f, -1.9f);
	textNumPosition = gef::Vector4(7000.0f, 220.0f, -1.9f);
	textScorePosition = gef::Vector4(4000.0f, 150.0f, -1.9f);
	DrawHUD();
}

void StateManager::SettingsStateUpdate(float frame_time)
{
	const gef::SonyController* controller = input_manager_->controller_input()->GetController(0);

	if (controller && controller->buttons_released() & gef_SONY_CTRL_SQUARE)
	{
		ChangeGameState(GameState::Menu);
	}
	else if (controller && controller->buttons_released() & gef_SONY_CTRL_CIRCLE)
	{
		ChangeGameState(GameState::Level1);
	}

	else if (controller && controller->buttons_released() & gef_SONY_CTRL_UP)
	{
		//DIFFICULTY DOWN
		diffNum += 1;
		switchDifficulty();
		
	}
	else if (controller && controller->buttons_released() & gef_SONY_CTRL_DOWN)
	{
		//DIFFICULTY UP
		diffNum -= 1;
		switchDifficulty();
	}
	else if (controller && controller->buttons_pressed() & gef_SONY_CTRL_RIGHT)
	{
		//if statement makes sure the volume stays within the parameters
		if (volume_ < 10)
		{
			volume_ += 1;
		}
		
	}
	else if (controller && controller->buttons_pressed() & gef_SONY_CTRL_LEFT)
	{
		//if statement makes sure the volume stays within the parameters
		if (volume_ > 0)
		{
			volume_ -= 1;
		}
	}
	audio_manager_->SetMasterVolume(volume_);//updates the volume to the user defined variable
}



void StateManager::SettingsStateRender()
{
	BackgroundRender("game-settings-screen.png");
	textPosition = gef::Vector4(690.0f, 330.0f, -1.9f);
	textNumPosition = gef::Vector4(695.0f, 199.0f, -1.9f);
	textScorePosition = gef::Vector4(4000.0f, 150.0f, -1.9f);
}

void StateManager::PauseStateUpdate(float frame_time)
{
	const gef::SonyController* controller = input_manager_->controller_input()->GetController(0);

	if (controller && controller->buttons_released() & gef_SONY_CTRL_CROSS)
	{
		//resets the game
		final_score_ = level_->getScore();
		level_->setScore(0.0f);
		level_->Restart();
		ChangeGameState(GameState::Init);
	}
	else if (controller && controller->buttons_released() & gef_SONY_CTRL_SQUARE)
	{
		ChangeGameState(GameState::Settings);
	}
	else if (controller && controller->buttons_released() & gef_SONY_CTRL_CIRCLE)
	{
		ChangeGameState(GameState::Controls);
	}
	else if (controller && controller->buttons_released() & gef_SONY_CTRL_TRIANGLE)
	{
		exit(0);
	}
	else if (controller && controller->buttons_released() & gef_SONY_CTRL_OPTIONS)
	{
		ChangeGameState(GameState::Level1);
	}
}

void StateManager::PauseStateRender()
{
	BackgroundRender("game-pause-screen.png");
	textPosition = gef::Vector4(6900.0f, 330.0f, -1.9f);
	textNumPosition = gef::Vector4(7000.0f, 220.0f, -1.9f);
	textScorePosition = gef::Vector4(4000.0f, 150.0f, -1.9f);
	DrawHUD();
}

void StateManager::LevelStateUpdate(float frame_time)
{
	level_->Update(frame_time, block_);
	
	const gef::SonyController* controller = input_manager_->controller_input()->GetController(0);

	if (controller && controller->buttons_released() & gef_SONY_CTRL_OPTIONS)
	{
		ChangeGameState(GameState::Pause);
	}
	
}

void StateManager::LevelStateRender()
{
	//updates the level class to play the game
	level_->Render();
}

void StateManager::GameOverStateUpdate(float frame_time)
{
	const gef::SonyController* controller = input_manager_->controller_input()->GetController(0);

	if (controller && controller->buttons_released() & gef_SONY_CTRL_SQUARE)
	{
		ChangeGameState(GameState::Init);
	}
	else if (controller && controller->buttons_released() & gef_SONY_CTRL_CIRCLE)
	{
		exit(0);
	}
}

void StateManager::GameOverStateRender()
{
	BackgroundRender("game-over-screen.png");
	textPosition = gef::Vector4(6900.0f, 330.0f, -1.9f);
	textNumPosition = gef::Vector4(7000.0f, 220.0f, -1.9f);
	textScorePosition = gef::Vector4(400.0f, 150.0f, -1.9f);
	DrawHUD();
}

void StateManager::switchDifficulty()
{
	//sets difficulty based on user defined variable
	//adds text to screen
	//based on difficulty it sets the score modifacator
	if (diffNum <= 0)
	{
		diffNum = 0;
	}
	else if (diffNum >= 2)
	{
		diffNum = 2;
	}

	switch (diffNum) {
	case 0:
		block_.setDifficulty(Difficulty::easy);
		text = "EASY";
		level_->setScoreScale(1.0f);

		break;
	case 1:
		block_.setDifficulty(Difficulty::normal);
		text = "NORMAL";
		level_->setScoreScale(2.0f);

		break;
	case 2:
		block_.setDifficulty(Difficulty::hard);
		text = "HARD";
		level_->setScoreScale(3.0f);
		break;
	default:
		block_.setDifficulty(Difficulty::normal);
	}
	DrawHUD();//draws text

}

void StateManager::BackgroundRender(const char* filename)
{
	sprite_renderer_->Begin();
	
	// Render button icon
	gef::Sprite background;
	gef::Texture* background_texture_ = CreateTextureFromPNG(filename, platform_);
	background.set_texture(background_texture_);
	background.set_position(gef::Vector4(platform_.width() * 0.5f, platform_.height() * 0.5f, -0.99f));
	background.set_height(544.0f);
	background.set_width(960.0f);
	sprite_renderer_->DrawSprite(background);
	
	DrawHUD();
	sprite_renderer_->End();
}

void StateManager::InitFont()
{
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}


void StateManager::DrawHUD()
{
	if (font_)
	{
		// display frame rate
		font_->RenderText(sprite_renderer_, textPosition, 1.0f, 0xffffffff, gef::TJ_LEFT, text);
		font_->RenderText(sprite_renderer_, textNumPosition, 2.0f, 0xffffffff, gef::TJ_LEFT, "%.0f", volume_);
		font_->RenderText(sprite_renderer_, textScorePosition, 2.0f, 0xffffffff, gef::TJ_LEFT, "Score: %.0f", final_score_);
	}
}