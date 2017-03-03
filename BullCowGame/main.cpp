/*
This is the console exe that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include <ctime>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int; 

void PrintIntroAndSetWord();
void InitializeWord(); 
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain(); 

FBullCowGame BCGame;				// Instantiate a new game

int main()							// Entry point for our application
{
	srand(time(NULL));				// Seed random number generator with new value on every run
	BCGame.ResetPlayerPointTotal();	// Initialize/Reset point total to 0 on game initialization

	bool bPlayAgain = false; 
	do {
		PrintIntroAndSetWord();
		PlayGame();
		bPlayAgain = AskToPlayAgain(); 
	} 
	while (bPlayAgain);
	
	return 0;						// Exit the application
}



void PrintIntroAndSetWord() // Introduce game
{
	std::cout << "-------------------------------------------\n";
	std::cout << "Welcome to Bulls and Cows, a fun word game!\n";
	std::cout << "-------------------------------------------\n"; 
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << std::endl;

	InitializeWord();

	std::cout << " << Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?? >>\n";
	std::cout << " ----------------------------------------------------------\n";
	std::cout << " << A Bull means a correct letter in the correct place.  >>\n";
	std::cout << " << A Cow means a correct letter in the incorrect place. >>\n";
	std::cout << " ----------------------------------------------------------\n";
	std::cout << " <<     If you get a Bull, watch for Helpful Hints!!     >>\n";
	std::cout << " ----------------------------------------------------------\n";
	std::cout << "                <<<<< Have fun!!!! >>>>>\n"; 
	std::cout << std::endl;

	return;
}

void InitializeWord()								// Get number from player, send to set up hidden word
{
	float WordLength;								// Float to handle case of user entering a decimal number
	std::cout << "Pick a number, 3 - 8: ";
	std::cin >> WordLength;
	std::cin.get();
	WordLength = round(WordLength); 
	if (WordLength < 3.0) { WordLength = 3.0; }		// Simple input validation check
	if (WordLength > 8.0) { WordLength = 8.0; }		// TODO handle cases of extreme input, ie 30123487023487120238471029
	std::cout << std::endl;
	BCGame.SetHiddenWordAndLength(WordLength);
	BCGame.SetBullPointMap(BCGame.GetHiddenWord());
}

void PlayGame()
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries(); 
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)	// Loop asking for guesses while the game is not won while have tries remaining
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);	// Submit valid guess to the game
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << ".\n";
		std::cout << "Helpful hint: In your guess, the letters { " << BCGame.GetGameHelper();
		std::cout << " } are in the correct position.\n";
		std::cout << "Current points: " << BCGame.GetMyPoints() << "\n\n";
	}

	PrintGameSummary();

	return; 
}

FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		BCGame.ResetGameHelper(); 
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);		// Get guess from player 

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Incorrect_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Word entered was not an isogram!\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter only lowercase letters.\n\n";
			break;
		default:							// If code gets here, assume Guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);	// Keep looping until input is valid

	return Guess;
	 
}

bool AskToPlayAgain()									// Ask player if they want to continue playing
{
	std::cout << "Do you want to play again? (y/n) ";	// TODO validate player input here
	FText Response = ""; 
	std::getline(std::cin, Response); 

	return (Response[0] == 'Y' || Response[0] == 'y');  
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) { std::cout << "WELL DONE - YOU WIN!!\n\n"; } 
	else { std::cout << "Better luck next time!\n\n"; }
}




