#pragma once

#include <iostream>
#include <string>
#include "TokenList.h"
#include "Parser.h"

#define DEFAULT_CONSOLE_SIZE 300

class Calculator
{
public:
	Calculator(bool debug = false) 
		: debug(debug)
	{
		consoleExpression = new char[consoleSize];
		system("title Proiect Calculator PO");
	}

	Calculator(size_t consoleSize, bool debug = false)
		: consoleSize(consoleSize), debug(debug)
	{
		consoleExpression = new char[consoleSize];

		system("title Proiect Calculator PO");
	}

	void			run();
	void			solveSequence(size_t lIndex, size_t rIndex);
	Token			solveCalculation(size_t index);
	const Token& solveExpression();

	inline bool isActive()
	{
		return active;
	}

private:
	char*			consoleExpression = nullptr;
	bool			active = true;
	bool			debug = false;
	TokenList		tokenList;
	const size_t	consoleSize = DEFAULT_CONSOLE_SIZE;
};
