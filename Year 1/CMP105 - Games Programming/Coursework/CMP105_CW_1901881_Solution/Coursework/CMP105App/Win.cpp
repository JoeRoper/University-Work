#include "Win.h"
Win::Win(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
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
	backgroundTexture.loadFromFile("gfx/Win.png");
	background.setSize(sf::Vector2f(1344, 768));
	background.setPosition(0, 0);
	background.setTexture(&backgroundTexture);

	//Exit Button
	exitBTexture.loadFromFile("gfx/Buttons/ExitButton.png");//loads the texture
	exitB->setSize(sf::Vector2f(200, 75));
	exitB->setPosition(700, 620);
	exitB->setTexture(&exitBTexture);//sets the texture
	exitB->setCollisionBox(0, 0, exitB->getSize().x, exitB->getSize().y);//sets the collision box of the button

	//restart Button
	restartBTexture.loadFromFile("gfx/Buttons/RestartButton.png");
	restartB->setSize(sf::Vector2f(200, 75));
	restartB->setPosition(400, 620);
	restartB->setTexture(&restartBTexture);
	restartB->setCollisionBox(0, 0, restartB->getSize().x, restartB->getSize().y);

	
}

Win::~Win()
{
	delete cursor;
}

void Win::handleInput(float dt)
{
	gameState->setCurrentState(State::WIN);//sets the game state to WIN screen

	//checks to see if the cursor is within the button and the left mouse button is pressed
	if (Collision::checkBoundingBox(exitB, cursor) && (input->isMouseLDown()))
	{
		window->close();//closes the game
	}

	if (Collision::checkBoundingBox(restartB, cursor) && (input->isMouseLDown()))
	{
		gameState->setCurrentState(State::RESTART);//set state to restart so that the level is reset
	}
}

void Win::update(float dt)
{
	window->setView(window->getDefaultView());//sets the view to show the game screen
	cursor->update(dt);
}

void Win::render()
{
	beginDraw();
	//draws the background texture, the buttons and the cursor
	window->draw(background);
	window->draw(*exitB);
	window->draw(*restartB);
	window->draw(*cursor);


	endDraw();
}

void Win::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

void Win::endDraw()
{
	window->display();
}
