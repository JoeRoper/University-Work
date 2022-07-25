#include "Level.h"
#include <iostream>
//sets a bunch of values to calculate with in the program 
#define HORIZONTAL_DOOR_WIDTH 224   
#define HORIZONTAL_DOOR_HEIGHT 100
#define VERTICAL_DOOR_WIDTH 55
#define VERTICAL_DOOR_HEIGHT 128
#define ROOM_WIDTH 1344
#define ROOM_HEIGHT 768
Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	audioManager = aud;
	gameState = gs;

	//Initialise pointers
	mc = new MC();
	blueSlime = new BlueSlime(mc);
	yellowSlime = new YellowSlime(mc);
	redSlime = new RedSlime(mc);
	grid1 = new GameObject();
	hearts = new Hearts(mc);

	//Rooms
	Room1Door2 = new GameObject();
	Room2Door1 = new GameObject();
	Room2Door2 = new GameObject();
	Room3Door1 = new GameObject();
	Room3Door2 = new GameObject();
	Room4Door1 = new GameObject();
	Room4Door2 = new GameObject();
	Room5Door1 = new GameObject();
	Room5Door2 = new GameObject();
	Room6Door1 = new GameObject();
	Room6Door2 = new GameObject();


	blueSlime->setAlive(true);
	yellowSlime->setAlive(true);
	redSlime->setAlive(true);
	mc->setAlive(true);

	// initialise game objects
	//MC
	mcTexture.loadFromFile("gfx/MCSheet.png");
	mc->setSize(sf::Vector2f(127, 127));
	mc->setPosition(tileObject.getRoom(1).getCenter().x , tileObject.getRoom(1).getCenter().y + 30);//sets the position of the player to be in room 1 to start
	mc->setTexture(&mcTexture);
	mc->setInput(input);
	mc->setCurrentRoom(1);

	//Blue Slime
	blueSlimeTexture.loadFromFile("gfx/SlimeBlueSpriteSheet.png");
	blueSlime->setSize(sf::Vector2f(127, 127));
	blueSlime->setPosition(tileObject.getRoom(1).getCenter().x - 200, tileObject.getRoom(1).getCenter().y - 100);
	blueSlime->setTexture(&blueSlimeTexture);
	blueSlime->setInput(input);
	blueSlime->setVelocity(10, 10);
	blueSlime->setCurrentRoom(1);

	//Yellow Slime
	yellowSlimeTexture.loadFromFile("gfx/SlimeYellowSpriteSheet.png");
	yellowSlime->setSize(sf::Vector2f(127, 127));
	yellowSlime->setPosition(tileObject.getRoom(2).getCenter().x, tileObject.getRoom(2).getCenter().y - 100);
	yellowSlime->setTexture(&yellowSlimeTexture);
	yellowSlime->setInput(input);
	yellowSlime->setVelocity(10, 10);
	yellowSlime->setCurrentRoom(2);

	//Red Slime
	redSlimeTextureSmall.loadFromFile("gfx/SlimeRedSpriteSheetSmall.png");
	redSlime->setTexture(&redSlimeTextureSmall);
	redSlime->setSize(sf::Vector2f(254, 254));
	redSlime->setPosition(tileObject.getRoom(3).getCenter().x , tileObject.getRoom(3).getCenter().y );
	redSlime->setInput(input);
	redSlime->setVelocity(10, 10);
	redSlime->setCurrentRoom(3);
	redSlime->setHit(false);

	//Rectangle Grid
	gridRectangleTexture.loadFromFile("gfx/GridRectangle.png");
	grid1->setSize(sf::Vector2f(125, 50));
	grid1->setPosition(tileObject.getRoom(1).getCenter().x + 200, tileObject.getRoom(1).getCenter().y - 100);
	grid1->setTexture(&gridRectangleTexture);
	grid1->setCollisionBox(0, 0, 17, 12);

	//Audio
	audioManager->addMusic("sfx/A_Journey_Awaits.ogg", "levelMusic");//add the music file
	audioManager->addSound("sfx/BABABOOEY.wav", "hitSound");//adds a hit sound effect to be played when the player takes damage
	

	//Doors
	//room1

	Room1Door2->setSize(sf::Vector2f(VERTICAL_DOOR_WIDTH, VERTICAL_DOOR_HEIGHT));//uses the defined values to set the doors width and height
	Room1Door2->setPosition(1344, 1888);
	Room1Door2->setCollisionBox(0, 0, VERTICAL_DOOR_WIDTH, VERTICAL_DOOR_HEIGHT);//uses the defined values to set the collision box
	

	//room 2
	Room2Door1->setSize(sf::Vector2f(VERTICAL_DOOR_WIDTH, VERTICAL_DOOR_HEIGHT));
	Room2Door1->setPosition(1225, 1888);
	Room2Door1->setCollisionBox(0, 0, VERTICAL_DOOR_WIDTH, VERTICAL_DOOR_HEIGHT);


	Room2Door2->setSize(sf::Vector2f(HORIZONTAL_DOOR_WIDTH, HORIZONTAL_DOOR_HEIGHT));
	Room2Door2->setPosition(560, 1536);
	Room2Door2->setCollisionBox(0, 0, HORIZONTAL_DOOR_WIDTH, HORIZONTAL_DOOR_HEIGHT);


	//room 3
	Room3Door1->setSize(sf::Vector2f(HORIZONTAL_DOOR_WIDTH, HORIZONTAL_DOOR_HEIGHT));
	Room3Door1->setPosition(560, 1393);
	Room3Door1->setCollisionBox(0, 0, HORIZONTAL_DOOR_WIDTH, HORIZONTAL_DOOR_HEIGHT);


	Room3Door2->setSize(sf::Vector2f(VERTICAL_DOOR_WIDTH, VERTICAL_DOOR_HEIGHT));
	Room3Door2->setPosition(1204, 1120);
	Room3Door2->setCollisionBox(0, 0, VERTICAL_DOOR_WIDTH, VERTICAL_DOOR_HEIGHT);


	//room 4
	Room4Door1->setSize(sf::Vector2f(VERTICAL_DOOR_WIDTH, VERTICAL_DOOR_HEIGHT));
	Room4Door1->setPosition(1344, 1120);
	Room4Door1->setCollisionBox(0, 0, VERTICAL_DOOR_WIDTH, VERTICAL_DOOR_HEIGHT);


	Room4Door2->setSize(sf::Vector2f(HORIZONTAL_DOOR_WIDTH, HORIZONTAL_DOOR_HEIGHT));
	Room4Door2->setPosition(1904, 768);
	Room4Door2->setCollisionBox(0, 0, HORIZONTAL_DOOR_WIDTH, HORIZONTAL_DOOR_HEIGHT);


	//room 5
	Room5Door1->setSize(sf::Vector2f(HORIZONTAL_DOOR_WIDTH, HORIZONTAL_DOOR_HEIGHT));
	Room5Door1->setPosition(1950, 650);
	Room5Door1->setCollisionBox(0, 0, HORIZONTAL_DOOR_WIDTH, HORIZONTAL_DOOR_HEIGHT);


	Room5Door2->setSize(sf::Vector2f(VERTICAL_DOOR_WIDTH, VERTICAL_DOOR_HEIGHT));
	Room5Door2->setPosition(1344, 352);
	Room5Door2->setCollisionBox(0, 0, VERTICAL_DOOR_WIDTH, VERTICAL_DOOR_HEIGHT);


	//room 6
	Room6Door1->setSize(sf::Vector2f(VERTICAL_DOOR_WIDTH, VERTICAL_DOOR_HEIGHT));
	Room6Door1->setPosition(1220, 352);
	Room6Door1->setCollisionBox(0, 0, VERTICAL_DOOR_WIDTH, VERTICAL_DOOR_HEIGHT);


	Room6Door2->setSize(sf::Vector2f(VERTICAL_DOOR_WIDTH, VERTICAL_DOOR_HEIGHT));
	Room6Door2->setPosition(10, 352);
	Room6Door2->setCollisionBox(0, 0, VERTICAL_DOOR_WIDTH, VERTICAL_DOOR_HEIGHT);


	mc->setCurrentRoom(1);
	camera = window->getView();//sets the camera to the windows view
	camera.setCenter(tileObject.getRoomCenter(1));//changes the cameras position to room 1
	window->setView(camera);//sets the view to look from the cameras view
}

