#pragma once

#include <SFML/Graphics.hpp>
//used for debug messages
#include <iostream>
using namespace std;

class CarFSM
{
public:
	CarFSM(sf::RenderWindow* window);
	~CarFSM();

	void Update(float dt);
	void GetLinePosition(sf::Vector2f linePos);
	void MoveCar(float dt);
	void Render();

private:
	sf::RenderWindow* window;

	sf::Texture carFSMTexture;
	sf::Sprite carFSMSprite;

	//Defining states for the machine
	enum class CarStates
	{
		HeavyLeft = 0,
		Left = 1,
		Centre = 2,
		Right = 3,
		HeavyRight = 4
	};

	CarStates currentState;
	sf::Vector2f linePosition;

	//Floats used to calculate car movement
	float velocity;
	float acceleration;
	float distanceFromLine;
	float speed;
};

