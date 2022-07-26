// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
// @author Paul Robertson

#include <iostream>
#include "Level.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Menu.h"
#include "Pause.h"
#include "Controls.h"
#include "Story.h"
#include "Win.h"
#include "Death.h"

void restartLevel(sf::RenderWindow* window, Input* input, GameState* gameState, AudioManager* audioManager, Level** level); //function used to reset the level so the player can restart the game

void windowProcess(sf::RenderWindow* window, Input* in)
{
	// Handle window events.
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			window->setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
			break;
		case sf::Event::KeyPressed:
			// update input class
			in->setKeyDown(event.key.code);
			break;
		case sf::Event::KeyReleased:
			//update input class
			in->setKeyUp(event.key.code);
			break;
		case sf::Event::MouseMoved:
			//update input class
			in->setMousePosition(event.mouseMove.x, event.mouseMove.y);
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//update input class
				in->setMouseLDown(true);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				in->setMouseRDown(true);
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//update input class
				in->setMouseLDown(false);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				in->setMouseRDown(false);
			}
			break;
		default:
			// don't handle other events
			break;
		}
	}
}

int main()
{
	//Create the window
	sf::RenderWindow window(sf::VideoMode(1344, 768, 32), "CMP105");

	// Initialise objects for delta time
	sf::Clock clock;
	float deltaTime;

	// Calculate delta time. How much time has passed 
	// since it was last calculated (in seconds) and restart the clock.
	deltaTime = clock.restart().asSeconds();

	// Initialise input and level objects.
	AudioManager audioManager;
	Input input;
	GameState gameState;
	Level* level = new Level(&window, &input, &gameState, &audioManager);
	Menu menu(&window, &input, &gameState, &audioManager);
	Pause pause(&window, &input, &gameState, &audioManager);
	Controls controls(&window, &input, &gameState, &audioManager);
	Story story(&window, &input, &gameState, &audioManager);
	Win win(&window, &input, &gameState, &audioManager);
	Death death(&window, &input, &gameState, &audioManager);


	//Get rid of mouse 
	window.setMouseCursorVisible(false);

	gameState.setCurrentState(State::MENU);//set the game to open on the menu screen

	// Game Loop
	while (window.isOpen())
	{
		//Process window events
		windowProcess(&window, &input);

		// Calculate delta time. How much time has passed 
		// since it was last calculated (in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();



		switch (gameState.getCurrentState())
		{

		case(State::MENU):
			menu.handleInput(deltaTime);
			menu.update(deltaTime);
			menu.render();
			break;

		case(State::PAUSE):
			pause.handleInput(deltaTime);
			pause.update(deltaTime);
			pause.render();
			break;

		case(State::CONTROLS):
			controls.handleInput(deltaTime);
			controls.update(deltaTime);
			controls.render();
			break;

		case(State::STORY):
			story.handleInput(deltaTime);
			story.update(deltaTime);
			story.render();
			break;

		case(State::WIN):
			win.handleInput(deltaTime);
			win.update(deltaTime);
			win.render();
			break;

		case(State::DEATH):
			death.handleInput(deltaTime);
			death.update(deltaTime);
			death.render();
			break;

		case(State::LEVEL):
			level->handleInput(deltaTime);
			level->update(deltaTime);
			level->render();
			break;

		case(State::RESTART):
			restartLevel(&window, &input, &gameState, &audioManager, &level);//uses function to reset level then changes the screen to menu
			gameState.setCurrentState(State::MENU);
			break;
		}
	}
}

void restartLevel(sf::RenderWindow* window, Input* input, GameState* gameState, AudioManager* audioManager, Level** level)//deletes the level then makes a new one when the function is used
{
	delete* level;
	*level = new Level(window, input, gameState, audioManager);
}