Level::~Level()
{
	//deletes everything in the deconstructor so the level can be reset
	delete mc;
	delete blueSlime;
	delete yellowSlime;
	delete redSlime;
	delete grid1;
	delete hearts;

	//Rooms
	delete Room1Door2;
	delete Room2Door1;
	delete Room2Door2;
	delete Room3Door1;
	delete Room3Door2;
	delete Room4Door1;
	delete Room4Door2;
	delete Room5Door1;
	delete Room5Door2;
	delete Room6Door1;
	delete Room6Door2;
}

// handle user input
void Level::handleInput(float dt)
{
	mc->handleInput(dt);

	//Game state pause menu
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		gameState->setCurrentState(State::PAUSE);
	}

}

// Update game objects
void Level::update(float dt)
{
	//updates the cameras view based on which room the player is in
	camera = window->getView();
	camera.setCenter(tileObject.getRoom(mc->getCurrentRoom()).getCenter());
	window->setView(camera);

	checkRoom();//plays check room function and updates the doors which teleport the player

	checkBoundaries(mc);//plays function to check if the player is within the room boundaries
	mc->subtractInvis(dt);//subtracts the players invisibility over delta time

	if (mc->isAlive())//if the player is alive they wll update otherwise they go to the death screen
	{
		mc->update(dt);
	}
	else 
	{
		gameState->setCurrentState(State::DEATH);
	}

	hearts->setPosition(window->getView().getCenter().x - ROOM_WIDTH / 2, window->getView().getCenter().y - ROOM_HEIGHT / 2);//makes sure the hearts are always in the top left of the screen
	hearts->update(dt);


	blueSlime->update(dt);
	checkBoundaries(blueSlime);//plays function to check if the slime is within the room boundaries
	blueSlime->subtractInvis(dt);//subtracts the slimes invisibility over delta time

	yellowSlime->update(dt);
	checkBoundaries(yellowSlime);//plays function to check if the slime is within the room boundaries
	yellowSlime->subtractInvis(dt);//subtracts the slimes invisibility over delta time

	redSlime->update(dt);
	checkBoundaries(redSlime);//plays function to check if the slime is within the room boundaries
	redSlime->subtractInvis(dt);//subtracts the slimes invisibility over delta time

	handleCollision();//updates the collision function


}

