
#include "FBullCowGame.h"
#include <iostream>
#include <map>
#include <vector>

#define TMap std::map

using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame() { Reset(); }										// Does the job of the constructor, resetting the game

int32 FBullCowGame::GetMinWordLength() const { return MinWordLength; }
int32 FBullCowGame::GetMaxWordLength() const { return MaxWordLength; }
int32 FBullCowGame::GetBonusWordLength() const { return BonusWordLength; }
int32 FBullCowGame::GetCurrentWordLength() const { return CurrentWordLength; }
int32 FBullCowGame::GetMaxTries() const { return GameMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWordLength; }
int32 FBullCowGame::GetMyPoints() const { return PlayerPointTotal; }
FString FBullCowGame::GetGameHelper() const { return GameHelper; }
FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }			// For testing only
bool FBullCowGame::IsWordGuessed() const { return bWordIsWon; }
bool FBullCowGame::GetEnterBonusRound() { return EnterBonusRound; }
bool FBullCowGame::GetCompleteBonusRound() { return CompleteBonusRound; }
bool FBullCowGame::GetRestartAfterBonus() { return RestartAfterBonus; }

bool FBullCowGame::IsGameWon()									// Check all values in GameCompletionMap
{
	for (int32 i = MinWordLength; i <= MaxWordLength; i++)		
	{
		if (!GameCompletionMap[i]) { return false; }			// If any value is false, game is not won
	}
	return true;
}



void FBullCowGame::SetHiddenWordAndLength(int32 WordLength)						// Maps number to vector, then randomly chooses word from vector
{
	HiddenWordLength = WordLength;
	TMap<int32, std::vector<FString>> WordLengthToWord
	{
		{ 3, { "rot", "bat", "run", "per", "set", "mix", "ton", "out", "far", "get", "fox" } },
		{ 4, { "folk", "bard", "rack", "port", "tarp", "soda", "hugs", "lazy", "cute", "spry" } },
		{ 5, { "weird", "tramp", "turns", "crash", "month", "steak", "horse", "crazy", "jumps", "snead" } },
		{ 6, { "planet", "ruined", "swipes", "county", "biomes", "racing", "mexico", "jockey", "hijack", "jumble" } },
		{ 7, { "talking", "calzone", "parking", "squirmy", "country", "jukebox", "mexican", "wackjob", "subject", "quicker" } },
		{ 8, { "muskoxen", "quadplex", "abjuring", "humpback", "chipmunk", "quackery", "hijacked", "jumbling", "longjump", "jackfish" } },
		{ BonusWordLength, { "dermatoglyphics", "hydropneumatics", "misconjugatedly", "uncopyrightable" } }
	};

	std::vector<FString> ChosenNumberVector = WordLengthToWord[WordLength]; // CurrentWordLength dictates the word set
	int32 RandomNumber = rand() % ChosenNumberVector.size();				// Create a random number to be used to select word from set
	MyHiddenWord = ChosenNumberVector[RandomNumber];						// Pick the word from the set
	return;
}

void FBullCowGame::SetPointMaps(FString HiddenWord)  // Takes in the HiddenWord and initializes PointMap with its characters
{
	for (char Letter : HiddenWord) 
	{ 
		BullPointMap[Letter] = false;
		CowPointMap[Letter] = false;
	}			
}

void FBullCowGame::SetGameCompletionMap()
{
	for (int32 i = MinWordLength; i <= MaxWordLength; i++) { GameCompletionMap[i] = false; }
	return;
}

void FBullCowGame::SetEnterBonusRound(bool Response) 
{
	EnterBonusRound = Response;
	return;
}

void FBullCowGame::SetCompleteBonusRound(bool Response)
{
	CompleteBonusRound = Response;
	return;
}

void FBullCowGame::SetRestartAfterBonus(bool Response)
{
	RestartAfterBonus = Response;
	return;
}

void FBullCowGame::AddPoints(int32 amount)  // Adds specified amount to PlayerPointTotal
{
	PlayerPointTotal += amount;				// TODO add output for the amount of points earned 
	return;
}

void FBullCowGame::SubtractPoints(int32 amount)
{
	PlayerPointTotal -= amount;
	return;
}

