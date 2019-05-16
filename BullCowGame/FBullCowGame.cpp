#pragma once

#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLen() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,3}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "ant"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	
	return;
}

EGuessStatus FBullCowGame::CheckGuessValid(FString Guess) const

{
	if (!IsIsogram(Guess)) // If guess not isogram
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowercase(Guess)) // If guess not lowercase
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length() != GetHiddenWordLen()) // If guess not wrong length, 
	{
		return EGuessStatus::Wrong_Length;
	}
	else // otherwise
	{
		return EGuessStatus::OK;
	}
		
}

// Recieves a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters in the hidden word
	int32 WordLen = MyHiddenWord.length(); // assuming same length as guess
	for (int32 i = 0; i < WordLen; i++) {
		// compare letters against the guess
		for (int32 j = 0; j < WordLen; j++) {
			// if they match
			if (Guess[j] == MyHiddenWord[i]) {
				if (i == j) { // in the same place
					BullCowCount.Bulls++; //increment bulls
				}
				// otherwise
				else {
					BullCowCount.Cows++; //increment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLen) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; } // treat 0 and 1 letter strings as isograms

	TMap<char, bool> LetterSeen; // setup our map
	for (char Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // Handle mixed case
		if (LetterSeen[Letter]) { return false; } // if the letter is in the map we do NOT have and isogram
		else { LetterSeen[Letter] = true;  } // add the letter to the map as seen					
	}	 
	
	return true; // for cases where '\0' is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (char Letter : Word)
	{
		if (!islower(Letter)) { return false; } // if not a lowercase letter return false					
	}
	return true;
}
