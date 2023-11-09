#include "Calculator.h"

void Calculator::solveSequence(int lIndex, int rIndex)
{
	for (auto j = lIndex + 1; j < rIndex; j++)
	{
		auto& token = tokenList[j];
		// Search for operator that has the biggest priority in that parenthesis
		if (token.type() == Token::Type::Operator && token.priority() == tokenList.getMaxPriority(lIndex, rIndex))
		{
			solveCalculation(j);
			break;
		}
	}
}

void Calculator::solveCalculation(int index)
{
	auto& token         = tokenList[index];
	auto leftNumber     = tokenList[index - 1].toDouble();
	auto rightNumber    = tokenList[index + 1].toDouble();

    long double result = 0;

    switch (token.string()[0]) {
    default:
        throw std::invalid_argument("Operator error");
        return;
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
		if(rightNumber == 0)
			throw std::invalid_argument("Can not divide by 0");
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
        std::cout << tokenList[i].string();
    }
    std::cout << '\n';
}

void Calculator::getTokens()
{
	for (auto i = 0; i < consoleExpression.size(); i++)
	{
		const auto c = consoleExpression[i];
		if (isdigit(c))
		{
			const auto startIndex = i;
			while (isdigit(consoleExpression[i]) || consoleExpression[i] == '.')
				i++;

			const auto number = std::string(consoleExpression, startIndex, i - startIndex);
			tokenList.addToken({ Token::Type::Number, number });

			i -= 1;
		}
		else
		{
			auto type		= Token::Type::Undefined;
			auto priority	= -1;
			auto sign		= false;
			auto right		= false;

			switch (c)
			{
			case '(':   
				type = Token::Type::LeftParenthesis;     
				break;

			case ')':   
				type = Token::Type::RightParenthesis;    
				break;
			case '^':   
				type = Token::Type::Operator;      
				priority = 4;
				right = true;  
				break;
			case '#':
				type = Token::Type::Operator;
				priority = 4;
				right = true;
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

			if(type != Token::Type::Undefined)
				tokenList.addToken({ type, std::string(1, c), priority, sign, right});
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
					tokenList.remove(i + 2, 1);
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

	std::cout << tokenList[0].normalize();

	tokenList.clear();
}

void Calculator::run()
{
	std::getline(std::cin, consoleExpression);
	//consoleExpression = "((40+(5-1*2))*2 / 2 + 2 ^ 3)*2 * (4 + 3 - 6 / 3 * 2)";
	getTokens();
	solveExpression();
}