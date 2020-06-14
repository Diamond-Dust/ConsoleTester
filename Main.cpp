#define _CRT_SECURE_NO_WARNINGS


#include<fstream>
#include<stdio.h>
#include<iostream>
#include "Questions.h"

enum class Action {
	END,
	FULL,
	ENDLESS, 
	RANDOM,
	CHANGE_LOCATION,
	CHANGE_CORRECT_SHOWING
};

void PrintStartingInfo();

void PrintInfo(Questions q);

void GetAction(Action* qType);

int main()
{
	Questions q{"./questions.txt"};

	Action action;
	PrintStartingInfo();
	while (true)
	{
		PrintInfo(q);
		GetAction(&action);
		if			(action == Action::END)
		{
			break;
		}
		else if		(action == Action::FULL)
		{
			q.FullQuestioning();
		}
		else if		(action == Action::ENDLESS)
		{
			q.EndlessQuestioning();
		}
		else if		(action == Action::RANDOM)
		{
			q.RandomQuestioning();
		}
		else if		(action == Action::CHANGE_LOCATION)
		{
			printf("Please enter the path to the desired file.\n"); 
			std::string path;
			std::cin.ignore();
			std::getline(std::cin, path);
			q = Questions{ path.c_str() };
		}
		else if		(action == Action::CHANGE_CORRECT_SHOWING)
		{
			q.ToggleShowingCorrectAnswer();
		}
	}

	return 0;
}

void PrintStartingInfo()
{
	printf("Welcome to the Console Tester.\n");
	printf("Made by Diamond Dust 31.01.2020\n");
	printf("Hope you find it useful.\n\n");

	printf("Instructions:\n");
	printf("Be sure that questions are in the same location as the .exe\n");
	printf("Question format:\n");
	printf("QUESTION1\n");
	printf(" Answer1.1\n");
	printf(" +Correct Answer1.2\n");
	printf(" Answer1.3\n");
	printf("QUESTION2\n");
	printf(" Answer2.1\n");
	printf(" Answer2.2\n");
	printf(" +Correct Answer2.3\n");
	printf(" Answer2.4\n");
	printf("etc.\n\n");
}

void PrintInfo(Questions q)
{
	printf("\nChoose your action:\n");
	printf("! - Quit the programme\n");
	printf("f - Full mode \t\t- programme will randomise the order and use each question once. Results outputted at the end.\n");
	printf("e - Endless mode \t- programme will randomise the order and use each question once, then repeat it. '!' ends. '%%' outputs results.\n");
	printf("r - Random mode \t- programme will randomise which question it shows, then repeat it. '!' ends. '%%' outputs results.\n");
	printf("l - Change location \t- load questions from another location.\n");
	printf("s - Toggle correct answer showing - By default, correct answers are not shown after answering. ");
	q.PrintShowingCorrectAnswer();
}

void GetAction(Action* action)
{
	char input;
	int scanfResult = scanf(" %c", &input);
	if (scanfResult > 0)
	{
		switch (input)
		{
			case '!':
				*action = Action::END;
				break;
			case 'f':
				*action = Action::FULL;
				break;
			case 'e':
				*action = Action::ENDLESS;
				break;
			case 'r':
				*action = Action::RANDOM;
				break;
			case 'l':
				*action = Action::CHANGE_LOCATION;
				break;
			case 's':
				*action = Action::CHANGE_CORRECT_SHOWING;
				break;
		}
	}
}