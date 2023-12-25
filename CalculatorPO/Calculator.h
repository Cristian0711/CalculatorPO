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

	inline bool isActive() const
	{
		return active;
	}

	void			run();
	Token			solveCalculation(const Token* token) const;
	const Token& solveExpression();

private:
	char* consoleExpression = nullptr;
	bool			active = true;
	bool			debug = false;
	TokenList		tokenList;
	const size_t	consoleSize = DEFAULT_CONSOLE_SIZE;
};
