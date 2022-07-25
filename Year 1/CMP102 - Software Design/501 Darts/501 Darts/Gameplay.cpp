#include "Gameplay.h"
void Gameplay::starter()
{

	int joeSuccessrate = 50;//sets joes and sids successrate to be the same so its a 50 50 chance for who goes first
	int sidSuccessrate = 50;
	int joe = 0;// these two ints will be used to record how many points the player got and determine who goes first
	int sid = 0;
	bool run = true;

	while (run) { 
		int x = rand() % 100 + 1; //this will be used to see if joe hits the bullseye
		int y = rand() % 100 + 1;//this will be used to see if sid ihts the bullseye
		int i = rand() % 21;//this will be used to determine wht joe hits if he misses the bullseye
		int j = rand() % 21;//this will be used to determine what is hit is sid misses the bullseye
		//Joes shot
		if (x <= joeSuccessrate) {//is true 50% of the time
			joe += 50;
			cout << "Joe hit the bullseye " << endl;
		}
		else if (board.getBoard(i) > 0) {//retrieves a number from the board array could be 1-20 or 25
			joe += board.getBoard(i);
			cout << "Joe missed the bullsey :( \nHowever Joe got " << board.getBoard(i) << " points!" << endl;
		}
		else if (board.getBoard(i) == 0) {
			cout << "Joe missed the board" << endl;
		}

		//Sids shot
		if (y <= sidSuccessrate) {
			sid += 50;
			cout << "Sid hit the bullseye " << endl;
		}
		else if (board.getBoard(j) > 0) {
			sid += board.getBoard(j);
			cout << "Sid missed the bullsey :( \nHowever Sid got " << board.getBoard(j) << " points!" << endl;
		}
		else if (board.getBoard(j) == 0) {
			cout << "Sid missed the board" << endl;
		}

		if (joe > sid) { //determines whos got more points
			//joe goes first
			cout << "Joe will go first" << endl;
			starterName = "Joe";//sets the starter name so joe will go first
			run = false;
		}
		if (sid > joe) {
			//sid goes first
			cout << "Sid will go first" << endl;
			starterName = "Sid";
			run = false;
		}
		if (joe == sid) { //if they tie the function will loop
			cout << " Joe and Sid tied they will have to throw again" << endl;
		}
	}
}

void Gameplay::final()
{
	int x;
	cout << "How many championships would you like to play?" << endl;
	cin >> x;


	for (int i = 0; i < x; i++)
	{
		while ((joe.getSets() < 7) && (sid.getSets() < 7))//stops when one of the players wins the game
		{
			set();
		}

		if (joe.getSets() == 7)//checks who won and sets up the winner and loser pointers
		{
			winner = &joe;
			loser = &sid;

		}
		else if (sid.getSets() == 7)
		{
			winner = &sid;
			loser = &joe;
		}

		cout << "The winner of the game was " << winner->getName() << endl;

		object.addTotalFinals(1);
		frequencyTable();

		joe.setSets(0);//resets the sets
		sid.setSets(0);
	}
}

void Gameplay::set()
{

	while ((joe.getGames() < 3) && (sid.getGames() < 3))//stops when one of the players wins the set
	{
		game();
	}

	if (joe.getGames() == 3)//checks who won and sets up the winner and loser pointers
	{
		winner = &joe;
		loser = &sid;
		joe.addSets(1);
	}
	else if (sid.getGames() == 3)
	{
		winner = &sid;
		loser = &joe;
		sid.addSets(1);
	}

	cout << "The winner of the set was " << winner->getName() << endl;
	
	joe.setGames(0);//resets the games variable
	sid.setGames(0);

}

void Gameplay::game()
{
	while (true) //loops until the player pointer points at joe or sid
	{
		starter();//function that decides who goes first
		if (getStarterName() == joe.getName())
		{
			player = &joe;//gets the player pointer to point at joe
			break;
		}
		else if (getStarterName() == sid.getName())
		{
			player = &sid;
			break;
		}
	}


	bool run = true;
	while (run)
	{
		for (int i = 0; i < 3; i++)//loops 3 player throws 3 times in a row
		{
			cout << player->getName() << "'s Turn" << endl;
			cout << player->getName() << " score: " << player->getScore() << endl;

			player->setLastHit(0);
			player->addTotalTurns(1);
			player->aim();//functions that sets up the players aim and has them shoot
			aimCase(player);
		}
		if (player->getScore() <= 0)
		{
			player->lastHitCheck();// checks if the player didn't break the rules
			if (player->getLastHitBool() == true)
			{
				cout << player->getName() << " Wins!!!" << endl;
				player->average();//works out player average
				player->addGames(1);
				joe.setScore(501);//resets players score at the end of the final
				sid.setScore(501);
				run = false;
			}
		}
		player->setLastHitTotal(0);
		//Changes the player
		if (player == &joe)
		{
			player = &sid;
		}
		else
		{
			player = &joe;
		}
	}
}

