#include "Player.h"

void Player::average()
{
	playerAverage = (((double)hits) / totalTurns) * 100; //works out the new player average
	cout << "Player Average: " << setprecision(3) << playerAverage << "%" << endl;
	cout << "Bullseyes hit: " << totalBullseyes << endl;
}

void Player::aim()
{

	//Determines where the player should throw based on their score
	if (score > 60)
	{
	aimCase = 1;
	}
	else if (score % 2 == 0 && score <= 60 && score >= 51)
	{
		aimCase = 2;
	}
	else if (score % 2 == 1 && score <= 60 && score >= 51)
	{
		aimCase = 1;
	}
	else if (score == 50)
	{
		aimCase = 3;
	}
	else if (score % 2 == 0 && score <= 49 && score >= 41)
	{
		aimCase = 4;
	}
	else if (score % 2 == 1 && score <= 49 && score >= 41)
	{
		aimCase = 5;
	}
	else if (score % 2 == 0 && score <= 40 && score >= 20)
	{
		aimCase = 6;
	}
	else if (score % 2 == 0 && score <= 20)
	{
		aimCase = 6;
	}
	else if (score % 2 == 1 )
	{
		aimCase = 7;
	}
}

void Player::lastHitCheck()
{

	int x = getLastHit();
	if ((x % 2 == 0 && x <= 40) || x == 50)//checks to see if the players last hit matched the numbers listed in the rules
	{
		lastHitBool = true;
	}
	else
	{
		addScore(lastHitTotal); //adds the points earned from the match back to the players score as they made an illegal throw
		cout << "Your score has been reset too: " << score << endl;
		lastHitBool = false;
	}

	setLastHit(0);//resets the variables for the next game
	setLastHitTotal(0);

}
