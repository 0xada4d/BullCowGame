
#include "FBullCowGame.h"
using int32 = int; 


FBullCowGame::FBullCowGame()
{
	Reset(); // Does the job of the constructor, resetting the game
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }


void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8; // Use name for easier management
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet"; 
	MyHiddenWord = HIDDEN_WORD; 

	MyCurrentTry = 1;
	
	return; 
}

bool FBullCowGame::IsGameWon() const
{ 
	return false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if the guess is not isogram
	if (false)
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false)
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Incorrect_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
	// if the guess is not lowercase, return error
	// if length is wrong, return error
	// otherwise return ok
}

// Recieves valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	// increment turn number
	MyCurrentTry++; 

	// set up return variable
	FBullCowCount BullCowCount; 

	int32 HiddenWordLength = MyHiddenWord.length();
	// loop through all letters in guess
	for (int32 i = 0; i < HiddenWordLength; i++)
	{
		// compare letters against the hidden word
		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			bool DoLettersMatch = (Guess[i] == MyHiddenWord[j]);
			// if they match, 
			if (DoLettersMatch)
			{
				if (i == j)
				{
					// and are in same place, increment bulls
					BullCowCount.Bulls++;
					break;
				}
				else
				{
					// not in same place, increment cows
					BullCowCount.Cows++;
				}
			}
		}
	}
		
	return BullCowCount;
}
