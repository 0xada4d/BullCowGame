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

void PrintIntro(); 
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain(); 

FBullCowGame BCGame; // Instantiate a new game

// Entry point for our application
int main()
{
	bool bPlayAgain = false; 
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain(); 
	} 
	while (bPlayAgain); 
	
	return 0; // Exit the application
}



void PrintIntro()
{
	// Introduce game
	std::cout << "\n\nThis is the bullcow game, a fun word game!\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of??\n";
	std::cout << std::endl;
	return;
}


void PlayGame()
{
	BCGame.Reset(); 
	int32 MaxTries = BCGame.GetMaxTries(); 

	// Loop asking for guesses while the game is not won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); // TODO make loop checking valid
				
		// Submit valid guess to the game and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess); 
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << ".\n\n";
	}

	PrintGameSummary();

	return; 
}

//Loop until user gives a valid guess.
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		// Get guess from player 
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Incorrect_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Word entered was not an isogram!\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please input only lowercase letters.\n";
			break;
		default:
			// If it makes it here, assume Guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // Keep looping until input is valid

	return Guess;
	 
}


bool AskToPlayAgain()
{
	// Ask player if he/she wants to continue
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = ""; 
	std::getline(std::cin, Response); 

	return (Response[0] == 'Y' || Response[0] == 'y');  
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!!\n\n";
	} 
	else
	{
		std::cout << "Better luck next time!\n\n";
	}
}


