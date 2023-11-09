#include "Calculator.h"

void Calculator::getExpressions()
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
			}

			tokenList.addToken({ type, std::string(1, c), priority, sign, right});
		}
	}

	tokenList.clear();
}

void Calculator::run()
{
	std::getline(std::cin, consoleExpression);
	getExpressions();
}