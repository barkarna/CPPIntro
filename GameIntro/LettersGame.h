#pragma once

#include <string>

using int32 = int;
using FString = std::string;
using FText = std::string;

enum class EWordStatus
{
	None,				// Initial state
	OK,					// Everything is OK
	Wrong_Length,		// Answer words length is incorrect
	Not_Lowercase,		// We need word in lowercase to type in
	Not_Isogram			// Check if wolld have different letters
};

class FLettersGame
{
public:

	FString HiddenWord = "unreal";
	FLettersGame();

	void Reset();																		// game reset
	EWordStatus ValidateAnswer(FString CurrentHiddenWord, FString Answer) const;		// input word check
	bool IsGameWon(FString CurrentHiddenWord, int32 res);								// win check

	int32 GetMaxTries() const;															// get number of attempts
	int32 GetCurrentTry() const;														// get number of current attempt
	int32 ChangeCurrentTry();
	int32 CommitAnswer(FString, char, int);	
	int32 GetHiddenWordLength(FString CurrentHiddenWord) const;							// get input word length

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
private:
	int32 MaxTries = 6;																	// maximum game loop iterations
	int32 CurrentTry = 1;																// current iteration
	bool bGameWon = false;

	// Utilities
	bool IsLowercase(FString) const;
	bool IsIsogram(FString) const;
};