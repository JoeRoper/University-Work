#include "Cursor.h"

Cursor::Cursor()
{
	cursor_t.loadFromFile("gfx/Mouse.png");//adds the cursor texture
	setTexture(&cursor_t);
	setSize(sf::Vector2f(40, 50));
	setPosition(100, 400);
	setCollisionBox(0, 0, 6, 8);
	setInput(input);//allows the cursor to get the input from the player
}

Cursor::~Cursor()
{
}

void Cursor::update(float dt)
{
	setPosition(input->getMouseX(), input->getMouseY());//sets the position of the cursor to that of the users mouse
}