// Render level
void Level::render()
{
	beginDraw();
	tileObject.render(window);
	
	window->draw(*grid1);
	window->draw(*hearts);
	window->draw(*mc);
	
	window->draw(*blueSlime);
	window->draw(*yellowSlime);
	window->draw(*redSlime);
	
	endDraw();
}

void Level::checkBoundaries(GameObject* currentObject)
{
	int scale = 0;
	if (currentObject == redSlime && redSlime->getHit() == false)//if the red slime isnt hit the scale is increased to map the room boundaries to the increased size of the slime
	{
		scale = 127;
	}
	
	//Level Boundaries
	//the boundaries are updated based on what room the player or enemies are in
	if (currentObject->getPosition().x <= tileObject.getRoom(currentObject->getCurrentRoom()).getCenter().x - (657))
	{
		currentObject->setPosition(currentObject->getPosition().x + 1, currentObject->getPosition().y);
		currentObject->setVelocity(0, 0);
	}
	else if (currentObject->getPosition().x >= tileObject.getRoom(currentObject->getCurrentRoom()).getCenter().x + (532 - scale))
	{
		currentObject->setPosition(currentObject->getPosition().x - 1, currentObject->getPosition().y);
		currentObject->setVelocity(0, 0);
	}
	else if (currentObject->getPosition().y <= tileObject.getRoom(currentObject->getCurrentRoom()).getCenter().y - (362 + scale))
	{
		currentObject->setPosition(currentObject->getPosition().x, currentObject->getPosition().y + 1);
		currentObject->setVelocity(0, 0);
	}
	else if (currentObject->getPosition().y >= tileObject.getRoom(currentObject->getCurrentRoom()).getCenter().y + (242 - scale))
	{
		currentObject->setPosition(currentObject->getPosition().x, currentObject->getPosition().y - 1);
		currentObject->setVelocity(0, 0);
	}
	else
	{
		currentObject->setInBoundaries(true);
	}
}

