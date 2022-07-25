#include "BlueSlime.h"

BlueSlime::BlueSlime(MC* mc)
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
	speed = 20.f; //this is the constant speed of the enemy
	acceleration = 10.f;//this will be used to calculate the velocity
	target = sf::Vector2f(50, 50);

	this->mc = mc;


}

BlueSlime::~BlueSlime()
{
}

void BlueSlime::update(float dt)
{
	if (moving) {
		current->animate(dt);
		setTextureRect(current->getCurrentFrame());
		//this is a switch statement that sets the collision box of the slime for each frame 
		//as the sprite doesn't stay in the same place in the texture to give the illusion of the slime jumping when played
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


	
	//Calculating target 
	//target is used to calculate the direction the slime will move in based on the player direction
	target = sf::Vector2f(mc->getPosition().x, mc->getPosition().y);

	//calculate direction and move
	direction = target - getPosition();
	direction = Vector::normalise(direction);
	velocity += (direction * acceleration) * dt;

	move(velocity * speed * dt);

	// if object is close enough to target
	if (Vector::magnitude(target - getPosition()) < 10.f) {
		setPosition(target);
	}
	

}
