#include "RoadLine.h"

RoadLine::RoadLine(sf::RenderWindow* window, sf::Vector2f size, sf::Vector2f position)
{
	this->window = window;//sets window pointer to match the one in the simulation

	//loads the texture for the road
	if (!roadLineTexture.loadFromFile("media/RoadLine.png"))
	{
		cout << "Couldnt load road line texture" << endl;
	}

	//Sets up the road sprite
	roadLineSprite.setTexture(roadLineTexture);
	roadLineSprite.setScale(sf::Vector2f(0.65f, 2.5f));
	roadLineSprite.setOrigin(sf::Vector2f(roadLineTexture.getSize().x / 2.0f, roadLineTexture.getSize().y));
	roadLineSprite.setPosition(window->getSize().x / 2.0f, window->getSize().y);
}

RoadLine::~RoadLine()
{
}

void RoadLine::Update(float dt)
{
	HandleInput(dt);//runs the user input function
}

void RoadLine::HandleInput(float dt)
{
	//Moves the road to the left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// makes it so it can not go past the screen
		if (roadLineSprite.getPosition().x > 30.0f)
		{
			roadLineSprite.move(sf::Vector2f(-speed * dt, 0.0f));
		}
	}

	// Moves the road to the right 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// makes it so it can not go past the screen
		if (roadLineSprite.getPosition().x < window->getSize().x - (roadLineTexture.getSize().x - 60))
		{
			roadLineSprite.move(sf::Vector2f(speed * dt, 0.0f));
		}
	}
}

void RoadLine::Render()
{
	window->draw(roadLineSprite);//renders the road to the screen
}