void Level::checkRoom()
{
	//Entering a new room
	//when a player enters the collision box of a door the player is teleported to the other side of the door
	if (Collision::checkBoundingBox(mc, Room1Door2))
	{
		mc->setCurrentRoom(2);
		grid1->setPosition(tileObject.getRoom(2).getCenter().x - 200, tileObject.getRoom(2).getCenter().y - 100);//the grid is teleported along with the player so only one grid is needed
		mc->setPosition(1100, 1920);
	}
	if (Collision::checkBoundingBox(mc, Room2Door2))
	{
		mc->setCurrentRoom(3);
		grid1->setPosition(tileObject.getRoom(3).getCenter().x - 200, tileObject.getRoom(3).getCenter().y + 100);
		mc->setPosition(672, 1200);
	}
	if (Collision::checkBoundingBox(mc, Room3Door2))
	{
		mc->setCurrentRoom(4);
		grid1->setPosition(tileObject.getRoom(4).getCenter().x + 200, tileObject.getRoom(4).getCenter().y - 100);
		mc->setPosition(1600, 1152);
	}
	if (Collision::checkBoundingBox(mc, Room4Door2))
	{
		mc->setCurrentRoom(5);
		grid1->setPosition(tileObject.getRoom(5).getCenter().x + 200, tileObject.getRoom(5).getCenter().y + 100);
		mc->setPosition(2016, 500);
	}
	if (Collision::checkBoundingBox(mc, Room5Door2))
	{
		mc->setCurrentRoom(6);
		grid1->setPosition(tileObject.getRoom(6).getCenter().x , tileObject.getRoom(6).getCenter().y + 200);
		mc->setPosition(672, 384);
	}
	if (Collision::checkBoundingBox(mc, Room6Door2))//when the player goes throught the last door the game screen is set to win
	{
		mc->setCurrentRoom(1);
		gameState->setCurrentState(State::WIN);
	}

	//Entering a previous room
	if (Collision::checkBoundingBox(mc, Room2Door1))
	{
		mc->setCurrentRoom(1);
		grid1->setPosition(tileObject.getRoom(1).getCenter().x + 200, tileObject.getRoom(1).getCenter().y - 100);
		mc->setPosition(1500, 1920);
	}
	if (Collision::checkBoundingBox(mc, Room3Door1))
	{
		mc->setCurrentRoom(2);
		grid1->setPosition(tileObject.getRoom(2).getCenter().x - 200, tileObject.getRoom(2).getCenter().y - 100);
		mc->setPosition(672, 1700);
	}
	if (Collision::checkBoundingBox(mc, Room4Door1))
	{
		mc->setCurrentRoom(3);
		grid1->setPosition(tileObject.getRoom(3).getCenter().x - 200, tileObject.getRoom(3).getCenter().y + 100);
		mc->setPosition(1100, 1152);
	}
	if (Collision::checkBoundingBox(mc, Room5Door1))
	{
		mc->setCurrentRoom(4);
		grid1->setPosition(tileObject.getRoom(4).getCenter().x + 200, tileObject.getRoom(4).getCenter().y - 100);
		mc->setPosition(2016, 900);
	}
	if (Collision::checkBoundingBox(mc, Room6Door1))
	{
		mc->setCurrentRoom(5);
		grid1->setPosition(tileObject.getRoom(5).getCenter().x + 200, tileObject.getRoom(5).getCenter().y + 100);
		mc->setPosition(1420, 384);
	}
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}

