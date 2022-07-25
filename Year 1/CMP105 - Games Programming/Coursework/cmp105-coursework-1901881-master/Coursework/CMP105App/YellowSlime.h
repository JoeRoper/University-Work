#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/Vector.h"
#include "Framework/Input.h"
#include "MC.h"
class YellowSlime : public GameObject
{
public:
	YellowSlime(MC* mc);
	~YellowSlime();
	void update(float dt) override;

protected:
	Animation A_move;
	Animation* current = &A_move;

private:
	float speed, acceleration;
	sf::Vector2f target, direction;
	bool moving = true;
	MC* mc;
};
