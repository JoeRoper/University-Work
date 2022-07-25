#pragma once
#include "Framework/GameObject.h"
#include "Framework/GameState.h"
#include "Framework/AudioManager.h"
#include "Framework/Collision.h"
#include "Cursor.h"
#include <iostream>//remove later asfter collision test
class Menu 
{
public:
	Menu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Menu();

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


	//title screen
	sf::RectangleShape ts;
	sf::Texture tsTexture;

	//Story Button
	GameObject* storyB;
	sf::Texture storyBTexture;

	//Controls Button
	GameObject* controlsB;
	sf::Texture controlsBTexture;

	//Start Button
	GameObject* startB;
	sf::Texture startBTexture;

	//Exit Button
	GameObject* exitB;
	sf::Texture exitBTexture;

	Cursor* cursor;

	//Audio 
	AudioManager* audioManager;

};

