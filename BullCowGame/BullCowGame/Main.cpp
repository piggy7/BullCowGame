/*This is the console executalbe, that makes use of the BullCow class 
This acts as the view in a MVC pattern, and it responsible for all
user interaction. for game locgic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include "FBullCowGame.h"

//To make syntax unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();


FBullCowGame BCGame;//instantiate a new game, which we re-use across plays

//The entry point for the application
int main() 
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;//Close Program
}

void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n\n";
	std::cout << "    ,           ," << std::endl;
	std::cout <<"    /             \\" << std::endl;
	std::cout << "  ((__-^^-,-^^-__))" << std::endl;
	std::cout << "   `-_---' `---_-'" << std::endl;
	std::cout << "    <__|o` 'o|__>" << std::endl;
	std::cout << "       \  `  /" << std::endl;
	std::cout << "        ): :(" << std::endl;
	std::cout << "        :o_o:" << std::endl << std::endl;
	
	std::cout << "Bull means one letter is in the correct spot,\n";
	std::cout << "Cow means one letter is correct but in the wrong spot.\n\n";
	std::cout << "Can you guess the "<< BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}
//This will play a single game to completion
void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();
	while( ! BCGame.IsGameWon() && BCGame.GetCurrentTry()<=MaxTries){
		FText Guess = GetValidGuess();
		FBullCowCount BullCountCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCountCount.Bulls;
		std::cout << ". cows = " << BullCountCount.Cows<<"\n\n";
	}
	PrintGameSummary();
	BCGame.Reset();
	return;
}
//This will check if the guess is valid 
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " out of "<< BCGame.GetMaxTries() << ". Enter your guess: ";
		
		std::getline(std::cin, Guess);

		 Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:std::cout << "please enter a " << BCGame.GetHiddenWordLength() << " Letter word.\n\n";break;
		case EGuessStatus::Not_Isogram: std::cout << "Please enter a Isogram.\n\n";break;
		case EGuessStatus::Not_Lowercase:std::cout << "please type in all lowercase letters.\n\n";break;
		default:break;
		}
		
	} while (Status != EGuessStatus::OK);//Keep looking until we get no errors
	return Guess;
}
//This asks the user if they would like to play again once they have finished the game
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word [Y/N]? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y')||(Response[0] == 'Y');
}
//This will print to the user the summary, whether they have won or lost
void PrintGameSummary() 
{
	if (BCGame.IsGameWon()) 
	{
		std::cout << "Well Done - You win!\n";
	}
	else 
	{
		std::cout << "better luck next time.\n";
	}

}
