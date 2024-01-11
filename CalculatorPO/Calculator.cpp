#include "Calculator.h"

Token Calculator::solveTheCalculation(const Token* token) const
{
	const Token&	leftToken	= *token->prev();
	const Token&	rightToken	= *token->next();
	const Token*	leftOperator = leftToken.prev();
	
	bool signFix = false;
	if (leftOperator != nullptr && (token->string() == "+" || token->string() == "-") && leftOperator->string() == "-")
		signFix = true;

	Token result;

	switch (token->string().at(0)) {
	default:
		throw InvalidOperator();
	case '^':
		result = pow(leftToken, rightToken);
		break;
	case '#':
		result = pow((long double)leftToken, 1.0 / (long double)rightToken);
		break;
	case '*':
		result = leftToken * rightToken;
		break;
	case '/':
		if (rightToken == 0)
			throw ZeroException();
		result = leftToken / rightToken;
		break;
	case '+':
		if (signFix)
			result = ((long double)leftToken * -1 + (long double)rightToken) * -1;
		else
			result = leftToken + rightToken;
		break;
	case '-':
		if (signFix)
			result = leftToken + rightToken;
		else
			result = leftToken - rightToken;
		break;
	}

	return result;
}

const Token& Calculator::solveExpression()
{
	while (tokenList.size() != 1)
	{
		const Token* token = tokenList.front();
		while (token != nullptr)
		{
			if (token->isOperator())
			{
				const Token* operatorToken = tokenList.getPriorityOperator(token);

				if (operatorToken == nullptr)
				{
					token = token->next();
					continue;
				}

				const Token result = solveTheCalculation(operatorToken);

				// 3+3-3 -> 6+3-3 ->
				*operatorToken->prev() = result;
				token = operatorToken->prev();

				// 6-3
				tokenList.removeToken(operatorToken->next());
				tokenList.removeToken(operatorToken);

				if (debug == true)
					std::cout << tokenList << '\n';
			}

			// Remove parenthesis 2+(3)+4
			if (token->prev() != nullptr && token->next() != nullptr &&
				token->prev()->isLeftParenthesis() &&
				token->next()->isRightParenthesis())
			{
				tokenList.removeToken(token->prev());
				tokenList.removeToken(token->next());
			}

			token = token->next();
		}
	}

	return *tokenList.front();
}

Token Calculator::solve(std::string_view expression)
{
	try
	{
		Parser parser;
		parser.getTokens(tokenList, variableList, expression);

		Token answer = solveExpression();

		if (parser.hasVariable())
			variableList.addVariable(parser.variableName(), answer.normalize());

		return answer;
	}
	catch (const CalculatorException& exception)
	{
		std::cout << exception.what() << '\n';
	
		ErrorToken token(exception.print());
		return token;
	}
}

void Calculator::handleConsoleExpression()
{
	std::cout << "Enter the expression: ";

	std::string consoleExpression;
	std::cin.ignore(LLONG_MAX, '\n');
	std::getline(std::cin, consoleExpression);

	std::cout << "Answer: " << solve(consoleExpression) << '\n';
}

void Calculator::handleFileExpression(bool saveToFile)
{
	std::string fileName, saveFileName;
	std::cout << "Enter the file path: ";
	std::cin >> fileName;

	std::ifstream fileStream(fileName);
	if (fileStream.fail())
		throw std::exception("CALCULATOR: Invalid file path!");

	std::ofstream saveFileStream;
	if (saveToFile)
	{
		std::cout << "Enter the save file path: ";
		std::cin >> saveFileName;

		saveFileStream.open(saveFileName);
		if (saveFileStream.fail())
			throw std::exception("CALCULATOR: Invalid save file path!");
	}

	std::string line;
	while (std::getline(fileStream, line))
	{
		if (saveToFile)
		{
			saveFileStream << line << '=' << solve(line) << '\n';
		}
		else
		{
			std::cout << line << '=' << solve(line) << '\n';
		}
		tokenList.clear();
	}

	fileStream.close();
	saveFileStream.close();
}

void Calculator::handleLoadVariables()
{
	std::cout << "Enter the variables file path: ";
	std::string path;
	std::cin >> path;
	variableList.loadVariablesFromFile(path);
}

void Calculator::handleSaveVariables()
{
	std::cout << "Enter the variables savefile path: ";
	std::string path;
	std::cin >> path;
	variableList.saveVariablesToFile(path);
}

void Calculator::run(std::string_view expression)
{
	if (expression.length() > 0)
	{
		std::cout << "Answer: " << solve(expression) << '\n';
		return;
	}

	GUI::showConsoleMenu();
	std::cin >> calculatorMode;

	try
	{
		if (calculatorMode == "1")
		{
			handleConsoleExpression();
		}
		else if (calculatorMode == "2")
		{
			handleFileExpression(false);
		}
		else if (calculatorMode == "3")
		{
			handleFileExpression(true);
		}
		else if (calculatorMode == "4")
		{
			handleLoadVariables();
		}
		else if (calculatorMode == "5")
		{
			handleSaveVariables();
		}
		else if (calculatorMode == "exit")
		{
			active = false;
			return;
		}
		else
		{
			throw std::exception("CALCULATOR: Invalid selection was given!");
		}
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << '\n';
	}

	tokenList.clear();
}