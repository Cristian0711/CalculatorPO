#pragma once

#include <string>
#include <stack>
#include "Token.h"
#include "TokenList.h"

class Parser
{
public:
	Parser() = default;

	Parser(TokenList& tokenList, const std::string& consoleExpression)
	{
		getTokens(tokenList, consoleExpression);
	}

	void getTokens(TokenList& tokenList, const std::string& consoleExpression) const;

private:
	static bool processNumbers(TokenList& tokenList, const std::string& consoleExpression, size_t& index);
	static void processOperators(TokenList& tokenList, const char& c);
	static bool processUnaryOperator(TokenList& tokenList, const char& c);

	static bool validParenthesis(const TokenList& tokenList);
	static bool validTokens(const TokenList& tokenList);
};

