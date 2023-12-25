#include "Parser.h"

bool Parser::validParenthesis(const TokenList& tokenList)
{
	std::string stack = "";
	Token* token = tokenList.front();

	while (token != nullptr)
	{
		if (token->type() == Token::Type::LeftParenthesis)
		{
			stack += token->string();
		}
		else if (token->type() == Token::Type::RightParenthesis)
		{
			if (stack.empty())
				return false;

			const char& c = token->string().at(0);
			if (c == ')' && stack.back() != '(' ||
				c == ']' && stack.back() != '[' ||
				c == '}' && stack.back() != '{')
				return false;

			stack.pop_back();
		}

		token = token->next();
	}

	return stack.empty();
}

bool Parser::validTokens(const TokenList& tokenList)
{
	if (tokenList.empty())
		return false;

	Token* token = tokenList.front();
	while (token != nullptr)
	{
		if (token->type() == Token::Type::Operator)
		{
			// First and last tokens cannot be operators
			if (token == tokenList.front() || token == tokenList.back())
				return false;

			// The prev token must be a number or right parenthesis
			const Token* prevToken = token->prev();
			if (prevToken->type() != Token::Type::Number &&
				prevToken->type() != Token::Type::RightParenthesis)
				return false;
		}

		if (token->type() == Token::Type::LeftParenthesis)
		{
			// Last token cannot be an left parenthesis
			if (token == tokenList.back())
				return false;

			// The next token must be a number
			const Token* nextToken = token->next();
			if (nextToken->type() != Token::Type::Number &&
				nextToken->type() != Token::Type::LeftParenthesis)
				return false;
		}

		if (token->type() == Token::Type::Number)
		{
			if (token == tokenList.back())
				break;

			// The next token must be an operator or right paranthesis
			const Token* nextToken = token->next();
			if (nextToken->type() != Token::Type::Operator &&
				nextToken->type() != Token::Type::RightParenthesis)
				return false;
		}
		token = token->next();
	}

	return true;
}

void Parser::getTokens(TokenList& tokenList, const std::string& consoleExpression) const
{
	if (consoleExpression.length() == 0)
		throw std::exception("CALCULATOR: No input given!");

	bool hasUnary = false;
	for (int i = 0; i < consoleExpression.length(); ++i)
	{
		const char& c = consoleExpression[i];
		if (isdigit(c))
		{
			// If it has a sign the start index must be modified
			const size_t startIndex = hasUnary ? i - 1 : i;
			while (i < consoleExpression.length() && isdigit(consoleExpression[i]) || consoleExpression[i] == '.')
				++i;

			const std::string number = std::string(consoleExpression, startIndex, i - startIndex);
			tokenList += { Token::Type::Number, number };

			hasUnary = false;
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

			// Do not add the '-/+' to the token list if it's an unary operator
			if (tokenList.empty() && (c == '-' || c == '+'))
			{
				hasUnary = true;
				continue;
			}

			// Used to work with parenthesis '(-30)/(+30)'
			if (!tokenList.empty() &&
				tokenList.back()->type() == Token::Type::LeftParenthesis && (c == '-' || c == '+'))
			{
				hasUnary = true;
				continue;
			}

			tokenList += { type, std::string(1, c), priority };
		}
	}

	if (!validParenthesis(tokenList))
		throw std::exception("CALCULATOR: Invalid parenthesis!");

	if (!validTokens(tokenList))
		throw std::exception("CALCULATOR: Invalid expression!");
}