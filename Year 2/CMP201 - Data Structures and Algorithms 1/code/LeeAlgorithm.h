#pragma once
#include <iostream>
#include <queue>
#include <climits>
#include <cstring>
#include <chrono>
#include <thread>

// Import things we need from the standard library
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::cout;
using std::endl;
using std::this_thread::sleep_for;
using namespace std;
typedef std::chrono::steady_clock the_clock;
typedef std::vector<std::vector<int>> vector2D;//creates a 2d array definition


class LeeAlgorithm
{
public:
	bool isOpen(int row, int column);
	void displayData(int min);
	void leeAlgorithm(int startX, int startY, int endX, int endY);
	void runLee(int repeat, int targetX, int targetY);
	void setMap(vector2D map);
	void setSize(int x) { size = x; };
	

private:

	//Creating a vertex structure which will hold the x and y coordinates aswell as the shortest distance from source
	struct Vertex
	{
		int x, y, distance;
	};

	//These arrays will be used to move the vertex between cells
	int size;
	int row[4] = { -1, 0, 0, 1 };
	int column[4] = { 0, -1, 1, 0 };

	vector2D map;
	std::vector<std::vector<bool>> visited2D;

	std::vector<float>  times;
	float timeSum;

	
};

