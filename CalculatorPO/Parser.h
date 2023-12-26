#pragma once

#include <string>
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

	static bool validParenthesis(const TokenList& tokenList);
	static bool validTokens(const TokenList& tokenList);
};

