#pragma once

#include <iostream>
#include <string>
#include "TokenList.h"
#include "Parser.h"

class Calculator
{
public:
	Calculator(bool debug = false) 
		: debug(debug)
	{
		consoleExpression = new char[150];
		consoleSize = 150;

		system("title Proiect Calculator PO");
	}

	Calculator(int consoleSize, bool debug = false)
		: consoleSize(consoleSize), debug(debug)
	{
		consoleExpression = new char[consoleSize];

		system("title Proiect Calculator PO");
	}

	void run();
	void solveSequence(size_t lIndex, size_t rIndex);
	void solveCalculation(size_t index);
	double solveExpression();

	inline bool isActive()
	{
		return active;
	}

private:
	char*		consoleExpression = nullptr;
	size_t		consoleSize = 150;
	bool		active = true;
	bool		debug = false;
	TokenList	tokenList;
};
