#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip> //For displaying the average
using namespace std;

//Class Includes
#include "Player.h"


class Board
{
public:
	void Single(int aim, Player* player);//used when the player wants to throw for a single
	void Double(int aim, Player* player);//used for when a players wants to aim for a doube
	void Treble(int aim, Player* player);//used for when the player wants to aim for a treble
	void Bullseye(Player* player);//used for when the player wants to aim for the bullseye
	int getBoard(int x) { return board[x]; };//used for when the other classes need access to the board such as the gameplay class for its starter function


private:
	int board[22] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 25 };//used for the single and bullseye functions
	//3 rows 2 collums
	int ring[2][20] = { {20, 15, 17, 18, 12, 13, 19, 16, 14, 6, 8, 9, 4, 11, 10, 7, 2, 1, 3, 5 }, { 18, 17, 19, 13, 20, 10, 16, 11, 12, 15, 14, 5, 6, 9, 2, 8, 3, 4, 7, 1 } };
	//int ring is a 2D array that stores the values of the dartboard of the left and right values in accordance to the numbers 1-20 this is used for when the player hits to the left or right of their target
	Player* player; //creates a player pointer that will be passed through parameters so that it always points at the right player


	

};

