#include "Calculator.h"

bool Calculator::validParenthesis(const TokenList& tokenList)
{
	std::string stack = "";
	for (int i = 0; i < tokenList.size(); ++i)
	{
		const Token& token = tokenList[i];
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

void Calculator::getTokens()
{
	if (strlen(consoleExpression) == 0)
		throw std::invalid_argument("CALCULATOR: No input given!");

	for (int i = 0; i < strlen(consoleExpression); ++i)
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
	const Token& token			= tokenList[index];
	const Token& leftToken		= tokenList[index - 1];
	const Token& rightToken		= tokenList[index + 1];

	Token result;

	switch (token.string().at(0)) {
	default:
		throw std::invalid_argument("CALCULATOR: The given operator is invalid!");
	case '^':
		result = pow(leftToken, rightToken);
		break;
	case '#':
		result = pow(leftToken, 1.0 / rightToken);
		break;
	case '*':
		result = leftToken * rightToken;
		break;
	case '/':
		if (rightToken == 0)
			throw std::invalid_argument("CALCULATOR: Cannot divide by 0!");
		result = leftToken / rightToken;
		break;
	case '+':
		result = leftToken + rightToken;
		break;
	case '-':
		result = leftToken - rightToken;
		break;
	}

	for (int i = 0; i < tokenList.size(); i++)
	{
		std::cout << tokenList[i];
	}
	std::cout << '\n';

	tokenList[index - 1] = result;
	tokenList.remove(index, 2);
}

void Calculator::solveSequence(size_t lIndex, size_t rIndex)
{
	while (tokenList.existsOperators(lIndex, rIndex))
	{
		const size_t index = tokenList.getPriorityOperator(lIndex, rIndex);
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
		unsigned int leftParenthesis = 0;
		unsigned int rightParenthesis = 0;
		for (int i = 0; i < tokenList.size(); ++i)
		{
			const Token& token = tokenList[i];
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

	std::cout << "Answer: " << tokenList[0] << '\n';
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
	for (int i = 0; i < strlen(consoleExpression); ++i)
	{
		char& chr = consoleExpression[i];
		if (chr == '[' || chr == '{')
			chr = '(';
		if (chr == ']' || chr == '}')
			chr = ')';
	}
}

void Calculator::run()
{
	std::cin.getline(consoleExpression, consoleSize_);
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(LLONG_MAX, '\n');
		throw std::invalid_argument("CALCULATOR: The sequence is bigger than 150 characters!");
	}

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