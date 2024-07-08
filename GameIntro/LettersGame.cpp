#include "LettersGame.h"
#include <map>
#include <iostream>
#include <windows.h>

#define TMap std::map

using FString = std::string;		//using namespace std;

FLettersGame::FLettersGame()
{
	Reset();
}

void FLettersGame::Reset()
{
	MaxTries = 6;
	CurrentTry = 1; 
	bGameWon = false;

	return;
}

int32 FLettersGame::CommitAnswer(FString CurrentHiddenWord, char Answer, int j)
{

	int32 HiddenWordLength = CurrentHiddenWord.length();
	int check = 15;

		// compare with symbols of suggested word
		for (int32 i = 0; i < HiddenWordLength; i++)
		{
			// if symbols match
			if (Answer == CurrentHiddenWord[i])
			{
				if (i != j)				// right letter and right position
					check = 111;
				else if (i == j)		// right letter but wrong position
					check = 47;
			}
		}
		
	return check;
}

EWordStatus FLettersGame::ValidateAnswer(FString CurrentHiddenWord, FString Answer) const
{
	if (Answer.length() != CurrentHiddenWord.length())
	{
		return EWordStatus::Wrong_Length;
	}
	else if (!IsIsogram(Answer))
	{
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowercase(Answer))
	{
		return EWordStatus::Not_Lowercase;
	}
	else
	{
		return EWordStatus::OK;
	}
}

int32 FLettersGame::GetMaxTries() const { return MaxTries; }
int32 FLettersGame::GetCurrentTry() const { return CurrentTry; }
int32 FLettersGame::GetHiddenWordLength(FString CurrentHiddenWord) const { return CurrentHiddenWord.length(); }
int32 FLettersGame::ChangeCurrentTry() { CurrentTry++; return CurrentTry; }

bool FLettersGame::IsGameWon(FString CurrentHiddenWord, int32 res) 
{ 
	if (res == CurrentHiddenWord.length())
		bGameWon = true;
	return bGameWon; 
}

bool FLettersGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))			
		{
			return false;
		}
	}
	
	return true;
}

bool FLettersGame::IsIsogram(FString Word) const
{
	// if word is too short (0, 1 symbol)
	if (Word.length() <= 1) { return true; }

	TMap <char, bool> LetterDictionary;
	// go through all word letters
	for (char Letter : Word)
	{
		Letter = tolower(Letter);					// convert to one register
		// if Map has symbol (key - symbol, value -  true)
		if (LetterDictionary[Letter])
		{
			return false;							// not isogram
		}
		else
		{
			LetterDictionary[Letter] = true;		// add key (current symbol) + value = true
		}
	}
	return true;
}