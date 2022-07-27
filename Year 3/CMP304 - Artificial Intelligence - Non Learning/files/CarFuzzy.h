#pragma once

#include <SFML/Graphics.hpp>
#include "fl/Headers.h"//imprts fuzzylite libraries

//used for debug messages
#include <iostream>
using namespace std;

using namespace fl;

class CarFuzzy
{
public:
	CarFuzzy(sf::RenderWindow* window);
	~CarFuzzy();

	void Update(float dt);
	void GetLinePosition(sf::Vector2f linePos);
	void MoveCar(float dt);
	void Render();

private:
	sf::RenderWindow* window;

	fl::Engine* fuzzyEngine;

	sf::Sprite carFuzzySprite;
	sf::Texture carFuzzyTexture;

	//defining states for the machine
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

	float velocity;
	float distanceFromLine;
	float direction;
	float speed;
};