void Gameplay::startup()
{

	sid.setName("Sid");
	joe.setName("Joe");
	int x, y;
	
	//Dart program intro
	cout << "Welcome to the darts game of the century between Joe and Sid!" << endl;
	cout << "Choose Joe's success rate for a bullseye between 1-100" << endl;
	cin >> x;
	joe.setSuccessrate(x);
	cout << "Choose Sid's success rate for a bullseye between 1-100" << endl;
	cin >> y;
	sid.setSuccessrate(y);
}

void Gameplay::frequencyTable()
{
	for (int i = 0; i < 7; i++)//Checks what the score was at the end of the game and adds one to the correct row in the array
	{
		if (joe.getSets() == 7 && sid.getSets() == i)
		{
			joe.addWinsArray(i);

		}
		if (sid.getSets() == 7 && joe.getSets() == i)
		{
			sid.addWinsArray(i);

		}
	}
	//calculates the percentages of games one and displays it on the console screen
	cout << "Joes Frequency Table:" << endl;
	cout << "	Joe		:	 Sid	:	Frequency" << endl;
	cout << "	7		:	  6		:    " << (((double)joe.getWinsArray(6)) / object.getTotalFinals()) * 100 << "%" << endl;
	cout << "	7		:	  5		:    " << (((double)joe.getWinsArray(5)) / object.getTotalFinals()) * 100 << "%" << endl;
	cout << "	7		:	  4		:    " << (((double)joe.getWinsArray(4)) / object.getTotalFinals()) * 100 << "%" << endl;
	cout << "	7		:	  3		:    " << (((double)joe.getWinsArray(3)) / object.getTotalFinals()) * 100 << "%" << endl;
	cout << "	7		:	  2		:    " << (((double)joe.getWinsArray(2)) / object.getTotalFinals()) * 100 << "%" << endl;
	cout << "	7		:	  1		:    " << (((double)joe.getWinsArray(1)) / object.getTotalFinals()) * 100 << "%" << endl;
	cout << "	7		:	  0		:    " << (((double)joe.getWinsArray(0)) / object.getTotalFinals()) * 100 << "%" << endl << endl <<endl;

	cout << "Sids Frequency Table:" << endl;
	cout << "	Sid		:	 Joe	:	Frequency" << endl;
	cout << "	7		:	  6		:    " << (((double)sid.getWinsArray(6)) / object.getTotalFinals()) * 100 << "%" << endl;
	cout << "	7		:	  5		:    " << (((double)sid.getWinsArray(5)) / object.getTotalFinals()) * 100 << "%" << endl;
	cout << "	7		:	  4		:    " << (((double)sid.getWinsArray(4)) / object.getTotalFinals()) * 100 << "%" << endl;
	cout << "	7		:	  3		:    " << (((double)sid.getWinsArray(3)) / object.getTotalFinals()) * 100 << "%" << endl;
	cout << "	7		:	  2		:    " << (((double)sid.getWinsArray(2)) / object.getTotalFinals()) * 100 << "%" << endl;
	cout << "	7		:	  1		:    " << (((double)sid.getWinsArray(1)) / object.getTotalFinals()) * 100 << "%" << endl;
	cout << "	7		:	  0		:    " << (((double)sid.getWinsArray(0)) / object.getTotalFinals()) * 100 << "%" << endl << endl << endl;
}

void Gameplay::aimCase(Player* player)
{
	this->player = player;
	//This function was created to access the board functions for the player as the player couldn't inherit the board class due to circular inheritance
	switch (player->getAimCase()) 
{
	case 1:
		board.Treble(20, player);
		break;
	case 2:
		board.Double(20, player);
		break;
	case 3:
		board.Bullseye(player);
		break;
	case 4:
		board.Double(10, player);
		break;
	case 5:
		board.Treble(7, player);
		break;
	case 6:
		board.Double((player->getScore() / 2), player);
		break;
	case 7:
		board.Single(1, player);
		break;
	}
}


