#pragma once
#include "Framework/GameObject.h"
#include "Framework/Input.h"
#include "Framework/Animation.h"
class MC : public GameObject, private Input
{
public:
	MC();
	~MC();
	void update(float dt) override;
	void handleInput(float dt) override;
	int getHealth() { return health; };
	void setHealth(int x) { health = x; };
	int getHealthMax() { return healthMax; };



protected:
	//these are the different animations that will be used for player movement
	Animation up;
	Animation down;
	Animation left;
	Animation right;
	Animation* current = &up;

	bool moving = true;
	
	int health = 3;//this will be used to see if the player is dead or not in level
	int healthMax = 3; //this will be used in the hearts class to calculate which frame the animation should be on

	sf::RenderWindow* window;
};

