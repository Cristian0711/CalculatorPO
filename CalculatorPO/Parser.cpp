#include "Parser.h"

bool Parser::validParenthesis(const TokenList& tokenList)
{
	std::string stack = "";
	for (int i = 0; i < tokenList.size(); ++i)
	{
		const Token& token = tokenList[i];
		if (token.type() == Token::Type::LeftParenthesis)
		{
			stack += token.string();
		}
		else if (token.type() == Token::Type::RightParenthesis)
		{
			if (stack.empty())
				return false;

			const char& c = token.string().at(0);
			if (c == ')' && stack.back() != '(' ||
				c == ']' && stack.back() != '[' ||
				c == '}' && stack.back() != '{')
				return false;

			stack.pop_back();
		}
	}

	return stack.empty() ? true : false;
}

bool Parser::validTokens(const TokenList& tokenList)
{
	for (int i = 0; i < tokenList.size(); ++i)
	{
		const Token& token = tokenList[i];
		if (token.type() == Token::Type::Operator)
		{
			// First and last tokens cannot be operators
			if (i == 0 || i == tokenList.size() - 1)
				return false;

			// The prev token must be a number or right parenthesis
			const Token& prevToken = tokenList[i - 1];
			if (prevToken.type() != Token::Type::Number &&
				prevToken.type() != Token::Type::RightParenthesis)
				return false;
		}

		if (token.type() == Token::Type::LeftParenthesis)
		{
			// Last token cannot be an left parenthesis
			if (i == tokenList.size() - 1)
				return false;

			// The next token must be a number
			const Token& nextToken = tokenList[i + 1];
			if (nextToken.type() != Token::Type::Number &&
				nextToken.type() != Token::Type::LeftParenthesis)
				return false;
		}

		if (token.type() == Token::Type::Number)
		{
			if (i == tokenList.size() - 1)
				continue;

			// The next token must be an operator or right paranthesis
			const Token& nextToken = tokenList[i + 1];
			if (nextToken.type() != Token::Type::Operator &&
				nextToken.type() != Token::Type::RightParenthesis)
				return false;
		}
	}
	return true;
}

void Parser::getTokens(TokenList& tokenList, const std::string& consoleExpression)
{
	if (consoleExpression.length() == 0)
		throw std::exception("CALCULATOR: No input given!");

	for (int i = 0; i < consoleExpression.length(); ++i)
	{
		const char& c = consoleExpression[i];
		if (isdigit(c))
		{
			const size_t startIndex = i;
			while (isdigit(consoleExpression[i]) || consoleExpression[i] == '.')
				++i;

			const std::string number = std::string(consoleExpression, startIndex, i - startIndex);
			tokenList += { Token::Type::Number, number };

			i -= 1;
		}
		else
		{
			Token::Type type = Token::Type::Undefined;
			unsigned int priority = 0;

			switch (c)
			{
			default:
				throw std::exception("CALCULATOR: Invalid expression was given!");
			case ' ':
				continue;
			case '(':
				type = Token::Type::LeftParenthesis;
				break;
			case '[':
				type = Token::Type::LeftParenthesis;
				break;
			case '{':
				type = Token::Type::LeftParenthesis;
				break;
			case ')':
				type = Token::Type::RightParenthesis;
				break;
			case ']':
				type = Token::Type::RightParenthesis;
				break;
			case '}':
				type = Token::Type::RightParenthesis;
				break;
			case '^':
				type = Token::Type::Operator;
				priority = 4;
				break;
			case '#':
				type = Token::Type::Operator;
				priority = 4;
				break;
			case '*':
				type = Token::Type::Operator;
				priority = 3;
				break;
			case '/':
				type = Token::Type::Operator;
				priority = 3;
				break;
			case '+':
				type = Token::Type::Operator;
				priority = 2;
				break;
			case '-':
				type = Token::Type::Operator;
				priority = 2;
				break;
			}

			if (type != Token::Type::Undefined)
				tokenList += { type, std::string(1, c), priority };
		}
	}

	if (!validParenthesis(tokenList))
		throw std::exception("CALCULATOR: Invalid parenthesis!");

	if (!validTokens(tokenList))
		throw std::exception("CALCULATOR: Invalid expression!");
}
