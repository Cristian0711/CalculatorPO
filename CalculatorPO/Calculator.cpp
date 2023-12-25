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

const Token& Calculator::solveExpression()
{
	while (tokenList.existsOperators(tokenList.front(), tokenList.back()))
	{
		Token* token = tokenList.front();
		while (token != nullptr)
		{
			if (token->isOperator())
			{
				const Token* operatorToken = tokenList.getPriorityOperator(token);

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