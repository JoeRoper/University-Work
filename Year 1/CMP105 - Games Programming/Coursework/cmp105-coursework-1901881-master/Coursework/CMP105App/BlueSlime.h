#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/Vector.h"
#include "Framework/Input.h"
#include "MC.h"
class BlueSlime : public GameObject
{
public:
	BlueSlime(MC* mc);
	~BlueSlime();
	void update(float dt) override;

protected:
	Animation A_move;
	Animation* current = &A_move;

private:
	float speed, acceleration;
	sf::Vector2f target, direction;//this will be used to calculate where the slime should be moving
	bool moving = true;
	MC* mc;
};



