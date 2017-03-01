
#include "FBullCowGame.h"
#include <map>
#define TMap std::map


using int32 = int; 


FBullCowGame::FBullCowGame()
{
	Reset(); // Does the job of the constructor, resetting the game
}


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


// PrintIntro function asks for a number,
// Sends number to SetHiddenWord,
// Maps the number to a word in the hashmap, and sets that word as the hidden word
void FBullCowGame::SetHiddenWord(int32 WordLength)
{
	TMap<int32, FString> WordLengthToWord
	{
		{ 3, "ant" },{ 4, "cats" },
		{ 5, "grasp" },{ 6, "planet" },
		{ 7, "talking" },{ 8, "brandish" }
	};

	MyHiddenWord = WordLengthToWord[WordLength];
}

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries
	{ 
		{3, 4}, {4, 5}, {5, 7}, {6, 10}, {7, 12}, {8, 15}
	};
	return WordLengthToMaxTries[MyHiddenWord.length()];
}





void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bGameIsWon = false;
	
	return; 
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase; // if the guess is not lowercase, return error
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Incorrect_Length; // if length is wrong, return error
	}
	else
	{
		return EGuessStatus::OK; // otherwise return ok
	}
	
	
	
}

// Recieves valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++; 
	FBullCowCount BullCowCount; 

	int32 WordLength = MyHiddenWord.length(); // assume same length as Guess

	// loop through all letters in hidden word
	for (int32 i = 0; i < WordLength; i++)
	{
		// compare letters against the guess
		for (int32 j = 0; j < WordLength; j++)
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

	if (BullCowCount.Bulls == WordLength) 
	{
		bGameIsWon = true;
		
	} 
	else 
	{
		bGameIsWon = false;
	}
		
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// Treat 0 and 1 letter strings as isograms
	if (Word.length() < 2) { return 1; }

	// set up our map
	TMap<char, bool> LetterSeen;

	for (auto Letter : Word) // Loop through all letters
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) // if the letter is in the map
		{
			return false;	// we do not have an isogram
		}
		else
		{
			LetterSeen[Letter] = true;	// otherwise add letter to map
		}
	}
			
	return true; // in case where \0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	if (Word.length() == 0) { return true; }

	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}

	return true;
}


