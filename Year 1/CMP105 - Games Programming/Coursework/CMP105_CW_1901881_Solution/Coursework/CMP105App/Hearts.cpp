#include "Hearts.h"

Hearts::Hearts(MC* mc)
{
	heartFrames.addFrame(sf::IntRect(0, 0, 51, 17));//This is where i added the frames for the heart sprite it goes from3 to 0
	heartFrames.addFrame(sf::IntRect(0, 18, 51, 17));
	heartFrames.addFrame(sf::IntRect(0, 36, 51, 17));
	heartFrames.addFrame(sf::IntRect(0, 54, 51, 17));

	this->mc = mc;//this makes it so that the player pointer created in this class holds the same data as the one in level so that i can get the correct player health

	int scale = 3;// this will be used to scale the size of the sprite
	heartsTexture.loadFromFile("gfx/Hearts.png");
	setSize(sf::Vector2f(51*scale, 17*scale));
	setPosition(0, 0);//makes it show at the top left of the screen
	setTexture(&heartsTexture);
}

Hearts::~Hearts()
{
}

void Hearts::update(float dt)
{
	setTextureRect(current->getCurrentFrame());

	current->setCurrentFrameNum(mc->getHealthMax() - mc->getHealth());//this calculates which frame the sprite should be on to represent the players health
	
}

