#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "MC.h"
#include "BlueSlime.h"
#include "YellowSlime.h"
#include "RedSlime.h"
#include "Hearts.h"
#include "Framework/Animation.h"
#include "Framework/Collision.h"
#include "Tiles.h"
#include <string>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();
	void checkBoundaries(GameObject*currentObject);
	void checkRoom();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();
	void handleCollision();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;

	//Animation
	//MC
	MC * mc;
	sf::Texture mcTexture;

	//Blue Slime
	BlueSlime* blueSlime;
	sf::Texture blueSlimeTexture;

	//Yellow Slime
	YellowSlime* yellowSlime;
	sf::Texture yellowSlimeTexture;

	//Red Slime
	RedSlime* redSlime;
	sf::Texture redSlimeTextureSmall;

	//Hearts
	Hearts* hearts;
	
	//Tilemap
	Tiles tileObject;

	//Window Size
	sf::Vector2u wind;

	//Camera
	sf::View camera;

	//Grid
	GameObject* grid1;
	sf::Texture gridRectangleTexture;

	//Audio 
	AudioManager* audioManager;
	
	//Doors
	GameObject* Room1Door2;

	GameObject* Room2Door1;
	GameObject* Room2Door2;

	GameObject* Room3Door1;
	GameObject* Room3Door2;

	GameObject* Room4Door1;
	GameObject* Room4Door2;

	GameObject* Room5Door1;
	GameObject* Room5Door2;

	GameObject* Room6Door1;
	GameObject* Room6Door2;

};