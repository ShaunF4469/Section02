/*
- This is the console executable that makes use of the BullCow class
- This acts as the view in a MVC pattern, and is responsible 
  for all user interation. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include <map>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool PlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //Instantiate a new game, which we re-use across plays

int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = PlayAgain();
	} 
	while (bPlayAgain);	
	return 0; //Exit app
}

void PrintIntro() 
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLen();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << "You have " << BCGame.GetMaxTries() << " tries to guess.\n";
	std::cout << std::endl;
	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText UserGuess = GetValidGuess(); 

		// submit valid guess to the game, and recieve count
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(UserGuess);
				
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	
}

// loop continually until user provides a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 GuessNum = BCGame.GetCurrentTry();
		std::cout << "Try " << GuessNum << ", " << (BCGame.GetMaxTries() - GuessNum) + 1;
		std::cout << " left. Please make a guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValid(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLen() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word that does not have repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout;
	} while (Status != EGuessStatus::OK); // keep looping until we get no erros
	return Guess;
}

bool PlayAgain() 
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You've won! great job!\n";
	}
	else
	{
		std::cout << "Sorry, not this time. Better luck next try.\n";
	}
}
