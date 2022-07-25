#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip> //For displaying the average
using namespace std;

//Class Includes
#include "Player.h"
#include "Board.h"

class Gameplay 
{
public:
	void starter();//Has the players throw for the bull to decide who goes first
	string getStarterName() { return starterName; }
	void final();//the main function for the dart championship loops set function
	void set();//set function plays one set of darts by looping the game function
	void game();//simulates 1 dart game
	void startup();//sets the player success rate and names
	void frequencyTable();//creates a frequenxy table to be printed out at the end of the game
	void aimCase(Player* player);//uses the dart throw functions based on the aim calculated in player cpp


private:
	string starterName;
	//Creating player objects
	Player joe;//used to access the player functions
	Player sid;
	Player object;

	Player *player;// used to point at joe or sid based on whos turn it is
	Player* winner;//used to point at the winner of the game
	Player* loser;//used to point at the loser of the game

	Board board;//used to access the board functions


};

