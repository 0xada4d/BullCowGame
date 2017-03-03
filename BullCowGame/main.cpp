/*
This is the console exe that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int; 

void PrintIntroAndSetWord(); 
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain(); 

FBullCowGame BCGame; // Instantiate a new game

int main() // Entry point for our application
{
	bool bPlayAgain = false; 
	do {
		PrintIntroAndSetWord();
		PlayGame();
		bPlayAgain = AskToPlayAgain(); 
	} 
	while (bPlayAgain); 
	
	return 0; // Exit the application
}

void PrintIntroAndSetWord() // Introduce game and set hidden word
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << std::endl;

	int32 WordLength;
	std::cout << "Pick a number, 3 - 8: ";
	std::cin >> WordLength;
	std::cout << "\n";
	BCGame.SetHiddenWord(WordLength);
	std::cin.get();

	std::cout << " << Can you guess the " << WordLength;
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

void PlayGame()
{
	BCGame.Reset(); 
	
	int32 MaxTries = BCGame.GetMaxTries();
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) // Loop asking for guesses while the game is not won and still have tries remaining
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);  // Submit valid guess to the game and recieve counts
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << ".\n";
		std::cout << "Helpful hint: " << BCGame.GetGameHelper() << "\n\n";
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
		std::getline(std::cin, Guess); // Get guess from player 

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
		default: // If it makes it here, assume Guess is valid and break out of loop
			break;
		}
	} while (Status != EGuessStatus::OK); // Keep looping until input is valid

	return Guess;
	 
}

bool AskToPlayAgain() // TODO validate user input for playing again
{
	std::cout << "Do you want to play again? (y/n) ";
	FText Response = ""; 
	std::getline(std::cin, Response); 

	return (Response[0] == 'Y' || Response[0] == 'y');  
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) { std::cout << "WELL DONE - YOU WIN!!\n\n"; } 
	else { std::cout << "Better luck next time!\n\n"; }
}


