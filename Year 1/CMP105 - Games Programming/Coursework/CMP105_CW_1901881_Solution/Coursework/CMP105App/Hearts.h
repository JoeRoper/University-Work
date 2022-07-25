#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "MC.h"
class Hearts : public GameObject
{
public:
	Hearts(MC* mc);
	~Hearts();
	void update(float dt) override;
protected:
	Animation heartFrames; //this will hold the hearts animation
	Animation* current = &heartFrames;//this will be used to decide what should be animated
	MC* mc;//this will be used to access the players health
	
	sf::Texture heartsTexture;//this will contain the hearts sprite sheet
};

