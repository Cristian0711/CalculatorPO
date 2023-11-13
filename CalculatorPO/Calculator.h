#pragma once

#include <iostream>
#include <string>
#include "TokenList.h"

class Calculator
{
public:
	Calculator(int consoleSize = 150)
	{
		consoleExpression = new char[consoleSize];
		consoleSize_ = consoleSize;

		system("title Proiect Calculator PO");
	}

	Calculator(const std::string& consoleTitle, int consoleSize = 150)
	{
		consoleExpression = new char[consoleSize];
		consoleSize_ = consoleSize;

		const std::string title = "title " + consoleTitle;
		system(title.c_str());
	}

	void run();
	void getTokens();
	void solveSequence(size_t lIndex, size_t rIndex);
	void solveCalculation(size_t index);
	void solveExpression();
	void verifyExpression();

	static bool validParenthesis(TokenList& tokenList);
	static bool validTokens(TokenList& tokenList);

	inline bool isActive()
	{
		return active;
	}

private:
	char*		consoleExpression = nullptr;
	size_t		consoleSize_ = 150;
	bool		active = true;
	TokenList	tokenList;
};
