#pragma once
#include "FBullCowGame.h"
#include<map>
#define TMap std::map // to make syntax Unreal friendly

FBullCowGame::FBullCowGame(){ Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon() const{return bGameIsWon;}



int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,10}, {4,15}, {5,20}, {6,25}, {7,30}, {8,40}, {9,45},{10,50} };
	return WordLengthToMaxTries[GetHiddenWordLength()]; 
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	int32 MyHiddenWordLength = MyHiddenWord.length();
	return MyHiddenWordLength;
}

// pick a random isogram 
void FBullCowGame::GetRandomWord()
{
	FString HiddenWordsList[] =
	{ "easy","hurt","guy","code","hate","ice","fire","destroy","red","king",
	  "house","prison","victory","computer","power","thunder","keyboard","algorithm"
	};
	const FString HIDDEN_WORD = HiddenWordsList[rand() % HiddenWordsList->length()]; // this must be an isogram
	MyHiddenWord = HIDDEN_WORD;

}

 void FBullCowGame::Reset()
{
	GetRandomWord();
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (! IsLowercase(Guess)) // if the guess isn't a lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != MyHiddenWord.length())	// if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else  // otherwise
	{
		return EGuessStatus::OK;
	} 
}

// receives a VALID guess, incriments turns , and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++; 
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming the same length as guess

	// loop through all leters in the hidden word
	for (int32 i = 0; i < WordLength; i++)
	{
		// compare letters against the guess
		for (int32 j = 0; j < WordLength; j++)
		{
			// if they match then
			if (Guess[j] == MyHiddenWord[i])
			{
				// if they're in the same place
				if (i == j)
				{
					BullCowCount.Bulls++; // incriment bulls
				}
				else
				{
					BullCowCount.Cows++; // incriment cows
				}
			}	
		}
	}
	if (Guess == MyHiddenWord)
	{
		FBullCowGame::bGameIsWon = true;
	}
	else
	{
		FBullCowGame::bGameIsWon = false;
	}
	

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 or 1 letter word as isogram
	if (Word.length() <= 1) { return true; }
	
	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) // if the letter is in the map
		{
			return false; // we dont have an isogram
		}
		else
		{
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}
	
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) // if not a lowercase letter
		{
			return false;
		}
	}
	return true;
}
