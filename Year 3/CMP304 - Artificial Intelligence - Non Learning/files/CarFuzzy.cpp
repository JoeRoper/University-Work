#include "CarFuzzy.h"

CarFuzzy::CarFuzzy(sf::RenderWindow* window)
{
	this->window = window;//sets window pointer to match the one in the simulation

	//loads the texture for the FLSM car
	if (!carFuzzyTexture.loadFromFile("media/BlueCar.png"))
	{
		cout << "Couldnt red car texture" << endl;
	}

	//sets up the FLSM car sprite
	carFuzzySprite.setTexture(carFuzzyTexture);
	carFuzzySprite.setScale(sf::Vector2f(0.65f, 0.65f));
	carFuzzySprite.setOrigin(sf::Vector2f(carFuzzyTexture.getSize().x / 2.0f, carFuzzyTexture.getSize().y / 2.0f));
	carFuzzySprite.setPosition(window->getSize().x / 2.0f, window->getSize().y / 3.5f);

	currentState = CarStates::Centre;//sets the state the car should be in at the start of the game

	//Sets up the car movement variables
	velocity = 0.0f;
	distanceFromLine = 0.0f;
	speed = 1000.0f;

	fuzzyEngine = FisImporter().fromFile("CarFuzzySystem2.fis");//imports the fuzzy engine created in MatLab
}

CarFuzzy::~CarFuzzy()
{
}

void CarFuzzy::Update(float dt)
{
	MoveCar(dt);
}

void CarFuzzy::GetLinePosition(sf::Vector2f linePos)
{
	linePosition = linePos;
}

void CarFuzzy::MoveCar(float dt)
{
	//calculates how far the car is from the road and also calculates the velocity
	distanceFromLine = linePosition.x - carFuzzySprite.getPosition().x;
	distanceFromLine /= window->getSize().x / 2.0f;
	velocity = distanceFromLine / (dt);
	velocity /= 60.0f;


	// Stops velocity from going out of the set ranged defined in the fuzzy engine
	if (velocity < -1.0f)
	{
		velocity = -1.0f;
	}
	else if (velocity > 1.0f)
	{
		velocity = 1.0f;
	}

	//Sets up the engine
	fuzzyEngine->setInputValue("Distance", distanceFromLine);
	fuzzyEngine->setInputValue("Velocity", velocity);
	fuzzyEngine->process();
	direction = fuzzyEngine->getOutputValue("Direction");

	//Sets the state of the car depending on how far and in which direction the car is from the road
	//Has the same values graphed within the fuzzy engine
	
	//CarHeavyLeft
	if (distanceFromLine < -1.0f && velocity < -1.0f)
	{
		currentState = CarStates::HeavyLeft;
	}
	//Car Left
	if (distanceFromLine < -0.43f && velocity < -0.43f)
	{
		currentState = CarStates::Left;
	}
	//Car Centre
	if (distanceFromLine > -0.1f && distanceFromLine < 0.1f && velocity > -0.1f && velocity < 0.1f)
	{
		currentState = CarStates::Centre;
	}
	//Car Right
	if (distanceFromLine > 0.43f && velocity > 0.43f)
	{
		currentState = CarStates::Right;
	}
	//Car Heavy Right
	if (distanceFromLine > 1.0f && velocity > 1.0f)
	{
		currentState = CarStates::HeavyRight;
	}

	float move = (direction * dt) * speed;

	switch (currentState)
	{
	case CarStates::HeavyLeft:
		carFuzzySprite.move(sf::Vector2f(move, 0.0f));
		break;
	case CarStates::Left:
		carFuzzySprite.move(sf::Vector2f(move, 0.0f));
		break;
	case CarStates::Centre:
		carFuzzySprite.move(sf::Vector2f(move, 0.0f));
		break;
	case CarStates::Right:
		carFuzzySprite.move(sf::Vector2f(move, 0.0f));
		break;
	case CarStates::HeavyRight:
		carFuzzySprite.move(sf::Vector2f(move, 0.0f));
		break;
	default:
		break;
	}

}

void CarFuzzy::Render()
{
	window->draw(carFuzzySprite);
}
