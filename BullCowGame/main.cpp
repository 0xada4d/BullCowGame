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

void PrintGameTitlePicture();
void PrintGameDirections();
void PrintIntroAndSetWord();
void InitializeWord();
void PrintGuessSummary(FBullCowCount);
void PlayGame();
void PrintRoundSummary();
void PrintGameWinSummary();
void PrintGameLossSummary(bool);
FText GetValidGuess();
bool AskToKeepPlaying();
bool CheckToContinuePlay(); 

FBullCowGame BCGame;				// Instantiate a new game

int main()							// Entry point for our application
{
	srand(time(NULL));				// Seed random number generator with new value on every run
	BCGame.ResetPlayerPointTotal();	// Initialize/Reset point total to 0 on game initialization

	bool bPlayAgain = false; 
	do {
		PrintIntroAndSetWord();
		PlayGame();
		bPlayAgain = CheckToContinuePlay(); 
	} 
	while (bPlayAgain);
	
	return 0;						// Exit the application
}

void PrintIntroAndSetWord() // Introduce game and set word
{
	PrintGameTitlePicture();
	InitializeWord();
	PrintGameDirections(); 
	std::cout << BCGame.GetHiddenWord() << "\n";
	std::cout << std::endl;

	return;
}

void PrintGameTitlePicture()
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
	return;
}

void InitializeWord()								// Get the current word length and set the word (and Maps) based on length
{
	int32 WordLength = BCGame.GetCurrentWordLength();
	BCGame.SetHiddenWordAndLength(WordLength);
	BCGame.SetPointMaps(BCGame.GetHiddenWord());
	BCGame.SetGameCompletionMap();
	return;
}

void PrintGameDirections()
{
	std::cout << " << Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?? >>\n";
	std::cout << " ----------------------------------------------------------\n";
	std::cout << " << A Bull means a correct letter in the correct place.  >>\n";
	std::cout << " << A Cow means a correct letter in the incorrect place. >>\n";
	std::cout << " ----------------------------------------------------------\n";
	std::cout << " <<     If you get a Bull, watch for Helpful Hints!!     >>\n";
	std::cout << " ----------------------------------------------------------\n";
	std::cout << "                <<<<< Have fun!!!! >>>>>\n";
	return;
}

void PlayGame()
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries(); 
	while (!BCGame.IsWordGuessed() && BCGame.GetCurrentTry() <= MaxTries)	// Loop asking for guesses while word is not guessed and while having tries remaining
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);		// Submit valid guess to the game
		PrintGuessSummary(BullCowCount);
	}

	if (BCGame.IsWordGuessed()) { BCGame.ImplementWordWinCondition(); }		// Player guessed the correct word in a round
	else { BCGame.ImplementWordLossCondition(); }							// Player did not guess the word

	return; 
}

void PrintGuessSummary(FBullCowCount BullCowCount)							// Shows Player the number of Bulls and Cows in guess
{																			// and prints a hint for the bulls
	std::cout << "Bulls = " << BullCowCount.Bulls;
	std::cout << ". Cows = " << BullCowCount.Cows << ".\n";
	std::cout << "Helpful hint: In your guess, the letters { " << BCGame.GetGameHelper();
	std::cout << " } are in the correct position.\n";
	std::cout << "Current points: " << BCGame.GetMyPoints() << "\n\n";
	return;
}

FText GetValidGuess()														// Makes sure player puts in a valid string for the game
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

bool CheckToContinuePlay()												// Check for correct conditions to continue game
{
	bool bPositivePoints = (BCGame.GetMyPoints() > 0);					// TODO make calculation for more robust check for negative value
	bool bGameIsWon = BCGame.IsGameWon();
	if (bPositivePoints && BCGame.GetCurrentWordLength() <= 8)	
	{
		PrintRoundSummary();
		std::cout << "On to the next word? (Y/n) ";
		return AskToKeepPlaying();
	}
	else					
	{
		if (bGameIsWon && bPositivePoints) { PrintGameWinSummary();; }
		else { PrintGameLossSummary(bPositivePoints); }
		if (AskToKeepPlaying()) {
			BCGame.ResetPlayerPointTotal();
			BCGame.ResetCurrentWordLength();
			return true;
		}
		else { return false; }
	}
}

void PrintRoundSummary()								// States the result of the round just played, including points
{
	int32 FinalPointValue = BCGame.GetMyPoints();
	std::cout << "Total points: " << FinalPointValue << std::endl;
	std::cout << std::endl;
	if (BCGame.IsWordGuessed()) { std::cout << "WELL DONE!!\n\n"; }
	else { std::cout << "Better luck next time!\n\n"; }
	return;
}

bool AskToKeepPlaying()									// Gets a player response and interprets it to proceed
{
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'Y' || Response[0] == 'y' || Response == "");
}

void PrintGameWinSummary()
{
	std::cout << "Final points: " << BCGame.GetMyPoints() << std::endl;
	std::cout << std::endl;
	std::cout << "=====================================\n";
	std::cout << "YOU WON THE GAME! CONGRATULATIONS!!!!\n";
	std::cout << "=====================================\n\n";
	std::cout << "Would you like to restart? (Y/n) \n";
	return;
}

void PrintGameLossSummary(bool PositivePoints)
{
	std::cout << "Final points: " << BCGame.GetMyPoints() << std::endl;
	std::cout << "\n====================================================\n";
	if (PositivePoints) { std::cout << "YOU LOST, you did not guess all of the words!\n"; }
	else { std::cout << "YOU LOST, you did not have enough points to continue.\n"; }
	std::cout << "====================================================\n\n";
	std::cout << "Would you like to restart? (Y/n) \n";
	return;
}






