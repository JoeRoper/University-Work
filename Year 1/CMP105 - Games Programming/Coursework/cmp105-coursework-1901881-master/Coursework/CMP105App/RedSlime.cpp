#include "RedSlime.h"

RedSlime::RedSlime(MC* mc)
{
	//move animation small
	A_move.addFrame(sf::IntRect(0, 0, 32, 32));
	A_move.addFrame(sf::IntRect(32, 0, 32, 32));
	A_move.addFrame(sf::IntRect(64, 0, 32, 32));
	A_move.addFrame(sf::IntRect(96, 0, 32, 32));
	A_move.addFrame(sf::IntRect(128, 0, 32, 32));
	A_move.addFrame(sf::IntRect(160, 0, 32, 32));
	A_move.setFrameSpeed(1.f / 7.f);

	//enemy movement
	speed = 20.f;
	acceleration = 10.f;
	target = sf::Vector2f(50, 50);

	this->mc = mc;


}

RedSlime::~RedSlime()
{
}

void RedSlime::update(float dt)
{
	if (moving)
	{
		current->animate(dt);
		setTextureRect(current->getCurrentFrame());

		if (!getHit())//sets a new collision box for each frame of the animation 
		{
			switch (A_move.getCurrentFrameNum())
			{
		
			case 0:
				setCollisionBox(24, 112, 206, 142);
				break;
			case 1:
				setCollisionBox(8, 142, 238, 112);
				break;
			case 2:
				setCollisionBox(24, 88, 206, 142);
				break;
			case 3:
				setCollisionBox(40, 24, 174, 182);
				break;
			case 4:
				setCollisionBox(56, 0, 134, 206);
				break;
			case 5:
				setCollisionBox(40, 48, 174, 182);
				break;
				
			}
		}

		if (getHit())//if the red slime is hit the collision boxes are made smaller as the slime decreses in size
		{
			switch (A_move.getCurrentFrameNum())
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
	}

	//Calculating target
	target = sf::Vector2f(mc->getPosition().x, mc->getPosition().y);

	//calculate direction and move
	direction = target - getPosition();
	direction = Vector::normalise(direction);
	velocity += (direction * acceleration) * dt; //fixed speed
	move(velocity * speed * dt);//moves the slime

	// if object is close enough to target
	if (Vector::magnitude(target - getPosition()) < 10.f)
	{
		setPosition(target);
	}


		
}

