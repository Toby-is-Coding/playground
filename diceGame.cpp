#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <ios>
#include <limits>
#define LOSE 0
#define WIN 1
#define TIE 2
#define ERRORCODE 3
#define PLAYERFOR for
#define COMPFOR for

using namespace std;

int randomRolling();
int addUpPlayerScore(int randPlayer, int sumPlayer);
int addUpCompScore(int randComp, int sumComp);
int playerWinQM(int sumPlayer, int sumComp);
void displayResultPlayer(int randPlayer);
void displayResultComp(int randComp);
void displayResult(int x);

void introScreen()
{
	cout << "                       _..._                           ___\n";
	cout << "_______              .-'_..._''.                     .'/   \\\n";
	cout << "\\  ___ `'.   .--.  .' .'      '.\\     __.....__     / /     \\\n";
	cout << " ' |--.\\  \\  |__| / .'            .-''         '.   | |     |\n";
	cout << " | |    \\  ' .--.. '             /     .-''\"'-.  `. | |     |\n";
	cout << " | |     |  '|  || |            /     /________\\   \\|/`.   .'\n";
	cout << " | |     |  ||  || |            |                  | `.|   |  \n";
	cout << " | |     ' .'|  |. '            \\    .-------------'  ||___|  \n";
	cout << " | |___.' /' |  | \\ '.          .\\    '-.____...---.  |/___/  \n";
	cout << "/_______.'/  |__|  '. `._____.-'/ `.             .'   .'.--.  \n";
	cout << "\\_______|/           `-.______ /    `''-...... -'    | |    | \n";
	cout << "                          `                         \\_\\    / \n";
	cout << "                                                      `''--'\n";
	cout << "  ____\n";
	cout << " /\\' .\\    _____\n";
	cout << "/: \\___\\  / .  /\\\n";
	cout << "\\' / . / /____/..\\\n";
	cout << " \\/___/  \\'  '\\  /\n";
	cout << "          \\'__'\\/\n";
	return;
}

int main()
{
	srand(time(NULL)); //gets the time at the time of use to configure rand function

	introScreen(); //Calls the introScreen func
	cout << "How many rolls do we get? In between 1 and 6." << endl;
	int amountOfRolls;
	cin >> amountOfRolls; //Gets amount of rolls player specified
	bool understand = false;
	while (understand == false) {
		if (amountOfRolls > 6 || amountOfRolls < 1) {
			cout << "An integer in between 1-6 only please." << endl;
			cin >> amountOfRolls;
		}
		else {
			understand = true;
		}
	}
	bool stopQM;
	string playAgain;
	int randPlayer;
	int randComp;
	int sumPlayer = 0;
	int sumComp = 0;
	string beginQM;
	cout << "Shall we begin?" << endl;
	cin >> beginQM;
	if (toupper(beginQM[0]) == 'Y') {
		stopQM = false;
	}
	else {
		stopQM = true;
		cout << "Fine I didn't wanna play anyways :c";
	}

	while (stopQM == false) { //GAME LOOP
		sumPlayer = 0; //resets sumPlayer at beginning of round
		sumComp = 0; //resets sumComp at beginning of round
		PLAYERFOR(int i = 0; i < amountOfRolls; i++) {
			randPlayer = randomRolling(); //Getting random num for player
			displayResultPlayer(randPlayer);
			sumPlayer = addUpPlayerScore(randPlayer, sumPlayer);
		}
		COMPFOR(int j = 0; j < amountOfRolls; j++) {
			randComp = randomRolling(); //Getting random num for comp
			displayResultComp(randComp);
			sumComp = addUpCompScore(randComp, sumComp);
		}
		switch (playerWinQM(sumPlayer, sumComp)) { //Announcing winner
		case LOSE:
			cout << sumPlayer << " < " << sumComp << endl;
			cout << "You lose! Play again?" << endl;
			break;
		case WIN:
			cout << sumPlayer << " > " << sumComp << endl;
			cout << "You win! Play again?" << endl;
			break;
		case TIE:
			cout << sumPlayer << " = " << sumComp << endl;
			cout << "It's a tie! Play again?" << endl;
			break;
		default:
			cout << "Error: Something went wrong getting the result." << endl;
			stopQM = true;
			break;
		}
		cin >> playAgain; //Getting player's response
		if (toupper(playAgain[0]) == 'N') {
			stopQM = true;
		}
		if (stopQM == false) {
			system("cls"); //Clear screen
			introScreen(); //Calls the introScreen func
		}
	}
	return 0;
}

int randomRolling()
{
	int randNum = rand() % 6 + 1; //devides random number by 6 and gets the remainder as outcome (+1)
	return randNum;
}

int addUpPlayerScore(int randPlayer, int sumPlayer)
{
	sumPlayer = sumPlayer + randPlayer; //Adds up score of all player rolls
	return sumPlayer;
}

int addUpCompScore(int randComp, int sumComp)
{
	sumComp = sumComp + randComp; //Adds up score of all comp rolls
	return sumComp;
}

int playerWinQM(int sumPlayer, int sumComp)
{
	if (sumPlayer < sumComp) { //if comp wins, return 0
		return LOSE;
	}
	else if (sumPlayer > sumComp) { //if player wins, return 1
		return WIN;
	}
	else if (sumPlayer == sumComp) { //if tied, return 2
		return TIE;
	}
	return ERRORCODE; //this return is not supposed to trigger
}

void displayResultPlayer(int randPlayer)
{
	//Displaying what you rolled
	cout << "You:" << endl;
	displayResult(randPlayer);
	return;
}

void displayResultComp(int randComp)
{
	//Displaying what comp rolled
	cout << "Computer:" << endl;
	displayResult(randComp);
	return;
}

void displayResult(int x)
{
	switch (x) {
	case 1:
		cout << "-----" << endl;
		cout << "|   |" << endl;
		cout << "| o |" << endl;
		cout << "|   |" << endl;
		cout << "-----" << endl;
		cout << "Rolled a " << "\x1B[32m" << "1" << "\x1B[0m" << endl;
		break;
	case 2:
		cout << "-----" << endl;
		cout << "|o  |" << endl;
		cout << "|   |" << endl;
		cout << "|  o|" << endl;
		cout << "-----" << endl;
		cout << "Rolled a " << "\x1B[32m" << "2" << "\x1B[0m" << endl;
		break;
	case 3:
		cout << "-----" << endl;
		cout << "|o  |" << endl;
		cout << "| o |" << endl;
		cout << "|  o|" << endl;
		cout << "-----" << endl;
		cout << "Rolled a " << "\x1B[32m" << "3" << "\x1B[0m" << endl;
		break;
	case 4:
		cout << "-----" << endl;
		cout << "|o o|" << endl;
		cout << "|   |" << endl;
		cout << "|o o|" << endl;
		cout << "-----" << endl;
		cout << "Rolled a " << "\x1B[32m" << "4" << "\x1B[0m" << endl;
		break;
	case 5:
		cout << "-----" << endl;
		cout << "|o o|" << endl;
		cout << "| o |" << endl;
		cout << "|o o|" << endl;
		cout << "-----" << endl;
		cout << "Rolled a " << "\x1B[32m" << "5" << "\x1B[0m" << endl;
		break;
	case 6:
		cout << "-----" << endl;
		cout << "|o o|" << endl;
		cout << "|o o|" << endl;
		cout << "|o o|" << endl;
		cout << "-----" << endl;
		cout << "Rolled a " << "\x1B[32m" << "6" << "\x1B[0m" << endl;
		break;
	}
	return;
}
