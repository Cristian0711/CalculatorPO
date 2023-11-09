#include "Calculator.h"
#include "Token.h"

void Calculator::getExpressions()
{
    for (int i = 0; i < (signed)consoleExpression.length(); ++i) {
        //The order of the following checks matters
        if (consoleExpression[i] == '(') {
            
        }
        else if (consoleExpression[i] == ')') {
            
        }
    }

    Token(Token::Type::Number)
}

void Calculator::run()
{
	std::getline(std::cin, consoleExpression);
	getExpressions();
}