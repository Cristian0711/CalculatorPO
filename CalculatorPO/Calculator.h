#pragma once

#include <iostream>
#include <string>
#include "TokenList.h"

class Calculator
{
public:
	Calculator(int consoleSize = 100)
	{
		consoleExpression = new char[consoleSize];
		consoleSize_ = consoleSize;

		system("title Proiect Calculator PO");
	}

	Calculator(const std::string& consoleTitle, int consoleSize = 100)
	{
		consoleExpression = new char[consoleSize];
		consoleSize_ = consoleSize;

		const std::string title = "title " + consoleTitle;
		system(title.c_str());
	}

	void run();
	void getTokens();
	void solveSequence(int lIndex, int rIndex);
	void solveCalculation(int index);
	void solveExpression();

	inline bool isActive()
	{
		return active;
	}

private:
	char*		consoleExpression = nullptr;
	int			consoleSize_ = 100;
	bool		active = true;
	TokenList	tokenList;
};
