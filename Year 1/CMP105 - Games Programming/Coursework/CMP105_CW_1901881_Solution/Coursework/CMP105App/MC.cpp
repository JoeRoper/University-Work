#include "MC.h"

MC::MC()
{
	//this is where i added the animation frames to each animation
	//up
	up.addFrame(sf::IntRect(0, 96, 32, 32));
	up.addFrame(sf::IntRect(32, 96, 32, 32));
	up.addFrame(sf::IntRect(64, 96, 32, 32));
	up.addFrame(sf::IntRect(96, 96, 32, 32));
	up.setFrameSpeed(1.f / 10.f);

	//down
	down.addFrame(sf::IntRect(0, 0, 32, 32));
	down.addFrame(sf::IntRect(32, 0, 32, 32));
	down.addFrame(sf::IntRect(64, 0, 32, 32));
	down.addFrame(sf::IntRect(96, 0, 32, 32));
	down.setFrameSpeed(1.f / 10.f);

	//left
	left.addFrame(sf::IntRect(0, 32, 32, 32));
	left.addFrame(sf::IntRect(32, 32, 32, 32));
	left.addFrame(sf::IntRect(64, 32, 32, 32));
	left.addFrame(sf::IntRect(96, 32, 32, 32));
	left.setFrameSpeed(1.f / 10.f);

	//right
	right.addFrame(sf::IntRect(0, 64, 32, 32));
	right.addFrame(sf::IntRect(32, 64, 32, 32));
	right.addFrame(sf::IntRect(64, 64, 32, 32));
	right.addFrame(sf::IntRect(96, 64, 32, 32));
	right.setFrameSpeed(1.f / 10.f);

}

MC::~MC()
{
}

void MC::update(float dt)
{
	if (moving) {
		current->animate(dt);
		setTextureRect(current->getCurrentFrame());
	}
	move(velocity * dt);//this makes the player move and the direction and speed of movement will be set in the handle input function
}

void MC::handleInput(float dt)
{
	setCollisionBox(7, 7, 17, 23);//sets a collision box around the players pixels for more accurate collsion detection
	setVelocity(0, 0);
	if (moving//this makes it so if WASD are not pressed the player stops moving and resets the animation so that the player looks like its standing still
		&& !(input->isKeyDown(sf::Keyboard::W))
		&& !(input->isKeyDown(sf::Keyboard::S))
		&& !(input->isKeyDown(sf::Keyboard::A))
		&& !(input->isKeyDown(sf::Keyboard::D))) {
		moving = false;
		current->reset();
		setTextureRect(current->getCurrentFrame());
	}

	while (getInBoundaries())//while the player is in the rooms boundaries they can move
	{
		//Character Movement
		//Up
		if (input->isKeyDown(sf::Keyboard::W))//makes the player move up when W is pressed by changing the velocity and sets the current animation to up
		{
			moving = true;
			current = &up;
			velocity += sf::Vector2f(0, -200);

		}
		//Down
		if (input->isKeyDown(sf::Keyboard::S))//makes the player move down when S is pressed by changing the velocity and sets the current animation to up
		{
			moving = true;
			current = &down;
			velocity += sf::Vector2f(0, 200);
		}
		//Left
		if (input->isKeyDown(sf::Keyboard::A))//makes the player move left when A is pressed by changing the velocity and sets the current animation to left
		{
			moving = true;
			current = &left;
			velocity += sf::Vector2f(-200, 0);
		}
		//Right
		if (input->isKeyDown(sf::Keyboard::D))//makes the player move right when D is pressed by changing the velocity and sets the current animation to right
		{
			moving = true;
			current = &right;
			velocity += sf::Vector2f(200, 0);
		}
		setInBoundaries(false);
	}
		

	
}
