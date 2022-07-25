#include "YellowSlime.h"

YellowSlime::YellowSlime(MC* mc)
{
	//move animation
	A_move.addFrame(sf::IntRect(0, 0, 32, 32));
	A_move.addFrame(sf::IntRect(32, 0, 32, 32));
	A_move.addFrame(sf::IntRect(64, 0, 32, 32));
	A_move.addFrame(sf::IntRect(96, 0, 32, 32));
	A_move.addFrame(sf::IntRect(128, 0, 32, 32));
	A_move.addFrame(sf::IntRect(160, 0, 32, 32));
	A_move.setFrameSpeed(1.f / 7.f);

	//enemy movement
	speed = 40.f;
	acceleration = 15.f;
	target = sf::Vector2f(50, 50);

	this->mc = mc;
}

YellowSlime::~YellowSlime()
{
}

void YellowSlime::update(float dt)
{
	if (moving) {
		current->animate(dt);
		setTextureRect(current->getCurrentFrame());

		switch (A_move.getCurrentFrameNum())//sets a new collision box for each frame of the animation 
		{
		case 0:
			setCollisionBox(12, 56, 103, 71);
			break;
		case 1:
			setCollisionBox(4, 71, 119, 56);
			break;
		case 2:
			setCollisionBox(12, 44, 103, 71);
			break;
		case 3:
			setCollisionBox(20, 12, 87, 91);
			break;
		case 4:
			setCollisionBox(28, 0, 67, 103);
			break;
		case 5:
			setCollisionBox(20, 24, 87, 91);
			break;
		}

	}


	//Calculating target
	target = sf::Vector2f(mc->getPosition().x, mc->getPosition().y);

	//calculate direction and move
	direction = target - getPosition();
	direction = Vector::normalise(direction);
	velocity += (direction * acceleration) * dt; //fixed speed

	move(velocity * speed * dt);//moves the slime

	// if object is close enough to target
	if (Vector::magnitude(target - getPosition()) < 10.f) {
		setPosition(target);
	}


}
