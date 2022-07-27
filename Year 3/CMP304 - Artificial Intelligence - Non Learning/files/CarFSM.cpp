#include "CarFSM.h"

CarFSM::CarFSM(sf::RenderWindow* window)
{
	this->window = window;//sets window pointer to match the one in the simulation

	//loads the texture for the FSM car
	if (!carFSMTexture.loadFromFile("media/RedCar.png"))
	{
		cout << "Couldnt red car texture" << endl;
	}

	//Sets up FSM car sprite
	carFSMSprite.setTexture(carFSMTexture);
	carFSMSprite.setScale(sf::Vector2f(0.65f, 0.65f));
	carFSMSprite.setOrigin(sf::Vector2f(carFSMTexture.getSize().x / 2.0f, carFSMTexture.getSize().y / 2.0f));
	carFSMSprite.setPosition(window->getSize().x / 2.0f, window->getSize().y / 1.5f);

	currentState = CarStates::Centre;//sets the state the car should be in at the start of the game

	//Sets up the car movement variables
	velocity = 0.0f;
	acceleration = 0.0f;
	distanceFromLine = 0.0f;
	speed = 30000.0f;
}

CarFSM::~CarFSM()
{
}

void CarFSM::Update(float dt)
{
	MoveCar(dt);
}

void CarFSM::GetLinePosition(sf::Vector2f linePos)
{
	linePosition = linePos;
}

void CarFSM::MoveCar(float dt)
{
	//calculates how far the car is from the road and also calculates the velocity
	distanceFromLine = linePosition.x - carFSMSprite.getPosition().x;
	distanceFromLine /= window->getSize().x;
	velocity = distanceFromLine / (dt);
	velocity /= 60.0f;

	//Sets the state of the car depending on how far and in which direction the car is from the road
	//CarHeavyLeft
	if (distanceFromLine < -1.0f && velocity < -1.0f)
	{
		currentState = CarStates::HeavyLeft;

	}
	//Car Left
	if (distanceFromLine < -0.5f && velocity < -0.5f)
	{
		currentState = CarStates::Left;

	}
	//Car Centre
	if (distanceFromLine > -0.1f && distanceFromLine < 0.1f && velocity > -0.1f && velocity < 0.1f)
	{
		currentState = CarStates::Centre;
	
	}
	//Car Right
	if (distanceFromLine > 0.5f && velocity > 0.5f)
	{
		currentState = CarStates::Right;

	}
	//Car Heavy Right
	if (distanceFromLine > 1.0f && velocity > 1.0f)
	{
		currentState = CarStates::HeavyRight;
		
	}

	//Switches the state based off the if statements 
	//each state has a different acceleration rate for the car
	switch (currentState)
	{
	case CarStates::HeavyLeft:
		acceleration = 0.15f;
		break;
	case CarStates::Left:
		acceleration = 0.075f;
		break;
	case CarStates::Centre:
		acceleration = 0.01f;
		break;
	case CarStates::Right:
		acceleration = 0.075f;
		break;
	case CarStates::HeavyRight:
		acceleration = 0.15f;
		break;
	default:
		break;
	}

	//moves the car based off the data calculated
	carFSMSprite.move(sf::Vector2f((velocity * acceleration * dt) * speed, 0.0f));
}

void CarFSM::Render()
{
	window->draw(carFSMSprite);
}
