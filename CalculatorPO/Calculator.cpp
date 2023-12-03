#include "Calculator.h"

Token Calculator::solveCalculation(size_t index)
{
	const Token& token			= tokenList[index];
	const Token& leftToken		= tokenList[index - 1];
	const Token& rightToken		= tokenList[index + 1];

	Token result;

	switch (token.string().at(0)) {
	default:
		throw std::exception("CALCULATOR: The given operator is invalid!");
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
			throw std::exception("CALCULATOR: Cannot divide by 0!");
		result = leftToken / rightToken;
		break;
	case '+':
		result = leftToken + rightToken;
		break;
	case '-':
		result = leftToken - rightToken;
		break;
	}

	if (debug == true)
	{
		for (int i = 0; i < tokenList.size(); i++)
		{
			std::cout << tokenList[i];
		}
		std::cout << '\n';
	}

	return result;
}

void Calculator::solveSequence(size_t lIndex, size_t rIndex)
{
	while (tokenList.existsOperators(lIndex, rIndex))
	{
		const size_t index = tokenList.getPriorityOperator(lIndex, rIndex);
		const Token  result = solveCalculation(index);

		tokenList[index - 1] = result;
		tokenList.remove(index, 2);
		
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

long double Calculator::solveExpression()
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
	return tokenList[0];
}

void Calculator::run()
{
	std::cin.getline(consoleExpression, consoleSize);
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(LLONG_MAX, '\n');
		throw std::exception("CALCULATOR: The sequence is bigger than 150 characters!");
	}

	if (strcmp(consoleExpression, "exit") == 0)
	{
		active = false;
		return;
	}

	try
	{
		Parser parser;
		parser.getTokens(tokenList, consoleExpression);

		std::cout << "Answer: " << solveExpression() << '\n';
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << '\n';
	}

	tokenList.clear();
}