#include "Calculator.h"

bool Calculator::validParenthesis(const TokenList& tokenList)
{
	std::string stack = "";
	for (auto i = 0; i < tokenList.size(); ++i)
	{
		const auto& token = tokenList[i];
		if (token.type() == Token::Type::LeftParenthesis)
		{
			stack += token.string();
		}
		else if(token.type() == Token::Type::RightParenthesis)
		{
			if (stack.empty())
				return false;

			if (stack.back() != '(')
				return false;

			stack.pop_back();
		}
	}

	return stack.empty() ? true : false;
}

bool Calculator::validTokens(const TokenList& tokenList)
{
	for (auto i = 0; i < tokenList.size(); ++i)
	{
		const auto& token = tokenList[i];
		if (token.type() == Token::Type::Operator)
		{
			// First and last tokens cannot be operators
			if (i == 0 || i == tokenList.size() - 1)
				return false;

			// The prev token must be a number or right parenthesis
			const auto& prevToken = tokenList[i - 1];
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
			const auto& nextToken = tokenList[i + 1];
			if (nextToken.type() != Token::Type::Number && 
				nextToken.type() != Token::Type::LeftParenthesis)
				return false;
		}

		if (token.type() == Token::Type::Number)
		{
			if (i == tokenList.size() - 1)
				continue;

			// The next token must be an operator or right paranthesis
			const auto& nextToken = tokenList[i + 1];
			if (nextToken.type() != Token::Type::Operator &&
				nextToken.type() != Token::Type::RightParenthesis)
				return false;
		}
	}
	return true;
}

void Calculator::getTokens()
{
	if (strlen(consoleExpression) == 0)
		throw std::invalid_argument("CALCULATOR: No input given!");

	for (auto i = 0; i < strlen(consoleExpression); ++i)
	{
		const auto c = consoleExpression[i];
		if (isdigit(c))
		{
			const auto startIndex = i;
			while (isdigit(consoleExpression[i]) || consoleExpression[i] == '.')
				++i;

			const auto number = std::string(consoleExpression, startIndex, i - startIndex);
			tokenList += { Token::Type::Number, number };

			i -= 1;
		}
		else
		{
			auto type = Token::Type::Undefined;
			auto priority = 0;

			switch (c)
			{
			default:
				throw std::invalid_argument("CALCULATOR: Invalid expression was given!");
			case ' ':
				continue;
			case '(':
				type = Token::Type::LeftParenthesis;
				break;
			case ')':
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
}

void Calculator::solveCalculation(size_t index)
{
	const auto& token	= tokenList[index];
	auto leftNumber		= tokenList[index - 1].toDouble();
	auto rightNumber	= tokenList[index + 1].toDouble();

	long double result = 0;

	switch (token.string().at(0)) {
	default:
		throw std::invalid_argument("CALCULATOR: The given operator is invalid!");
	case '^':
		result = pow(leftNumber, rightNumber);
		break;
	case '#':
		result = pow(leftNumber, 1.0 / rightNumber);
		break;
	case '*':
		result = leftNumber * rightNumber;
		break;
	case '/':
		if (rightNumber == 0)
			throw std::invalid_argument("CALCULATOR: Cannot divide by 0!");
		result = leftNumber / rightNumber;
		break;
	case '+':
		result = leftNumber + rightNumber;
		break;
	case '-':
		result = leftNumber - rightNumber;
		break;
	}

	tokenList[index - 1] = { Token::Type::Number, std::to_string(result) };
	tokenList.remove(index, 2);
}

void Calculator::solveSequence(size_t lIndex, size_t rIndex)
{
	while (tokenList.existsOperators(lIndex, rIndex))
	{
		const auto index = tokenList.getPriorityOperator(lIndex, rIndex);
		solveCalculation(index);

		// Deleted 2 tokens from tokenList
		rIndex -= 2;
	}

	// Remove the parenthesis if the sequence was solved and had parenthesis
	if (tokenList[lIndex].type() == Token::Type::LeftParenthesis && 
		tokenList[rIndex].type() == Token::Type::RightParenthesis)
	{
		tokenList.remove(rIndex, 1);
		tokenList.remove(lIndex, 1);
	}
}

void Calculator::solveExpression()
{
	while (tokenList.existsParentheses())
	{
		auto leftParenthesis = 0;
		auto rightParenthesis = 0;
		for (auto i = 0; i < tokenList.size(); ++i)
		{
			const auto& token = tokenList[i];
			if (token.type() == Token::Type::LeftParenthesis)
			{
				leftParenthesis = i;
				continue;
			}
			if (token.type() == Token::Type::RightParenthesis)
			{
				rightParenthesis = i;
				break;
			}
		}

		solveSequence(leftParenthesis, rightParenthesis);
	}

	solveSequence(0, tokenList.size());

	std::cout << "Answer: " << tokenList[0].normalize() << '\n';
}

void Calculator::verifyExpression()
{
	if (!validParenthesis(tokenList))
		throw std::invalid_argument("CALCULATOR: Invalid parenthesis!");

	if(!validTokens(tokenList))
		throw std::invalid_argument("CALCULATOR: Invalid expression!");
}

void Calculator::replaceParenthesis()
{
	for (auto i = 0; i < strlen(consoleExpression); i++)
	{
		auto& chr = consoleExpression[i];
		if (chr == '[' || chr == '{')
			chr = '(';
		if (chr == ']' || chr == '}')
			chr = ')';
	}
}

void Calculator::run()
{
	gets_s(consoleExpression, consoleSize_);

	if (strcmp(consoleExpression, "exit") == 0)
	{
		active = false;
		return;
	}

	replaceParenthesis();

	try
	{
		getTokens();
		verifyExpression();
		solveExpression();
	}
	catch (const std::invalid_argument& exception)
	{
		std::cout << exception.what() << '\n';
	}

	tokenList.clear();
}