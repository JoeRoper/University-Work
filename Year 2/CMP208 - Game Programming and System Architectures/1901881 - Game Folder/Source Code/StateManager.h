#pragma once
#include <system/application.h>
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <input/input_manager.h>
#include <input/sony_controller_input_manager.h>
#include <box2d/Box2D.h>
#include "game_object.h"
#include "Level.h"
#include <audio/audio_manager.h>

enum GameState {
	None,
	Init,
	Menu,
	Pause,
	Controls,
	Settings,
	Level1,
	GameOver
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

class StateManager
{
public:
	StateManager(gef::Platform& platform);
	void Init();
	void StateUpdate(float frame_time);
	void StateRender();
	void ChangeGameState(GameState new_state);
	

private:
	void InitStateUpdate(float frame_time);
	void InitStateRender();
	void MenuStateUpdate(float frame_time);
	void MenuStateRender();
	void ControlStateUpdate(float frame_time);
	void ControlStateRender();
	void SettingsStateUpdate(float frame_time);
	void SettingsStateRender();
	void PauseStateUpdate(float frame_time);
	void PauseStateRender();
	void LevelStateUpdate(float frame_time);
	void LevelStateRender();
	void GameOverStateUpdate(float frame_time);
	void GameOverStateRender();

	void BackgroundRender(const char* filename);
	void InitFont();
	void DrawHUD();
	void switchDifficulty();

	GameState game_state_;
	float state_timer_;

	gef::SpriteRenderer* sprite_renderer_;
	gef::InputManager* input_manager_;
	gef::Platform& platform_;
	gef::AudioManager* audio_manager_;
	gef::Renderer3D* renderer_3d_;
	Level* level_;
	Block block_;
	//text
	gef::Font* font_;
	const char* text = "";
	gef::Vector4 textPosition, textNumPosition, textScorePosition;
	
	float final_score_ = 0.0f;
	float volume_ = 2.0f;
	int music_id_ = -1;
	int diffNum = 0;
};

