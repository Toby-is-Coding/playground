#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <ios>
#include <limits>
#include <vector>
#include <thread>
#include <chrono>
#define LOSE 0
#define WIN 1
#define TIE 2
#define ERRORCODE 3
#define PLAYERFOR for
#define COMPFOR for
#define CYN "\x1B[36m"
#define YLW "\x1B[33m"
#define GRN "\x1B[32m"
#define RED "\x1B[31m"
#define MAG "\x1B[35m"
#define WHT "\x1B[37m"
#define NRM "\x1B[0m"

using namespace std;

int randomRolling();
int sumUpScores(bool isPlayer);
int playerWinQM(int sumPlayer, int sumComp);
int toCheatOrNotToCheat(int frustrationFactor, bool isCheating);
bool needToCheat(bool isCheating, int playerWins);
void displayResultWho(bool needToCheat);
void displayResult(int x);

vector<int> savedPlayerRolls;
vector<int> savedCompRolls;

void introScreen(int lowScore, bool notFirstTime, int innerGullibility)
{
	cout << WHT;
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
	cout << " \\/___/  \\'  '\\  /              ";
	innerGullibility < 30 && notFirstTime ? cout << MAG << "Lowest Gullibility: " << GRN << lowScore << WHT << endl : innerGullibility >= 30 ? cout << MAG << "Gullibility: " << RED << "INFINITE (you suck at this)" << NRM << endl : cout << endl;
	//if innerGullibility < 30 AND notFirstTime == true, do all this ^                                               if not, check if innerGullibility >= 30, if yes, do all this ^                                                  if not, skip
	cout << "          \\'__'\\/\n";
	cout << NRM;
	return;
}

