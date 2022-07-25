#include "Board.h"

//These functions use the player functions to access the players data and change it, for example decreasing the players score by what they aimed for
void Board::Single(int aim, Player* player)
{
	this->player = player;//sets it up so the player pointer carries over and stays pointed at the right player
	int x = rand() % 100 + 1;//creates a random number between 1-100 used to calculate where the dart hits
	int i = rand() % 21;//creates a random number between 0-21 used to choose what number is taken out of the ring function

	if (aim == 25) {
		if (x <= player->getSuccessrate()) {//determines if the player will hit their shot based on their successrate
			player->subtractScore(aim);
			cout << "You hit your target: " << aim << "\nYour score is now: " << player->getScore() << endl << endl;
			player->addHits(1);//adds one to successful hits used to calculate the player average
			player->addTotalTurns(1);
			player->setLastHit(aim);
			player->addLastHitTotal(aim);
		}
		else if (x <= 90) {
			player->subtractScore(50);
			cout << "You hit the bullseye: " << 50 << "\nYour score is now: " << player->getScore() << endl << endl;
			player->addTotalTurns(1);
			player->setLastHit(50);
			player->addLastHitTotal(50);
		}
		else {
			aim = rand() % 20;
		}

	}

	if (aim <= 20) {
		if (x <= player->getSuccessrate()) {
			player->subtractScore(aim);
			cout << "You hit your target: " << aim << "\nYour score is now: " << player->getScore() << endl << endl;
			player->addHits(1);
			player->addTotalTurns(1);
			player->setLastHit(aim);
			player->addLastHitTotal(aim);
		}
		else if (x < 92) {
			player->subtractScore(ring[0][aim - 1]);
			player->addTotalTurns(1);
			cout << "You hit to the left of the target: " << ring[0][aim - 1] << "\nYour score is now: " << player->getScore() << endl << endl;
			player->setLastHit(ring[0][aim - 1]);
			player->addLastHitTotal(ring[0][aim - 1]);
		}
		else if (x < 96) {
			player->subtractScore(ring[1][aim - 1]);
			player->addTotalTurns(1);
			cout << "You hit to the right of the target: " << ring[1][aim - 1] << "\nYour score is now: " << player->getScore() << endl << endl;
			player->setLastHit(ring[1][aim - 1]);
			player->addLastHitTotal(ring[1][aim - 1]);
		}
		else if (x < 98) {
			player->subtractScore(3 * aim);
			player->addTotalTurns(1);
			cout << "You hit a triple: " << 3 * aim << "\nYour score is now: " << player->getScore() << endl << endl;
			player->setLastHit(3 * aim);
			player->addLastHitTotal(3 * aim);
		}
		else
		{
			player->subtractScore(2 * aim);
			player->addTotalTurns(1);
			cout << "You hit a double: " << 2 * aim << "\nYour score is now: " << player->getScore() << endl << endl;
			player->setLastHit(2 * aim);
			player->addLastHitTotal(2 * aim);
		}
	}
}

void Board::Double(int aim, Player* player)
{
	this->player = player;
	int x = rand() % 100 + 1;
	int i = rand() % 21;

	if (x < player->getSuccessrate()) {
		player->subtractScore(2 * aim);
		cout << "You hit your target: " << 2 * aim << "\nYour score is now: " << player->getScore() << endl << endl;
		player->addHits(1);
		player->addTotalTurns(1);
		player->setLastHit(2 * aim);
		player->addLastHitTotal(2 * aim);
	}
	else if (x < 85) {
		cout << "You missed the board :( \nYour score is " << player->getScore() << endl << endl;
		player->addTotalTurns(1);
		player->setLastHit(0);
	}
	else if (x < 90) {
		player->subtractScore(aim);
		cout << "You hit below your target: " << aim << "\nYour score is now: " << player->getScore() << endl << endl;
		player->addTotalTurns(1);
		player->setLastHit(aim);
		player->addLastHitTotal(aim);
	}
	else if (x < 93) {
		player->subtractScore(2 * ring[0][aim - 1]);
		player->addTotalTurns(1);
		cout << "You hit to the left of the target: " << 2 * ring[0][aim - 1] << "\nYour score is now: " << player->getScore() << endl << endl;
		player->setLastHit(2 * ring[0][aim - 1]);
		player->addLastHitTotal(2 * ring[0][aim - 1]);
	}
	else if (x < 96) {
		player->subtractScore(2 * ring[1][aim - 1]);
		player->addTotalTurns(1);
		cout << "You hit to the right of the target: " << 2 * ring[1][aim - 1] << "\nYour score is now: " << player->getScore() << endl << endl;
		player->setLastHit(2 * ring[1][aim - 1]);
		player->addLastHitTotal(2 * ring[1][aim - 1]);
	}
	else if (x < 98) {
		player->subtractScore(ring[0][aim - 1]);
		player->addTotalTurns(1);
		cout << "You hit to the left of the target: " << ring[0][aim - 1] << "\nYour score is now: " << player->getScore() << endl << endl;
		player->setLastHit(ring[0][aim - 1]);
		player->addLastHitTotal(ring[0][aim - 1]);
	}
	else {
		player->subtractScore(ring[1][aim - 1]);
		player->addTotalTurns(1);
		cout << "You hit to the right of the target: " << ring[1][aim - 1] << "\nYour score is now: " << player->getScore() << endl << endl;
		player->setLastHit(ring[1][aim - 1]);
		player->addLastHitTotal(ring[1][aim - 1]);
	}
}

