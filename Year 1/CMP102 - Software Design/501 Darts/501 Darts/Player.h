#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip> //For displaying the average
using namespace std;
class Player
{
public:
	//A bunch of function to access and manipulate the private data
	string getName() { return name; }
	void setName(string name) { this->name = name; }

	int getSuccessrate() { return successrate; }
	void setSuccessrate(int  x) { successrate = x; }

	double getPlayerAverage() { return playerAverage; }
	void setPlayerAverage(int  x) { playerAverage = x; }

	int getScore() { return score; }
	void setScore(int  x) { score = x; }
	void addScore(int x) { score += x; }
	void subtractScore(int x) { score -= x; }

	int getSets() { return sets; }
	void setSets(int  x) { sets = x; }
	void addSets(int x) { sets += x; }

	int getGames() { return games; }
	void setGames(int  x) { games = x; }
	void addGames(int x) { games += x; }

	int getHits() { return hits; }
	void setHits(int  x) { hits = x; }
	void addHits(int x) { hits += x; }

	int getTotalBullseyes() { return totalBullseyes; }
	void setTotalBullseyes(int  x) { totalBullseyes = x; }
	void addTotalBullseyes(int x) { totalBullseyes += x; }

	int getTotalTurns() { return totalTurns; }
	void setTotalTurns(int  x) { totalTurns = x; }
	void addTotalTurns(int x) { totalTurns += x; }

	void average();//Works out the player average based on the game results

	void aim();//Function to decide what the player trows for based on their score
	int getAimCase() { return aimCase; }

	//LastHit Functions
	//used to find out if the player has made an illegal move and has to have their score reset
	void lastHitCheck();

	int getLastHitTotal() { return lastHitTotal; }
	void setLastHitTotal(int  x) { lastHitTotal = x; }
	void addLastHitTotal(int x) { lastHitTotal += x; }

	int getLastHit() { return lastHit; }
	void setLastHit(int  x) { lastHit = x; }

	bool getLastHitBool() { return lastHitBool; }

	//Functions for Frequency chart
	int getWinsArray(int x) { return winsArray[x]; };
	void addWinsArray(int x) { winsArray[x]++; }

	int getTotalFinals() { return totalFinals; }
	void addTotalFinals(int x) { totalFinals += x; }


private:
	string name;
	int successrate = 0; 
	double playerAverage = 0;
	int score = 501;
	int sets = 0;
	int games = 0;
	int lastHit;
	int lastHitTotal;
	bool lastHitBool;
	int hits;
	int totalBullseyes;
	int totalTurns;
	int aimCase;

	int winsArray[7] = { 0, 0, 0, 0, 0, 0, 0 }; // 70, 71, 72, 73, 74, 75, 76
	int totalFinals;
};

