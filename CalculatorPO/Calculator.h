#pragma once

#include <iostream>
#include <string>
#include "TokenList.h"

class Calculator
{
public:
	Calculator()
	{
		system("title Proiect Calculator PO");
	}

	Calculator(const std::string& consoleTitle)
	{
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
	std::string consoleExpression	= "";
	bool		active				= true;
	TokenList	tokenList;
};

