#pragma once
#include <SFML/Graphics.hpp>

#include "RoadLine.h"
#include "CarFSM.h"
#include "CarFuzzy.h"

//used for system timings
#include <chrono>
#include <fstream>//used to save system timings into a file

using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::ofstream;
typedef std::chrono::steady_clock timingsClock;

class RaceTrack
{
public:
	RaceTrack(sf::RenderWindow* hwnd);
	~RaceTrack();

	void update(float dt);
	void render(float dt);

private:
	sf::RenderWindow* window;

	RoadLine* roadLine;
	CarFSM* carFSM;
	CarFuzzy* carFuzzy;
	
	ofstream fout;//used for savings timings into an excel file
	int iteration = 0;//used for knowing how many times the program has run the update functions

	void beginDraw();
	void endDraw();
};