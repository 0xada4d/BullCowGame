#pragma once
#include <string>
#include <map>
#define TMap std::map

using FString = std::string; 
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0; 
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Incorrect_Length,
	Not_Lowercase,
};

class FBullCowGame
{
public:
	FBullCowGame();							// constructor
	
	int32 GetMaxTries() const;				// const at end of declaration prevents function from modifying variables of object
	int32 GetCurrentTry() const;			
	int32 GetHiddenWordLength() const;
	int32 GetMyPoints() const;
	FString GetGameHelper() const;
	FString GetHiddenWord() const;			// for testing only
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;
	void CheckForWinStatus(FBullCowCount);
	
	void Reset();							
	void ResetGameHelper();
	void ResetPlayerPointTotal();			// Resets PlayerPointTotal to 0

	void SetHiddenWordAndLength(int32);		// Player indirectly chooses the hidden word based on number
	void SetBullPointMap(FString);
	void AddPoints(int32);					// TODO add SubtractPoints() method

	FBullCowCount SubmitValidGuess(FString);// counts bulls and cows, and increasing try number assuming valid guess

private:
	int32 MyCurrentTry;
	int32 HiddenWordLength;
	int32 PlayerPointTotal;					// Container for player points earned throughout the game
	FString MyHiddenWord;
	FString GameHelper;						// String used to give user hint when they get a bull
	bool bGameIsWon;
	TMap<char, bool> BullPointMap;			// Keep track of points earned upon receiving a bull

	bool IsIsogram(FString) const; 
	bool IsLowerCase(FString) const;
};