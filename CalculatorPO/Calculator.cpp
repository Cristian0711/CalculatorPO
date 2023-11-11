#include "Calculator.h"

bool Calculator::validParenthesis(TokenList& tokenList)
{
	std::string stack = "";
	for (auto i = 0; i < tokenList.size(); i++)
	{
		auto& token = tokenList[i];
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

bool Calculator::validOperators(TokenList& tokenList)
{
	for (auto i = 0; i < tokenList.size(); i++)
	{
		auto& token = tokenList[i];
		if (token.type() == Token::Type::Operator)
		{
			// First token cannot be an operator
			if (i == 0)
				return false;

			// The prev token must be a number or right parenthesis
			auto& prevToken = tokenList[i - 1];
			if (prevToken.type() != Token::Type::Number &&
				prevToken.type() != Token::Type::RightParenthesis)
				return false;
		}

		if (token.type() == Token::Type::Number)
		{
			if (i == tokenList.size() - 1)
				continue;

			// The next token must be an operator or right paranthesis
			auto& nextToken = tokenList[i + 1];
			if (nextToken.type() != Token::Type::Operator &&
				nextToken.type() != Token::Type::RightParenthesis)
				return false;
		}
	}
	return true;
}

void Calculator::solveSequence(int lIndex, int rIndex)
{
	for (auto i = lIndex + 1; i < rIndex; i++)
	{
		auto& token = tokenList[i];

		if (token.type() != Token::Type::Operator)
			continue;

		// Search for operator that has the biggest priority in that parenthesis
		if (token.priority() != tokenList.getMaxPriority(lIndex, rIndex))
			continue;

		solveCalculation(i);
		break;
	}
}

void Calculator::solveCalculation(int index)
{
	auto& token = tokenList[index];
	auto leftNumber = tokenList[index - 1].toDouble();
	auto rightNumber = tokenList[index + 1].toDouble();

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

	for (auto i = 0; i < tokenList.size(); i++)
	{
		std::cout << tokenList[i];
	}
	std::cout << '\n';
}

void Calculator::getTokens()
{
	if(strlen(consoleExpression) == 0)
		throw std::invalid_argument("CALCULATOR: No input given!");

	for (auto i = 0; i < strlen(consoleExpression); i++)
	{
		const auto c = consoleExpression[i];
		if (isdigit(c))
		{
			const auto startIndex = i;
			while (isdigit(consoleExpression[i]) || consoleExpression[i] == '.')
				i++;

			const auto number = std::string(consoleExpression, startIndex, i - startIndex);
			tokenList += { Token::Type::Number, number };

			i -= 1;
		}
		else
		{
			auto type = Token::Type::Undefined;
			auto priority = -1;

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

void Calculator::solveExpression()
{
	while (tokenList.existsParentheses())
	{
		auto leftParenthesis = -1;
		auto rightParenthesis = -1;
		for (auto i = 0; i < tokenList.size(); i++)
		{
			auto& token = tokenList[i];
			if (token.type() == Token::Type::LeftParenthesis)
			{
				// Verify if the parenthesis was solved
				if (tokenList[i + 2].type() == Token::Type::RightParenthesis)
				{
					// Remove second parenthesis
					tokenList.remove(i + 2, 1);

					// Remove first parenthesis
					tokenList.remove(i, 1);
					break;
				}

				leftParenthesis = i;
				continue;
			}
			if (token.type() == Token::Type::RightParenthesis)
			{
				rightParenthesis = i;
				break;
			}
		}

		if (leftParenthesis != -1 && rightParenthesis != -1)
		{
			solveSequence(leftParenthesis, rightParenthesis);
		}
	}

	while (tokenList.size() != 1)
	{
		solveSequence(0, tokenList.size());
	}

	std::cout << "Answer: " << tokenList[0].normalize() << '\n';
}

void Calculator::verifyExpression()
{
	if (!validParenthesis(tokenList))
		throw std::invalid_argument("CALCULATOR: Invalid parenthesis!");

	if(!validOperators(tokenList))
		throw std::invalid_argument("CALCULATOR: Invalid expression!");
}

void Calculator::run()
{
	gets_s(consoleExpression, consoleSize_);

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