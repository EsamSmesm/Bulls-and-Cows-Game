
/* This is the console excutable, that makes use of the BullCow class
This acts as the view in a MVC pattern , and is responsible for all 
user interaction. for game logic see the FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText =FString;
using int32 = int;
// function prototypes as outside a class
void Printintro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain(); 
FBullCowGame BCGame; // instantiate a new game , which we re-use across plays



int main()
{
	bool bPlayAgain = false;
	do
	{
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	
	return 0; // exit the application 
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	Printintro();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <=MaxTries)
	{
		FText Guess = GetValidGuess(); 
 		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print32 number of bulls and cows 
		std::cout << "Bulls = " << BullCowCount.Bulls<<std::endl;
		std::cout << "Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

void Printintro()
{
	// introduce the game 
	std::cout << "Welcome to Bulls and Cows , a fun word game\n";
	std::cout << "Can you guess the  " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of ?\n" << std::endl;

}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratelations, YOU WIN ! \n\n";
	}
	else if(BCGame.GetCurrentTry() > BCGame.GetMaxTries())
	{
		std::cout << "Bad luck, try agin! \n\n";
	}
	return;
}

// loop contiually until the user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "try " << CurrentTry << " of " << BCGame.GetMaxTries()<<".";
		std::cout<< " Whats your guess? ";
		std::getline(std::cin, Guess);
		// check status and give feedback
	    Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "please enter a " << BCGame.GetHiddenWordLength() << " letter word .\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "please enter a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "please enter a lowercase word \n\n";
			break;
		default:
			// assume the guess is valid
			break;
	    }
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "DO you want to play again (y/n) ? \n";
	FText Response = "";
	std::getline(std::cin, Response);  
	return (Response[0]=='y' || Response[0] == 'Y');
}