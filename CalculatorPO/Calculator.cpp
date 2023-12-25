#include "Calculator.h"

Token Calculator::solveCalculation(const Token* token)
{
	const Token& leftToken		= *token->prev();
	const Token& rightToken		= *token->next();

	Token result;

	switch (token->string().at(0)) {
	default:
		throw std::exception("CALCULATOR: The given operator is invalid!");
	case '^':
		result = pow(leftToken, rightToken);
		break;
	case '#':
		result = pow((double)leftToken, 1.0 / (double)rightToken);
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
		std::cout << tokenList << '\n';

	return result;
}

const Token* Calculator::getPriorityOperator(const Token* tokenOperator)
{
	Token* nextNumber = tokenOperator->next();
	Token* prevNumber = tokenOperator->prev();

	Token* nextOperator = nextNumber->next();
	Token* prevOperator = prevNumber->prev();

	if (prevOperator == nullptr && nextOperator == nullptr)
		return tokenOperator;

	// 2+2*3 if we check this for the addition operator it has no previous operator
	if (prevOperator == nullptr)
	{
		/* Used in case nextOperator is not a number and it's because tokenOperator's next is a paraenthesis
		  and in this case we need to solve the parenthesis first '2*(3-4)' */
		if (!nextOperator->isOperator())
			return nullptr;

		/* In this case it should not return the multiplication operator 2+2*(3-4) */
		if (!nextOperator->next()->isNumber())
			return nullptr;

		if (tokenOperator->priority() >= nextOperator->priority())
			return tokenOperator;
		else
			return nextOperator;
	}

	// 2+2*3 if we check this for the multiplication operator it has no next operator
	if (nextOperator == nullptr)
	{
		/* Used in case prevOperator is not a number and it's because tokenOperator's prev is a paraenthesis
		  and in this case we need to solve the parenthesis first '(3-4)*2'*/
		if (!prevOperator->isOperator())
			return nullptr;

		/* In this case it should not return the multiplication operator (3-4)*2+2 */
		if (!prevOperator->prev()->isNumber())
			return nullptr;

		if (tokenOperator->priority() >= prevOperator->priority())
			return tokenOperator;
		else
			return prevOperator;
	}

	// Search for the highest priority between all 3 operators and save it to check if it is valid
	const Token* returnOperator;
	if (tokenOperator->priority() >= nextOperator->priority() && tokenOperator->priority() >= prevOperator->priority())
	{
		returnOperator = tokenOperator;
	}
	else if (nextOperator->priority() >= prevOperator->priority())
	{
		returnOperator = nextOperator;
	}
	else
	{
		returnOperator = prevOperator;
	}

	// Used to check if the both terms of the operation are numbers else the parenthesis needs to be solved
	if (!returnOperator->prev()->isNumber() || !returnOperator->next()->isNumber())
		return nullptr;

	return returnOperator;
}

const Token& Calculator::solveExpression()
{
	while (tokenList.existsOperators(tokenList.front(), tokenList.back()))
	{
		Token* token = tokenList.front();
		while (token != nullptr)
		{
			if (token->isOperator())
			{
				const Token* operatorToken = getPriorityOperator(token);

				if (operatorToken == nullptr)
					goto nextToken;

				const Token  result = solveCalculation(operatorToken);

				// 3+3-3 -> 6+3-3 ->
				*operatorToken->prev() = result;
				token = operatorToken->prev();

				// 6-3
				tokenList.removeToken(operatorToken->next());
				tokenList.removeToken(operatorToken);
			}

			// Remove parenthesis 2+(3)+4
			if (token->prev() != nullptr && token->next() != nullptr &&
				token->prev()->isLeftParenthesis() &&
				token->next()->isRightParenthesis())
			{
				tokenList.removeToken(token->prev());
				tokenList.removeToken(token->next());
			}

			nextToken:
			token = token->next();
		}
	}

	return *tokenList.front();
}

void Calculator::run()
{
	std::cin.getline(consoleExpression, consoleSize);
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(LLONG_MAX, '\n');
		throw std::exception(std::string("CALCULATOR: The sequence is bigger than " + std::to_string(consoleSize) + " characters!" ).c_str());
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
		//parser.getTokens(tokenList, "(-1+2-3)+4+5*(6+7/8)#9");

		std::cout << "Answer: " << solveExpression() << '\n';
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << '\n';
	}

	tokenList.clear();
}