#pragma once
#include "Framework/GameObject.h"
#include "Framework/GameState.h"
#include "Framework/AudioManager.h"
#include "Framework/Collision.h"
#include "Cursor.h"
#include <iostream>//remove later asfter collision test
class Pause
{
public:
	Pause(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Pause();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;

	sf::Text textOb;
	sf::Font fontOb;

	//Background screen
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	//Story Button
	GameObject* storyB;
	sf::Texture storyBTexture;

	//Controls Button
	GameObject* controlsB;
	sf::Texture controlsBTexture;

	//Exit Button
	GameObject* exitB;
	sf::Texture exitBTexture;

	//Restart Button
	GameObject* restartB;
	sf::Texture restartBTexture;

	//Backspace Button
	GameObject* backB;
	sf::Texture backBTexture;

	//Audio 
	AudioManager* audioManager;

	Cursor* cursor;
};