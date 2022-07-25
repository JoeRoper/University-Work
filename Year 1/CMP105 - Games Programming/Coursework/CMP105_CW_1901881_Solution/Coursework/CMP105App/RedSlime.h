#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/Vector.h"
#include "Framework/Input.h"
#include "MC.h"
class RedSlime : public GameObject
{
public:
	RedSlime(MC* mc);
	~RedSlime();
	void update(float dt) override;
	void setHit(bool b) { hit = b; };
	bool getHit() { return hit; };

protected:
	Animation A_move, A_move2;
	Animation* current = &A_move;

private:
	float speed, acceleration;
	sf::Vector2f target, direction;
	bool moving = true;
	bool hit = false;
	MC* mc;
};
