#include <iostream>
#include <string>

using namespace std;

//Declaring a bunch of functions
void startGame();
void display();
void guessing();

//Declaring a bunch of variables
string word;
string wordDisplay;
int attempts;
char playerGuess;
string wrongGuesses;

void startGame()
{
	cout <<"Let's play hangman! What's the word?" <<endl;
	cin >> word; //Getting the word you said
	wordDisplay = word;
	for (int i = 0; i<word.length(); i++) { //Creating wordDisplay to have the same amount of -'s as the word length
		wordDisplay[i] = '-';
	}
	cout <<"How many attempts does Player 2 have to guess the word?" <<endl;
	cin >> attempts; //Getting the amount of attempts you said
	cout <<"Clearing chat... \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" //Clearing Chat
	<<"Chat cleared." <<endl;
	cout <<wordDisplay <<endl; //Displaying hidden word (----)
	return;
}

int main()
{
	bool hangingMan = true;
	while (hangingMan == true) {
		startGame(); //Calling the startGame function
		cout <<"The word has " <<word.length() <<" characters." <<endl;
		if (attempts == 1) { //Grammar correcting
			cout <<"You have " <<attempts <<" attempt to guess the word." <<endl;
		}
		else {
			cout <<"You have " <<attempts <<" attempts to guess the word." <<endl;
		}
		cout <<"You can start guessing now." <<endl;
		while (attempts > 0 && word != wordDisplay) { //while attempts > 0 AND word does not equal to displayed hidden word, continue guessing
			guessing(); //Calling the guessing function
			display(); //Calling the display function
		}
		if (attempts <= 0) {
			cout <<"You ran out of attempts! You lost. \n The word was \"" <<word <<"\"" <<endl; //Lose message
		}
		else if (attempts == 1){
			cout <<"You guessed the word \"" <<word <<"\" with only " <<attempts << " attempt left! You won!" <<endl; //Win message with singular attempt left
		}
		else if (attempts > 1) {
			cout <<"You guessed the word \"" <<word <<"\" with only " <<attempts << " attempts left! You won!" <<endl; //Win message with multiple attempts left
		}
		cout <<"Would you like to play again?" <<endl;
		string playAgain;
		bool understand = false;
		while (understand == false) {
			cin >> playAgain; //Getting your answer
			switch(toupper(playAgain[0])) {
			case 'N': //if answer is no
				cout <<"'Twas fun, bye!" <<endl;
				hangingMan = false;
				understand = true;
				break;
			case 'Y': //if answer is yes
				cout <<endl <<"Alright. ";
				wrongGuesses.clear(); //Clears the wrongGuesses variable from last game
				understand = true;
				break;
			default:
				cout <<"I didn't understand, please say yes or no." <<endl; //if answer is neither yes or no, ask again
				break;
			}
		}
	}
	return 0;
}

void guessing()
{
	cin >> playerGuess;
	bool letterFound = false;
	bool alreadyWarned = false;
	bool alreadyGuessed = false;
	for (int i = 0; i < word.length(); i++) {
		if (playerGuess == wordDisplay[i] && alreadyWarned == false) { //Checks if playerGuess is already in wordDisplay & accounts for double warning
			cout <<"You already guessed that letter!" <<endl;
			alreadyWarned = true;
			alreadyGuessed = true;
		}
		else if (playerGuess == word[i]) { //Checks if playerGuess is in word
			wordDisplay[i] = playerGuess;
			letterFound = true;
		}
	}
	for (int j = 0; j < wrongGuesses.length(); j++) {
		if (playerGuess == wrongGuesses[j]) { //Checks if playerGuess is already in wrongGuesses
			cout <<"You already guessed that letter!" <<endl;
			alreadyGuessed = true;
		}
	}
	if (letterFound == false && alreadyGuessed == false) { //if guessed letter isn't in word, add it to wrongGuesses
		wrongGuesses += playerGuess;
		attempts--; //use up an attempt if guessed incorrectly
		cout <<"You guessed wrong!" <<endl;
	}
	else if (letterFound == true && alreadyGuessed == false) {
		cout <<"You guessed right!" <<endl;
	}
	return;
}

void display()
{
	bool endGame = false;
	if (word == wordDisplay || attempts <= 0) {
		endGame = true;
	}
	cout <<endl <<wordDisplay <<endl; //Displaying wordDisplay
	if (attempts == 1 && endGame == false) { //if there's only 1 attempt left, say attempt
		cout <<"You have: " <<attempts <<" attempt remaining." <<endl;
	}
	else if (attempts != 1 && endGame == false) { //otherwise, say attempts
		cout <<"You have: " <<attempts <<" attempts remaining." <<endl;
	}
	if (wrongGuesses.length() != 0) { //if there's nothing in wrongGuesses, don't say it
		cout <<"Failed attempts: " <<wrongGuesses <<endl;
	}
	return;
}
