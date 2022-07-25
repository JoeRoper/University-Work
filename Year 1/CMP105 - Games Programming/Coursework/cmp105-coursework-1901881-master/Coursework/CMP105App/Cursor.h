#pragma once
#include "Framework/GameObject.h"
class Cursor : public GameObject
{
private:
	sf::Vector2f* offset;
	sf::Texture cursor_t;
	
public:
	Cursor();
	~Cursor();

	void update(float dt) override;


};

