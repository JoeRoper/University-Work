#include <SFML/Graphics.hpp>
#include "RaceTrack.h"//Include the game simulation file

int main()
{
	//Used to calculate delta time for the game simulation
	sf::Clock clock;
	float dt;

	sf::RenderWindow window(sf::VideoMode(800, 600), "FSM vs FLSM");

	RaceTrack raceTrack(&window);//Initialise the racetrack class and build the constructor

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		dt = clock.restart().asSeconds();//Calcualte game time for the car functions so that the movement doesnt look choppy

		//Update and render the racetrack class which holds the game simmulation
		raceTrack.update(dt);
		raceTrack.render(dt);
	}
	return 0;
}