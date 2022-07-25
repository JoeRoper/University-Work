#pragma once
#include "Framework/GameObject.h"
#include "Framework/GameState.h"
#include "Framework/AudioManager.h"
#include "Framework/Collision.h"
#include "Cursor.h"
#include <iostream>//remove later asfter collision test
class Win
{
public:
	Win(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Win();

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
	AudioManager* audioManager;

	//Background screen
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	//Exit Button
	GameObject* exitB;
	sf::Texture exitBTexture;

	//Restart Button
	GameObject* restartB;
	sf::Texture restartBTexture;

	Cursor* cursor;//cursor pointer used to add the cursor to the screen
};