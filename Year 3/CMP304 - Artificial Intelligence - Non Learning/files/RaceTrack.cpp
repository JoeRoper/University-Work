#include "RaceTrack.h"

RaceTrack::RaceTrack(sf::RenderWindow* window)
{
	this->window = window; //sets the render window to be the same as used in main

	//Sets up the class pointers
	roadLine = new RoadLine(window, sf::Vector2f(5.0f, window->getSize().y), sf::Vector2f(window->getSize().x / 2.0f, 0.0f));
	carFSM = new CarFSM(window);
	carFuzzy = new CarFuzzy(window);

	fout.open("systemsTimingsFile.csv");
	//fout.open("systemsTimingsFile.txt");
}

RaceTrack::~RaceTrack()
{
	fout.close();//when the application is closed it stops writing to the excel file
}

void RaceTrack::update(float dt)
{
	//updates the racing line and provides the new information the the two systems
	roadLine->Update(dt);
	carFSM->GetLinePosition(roadLine->GetPosition());
	carFuzzy->GetLinePosition(roadLine->GetPosition());

	//Times the two systems update functions
	timingsClock::time_point startTimingFSM = timingsClock::now();
	carFSM->Update(dt);
	timingsClock::time_point endTimingFSM = timingsClock::now();

	timingsClock::time_point startTimingFLSM = timingsClock::now();
	carFuzzy->Update(dt);
	timingsClock::time_point endTimingFLSM = timingsClock::now();
	
	//Calculates the update time for both systems
	auto timeFSM = duration_cast<nanoseconds>(endTimingFSM - startTimingFSM).count();
	auto timeFuzzy = duration_cast<nanoseconds>(endTimingFLSM - startTimingFLSM).count();

	//Commented out for testing as I already got the timings
	//fout << "Iteration: " << "," << iteration << "," << "Finite Time (ns): " << "," << timeFSM << "," << "," << "Iteration: " << "," << iteration << "," << "Fuzzy Time (ns): " << "," << timeFuzzy << std::endl;
	
	iteration++;
	


}

void RaceTrack::render(float dt)
{
	beginDraw();

	//Renders the different game objects to the screen
	roadLine->Render();
	carFSM->Render();
	carFuzzy->Render();

	endDraw();
}

void RaceTrack::beginDraw()
{
	window->clear(sf::Color(18, 33, 43)); 
}

void RaceTrack::endDraw()
{
	window->display();
}