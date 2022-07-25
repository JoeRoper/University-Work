#include "Pause.h"
Pause::Pause(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audioManager = aud;

	storyB = new GameObject();
	controlsB = new GameObject();
	restartB = new GameObject();
	exitB = new GameObject();
	backB = new GameObject();

	cursor = new Cursor;
	cursor->setInput(in);


	//pause screen
	backgroundTexture.loadFromFile("gfx/BrickBackground.png");
	background.setSize(sf::Vector2f(1344, 768));
	background.setPosition(0, 0);
	background.setTexture(&backgroundTexture);


	//Story Button
	storyBTexture.loadFromFile("gfx/Buttons/StoryButton.png");
	storyB->setSize(sf::Vector2f(220, 75));
	storyB->setPosition(350, 190);
	storyB->setTexture(&storyBTexture);
	storyB->setCollisionBox(0, 0, storyB->getSize().x, storyB->getSize().y);


	//Controls Button
	controlsBTexture.loadFromFile("gfx/Buttons/ControlsButton.png");
	controlsB->setSize(sf::Vector2f(200, 75));
	controlsB->setPosition(370, 390);
	controlsB->setTexture(&controlsBTexture);
	controlsB->setCollisionBox(0, 0, controlsB->getSize().x, controlsB->getSize().y);


	//restart Button
	restartBTexture.loadFromFile("gfx/Buttons/RestartButton.png");
	restartB->setSize(sf::Vector2f(200, 75));
	restartB->setPosition(670, 390);
	restartB->setTexture(&restartBTexture);
	restartB->setCollisionBox(0, 0, restartB->getSize().x, restartB->getSize().y);

	//Exit Button
	exitBTexture.loadFromFile("gfx/Buttons/ExitButton.png");
	exitB->setSize(sf::Vector2f(200, 75));
	exitB->setPosition(670, 190);
	exitB->setTexture(&exitBTexture);
	exitB->setCollisionBox(0, 0, exitB->getSize().x, exitB->getSize().y);

	//Back		
	backBTexture.loadFromFile("gfx/Buttons/backButton.png");
	backB->setSize(sf::Vector2f(100, 65));
	backB->setPosition(25, 25);
	backB->setTexture(&backBTexture);
	backB->setCollisionBox(0, 0, backB->getSize().x, backB->getSize().y);



}

Pause::~Pause()
{
	delete cursor;
}

void Pause::handleInput(float dt)
{
	gameState->setCurrentState(State::PAUSE);
	gameState->setLastState(State::PAUSE);

	if (Collision::checkBoundingBox(storyB, cursor) && (input->isMouseLDown()))
	{
		audioManager->stopAllMusic();
		audioManager->playMusicbyName("menuMusic");//plays the added music
		gameState->setCurrentState(State::STORY);
	}

	if (Collision::checkBoundingBox(controlsB, cursor) && (input->isMouseLDown()))
	{
		audioManager->stopAllMusic();
		audioManager->playMusicbyName("menuMusic");//plays the added music
		gameState->setCurrentState(State::CONTROLS);
	}

	if (Collision::checkBoundingBox(restartB, cursor) && (input->isMouseLDown()))
	{
		audioManager->stopAllMusic();
		audioManager->playMusicbyName("menuMusic");//plays the added music
		gameState->setCurrentState(State::RESTART);
	}

	if (Collision::checkBoundingBox(exitB, cursor) && (input->isMouseLDown()))
	{
		audioManager->stopAllMusic();
		window->close();
	}

	if (Collision::checkBoundingBox(backB, cursor) && (input->isMouseLDown()))
	{
		audioManager->stopAllMusic();
		audioManager->playMusicbyName("levelMusic");//plays the added music
		gameState->setCurrentState(State::LEVEL);
	}
}

void Pause::update(float dt)
{
	window->setView(window->getDefaultView());//sets the view to show the game screen
	cursor->update(dt);
}

void Pause::render()
{
	beginDraw();
	//window->draw(textOb);
	window->draw(background);
	window->draw(*storyB);
	window->draw(*controlsB);
	window->draw(*restartB);
	window->draw(*exitB);
	window->draw(*backB);
	window->draw(*cursor);


	endDraw();
}

void Pause::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

void Pause::endDraw()
{
	window->display();
}
