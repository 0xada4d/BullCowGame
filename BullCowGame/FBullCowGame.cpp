
#include "FBullCowGame.h"
#include <map>
#include <vector>
#include <ctime>
#define TMap std::map


using int32 = int;
using FString = std::string;


FBullCowGame::FBullCowGame()
{
	Reset(); // Does the job of the constructor, resetting the game
}


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
FString FBullCowGame::GetGameHelper() const { return GameHelper; }
FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; } // For testing only

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


// PrintIntro function asks for a number,
// Sends number to SetHiddenWord,
// Maps the number to a word in the hashmap, and sets that word as the hidden word
void FBullCowGame::SetHiddenWord(int32 WordLength)
{
	TMap<int32, std::vector<FString>> WordLengthToWord
	{
		{ 3, { "lit", "bat", "run", "per", "set" } },
		{ 4, { "folk", "bard", "rack", "port", "tarp" } },
		{ 5, { "weird", "tramp", "turns", "crash", "month" } },
		{ 6, { "planet", "ruined", "trader", "county", "biomes" } },
		{ 7, { "talking", "torment", "parking", "germany", "country" } },
		{ 8, { "portugal", "quadplex", "jarovize", "humpback", "chipmunk" } }
	};

	std::vector<FString> ChosenNumberVector = WordLengthToWord[WordLength]; // User's number picks the word set
	srand(time(NULL)); 
	int32 RandomChoice = rand() % 5; // Create a random number to be used to select word from set
	MyHiddenWord = ChosenNumberVector[RandomChoice]; // Pick the word from the set
	return;
}

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries
	{ 
		{3, 6}, {4, 8}, {5, 10}, {6, 12}, {7, 15}, {8, 18}
	};
	return WordLengthToMaxTries[MyHiddenWord.length()];
}





void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bGameIsWon = false;
	
	return; 
}

void FBullCowGame::ResetGameHelper()
{
	GameHelper = ""; 
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
					GameHelper += toupper(Guess[i]);  // Give player a hint when they get a bull
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


