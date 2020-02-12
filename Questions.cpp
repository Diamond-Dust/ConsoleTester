#include "Questions.h"

Questions::Questions(std::string location)
{
	randomEngine = std::default_random_engine((unsigned) std::chrono::system_clock::now().time_since_epoch().count());

	qFileLocation			= location;
	qList					= std::vector<Question>();
	qListIndexes			= std::vector<unsigned int>();
	qCurrentIndex			= 0;
	qCurrentCorrect			= 0;
	qCurrentTotal			= 0;
	isShowingCorrectAnswer	= false;

	qFile.open(qFileLocation.c_str());
	if (!qFile.is_open())
	{
		printf("THERE HAS BEEN A PROBLEM WITH READING YOUR QUESTIONS FILE.\n");
		return;
	}

	ReadQuestions();
}

Questions::Questions(const Questions& other)
{
	randomEngine			= other.randomEngine;
	qFileLocation			= other.qFileLocation;
	qList					= other.qList;
	qListIndexes			= other.qListIndexes;
	qCurrentIndex			= other.qCurrentIndex;
	qCurrentCorrect			= other.qCurrentCorrect;
	qCurrentTotal			= other.qCurrentTotal;
	isShowingCorrectAnswer	= other.isShowingCorrectAnswer;

	qFile.open(qFileLocation.c_str());
	if (!qFile.is_open())
	{
		printf("THERE HAS BEEN A PROBLEM WITH READING YOUR QUESTIONS FILE.\n");
		return;
	}
}

Questions& Questions::operator=(const Questions& other)
{
	randomEngine			= other.randomEngine;
	qFileLocation			= other.qFileLocation;
	qList					= other.qList;
	qListIndexes			= other.qListIndexes;
	qCurrentIndex			= other.qCurrentIndex;
	qCurrentCorrect			= other.qCurrentCorrect;
	qCurrentTotal			= other.qCurrentTotal;
	isShowingCorrectAnswer	= other.isShowingCorrectAnswer;

	qFile.close();
	qFile.open(qFileLocation.c_str());
	if (!qFile.is_open())
	{
		printf("THERE HAS BEEN A PROBLEM WITH READING YOUR QUESTIONS FILE.\n");
		return *this;
	}

	return *this;
}

Questions::~Questions()
{
	qFile.close();
}

void Questions::ReadQuestions()
{
	std::string line;
	int currentIndex = -1;
	while (std::getline(qFile, line)) 
	{
		if (line[0] == ' ' || line[0] == '\t')
		{
			if (line[1] == '+')
			{
				qList[currentIndex].qAnswers.push_back(line.substr(2, std::string::npos));
				qList[currentIndex].qCorrectAnswerIndexes.push_back(true);
			}
			else
			{
				qList[currentIndex].qAnswers.push_back(line.substr(1, std::string::npos));
				qList[currentIndex].qCorrectAnswerIndexes.push_back(false);
			}
		}
		else
		{
			currentIndex++;
			qListIndexes.push_back((unsigned int)qList.size());
			qList.push_back(Question{});
			qList[currentIndex].qQuestion = line;
		}
	}
}

void Questions::ToggleShowingCorrectAnswer()
{
	isShowingCorrectAnswer = !isShowingCorrectAnswer;
	PrintShowingCorrectAnswer();
}

void Questions::PrintShowingCorrectAnswer()
{
	printf("Current status : % s.\n", (isShowingCorrectAnswer) ? "SHOWING" : "NOT SHOWING");
}

void Questions::RandomQuestioning()
{
	qCurrentCorrect = 0;
	qCurrentTotal = 0;
	qCurrentIndex = 0;

	bool wroteResults = false;
	Question q;
	std::string input;
	while (true)
	{
		input = "";
		if (!wroteResults)
		{
			q = RandomQuestion();
		}
		PrintQuestion(q);
		wroteResults = false;

		while (input.length() == 0)
		{
			std::getline(std::cin, input);
		}
		if (input.compare("!") == 0)
		{
			PrintResults();
			break;
		}
		else if (input.compare("%") == 0)
		{
			wroteResults = true;
			PrintResults();
		}
		else
		{
			CheckAnswer(input, q);
		}
	}
}

void Questions::FullQuestioning()
{
	qCurrentCorrect = 0;
	qCurrentTotal = 0;
	qCurrentIndex = 0;

	std::string input;
	ShuffleQuestions();
	while (qCurrentIndex < qList.size())
	{
		input = "";
		Question q = NextQuestion();
		PrintQuestion(q);

		while (input.length() == 0) 
		{
			std::getline(std::cin, input);
		}
		if (input.compare("!") == 0)
		{
			PrintResults();
			break;
		}
		else
		{
			CheckAnswer(input, q);
		}
	}
	qCurrentIndex = 0;
	PrintResults();
}

