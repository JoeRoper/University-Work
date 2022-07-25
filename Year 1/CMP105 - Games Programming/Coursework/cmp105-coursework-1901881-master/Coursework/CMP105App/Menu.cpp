#include "Menu.h"

Menu::Menu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audioManager = aud;

	storyB = new GameObject();
	controlsB = new GameObject();
	startB = new GameObject();
	exitB = new GameObject();


	cursor = new Cursor;
	cursor->setInput(in);


	//title screen
	tsTexture.loadFromFile("gfx/TitleScreen.png");
	ts.setSize(sf::Vector2f(1344, 768));
	ts.setPosition(0, 0);
	ts.setTexture(&tsTexture);

	//Story Button
	storyBTexture.loadFromFile("gfx/Buttons/StoryButton.png");
	storyB->setSize(sf::Vector2f(200, 75));
	storyB->setPosition(190, 640);
	storyB->setTexture(&storyBTexture);
	storyB->setCollisionBox(0, 0, storyB->getSize().x, storyB->getSize().y);


	//Controls Button
	controlsBTexture.loadFromFile("gfx/Buttons/ControlsButton.png");
	controlsB->setSize(sf::Vector2f(200, 75));
	controlsB->setPosition(430, 640);
	controlsB->setTexture(&controlsBTexture);
	controlsB->setCollisionBox(0, 0, controlsB->getSize().x, controlsB->getSize().y);

	//Start Button
	startBTexture.loadFromFile("gfx/Buttons/StartButton.png");
	startB->setSize(sf::Vector2f(200, 75));
	startB->setPosition(670, 640);
	startB->setTexture(&startBTexture);
	startB->setCollisionBox(0, 0, startB->getSize().x, startB->getSize().y);

	//Exit Button
	exitBTexture.loadFromFile("gfx/Buttons/ExitButton.png");
	exitB->setSize(sf::Vector2f(200, 75));
	exitB->setPosition(910, 640);
	exitB->setTexture(&exitBTexture);
	exitB->setCollisionBox(0, 0, exitB->getSize().x, exitB->getSize().y);

	//Audio
	audioManager->stopAllMusic();
	audioManager->addMusic("sfx/On_My_Way.wav", "menuMusic");//adds the music file
	audioManager->playMusicbyName("menuMusic");//plays the added music

}

Menu::~Menu()
{
	delete cursor;
}

void Menu::handleInput(float dt)
{
	gameState->setCurrentState(State::MENU);
	gameState->setLastState(State::MENU); //sets the lastState to MENU this will be used for the back button in the controls and story state screen

	if (Collision::checkBoundingBox(storyB, cursor) && (input->isMouseLDown()))
	{
		gameState->setCurrentState(State::STORY);
		audioManager->stopAllMusic();
		audioManager->playMusicbyName("menuMusic");//plays the added music
	}

	if (Collision::checkBoundingBox(controlsB, cursor) && (input->isMouseLDown()))
	{
		//std::cout << "Orange" << std::endl;
		gameState->setCurrentState(State::CONTROLS);
		audioManager->stopAllMusic();
		audioManager->playMusicbyName("menuMusic");//plays the added music
	}

	if (Collision::checkBoundingBox(startB, cursor) && (input->isMouseLDown()))
	{
		audioManager->stopAllMusic();
		audioManager->playMusicbyName("levelMusic");
		gameState->setCurrentState(State::LEVEL);
	}

	if (Collision::checkBoundingBox(exitB, cursor) && (input->isMouseLDown()))
	{
		audioManager->stopAllMusic();
		window->close();
	}
}

void Menu::update(float dt)
{
	 
	window->setView(window->getDefaultView());//sets the view to show the game screen
	cursor->update(dt);
}

void Menu::render()
{
	beginDraw();
	window->draw(ts);
	window->draw(*storyB);
	window->draw(*controlsB);
	window->draw(*startB);
	window->draw(*exitB);
	window->draw(*cursor);


	endDraw();
}

void Menu::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

void Menu::endDraw()
{
	window->display();
}
