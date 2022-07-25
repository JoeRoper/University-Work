#include "Controls.h"
Controls::Controls(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audioManager = aud;

	backB = new GameObject();

	cursor = new Cursor;
	cursor->setInput(in);



	//title screen
	backgroundTexture.loadFromFile("gfx/ControlsScreen.png");
	background.setSize(sf::Vector2f(1344, 768));
	background.setPosition(0, 0);
	background.setTexture(&backgroundTexture);


	//Back		
	backBTexture.loadFromFile("gfx/Buttons/backButton.png");
	backB->setSize(sf::Vector2f(100, 65));
	backB->setPosition(25, 25);
	backB->setTexture(&backBTexture);
	backB->setCollisionBox(0, 0, backB->getSize().x, backB->getSize().y);



}

Controls::~Controls()
{
	delete cursor;
}

void Controls::handleInput(float dt)
{
	gameState->setCurrentState(State::CONTROLS);


	if (Collision::checkBoundingBox(backB, cursor) && (input->isMouseLDown()))
	{
		audioManager->stopAllMusic();
		audioManager->playMusicbyName("menuMusic");//plays the added music

		if (gameState->getLastState() == State::MENU)//makes it so when the button is pressed it goes back to the previous screen
		{
			gameState->setCurrentState(State::MENU);
		}
		else if (gameState->getLastState() == State::PAUSE)
		{
			gameState->setCurrentState(State::PAUSE);
		}
	}
}

void Controls::update(float dt)
{
	window->setView(window->getDefaultView());//sets the view to show the game screen
	cursor->update(dt);
}

void Controls::render()
{
	beginDraw();

	window->draw(background);
	window->draw(*backB);
	window->draw(*cursor);


	endDraw();
}

void Controls::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

void Controls::endDraw()
{
	window->display();
}
