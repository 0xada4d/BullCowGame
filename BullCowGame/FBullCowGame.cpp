
#include "FBullCowGame.h"
#include <map>
#include <vector>

#define TMap std::map

using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame() { Reset(); }										// Does the job of the constructor, resetting the game

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWordLength; }
int32 FBullCowGame::GetMyPoints() const { return PlayerPointTotal; }
FString FBullCowGame::GetGameHelper() const { return GameHelper; }
FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }			// For testing only
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::SetHiddenWordAndLength(int32 WordLength)						// Maps number to vector, then randomly chooses word from vector
{
	HiddenWordLength = WordLength;
	TMap<int32, std::vector<FString>> WordLengthToWord
	{
		{ 3, { "rot", "bat", "run", "per", "set", "mix", "ton", "out", "far", "get", "fox" } },
		{ 4, { "folk", "bard", "rack", "port", "tarp", "soda", "hugs", "lazy", "cute", "spry" } },
		{ 5, { "weird", "tramp", "turns", "crash", "month", "steak", "horse", "crazy", "jumps", "snead" } },
		{ 6, { "planet", "ruined", "trader", "county", "biomes", "racing", "mexico", "jockey", "hijack", "jumble" } },
		{ 7, { "talking", "torment", "parking", "squirmy", "country", "jukebox", "mexican", "wackjob", "subject", "quicker" } },
		{ 8, { "muskoxen", "quadplex", "abjuring", "humpback", "chipmunk", "quackery", "hijacked", "jumbling", "longjump", "jackfish" } }
	};

	std::vector<FString> ChosenNumberVector = WordLengthToWord[WordLength]; // User's number picks the word set
	int32 RandomChoice = rand() % ChosenNumberVector.size();				// Create a random number to be used to select word from set
	MyHiddenWord = ChosenNumberVector[RandomChoice];						// Pick the word from the set
	return;
}

void FBullCowGame::SetBullPointMap(FString HiddenWord)  // Takes in the HiddenWord and initializes PointMap with its characters
{
	for (char Letter : HiddenWord) { BullPointMap[Letter] = false; }			
}

void FBullCowGame::AddPoints(int32 amount)  // Adds specified amount to PlayerPointTotal
{
	PlayerPointTotal += amount;				// TODO add output for the amount of points earned 
	return;
}

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries
	{ 
		{3, 7}, {4, 10}, {5, 12}, {6, 14}, {7, 18}, {8, 22}
	};
	return WordLengthToMaxTries[GetHiddenWordLength()];
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

void FBullCowGame::ResetPlayerPointTotal()
{
	PlayerPointTotal = 0;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) { return EGuessStatus::Not_Isogram; }
	else if (!IsLowerCase(Guess)) { return EGuessStatus::Not_Lowercase; }							// if the guess is not lowercase, return error
	else if (Guess.length() != GetHiddenWordLength()) { return EGuessStatus::Incorrect_Length; }	// if length is wrong, return error
	else { return EGuessStatus::OK; }																// otherwise return ok 
}

void FBullCowGame::CheckForWinStatus(FBullCowCount BullCowCount)		// If bulls = hidden word length, the player wins the game
{																		
	if (BullCowCount.Bulls == MyHiddenWord.length())
	{
		bGameIsWon = true;
		AddPoints(30);													// TODO Get rid of magic number
	}
	else { bGameIsWon = false; }
	return;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)				// Recieves valid guess, increments turn, and returns count
{
	MyCurrentTry++; 
	FBullCowCount BullCowCount; 

	int32 WordLength = MyHiddenWord.length();							// assume same length as Guess
	for (int32 i = 0; i < WordLength; i++)								// loop through all letters in hidden word
	{
		for (int32 j = 0; j < WordLength; j++)							// compare letters against the guess
		{
			bool DoLettersMatch = (Guess[i] == MyHiddenWord[j]);
			if (DoLettersMatch)											// if they match,
			{
				if (i == j)												// and are in same place, increment bulls
				{
					char CurrentChar = Guess[i];
					BullCowCount.Bulls++;								// TODO Fix magic numbers for points
					GameHelper += toupper(CurrentChar);					// Give player a hint when they get a bull		

					if (!BullPointMap[CurrentChar])						// Check BullPointMap value for current character
					{													// If value is false, letter has not been counted, thus
						AddPoints(10);									// Add points to total and set value to true
						BullPointMap[CurrentChar] = true;
					}													// Otherwise don't do anything
					break;
				}
				else { BullCowCount.Cows++; }							// not in same place, increment cows
			}
		}
	}
	CheckForWinStatus(BullCowCount);									// Check for win status
		
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() < 2) { return 1; }			// Treat 0 and 1 letter strings as isograms

	TMap<char, bool> LetterSeen;					// set up our map
	for (auto Letter : Word)						// Loop through all letters
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false;	}	// If letter in map, we do not have an isogram
		else { LetterSeen[Letter] = true; }			// otherwise add letter to map
	}
			
	return true;									// Handles case of \0
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	if (Word.length() == 0) { return true; }

	for (auto Letter : Word)
	{
		if (!islower(Letter)) { return false; }
	}

	return true;
}



