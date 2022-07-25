#include "Tiles.h"
#define ROOM_WIDTH 1344 //defines a number will be used for setting the rooms position
#define ROOM_HEIGHT 768

Tiles::Tiles()
{
	//Creating the tile set
	GameObject tile;
	std::vector<GameObject> tiles;
	for (int i = 0; i < 28; i++)//sets the size of each tile
	{
		tile.setSize(sf::Vector2f(224, 128));
		tile.setCollisionBox(0, 0, 32, 32);
		tile.setCollider(true);
		tiles.push_back(tile);
	}
	tiles[0].setCollider(false);//left, top, width, height
	
	//Sets the coordinates of the tiles based on the tile map
	//Row 1
	tiles[0].setTextureRect(sf::IntRect(0, 0, 32, 32));
	tiles[1].setTextureRect(sf::IntRect(32, 0, 32, 32));
	tiles[2].setTextureRect(sf::IntRect(64, 0, 32, 32));
	tiles[3].setTextureRect(sf::IntRect(96, 0, 32, 32));
	tiles[4].setTextureRect(sf::IntRect(128, 0, 32, 32));
	tiles[5].setTextureRect(sf::IntRect(160, 0, 32, 32));
	tiles[6].setTextureRect(sf::IntRect(192, 0, 32, 32));
	//Row 2
	tiles[7].setTextureRect(sf::IntRect(0, 32, 32, 32));
	tiles[8].setTextureRect(sf::IntRect(32, 32, 32, 32));
	tiles[9].setTextureRect(sf::IntRect(64, 32, 32, 32));
	tiles[10].setTextureRect(sf::IntRect(96, 32, 32, 32));
	tiles[11].setTextureRect(sf::IntRect(128, 32, 32, 32));
	tiles[12].setTextureRect(sf::IntRect(160, 33, 32, 32));
	tiles[13].setTextureRect(sf::IntRect(192, 33, 32, 32));
	//Row 3
	tiles[14].setTextureRect(sf::IntRect(0, 64, 32, 32));
	tiles[15].setTextureRect(sf::IntRect(32, 64, 32, 32));
	tiles[16].setTextureRect(sf::IntRect(64, 64, 32, 32));
	tiles[17].setTextureRect(sf::IntRect(96, 64, 32, 32));
	tiles[18].setTextureRect(sf::IntRect(128, 64, 32, 32));
	tiles[19].setTextureRect(sf::IntRect(160, 64, 32, 32));
	tiles[20].setTextureRect(sf::IntRect(192, 64, 32, 32));
	//Row 4
	tiles[21].setTextureRect(sf::IntRect(0, 96, 32, 32));
	tiles[22].setTextureRect(sf::IntRect(32, 96, 32, 32));
	tiles[23].setTextureRect(sf::IntRect(64, 96, 32, 32));
	tiles[24].setTextureRect(sf::IntRect(96, 96, 32, 32));
	tiles[25].setTextureRect(sf::IntRect(128, 96, 32, 32));
	tiles[26].setTextureRect(sf::IntRect(160, 96, 32, 32));
	tiles[27].setTextureRect(sf::IntRect(192, 96, 32, 32));

	for (int i = 0; i < 6; i++) {//sets up all the rooms
		TileMap temp;
		temp.loadTexture("gfx/DungeonTileMap.png");
		temp.setTileSet(tiles);
		rooms.push_back(temp);
	}
	

	//Room 6 Map creation
	// Map dimensions
	sf::Vector2u mapSize6(6, 6);//sets the map size to 6 tiles by 6 tiles
	// build map
	std::vector<int> map6 =
	{
		0, 4, 5, 4, 5, 3,
		11, 8, 8, 8, 8, 12,
		7, 8, 8, 8, 8, 10,
		14, 8, 8, 8, 8, 17,
		18, 8, 8, 8, 8, 19,
		21, 25, 26, 25, 26, 24
	};
	rooms[5].setTileMap(map6, mapSize6);
	rooms[5].setPosition(sf::Vector2f(0, 0));//sets the position of the room 
	rooms[5].setCenter(sf::Vector2f(rooms[5].getPosition().x + ROOM_WIDTH/2, rooms[5].getPosition().y + ROOM_HEIGHT / 2));//sets the centre of the room by adding the ROOM_WIDTH and ROOM_HEIGHT to the rooms position in the window
	rooms[5].buildLevel();

	//Room 1 Map creation
	// Map dimensions
	sf::Vector2u mapSize1(6, 6);
	// build map
	std::vector<int> map1 = 
	{
		0, 4, 5, 4, 5, 3, 
		11, 8, 8, 8, 8, 12,
		7, 8, 8, 8, 8, 19,
		14, 8, 8, 8, 8, 12,
		18, 8, 8, 8, 8, 19,
		21, 25, 22, 23, 26, 24

	};
	rooms[0].setTileMap(map1, mapSize1);
	rooms[0].setPosition(sf::Vector2f(rooms[5].getPosition().x + ROOM_WIDTH, rooms[5].getPosition().y + ROOM_HEIGHT * 2));//sets the position of the room to be underneath room 4
	rooms[0].setCenter(sf::Vector2f(rooms[0].getPosition().x + ROOM_WIDTH / 2, rooms[0].getPosition().y + ROOM_HEIGHT / 2));
	rooms[0].buildLevel();

	//Room 2 Map creation
	// Map dimensions
	sf::Vector2u mapSize2(6, 6);
	// build map
	std::vector<int> map2 =
	{
		0, 4, 1, 2, 5, 3, 
		11, 8, 8, 8, 8, 12, 
		18, 8, 8, 8, 8, 10, 
		11, 8, 8, 8, 8, 17, 
		18, 8, 8, 8, 8, 19, 
		21, 25, 26, 25, 26, 24

	};
	rooms[1].setTileMap(map2, mapSize2);
	rooms[1].setPosition(sf::Vector2f(rooms[5].getPosition().x , rooms[5].getPosition().y + ROOM_HEIGHT * 2));//sets the position of the room to be under room 3
	rooms[1].setCenter(sf::Vector2f(rooms[1].getPosition().x + ROOM_WIDTH / 2, rooms[1].getPosition().y + ROOM_HEIGHT / 2));
	rooms[1].buildLevel();

	//Room 3 Map creation
	// Map dimensions
	sf::Vector2u mapSize3(6, 6);
	// build map
	std::vector<int> map3 =
	{
		0, 4, 5, 4, 5, 3, 
		11, 8, 8, 8, 8, 12, 
		18, 8, 8, 8, 8, 10, 
		11, 8, 8, 8, 8, 17, 
		18, 8, 8, 8, 8, 19, 
		21, 25, 22, 23, 26, 24

	};
	rooms[2].setTileMap(map3, mapSize3);
	rooms[2].setPosition(sf::Vector2f(rooms[5].getPosition().x , rooms[5].getPosition().y + ROOM_HEIGHT));//sets the position of the room to be under room 6
	rooms[2].setCenter(sf::Vector2f(rooms[2].getPosition().x + ROOM_WIDTH / 2, rooms[2].getPosition().y + ROOM_HEIGHT / 2));
	rooms[2].buildLevel();

	//Room 4 Map creation
	// Map dimensions
	sf::Vector2u mapSize4(6, 6);
	// build map
	std::vector<int> map4 =
	{
		0, 4, 1, 2, 5, 3,
		11, 8, 8, 8, 8, 12,
		7, 8, 8, 8, 8, 19,
		14, 8, 8, 8, 8, 12,
		18, 8, 8, 8, 8, 19,
		21, 25, 26, 25, 26, 24

	};
	rooms[3].setTileMap(map4, mapSize4);
	rooms[3].setPosition(sf::Vector2f(rooms[5].getPosition().x + ROOM_WIDTH, rooms[5].getPosition().y + ROOM_HEIGHT));//sets the position of the room to be under room 5
	rooms[3].setCenter(sf::Vector2f(rooms[3].getPosition().x + ROOM_WIDTH / 2, rooms[3].getPosition().y + ROOM_HEIGHT / 2));
	rooms[3].buildLevel();

	//Room 5 Map creation
	// Map dimensions
	sf::Vector2u mapSize5(6, 6);
	// build map
	std::vector<int> map5 =
	{
		 0, 4, 5, 4, 5, 3,
		 11, 8, 8, 8, 8, 12,
		 7, 8, 8, 8, 8, 19,
		 14, 8, 8, 8, 8, 12,
		 18, 8, 8, 8, 8, 19,
		 21, 25, 22, 23, 26, 24
	};
	rooms[4].setTileMap(map5, mapSize5);
	rooms[4].setPosition(sf::Vector2f(rooms[5].getPosition().x + ROOM_WIDTH, rooms[5].getPosition().y));//sets the position of the room to the right of room 6
	rooms[4].setCenter(sf::Vector2f(rooms[4].getPosition().x + ROOM_WIDTH / 2, rooms[4].getPosition().y + ROOM_HEIGHT / 2));
	rooms[4].buildLevel();

	
}

Tiles::~Tiles()
{
}

void Tiles::render(sf::RenderWindow* wind)
{
	for (int i = 0; i < rooms.size(); i++) {
		rooms[i].render(wind);//renders the room
	};
}


sf::Vector2f Tiles::getRoomCenter(int x)//function used in level to set the boudaries of the room
{
	return rooms[x - 1].getCenter();
}
