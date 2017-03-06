#pragma once
#include <string>
#include <map>
#include <vector>
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
	Hint,
	Not_Isogram,
	Incorrect_Length,
	Not_Lowercase,
};

class FBullCowGame
{
public:
	FBullCowGame();							// constructor
	
	int32 GetMinWordLength() const;
	int32 GetMaxWordLength() const;
	int32 GetBonusWordLength() const;
	int32 GetCurrentWordLength() const;
	int32 GetMaxTries() const;				// const at end of declaration prevents function from modifying variables of object
	int32 GetCurrentTry() const;			
	int32 GetHiddenWordLength() const;
	int32 GetMyPoints() const;
	FString GetGameHelper() const;
	FString GetHiddenWord() const;			// for testing only
	bool IsWordGuessed() const;
	bool IsGameWon();						// Looks at GameCompletionMap and returns true if all values are true
	bool GetEnterBonusRound();
	bool GetCompleteBonusRound();
	bool GetRestartAfterBonus();

	EGuessStatus CheckGuessValidity(FString) const;
	void CheckForMaxBulls(FBullCowCount);
	void CheckBullPointMap(char);
	void CheckCowPointMap(char);
	void CheckForPointLoss(bool);
	
	void Reset();							
	void ResetGameHelper();
	void ResetPlayerPointTotal();			// Resets PlayerPointTotal to 0
	void ResetCurrentWordLength();

	void SetMaxTries();
	void SetHiddenWordAndLength(int32);		// Player indirectly chooses the hidden word based on number
	void SetPointMaps(FString);
	void SetGameCompletionMap();
	void SetEnterBonusRound(bool);
	void SetCompleteBonusRound(bool);
	void SetRestartAfterBonus(bool);
	void AddPoints(int32);					
	void SubtractPoints(int32);

	FBullCowCount SubmitValidGuess(FString);// counts bulls and cows, and increasing try number assuming valid guess

	void ImplementWordWinCondition();		// Action to perform when player guesses a word correctly
	void ImplementWordLossCondition();		// Action to perform when player runs out of tries when guessing a word

private:
	const int32 MinWordLength = 3;
	const int32 MaxWordLength = 8;
	const int32 BonusWordLength = 15;
	int32 CurrentWordLength = MinWordLength;
	int32 MyCurrentTry;
	int32 GameMaxTries;
	int32 HiddenWordLength;
	int32 PlayerPointTotal;					// Container for player points earned throughout the game 
	FString MyHiddenWord;
	FString GameHelper;						// String used to give user hint when they get a bull
	bool bWordIsWon;
	TMap<char, bool> BullPointMap;			// Keep track of char's used when giving points for bulls
	TMap<char, bool> CowPointMap;			// Keep track of char's used when giving points for cows
	TMap<int32, bool> GameCompletionMap;	// Keep track of what word lengths the user has successfully guessed

	bool EnterBonusRound = false;
	bool CompleteBonusRound = false;
	bool RestartAfterBonus = false;

	const int32 BullPV = 10;				// Point System Variables
	const int32 CowPV = 5;
	const int32 NoMatchInGuessPV = 5;
	const int32 NoMatchMidGamePV = 30;
	const int32 FailurePV = 200;
	const int32 WinPV = 100;
	const int32 ExtraHintPV = 150;			// TODO implement extra hint functionality (through command?)
	
	bool IsIsogram(FString) const; 
	bool IsLowerCase(FString) const;
};