#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "TokenList.h"
#include "Parser.h"
#include "GUI.h"

#define DEFAULT_CALCULATOR_MODE_SIZE 10

class Calculator
{
public:
	Calculator(bool debug = false)
		: debug(debug)
	{
		calculatorMode = new char[calculatorModeSize];
		system("title Proiect Calculator PO");
	}

	Calculator(size_t calculatorModeSize, bool debug = false)
		: calculatorModeSize(calculatorModeSize), debug(debug)
	{
		calculatorMode = new char[calculatorModeSize];

		system("title Proiect Calculator PO");
	}

	inline bool isActive() const
	{
		return active;
	}

	void			handleConsoleExpression();
	void			handleFileExpression(bool saveToFile);

	Token			solve(const std::string& expression);
	void			run(const char* expression = nullptr);
	const Token&	solveExpression();
	Token			solveTheCalculation(Token* token) const;

private:
	char*			calculatorMode = nullptr;
	bool			active = true;
	bool			debug = false;
	TokenList		tokenList;
	const size_t	calculatorModeSize = DEFAULT_CALCULATOR_MODE_SIZE;
};