int main()
{
	srand(time(NULL)); //gets the time at the time of use to configure rand function

	introScreen(0, false, 0); //Calls the introScreen func

	//EXPLANATION
	cout << GRN << "Welcome to " << RED << "diceGame!\n" << GRN << "The way this works is you'll be playing against " << CYN << "me! The Computer!"
		<< GRN << "\nThe rules are simple. You choose how many times we each get to roll the dice at the start."
		<< "\nThen in the following rounds, we roll! " << RED << "Whoever has the highest sum wins!\n"
		//TIP PART:
		<< MAG << "Tip: Watch out for the " << CYN << "Computer" << MAG << " He gets frustrated pretty easily.\n"
		<< "If you think he's cheating, don't be gullible. Call him out by saying \"cheater!\"" << NRM << endl;
	//EXPLANATION OVER

	cout << "How many rolls do we get? In between 1 and 6." << endl;
	int amountOfRolls;
	while ((!(cin >> amountOfRolls)) || (amountOfRolls < 1 || amountOfRolls > 6)) { //While cin is NOT int, OR int < 1, > 6, cout error message
		cout << "An integer between 1-6 only please." << endl;
		cin.clear(); //Clears previous cin
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Clears buffer before taking new line
	}
	bool stopQM;	
	string playAgain;
	int randPlayer;
	int randComp;
	int sumPlayer = 0;
	int sumComp = 0;
	int frustrationFactor = 0;
	bool isCheating = false; //CHANGE THIS TO FALSE
	bool cheatNextRound = false;
	int gullibility = 0;
	int innerGullibility = 0;
	int lowScore = 666;
	bool notFirstTime = false; //not first time Comp cheated
	string beginQM;
	cout << "Shall we begin?" << endl;
	cin >> beginQM;
	if (toupper(beginQM[0]) == 'Y') {
		stopQM = false;
	}
	else {
		stopQM = true;
		cout << "Fine, I didn't wanna play anyways :c";
	}

	while (stopQM == false) { //GAME LOOP
		sumPlayer = 0; //resets sumPlayer at beginning of round
		sumComp = 0; //resets sumComp at beginning of round
		savedPlayerRolls.clear(); //clears last game's playerRolls
		savedCompRolls.clear(); //clears last game's compRolls
		PLAYERFOR(int i = 0; i < amountOfRolls; i++) {
			randPlayer = randomRolling(); //Getting random num for player
			savedPlayerRolls.push_back(randPlayer); //Saving roll
			sumPlayer = sumUpScores(true);
		}
		COMPFOR(int j = 0; j < amountOfRolls; j++) {
			randComp = randomRolling(); //Getting random num for comp
			savedCompRolls.push_back(randComp); //Saving roll
			sumComp = sumUpScores(false);
		}
		displayResultWho(needToCheat(isCheating, playerWinQM(sumPlayer, sumComp)));

		//Announcing winner
		if (needToCheat(isCheating, playerWinQM(sumPlayer, sumComp)) == true) { //if needToCheat == true, then swap results
			cout << YLW << "Your" << NRM << " total: " << sumComp << endl << CYN << "My " << "(Computer)" << NRM << " total: " << sumPlayer << endl;
		}
		else { //if false, remain honest
			cout << YLW << "Your" << NRM << " total: " << sumPlayer << endl << CYN << "My " << "(Computer)" << NRM << " total: " << sumComp << endl;
		}
		switch (playerWinQM(sumPlayer, sumComp)) {
		case LOSE: //if player lost
			cout << RED << "You lose!" <<NRM <<" Play again?" << endl;
			isCheating ? frustrationFactor = 0 : frustrationFactor -= 2; //Reduce 2% from frustrationFactor if Comp won
			cheatNextRound = toCheatOrNotToCheat(frustrationFactor, isCheating); //to Cheat or Not to cheat? that is the question
			break;
		case WIN: //if player won
			if (needToCheat(isCheating, playerWinQM(sumPlayer, sumComp)) == true) {
				cout << RED << "You lose!" << NRM << " Play again?" << endl; //if needToCheat == true, Announce Player lost
			}
			else {
				cout << GRN << "You win!" << NRM << " Play again?" << endl; //if false, remain honest
			}
			isCheating ? frustrationFactor = 0 : frustrationFactor += 5; //Add 5% to frustrationFactor if Player won
			cheatNextRound = toCheatOrNotToCheat(frustrationFactor, isCheating); //to Cheat or Not to cheat? that is the question
			break;
		case TIE: //if tied
			cout << WHT << "It's a tie!" <<NRM <<" Play again?" << endl;
			isCheating ? frustrationFactor = 0 : frustrationFactor += 1; //Add 1% to frustrationFactor if tied
			cheatNextRound = toCheatOrNotToCheat(frustrationFactor, isCheating); //to Cheat or Not to cheat? that is the question
			break;
		default: //Error message; should not happen.
			cout << "Error: Something went wrong getting the result." << endl;
			stopQM = true;
			break;
		}
		bool skipGullibilityDisplay = false;
		bool alreadyAccused = false;
		bool continueQM = false;
		while (continueQM == false) {
			cin >> playAgain; //Getting player's response to if they want to play again
			switch (toupper(playAgain[0])) {
			case 'N': //if answer is no
				if (alreadyAccused == true) {
					cout << RED << "Oh man, sorry..." << NRM;
					this_thread::sleep_for(chrono::milliseconds(350));
				}
				stopQM = true; //Stops the game loop
				continueQM = true;
				break;
			case 'Y': //if answer is yes
				if (isCheating == true) {
					gullibility += 5;
					innerGullibility += 1;
				}
				continueQM = true;
				break;
			case 'C': //if Player accuses Comp of cheating
				if (isCheating == true) { //if Comp was cheating
					if (lowScore > gullibility && innerGullibility < 30) {
						if (gullibility > 100) { //if lowScore > gullibility AND gullibility < 100, new lowScore, w/max cap at 100
							lowScore = 100;
							gullibility = 100;
						}
						else {
							lowScore = gullibility;
						}
						cout << MAG << "Congratulations! You're less gullible this time." << " New lowest gullibility level: " << GRN << lowScore << NRM << endl;
						skipGullibilityDisplay = true;
					}
					else if (innerGullibility > 30) {
						cout << MAG << "Finally! You're really gullible, aren't ya?" << NRM << endl; //if it took Player over 30 rounds to guess that Comp is cheating, Player is very very bad
						skipGullibilityDisplay = true;
					}
					if (skipGullibilityDisplay == false) {
						cout << MAG << "Gullibility level: " << RED << gullibility << NRM << endl;
					}
					cout << GRN << "Aah! Alright, I'm sorry. Let's continue?" << NRM << endl;
					isCheating = false;
					alreadyAccused = true;
					notFirstTime = true;
					gullibility = 0;
					innerGullibility = 0;
					frustrationFactor = 0;
					break;
				}
				else if (alreadyAccused == true) { //if Player already accused Comp like 2 seconds ago
					cout << RED "You already called me out on it, I get it! I'll go!" << NRM;
					this_thread::sleep_for(chrono::milliseconds(500));
					stopQM = true; //Stops the game loop
					continueQM = true;
					break;
				}
				else { //if Comp wasn't cheating
					cout << RED "You don't trust me? I can't believe it. That is so rude... I quit!\n" << CYN << "Computer" << MAG << " wasn't cheating... You offended it." << NRM << endl;
					this_thread::sleep_for(chrono::seconds(1));
					stopQM = true; //Stops the game loop
					continueQM = true;
					break;
				}
			default: //default response
				cout << GRN << "I'll take that as a yes!" << NRM << endl;
				this_thread::sleep_for(chrono::milliseconds(350));
				if (isCheating == true) {
					gullibility += 10;
				}
				continueQM = true;
			}
		}
		if (cheatNextRound == true && alreadyAccused == false) {
			isCheating = true;
		}
		if (stopQM == false) {
			system("cls"); //Clear screen
			introScreen(lowScore, notFirstTime, innerGullibility); //Calls the introScreen func
		}
	}
	return 0;
}

