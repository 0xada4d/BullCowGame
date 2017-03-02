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
	FString GetGameHelper() const;
	FString GetHiddenWord() const; // for testing only
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	
	void SetHiddenWord(int32); // Player indirectly chooses the hidden word based on number
	void Reset(); // TODO Make a richer return value
	void ResetGameHelper(); 
	
	
	// counts bulls and cows, and increasing try number assuming valid guess
	FBullCowCount SubmitValidGuess(FString); 

private:
	// See constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	FString GameHelper;  // Variable to help player know where bulls are located
	bool bGameIsWon;

	bool IsIsogram(FString) const; 
	bool IsLowerCase(FString) const;
};