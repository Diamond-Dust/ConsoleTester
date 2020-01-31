#pragma once
#include<string>
#include<fstream>
#include<vector>
#include <algorithm>
#include <random>
#include <chrono>
#include<iostream>

struct Question {
	std::string					qQuestion;
	std::vector<std::string>	qAnswers;
	int							qCorrectAnswerIndex;
};

class Questions {
	public:
		Questions(std::string location);
		Questions(const Questions & other);
		Questions& operator=(const Questions & other);
		~Questions();

		void ToggleShowingCorrectAnswer();
		void PrintShowingCorrectAnswer();

		void FullQuestioning();
		void RandomQuestioning();
		void EndlessQuestioning();

	private:
		std::default_random_engine	randomEngine;

		std::string					qFileLocation;
		std::ifstream				qFile;
		std::vector<Question>		qList;
		std::vector<unsigned int>	qListIndexes;
		unsigned int				qCurrentIndex;
		unsigned int				qCurrentCorrect;
		unsigned int				qCurrentTotal;
		bool						isShowingCorrectAnswer;

		void ReadQuestions();
		void ShuffleQuestions();

		Question NextQuestion();
		Question RandomQuestion();

		void PrintQuestion(Question q);
		void PrintResults();
		void PrintResult(bool correct, unsigned int correctIndex);

		int StringToNumber(std::string s);
		std::string NumberToString(int n);
};