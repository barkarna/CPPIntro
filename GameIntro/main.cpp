// Test Game program

#include "LettersGame.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>


FLettersGame TheGame;	// instantiate new LetterGame
HANDLE ConsoleCLR;

std::vector<FString> AllWords();
FString GetAnswer(FString);
void BeginPlay(FString);
bool AskReplay();
void GameIntro();
void GameSessionSummary(FString, int32);
void GameTrySummary(FString, int32);
int Check(FString, FString);
void Color(int32);

int main()
{
	srand(time(0));
	ConsoleCLR = GetStdHandle(STD_OUTPUT_HANDLE);
	AllWords();
	int32 j = 1;
	
	bool bPlayAgain = false;
	FString HiddenWord = "unreal";

	GameIntro();

	do
	{
		j = 1 + rand() % (AllWords().size() - 1);
		HiddenWord = AllWords()[j];
		BeginPlay(HiddenWord);

		bPlayAgain = AskReplay();
	} while (bPlayAgain);
	return 0;
}

void BeginPlay(FString CurrentHiddenWord)
{
	int32 ResultCount = 0;
	TheGame.Reset();

	while (!TheGame.IsGameWon(CurrentHiddenWord, ResultCount) && TheGame.GetCurrentTry() <= TheGame.GetMaxTries())
	{
		FString Answer = GetAnswer(CurrentHiddenWord);
		ResultCount = Check(CurrentHiddenWord, Answer);

		GameTrySummary(CurrentHiddenWord, ResultCount);
	}
	GameSessionSummary(CurrentHiddenWord, ResultCount);
}

std::vector<FString> AllWords()
{
	FString SetHiddenWord;
	bool res;
	std::ifstream fin("nouns_with_6_letters.txt");
	std::vector<FString> str;
	FString s;

	if (!fin.is_open())
	{
		//std::cout << "ERROR" << std::endl;
		res = false;
	}
	else
	{
		
		while (!fin.eof())
		{
			fin >> s;
			str.push_back(s);
		}
		//std::cout << "OK" << std::endl;
		res = true;
	}
	fin.close();

	return str;
	//return res;
}

FString GetAnswer(FString CurrentHiddenWord)
{
	FString Response = "";
	EWordStatus Status = EWordStatus::None;

	// TODO response 
	do
	{
		std::cout << "\n" << TheGame.GetCurrentTry() << ") ENTER THE WORD: ";
		getline(std::cin, Response);

		Status = TheGame.ValidateAnswer(CurrentHiddenWord, Response);

		// TODO response
		switch (Status)
		{
		case EWordStatus::Wrong_Length:
		{
			Color(12);
			std::cout << "  TRY AGAIN (wrong length)\n";
			Color(15);
			break;
		}
		case EWordStatus::Not_Lowercase:
		{
			Color(12);
			std::cout << "  TRY AGAIN (wrong capitalization)\n";
			Color(15);
			break;
		}
			
		case EWordStatus::Not_Isogram:
		{
			Color(12);
			std::cout << "  TRY AGAIN (without repeated letters)\n";
			Color(15);
			break;
		}
		default:
			std::cout << "\t";
		}
	} while (Status != EWordStatus::OK);		// keep trying untill success

	return Response;
}

int Check(FString CurrentHiddenWord, FString Answer)
{
	int res = 0;
	int32 CLR = 15;

	for (int32 i = 0; i < TheGame.GetHiddenWordLength(CurrentHiddenWord); i++)
	{
		char Letter = Answer[i];
		CLR = TheGame.CommitAnswer(CurrentHiddenWord, Letter, i);
		if (CLR == 47) 
			res++;
		Color(CLR);
		std::cout << "  " << Letter << "  ";
		CLR = 15;
		Color(CLR);
	}
	std::cout << "\n";
	TheGame.ChangeCurrentTry();

	return res;
}

bool AskReplay()
{
	std::cout << "\n\nWould you like to play it again? (y/n): ";
	FText Responce = "";
	std::getline(std::cin, Responce);
	return (tolower(Responce[0]) == 'y');
}

void GameIntro()
{
	system("cls");

	Color(15);	std::cout << "\t\t\t";  Color(159);  std::cout << "<<<<<<<< LETTERS GAME >>>>>>>>";  Color(15);  std::cout << " \n\n";
	Color(159);	std::cout << "RULES:";  Color(15);  std::cout << " You have 6 tries only to guess 6 letter ";  Color(6);  std::cout << "noun";  Color(15); std::cout << "!\n";
	Color(79);	std::cout << "IMPORTANT!";  Color(15);  std::cout << " The word consists of ";  Color(6);  std::cout << "different";  Color(15);  std::cout<< " letters\n\n";
	Color(47);	std::cout << "GREEN LETTER";	Color(15);  std::cout << " - ";  Color(2);  std::cout << "right";  Color(15);  std::cout << " letter and ";
		Color(2);	std::cout << "right"; Color(15);  std::cout << " position\n";
	Color(111);	std::cout << "YELLOW LETTER";  Color(15);  std::cout << " - ";  Color(2);  std::cout << "right"; Color(15);  std::cout << " letter but ";
		Color(12);  std::cout << "wrong";  Color(15);  std::cout << " position\n\n";
	
	return;
}

void GameSessionSummary(FString CurrentHiddenWord, int32 ResultCount)
{
	// TODO Summary for WHOLE game session
	if (TheGame.IsGameWon(CurrentHiddenWord, ResultCount))
	{
		std::cout << "\n\n\t\t\t\t";
		Color(47);
		std::cout << "(=   CONGRATULATIONS, YOU WON!!!   =)";
		Color(15);
	}
	else
	{
		std::cout << "\n\n\t\t\t\t";
		Color(79);  
		std::cout << ")=   SORRY, YOU LOSE...   =(";
		Color(15);
		std::cout << "\n\n\tYour word was ";
		Color(79);
		std::cout << CurrentHiddenWord;
		Color(15);
	}
	return;
}

void GameTrySummary(FString CurrentHiddenWord, int32 ResultCount)
{

	if (TheGame.GetCurrentTry() < TheGame.GetMaxTries() && ResultCount != TheGame.GetHiddenWordLength(CurrentHiddenWord))
	{
		Color(6);
		std::cout << "  <" << TheGame.GetMaxTries() - TheGame.GetCurrentTry() + 1 << ">" << " attempts left\n";
		Color(15);
	}
	else if (TheGame.GetCurrentTry() == TheGame.GetMaxTries() && ResultCount != TheGame.GetHiddenWordLength(CurrentHiddenWord))
	{
		Color(12);
		std::cout << "  The last attempt!\n";
		Color(15);
	}
		
	return;
}

void Color(int32 CLR)
{
	SetConsoleTextAttribute(ConsoleCLR, CLR);

	return;
}