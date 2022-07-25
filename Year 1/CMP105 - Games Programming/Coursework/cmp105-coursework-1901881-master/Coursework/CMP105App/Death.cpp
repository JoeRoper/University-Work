#include "Death.h"
Death::Death(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audioManager = aud;

	exitB = new GameObject();
	restartB = new GameObject();

	cursor = new Cursor;
	cursor->setInput(in);



	//title screen
	backgroundTexture.loadFromFile("gfx/Death.png");
	background.setSize(sf::Vector2f(1344, 768));
	background.setPosition(0, 0);
	background.setTexture(&backgroundTexture);

	//Exit Button
	exitBTexture.loadFromFile("gfx/Buttons/ExitButton.png");
	exitB->setSize(sf::Vector2f(200, 75));
	exitB->setPosition(700, 620);
	exitB->setTexture(&exitBTexture);
	exitB->setCollisionBox(0, 0, exitB->getSize().x, exitB->getSize().y);

	//restart Button
	restartBTexture.loadFromFile("gfx/Buttons/RestartButton.png");
	restartB->setSize(sf::Vector2f(200, 75));
	restartB->setPosition(400, 620);
	restartB->setTexture(&restartBTexture);
	restartB->setCollisionBox(0, 0, restartB->getSize().x, restartB->getSize().y);

	
}

Death::~Death()
{
	delete cursor;
}

void Death::handleInput(float dt)
{
	gameState->setCurrentState(State::DEATH);


	if (Collision::checkBoundingBox(exitB, cursor) && (input->isMouseLDown()))//makes it so when the button is pressed it goes back to the previous screen
	{
		window->close();
	}

	if (Collision::checkBoundingBox(restartB, cursor) && (input->isMouseLDown()))
	{
		gameState->setCurrentState(State::RESTART);
	}
}

void Death::update(float dt)
{
	window->setView(window->getDefaultView());//sets the view to show the game screen
	cursor->update(dt);
}

void Death::render()
{
	beginDraw();

	window->draw(background);
	window->draw(*exitB);
	window->draw(*restartB);
	window->draw(*cursor);


	endDraw();
}

void Death::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

void Death::endDraw()
{
	window->display();
}
