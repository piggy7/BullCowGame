#pragma once
#include "FBullCowGame.h"
#include <map>
#include <cstdlib> 
#include <ctime>
//to make syntax unreal friendly
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }//Defualt constructor


int32 FBullCowGame::GetCurrentTry() const{ return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon()const { return bGameIsWon; }
int32 FBullCowGame::GetMaxTries() const 

{
	TMap<int32, int32>WordLengthToMaxTries{ {3,4} ,{4,7} ,{5,10} ,{6,15},{7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

//This is the reset and is called to reset all variables to the starting ones
void FBullCowGame::Reset()
{
	
	MyHiddenWord = WordPicker();
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


//This is going to check if the guess is valid.
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))//if the guess isn't a isogram,
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (IsLowercase(Guess))//if the guess isn't all lowercase, return an error
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{

		return EGuessStatus::Wrong_Length;
	}
	else 
	{
		return EGuessStatus::OK;

	}
}




//Receives a VALID guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	//loop through all letters in the Word 
	int32 WordLength = MyHiddenWord.length();//Assuming same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		//comapre letters against the hidden Guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
		//If they match
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;//Increment bulls if they are in the same place
				}
				else
				{
					BullCowCount.Cows++;//increment cows if they are not
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}
//This will scan the word can check if its all lower case
bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter))
		{
			return true;
		}
	}
	return false;
}
//This will check if there are any repeating letters in the word.
bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool>LetterSeen;//Setup our map
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter);//handle mixed case
		if(LetterSeen[Letter]){
			return false;
		}else{
			LetterSeen[Letter] = true;
		}
	}
	
		
	return true;//for example in cases where /0 is entered
}
FString FBullCowGame::WordPicker()const { 
	srand(time(NULL)); 
	return Words[rand() % Size]; 
}

