#pragma once
#include "Framework/GameObject.h"
#include "Framework/GameState.h"
#include "Framework/AudioManager.h"
#include "Framework/Collision.h"
#include "Cursor.h"
#include <iostream>//remove later asfter collision test
class Story
{
public:
	Story(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Story();

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

	//Background screen
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	//Backspace Button
	GameObject* backB;
	sf::Texture backBTexture;

	//Audio 
	AudioManager* audioManager;

	Cursor* cursor;
};