void Level::handleCollision()
{
	if (Collision::checkBoundingBox(blueSlime, grid1) && !mc->getInvis())
	{
		blueSlime->addInvis(5);//stops the slime from getting hit by the grid again
		//too save data the slimes dont die they just get teleported to a different room
		if (blueSlime->getCurrentRoom() == 6)
		{
			blueSlime->setCurrentRoom(1);
			blueSlime->setPosition(tileObject.getRoom(1).getCenter().x , tileObject.getRoom(1).getCenter().y );
		}
		if (blueSlime->getCurrentRoom() == 5)
		{
			blueSlime->setCurrentRoom(6);
			blueSlime->setPosition(tileObject.getRoom(6).getCenter().x , tileObject.getRoom(6).getCenter().y );
		}
		if (blueSlime->getCurrentRoom() == 4)
		{
			blueSlime->setCurrentRoom(5);
			blueSlime->setPosition(tileObject.getRoom(5).getCenter().x , tileObject.getRoom(5).getCenter().y );
		}
		if (blueSlime->getCurrentRoom() == 1)
		{
			blueSlime->setCurrentRoom(4);
			blueSlime->setPosition(tileObject.getRoom(4).getCenter().x , tileObject.getRoom(4).getCenter().y );
		}
		
		
		
	}
	if (Collision::checkBoundingBox(yellowSlime, grid1) && !mc->getInvis())
	{
		yellowSlime->addInvis(5);//stops the slime from getting hit by the grid again
		//too save data the slimes dont die they just get teleported to a different room
		if (yellowSlime->getCurrentRoom() == 6)
		{
			yellowSlime->setCurrentRoom(2);
			yellowSlime->setPosition(tileObject.getRoom(2).getCenter().x, tileObject.getRoom(2).getCenter().y);
		}
		if (yellowSlime->getCurrentRoom() == 4)
		{
			yellowSlime->setCurrentRoom(6);
			yellowSlime->setPosition(tileObject.getRoom(6).getCenter().x, tileObject.getRoom(6).getCenter().y );
		}
		if (yellowSlime->getCurrentRoom() == 2)
		{
			yellowSlime->setCurrentRoom(4);
			yellowSlime->setPosition(tileObject.getRoom(4).getCenter().x, tileObject.getRoom(4).getCenter().y );
		}
		
		
	}
	if (Collision::checkBoundingBox(redSlime, grid1) && !mc->getInvis())
	{
		redSlime->addInvis(10);//stops the slime from getting hit by the grid again
		//too save data the slimes dont die they just get teleported to a different room
		double scale = 0.5;
		redSlime->setSize(sf::Vector2f(254 * scale, 254 * scale));//if the red slime is hit the size of the slime is decreased
		if (redSlime->getHit() == true)
		{
			redSlime->setHit(false);

			if (redSlime->getCurrentRoom() == 6)
			{
				blueSlime->setCurrentRoom(3);
				redSlime->setPosition(tileObject.getRoom(3).getCenter().x, tileObject.getRoom(3).getCenter().y);
			}
			if (redSlime->getCurrentRoom() == 5)
			{
				blueSlime->setCurrentRoom(6);
				redSlime->setPosition(tileObject.getRoom(6).getCenter().x, tileObject.getRoom(6).getCenter().y);
			}
			if (redSlime->getCurrentRoom() == 3)
			{
				blueSlime->setCurrentRoom(5);
				redSlime->setPosition(tileObject.getRoom(5).getCenter().x, tileObject.getRoom(5).getCenter().y);
			}
			redSlime->setSize(sf::Vector2f(254, 254));//resets the slime to its original size after its been hit twice
		}
		redSlime->setHit(true);
	}
	//checks to see if the player has been hit by a slime
	if (((Collision::checkBoundingBox(mc, blueSlime))
		|| (Collision::checkBoundingBox(mc, yellowSlime)) 
		|| (Collision::checkBoundingBox(mc, redSlime))) 
		&& !mc->getInvis())
	{
		audioManager->playSoundbyName("hitSound");//plays this sound when the player is hit
		mc->addInvis(0.5);
		
		int x = mc->getHealth() - 1;//when hit decreases health
		mc->setHealth(x);

		if (mc->getHealth() <= 0)//when the players health hits 0 the death screen is displayed
		{
			mc->setAlive(false);//this stops updating the player in the level update function
			gameState->setCurrentState(State::DEATH);
		}
	}
}
