#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <string_view>
#include "TokenList.h"
#include "Parser.h"
#include "GUI.h"
#include "Exceptions.h"
#include "VariableList.h"

class Calculator
{
public:
	Calculator(bool debug = false)
		: debug(debug)
	{
		//system("title Proiect Calculator PO");
	}

	inline bool isActive() const
	{
		return active;
	}

	void			handleConsoleExpression();
	void			handleFileExpression(bool saveToFile);
	void			handleLoadVariables();
	void			handleSaveVariables();
	
	Token			solve(std::string_view expression);
	void			run(std::string_view expression);
	const Token&	solveExpression();
	Token			solveTheCalculation(const Token* token) const;

private:
	std::string		calculatorMode;
	bool			active = true;
	bool			debug = false;

	TokenList		tokenList;
	VariableList	variableList;
};
