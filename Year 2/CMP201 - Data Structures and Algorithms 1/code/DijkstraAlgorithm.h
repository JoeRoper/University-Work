#pragma once
#include <chrono>
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>

// Import things we need from the standard library
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::cout;
using std::endl;
using std::this_thread::sleep_for;
using namespace std;
typedef std::chrono::steady_clock the_clock;
typedef std::vector<std::vector<int>> vector2D;//creates a 2d array definition

class DijkstraAlgorithm
{
public:
	int minDistance();
	void displayData();
	void dijkstra(int vertexSource);
	void runDijkstra(int repeat);
	void setMap(vector2D map);
	void setSize(int x) { size = x; };

private:

	int size;
	int initialValue;
	vector2D map;


	std::vector<bool> pathSetArray;
	std::vector<int> distanceArray;

	std::vector<float>  times;
	float timeSum;

	
};

