#pragma once
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

//all values initialized to zero
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;	
};

enum EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); //Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLen() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValid(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);
		

private:
	//See Constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
