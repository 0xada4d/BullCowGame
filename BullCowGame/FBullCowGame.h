#pragma once
#include <string>

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

	FBullCowGame(); //constructor
	
	int32 GetMaxTries() const; // const at end of declaration prevents--
	int32 GetCurrentTry() const;  // function from modifying variables of object
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	

	// TODO Make a richer return value
	void Reset();
	

	// counts bulls and cows, and increasing try number assuming valid guess
	FBullCowCount SubmitValidGuess(FString); 

private:
	// See constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const; 
};