#pragma once

#include <string>
#include "Token.h"
#include "TokenList.h"

class Parser
{
public:
	Parser()
	{

	}

	Parser(TokenList& tokenList, const std::string& consoleExpression)
	{
		getTokens(tokenList, consoleExpression);
	}

	void getTokens(TokenList& tokenList, const std::string& consoleExpression) const;

	static bool validTokens(const TokenList& tokenList);
	static bool validParenthesis(const TokenList& tokenList);
};

