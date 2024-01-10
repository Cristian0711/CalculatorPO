#include "Parser.h"
#include <stack>

bool Parser::validParenthesis(const TokenList& tokenList)
{
	std::stack<char> stack;

	Token*		token = tokenList.front();
	while (token != nullptr)
	{
		if (token->type() == Token::Type::LeftParenthesis)
		{
			stack.push(token->string().at(0));
		}
		else if (token->type() == Token::Type::RightParenthesis)
		{
			if (stack.empty())
				return false;

			const char& c = token->string().at(0);
			if (c == ')' && stack.top() != '(' ||
				c == ']' && stack.top() != '[' ||
				c == '}' && stack.top() != '{')
				return false;

			stack.pop();
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

			// The next token must be a number or left parenthesis
			const Token* nextToken = token->next();
			if (nextToken->type() != Token::Type::Number &&
				nextToken->type() != Token::Type::LeftParenthesis)
				return false;
		}

		if (token->type() == Token::Type::RightParenthesis)
		{
			if (token == tokenList.back())
				break;

			// The next token must be an operator or right parenthesis
			const Token* nextToken = token->next();
			if (nextToken->type() != Token::Type::Operator &&
				nextToken->type() != Token::Type::RightParenthesis)
				return false;
		}

		if (token->type() == Token::Type::Number)
		{
			if (token == tokenList.back())
				break;

			// The next token must be an operator or right parenthesis
			const Token* nextToken = token->next();
			if (nextToken->type() != Token::Type::Operator &&
				nextToken->type() != Token::Type::RightParenthesis)
				return false;
		}
		token = token->next();
	}

	return true;
}

bool Parser::processNumbers(TokenList& tokenList, const std::string& consoleExpression, size_t& index)
{
	const size_t startIndex = index;
	bool hasDecimalPoint = false;

	index++;
	while (index < consoleExpression.length() && isdigit(consoleExpression[index]) || consoleExpression[index] == '.')
	{
		if (consoleExpression[index] == '.' && hasDecimalPoint)
			throw InvalidNumber();

		if (consoleExpression[index] == '.')
			hasDecimalPoint = true;

		++index;
	}

	const std::string number = std::string(consoleExpression, startIndex, index - startIndex);
	tokenList += { Token::Type::Number, number };

	index -= 1;

	return true;
}

// Do not add the '-/+' to the token list if it's an unary operator '(-30)/(+30)' / '-30/+30'
bool Parser::processUnaryOperator(TokenList& tokenList, const char& c)
{
	if ((c == '-' || c == '+') &&
		(tokenList.empty() || tokenList.back()->type() == Token::Type::LeftParenthesis))
		return true;

	return false;
}

void Parser::processOperators(TokenList& tokenList, const char& c)
{
	Token::Type type = Token::Type::Undefined;
	unsigned int priority = 0;

	switch (c)
	{
	default:
		throw InvalidExpression();
	case ' ':
		return;
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
		priority = 3;
		break;
	case '#':
		type = Token::Type::Operator;
		priority = 3;
		break;
	case '*':
		type = Token::Type::Operator;
		priority = 2;
		break;
	case '/':
		type = Token::Type::Operator;
		priority = 2;
		break;
	case '+':
		type = Token::Type::Operator;
		priority = 1;
		break;
	case '-':
		type = Token::Type::Operator;
		priority = 1;
		break;
	}

	tokenList += { type, std::string(1, c), priority };
}

void Parser::getTokens(TokenList& tokenList, const std::string& consoleExpression) const
{
	if (consoleExpression.length() == 0)
		throw std::exception("CALCULATOR: No input given!");

	for (size_t i = 0; i < consoleExpression.length(); ++i)
	{
		const char& c = consoleExpression[i];

		bool hasUnary = processUnaryOperator(tokenList, c);

		if (isdigit(c) || hasUnary)
		{
			processNumbers(tokenList, consoleExpression, i);
			hasUnary = false;
		}
		else
		{
			processOperators(tokenList, c);
		}
	}

	if (!validParenthesis(tokenList))
		throw InvalidParenthesis();

	if (!validTokens(tokenList))
		throw InvalidMathExpression();
}