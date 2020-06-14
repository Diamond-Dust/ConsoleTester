#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include<iostream>
#include <sstream>

struct Question {
	std::string					qQuestion;
	std::vector<std::string>	qAnswers;
	std::vector<int>			qAnswerIndexes;
	std::vector<bool>			qCorrectAnswerIndexes;
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
		double						qCurrentCorrect;
		double						qCurrentTotal;
		bool						isShowingCorrectAnswer;

		void ReadQuestions();
		void ShuffleQuestions();

		void ShuffleAnswers(Question& q);

		Question NextQuestion();
		Question RandomQuestion();

		void PrintQuestion(Question q);
		void PrintResults();
		void PrintResult(bool correct, std::vector<bool> answers);

		int StringToNumber(std::string s);
		std::string NumberToString(int n);

		void CheckAnswer(std::string answer, Question q);
};