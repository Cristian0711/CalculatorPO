#pragma once

#include <string>
#include <stack>
#include <ranges>
#include <algorithm>
#include <regex>
#include "Token.h"
#include "TokenList.h"
#include "VariableList.h"
#include "Exceptions.h"

class Parser
{
public:
	Parser() = default;

	Parser(TokenList& tokenList, const VariableList& variableList, std::string_view consoleExpression)
	{
		getTokens(tokenList, variableList, consoleExpression);
	}

	bool hasVariable() const
	{
		return hasVariable_;
	}

	std::string_view variableName() const
	{
		return variableName_;
	}

	void setVariableValue(std::string_view value)
	{
		variableValue = value;
	}

	void getTokens(TokenList& tokenList, const VariableList& variableList, std::string_view consoleExpression);

private:
	void		assignVariable(std::string_view expression, size_t& index);

	static void processNumbers(TokenList& tokenList, std::string_view consoleExpression, size_t& index);
	static void processVariable(TokenList& tokenList, const VariableList& variableList, std::string_view consoleExpression, size_t& index);
	static void processOperators(TokenList& tokenList, const char& c);
	static bool processUnaryOperator(TokenList& tokenList, const char& c);

	static bool validParenthesis(const TokenList& tokenList);
	static bool validTokens(const TokenList& tokenList);

	bool		hasVariable_ = false;
	std::string variableName_;
	std::string variableValue;
};

