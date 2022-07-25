#pragma once
#include "Framework/TileMap.h"
#include "Framework/GameObject.h"
class Tiles : public TileMap
{
private:
	sf::RenderWindow* windRender;
	TileMap currentRoom;
	std::vector<TileMap> rooms;
	sf::Vector2u* wind;
public:
	Tiles();
	~Tiles();
	void render(sf::RenderWindow* wind);
	sf::Vector2f getRoomCenter(int x);
	TileMap getCurrentRoom() { return currentRoom; };
	void setCurrentRoom(TileMap room) { currentRoom = room; };
	TileMap getRoom(int  x) { return rooms[x -= 1];};//x is decreased by 1 to match the number in the array 
		
};