void Questions::EndlessQuestioning()
{
	qCurrentCorrect = 0;
	qCurrentTotal = 0;
	qCurrentIndex = 0;

	bool end = false;
	bool wroteResults = false;
	Question q;
	std::string input;
	while (true)
	{
		ShuffleQuestions();
		while (qCurrentIndex < qList.size())
		{
			input = "";
			if (!wroteResults)
			{
				q = NextQuestion();
			}
			PrintQuestion(q);
			wroteResults = false;

			while (input.length() == 0)
			{
				std::getline(std::cin, input);
			}
			if (input.compare("!") == 0)
			{
				PrintResults();
				end = true;
				break;
			}
			else if (input.compare("%") == 0)
			{
				PrintResults();
				wroteResults = true;
			}
			else
			{
				CheckAnswer(input, q);
			}
		}
		qCurrentIndex = 0;
		if (end)
		{
			break;
		}
	}
}

void Questions::ShuffleQuestions()
{
	std::shuffle(qListIndexes.begin(), qListIndexes.end(), randomEngine);
}

Question Questions::NextQuestion()
{
	return qList[qListIndexes[qCurrentIndex++]];
}

Question Questions::RandomQuestion()
{
	static std::uniform_int_distribution<> d{ 0, static_cast<unsigned char>(qList.size()-1) };
	int index = d(randomEngine);
	return qList[index];
}

void Questions::PrintQuestion(Question q)
{
	printf("%s\n", q.qQuestion.c_str());
	for (unsigned int i = 0; i < q.qAnswers.size(); i++)
	{
		printf("%s) %s\n", NumberToString(i).c_str(), q.qAnswers[i].c_str());
	}
}

void Questions::PrintResults()
{
	printf("|-----------\n");
	printf("Current result: %f%%.\n", ((double)qCurrentCorrect/(double)qCurrentTotal)*100. );
	printf("|-----------\n");
}

void Questions::PrintResult(bool correct, std::vector<bool> answers)
{
	if (correct)
	{
		printf("Good! Correct!\n");
	}
	else
	{
		printf("Sorry, incorrect.\n");
		if (isShowingCorrectAnswer)
		{
			unsigned int numberOfCorrectAnswers = count(answers.begin(), answers.end(), true);
			switch (numberOfCorrectAnswers) {
				case 0:
					printf("There was no correct answer in those given.\n");
					break;
				case 1:
					printf("Correct answer was: %s.\n", NumberToString(std::find(answers.begin(), answers.end(), true) - answers.begin()).c_str());
					break;
				deafult:
					printf("Correct answers were: ");
					for (int i = 0; i < answers.size(); i++)
					{
						if (answers[i])
						{
							printf("%s, ", NumberToString(i).c_str());
						}
					}
					printf("\b\b. \n");
					break;
			}
		}
	}
}

int Questions::StringToNumber(std::string s)
{
	int result = 0;
	bool earlyBreak = false;
	for (unsigned int i = 0; i < s.size()-1; i++)
	{
		if (s[i] == 'A' || s[i] == 'a')
		{
			result += 26;
		}
		else if ('A' <= s[i] && s[i] <= 'Z')
		{
			result += s[i] - 'A';
			earlyBreak = true;
			break;
		}
		else if ('a'<= s[i] && s[i] <= 'z')
		{
			result += s[i] - 'a';
			earlyBreak = true;
			break;
		}
	}
	if (!earlyBreak)
	{
		if ('A' <= s[s.size() - 1] && s[s.size() - 1] <= 'Z')
		{
			result += s[s.size() - 1] - 'A';
		}
		else if ('a' <= s[s.size() - 1] && s[s.size() - 1] <= 'z')
		{
			result += s[s.size() - 1] - 'a';
		}
	}

	return result;
}

std::string Questions::NumberToString(int n)
{
	std::string result;
	while (n > 25)
	{
		n -= 26;
		result += "A";
	}
	result += 'A' + n;

	return result;
}

void Questions::CheckAnswer(std::string answer, Question q)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(answer);
	while (std::getline(tokenStream, token, ' '))
	{
		tokens.push_back(token);
	}

	std::vector<bool> answerAssignment(q.qAnswers.size(), false);


	unsigned int numberOfCorrectCorrectAnswers		= 0;
	unsigned int numberOfCorrectIncorrectAnswers	= 0;
	unsigned int numberOfCorrectAnswers				= count(q.qCorrectAnswerIndexes.begin(), q.qCorrectAnswerIndexes.end(), true);
	unsigned int numberOfIncorrectAnswers			= q.qAnswers.size() - numberOfCorrectAnswers;
	
	for (int i = 0; i < tokens.size(); i++)
	{
		answerAssignment[StringToNumber(tokens[i])] = true;
	}

	for (int i = 0; i < answerAssignment.size(); i++)
	{
		if (answerAssignment[i] == q.qCorrectAnswerIndexes[i])
		{
			if (answerAssignment[i])
			{
				numberOfCorrectCorrectAnswers++;
			}
			else
			{
				numberOfCorrectIncorrectAnswers++;
			}
		}
	}

	double valueCorrect = std::min((double)numberOfCorrectCorrectAnswers / (double)numberOfCorrectAnswers, (double)numberOfCorrectIncorrectAnswers / (double)numberOfIncorrectAnswers);
	qCurrentCorrect += valueCorrect;
	qCurrentTotal++;

	PrintResult(valueCorrect == 1.0, q.qCorrectAnswerIndexes);
}