void Board::Treble(int aim, Player* player)
{
	this->player = player;
	int x = rand() % 100 + 1;
	int i = rand() % 21;
	
	if (x < player->getSuccessrate()) {
		player->subtractScore(3 * aim);
		cout << "You hit your target: " << 3 * aim << "\nYour score is now: " << player->getScore() << endl << endl;
		player->addHits(1);
		player->addTotalTurns(1);
		player->setLastHit(3 * aim);
		player->addLastHitTotal(3 * aim);
	}
	else if (x < 85) {
		cout << "You missed the board :( \nYour score is " << player->getScore() << endl << endl;
		player->addTotalTurns(1);
		player->setLastHit(0);
	}
	else if (x < 90) {
		player->subtractScore(aim);
		cout << "You hit below your target: " << aim << "\nYour score is now: " << player->getScore() << endl << endl;
		player->addTotalTurns(1);
		player->setLastHit(aim);
		player->addLastHitTotal(aim);
	}
	else if (x < 93) {
		player->subtractScore(3 * ring[0][aim - 1]);
		player->addTotalTurns(1);
		cout << "You hit to the left of the target: " << 3 * ring[0][aim - 1] << "\nYour score is now: " << player->getScore() << endl << endl;
		player->setLastHit(3 * ring[0][aim - 1]);
		player->addLastHitTotal(3 * ring[1][aim - 1]);
	}
	else if (x < 96) {
		player->subtractScore(3 * ring[1][aim - 1]);
		player->addTotalTurns(1);
		cout << "You hit to the right of the target: " << 3 * ring[1][aim - 1] << "\nYour score is now: " << player->getScore() << endl << endl;
		player->setLastHit(3 * ring[1][aim - 1]);
		player->addLastHitTotal(3 * ring[1][aim - 1]);
	}
	else if (x < 98) {
		player->subtractScore(ring[0][aim - 1]);
		player->addTotalTurns(1);
		cout << "You hit to the left of the target: " << ring[0][aim - 1] << "\nYour score is now: " << player->getScore() << endl << endl;
		player->setLastHit(ring[0][aim - 1]);
		player->addLastHitTotal(ring[0][aim - 1]);
	}
	else {
		player->subtractScore(ring[1][aim - 1]);
		player->addTotalTurns(1);
		cout << "You hit to the right of the target: " << ring[1][aim - 1] << "\nYour score is now: " << player->getScore() << endl << endl;
		player->setLastHit(ring[1][aim - 1]);
		player->addLastHitTotal(ring[1][aim - 1]);
	}
}

void Board::Bullseye(Player* player)
{
	this->player = player;
	int x = rand() % 100 + 1;
	int i = rand() % 21;

	if (x <= player->getSuccessrate()) {
		player->subtractScore(50);
		cout << "Bullseye" << endl;
		cout << "You got 50 points! \nYour score is now: " << player->getScore() << endl << endl;
		player->addHits(1); 
		player->addTotalBullseyes(1);  
		player->addTotalTurns(1);
		player->setLastHit(50);
		player->addLastHitTotal(50);

	}
	else if (board[i] > 0) {
		player->subtractScore(board[i]);
		cout << "You missed the bullsey :( \nHowever you got " << board[i] << " points! \nYour score is now: " << player->getScore() << endl << endl;
		player->addTotalTurns(1);
		player->setLastHit(board[i]);
		player->addLastHitTotal(board[i]);

	}
	else if (board[i] == 0) {
		cout << "You missed the board :( \nYour score is " << player->getScore() << endl << endl;
		player->addTotalTurns(1);
		player->setLastHit(0);
	}
}
