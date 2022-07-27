#pragma once
#include <SFML/Graphics.hpp>

//used for debug messages
#include <iostream>
using namespace std;

class RoadLine
{
public:
	RoadLine(sf::RenderWindow* window, sf::Vector2f size, sf::Vector2f position);
	~RoadLine();

	void Update(float dt);
	void HandleInput(float dt);
	sf::Vector2f GetPosition() { return roadLineSprite.getPosition(); };
	void Render();

private:
	sf::RenderWindow* window;

	sf::Texture roadLineTexture;
	sf::Sprite roadLineSprite;

	float speed = 1000.0f;//set speed for the road to move in
};