void FBullCowGame::SetMaxTries() 
{ 
	TMap<int32, int32> WordLengthToMaxTries
	{ 
		{3, 6}, {4, 10}, {5, 12}, {6, 14}, {7, 18}, {8, 22}, {15, 25}
	};
	GameMaxTries = WordLengthToMaxTries[HiddenWordLength];
	return;
}

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bWordIsWon = false;
	SetMaxTries();
	
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

void FBullCowGame::ResetCurrentWordLength()
{
	CurrentWordLength = MinWordLength;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false) { return EGuessStatus::Hint; }														// if player submits @hint, return Hint status
	else if (!IsIsogram(Guess)) { return EGuessStatus::Not_Isogram; }
	else if (!IsLowerCase(Guess)) { return EGuessStatus::Not_Lowercase; }							// if the guess is not lowercase, return error
	else if (Guess.length() != GetHiddenWordLength()) { return EGuessStatus::Incorrect_Length; }	// if length is wrong, return error
	else { return EGuessStatus::OK; }																// otherwise return ok 
}

void FBullCowGame::CheckForMaxBulls(FBullCowCount BullCowCount)			// If bulls = hidden word length, the player wins the game
{																		
	if (BullCowCount.Bulls == HiddenWordLength)	{ bWordIsWon = true; }	
	else { bWordIsWon = false; }
	return;
}

void FBullCowGame::ImplementWordWinCondition()
{
	AddPoints(WinPV);
	GameCompletionMap[HiddenWordLength] = true;
	std::cout << "You guessed the word! Adding " << WinPV << " points...\n";
	CurrentWordLength++;
	return;
}

void FBullCowGame::ImplementWordLossCondition()			// If bGameIsWon remains false throughout tries for word, player loses points
{
	SubtractPoints(FailurePV);
	std::cout << "You didn't guess the word. Subtracting " << FailurePV << " points...\n";
	return;
}

void FBullCowGame::CheckBullPointMap(char GuessChar)
{
	if (!BullPointMap[GuessChar])						// Check BullPointMap value for current character
	{													
		AddPoints(BullPV);								// If value is false, letter has not been counted, thus
		BullPointMap[GuessChar] = true;					// Add points to total and set value to true
	}
	return;
}

void FBullCowGame::CheckCowPointMap(char GuessChar)
{
	if (!CowPointMap[GuessChar])						// Check CowPointMap value for current character
	{
		AddPoints(CowPV);								// If value is false, letter has not been counted, thus
		CowPointMap[GuessChar] = true;					// Add points to total and set value to true
	}
	return;
}

void FBullCowGame::CheckForPointLoss(bool IsMatch)
{
	if (!IsMatch && (MyCurrentTry > (GameMaxTries * .5)))		// Halfway through game and make bad guess, player loses points
	{
		SubtractPoints(NoMatchMidGamePV);
	}
	else if (!IsMatch)											// Player makes a bad guess anytime
	{
		SubtractPoints(NoMatchInGuessPV);
	}
	else { return; }
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)	// Recieves valid guess, increments turn, and returns count
{ 
	FBullCowCount BullCowCount; 							
	bool GuessHasMatch = false;
	for (int32 i = 0; i < HiddenWordLength; i++)			// loop through all letters in hidden word
	{
		for (int32 j = 0; j < HiddenWordLength; j++)		// compare letters against the guess
		{
			if (Guess[i] == MyHiddenWord[j])				// if letters match,
			{
				GuessHasMatch = true;
				char CurrentChar = Guess[i];
				if (i == j)												
				{
					BullCowCount.Bulls++;					// and are in same place, increment bulls
					GameHelper += toupper(CurrentChar);		// Give player a hint when they get a bull
					CheckBullPointMap(CurrentChar);
				}
				else 
				{ 
					BullCowCount.Cows++;					// not in same place, increment cows
					CheckCowPointMap(CurrentChar);
				}							
			}
		}
	}
	CheckForPointLoss(GuessHasMatch);
	CheckForMaxBulls(BullCowCount);							// Check for win status (Bulls = Hidden word length)
	MyCurrentTry++;
		
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



