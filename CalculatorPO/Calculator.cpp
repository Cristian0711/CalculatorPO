#include "Calculator.h"

void Calculator::getTokens()
{
	for (auto i = 0; i < consoleExpression.size(); i++)
	{
		const auto c = consoleExpression[i];
		if (isdigit(c))
		{
			const auto startIndex = i;
			while (isdigit(consoleExpression[i]))
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

		for (auto j = leftParenthesis + 1; j < rightParenthesis; j++)
		{
			auto& token = tokenList[j];
			// Search for operator that has the biggest priority in that parenthesis
			if (token.type() == Token::Type::Operator && token.priority() == tokenList.getMaxPriority(leftParenthesis, rightParenthesis))
			{
				tokenList.solveCalculation(j);
				break;
			}
		}
	}

	tokenList.solveCalculation(1);
	tokenList.clear();
}

void Calculator::run()
{
	std::getline(std::cin, consoleExpression);
	consoleExpression = "((1+2+3)+2+(1+2+3+4))+6";
	getTokens();
	tokenList.clear();
}