int randomRolling()
{
	int randNum = rand() % 6 + 1; //devides random number by 6 and gets the remainder as outcome (+1)
	return randNum;
}

int sumUpScores(bool isPlayer) {
	int sum = 0;
	if (isPlayer == true) {
		for (int i = 0; i < savedPlayerRolls.size(); i++) {
			sum = savedPlayerRolls[i] + sum; //adds up the player rolls
		}
	}
	else {
		for (int j = 0; j < savedCompRolls.size(); j++) {
			sum = savedCompRolls[j] + sum; //adds up the comp rolls
		}
	}
	return sum;
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

int toCheatOrNotToCheat(int frustrationFactor, bool isCheating)
{
	if (isCheating == false) {
		int cheatChance = rand() % 100; //Gets a random num out of 100
		if (cheatChance < frustrationFactor) { //frustrationFactor acts as a percentage to if Comp will start cheating
			isCheating = true;
		}
		//cout << "cheatChance: " << cheatChance << endl; //DEBUGGING
		//cout << "frustrationFactor: " << frustrationFactor << endl; //DEBUGGING
	}
	return isCheating;
}

bool needToCheat(bool isCheating, int playerWins)
{
	return (isCheating && playerWins == WIN); //if isCheating == true && playerWinQM returned a '1', return true
}

void displayResultWho(bool needToCheat)
{
	PLAYERFOR(int i = 0; i < savedPlayerRolls.size(); i++) {
		if (needToCheat == false) {
			cout << YLW << "You:" << endl;
			displayResult(savedPlayerRolls[i]); //if Normal, Announce Player rolls as Player rolls
		}
		else {
			cout << YLW << "You:" << endl;
			displayResult(savedCompRolls[i]); //if Cheating w/reason, Announce Comp rolls as Player rolls
		}
	}
	COMPFOR(int j = 0; j < savedCompRolls.size(); j++) {
		if (needToCheat == false) {
			cout << CYN << "Comp:" << endl;
			displayResult(savedCompRolls[j]); //if Normal, Announce Comp rolls as Comp rolls
		}
		else {
			cout << CYN << "Comp:" << endl;
			displayResult(savedPlayerRolls[j]); //if Cheating w/reason, Announce Player rolls as Comp rolls
		}
	}
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
		cout << "Rolled a " << GRN << "1" << NRM << endl;
		break;
	case 2:
		cout << "-----" << endl;
		cout << "|o  |" << endl;
		cout << "|   |" << endl;
		cout << "|  o|" << endl;
		cout << "-----" << endl;
		cout << "Rolled a " << GRN << "2" << NRM << endl;
		break;
	case 3:
		cout << "-----" << endl;
		cout << "|o  |" << endl;
		cout << "| o |" << endl;
		cout << "|  o|" << endl;
		cout << "-----" << endl;
		cout << "Rolled a " << GRN << "3" << NRM << endl;
		break;
	case 4:
		cout << "-----" << endl;
		cout << "|o o|" << endl;
		cout << "|   |" << endl;
		cout << "|o o|" << endl;
		cout << "-----" << endl;
		cout << "Rolled a " << GRN << "4" << NRM << endl;
		break;
	case 5:
		cout << "-----" << endl;
		cout << "|o o|" << endl;
		cout << "| o |" << endl;
		cout << "|o o|" << endl;
		cout << "-----" << endl;
		cout << "Rolled a " << GRN << "5" << NRM << endl;
		break;
	case 6:
		cout << "-----" << endl;
		cout << "|o o|" << endl;
		cout << "|o o|" << endl;
		cout << "|o o|" << endl;
		cout << "-----" << endl;
		cout << "Rolled a " << GRN << "6" << NRM << endl;
		break;
	}
	return;
}
