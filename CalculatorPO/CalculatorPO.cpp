// CalculatorPO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Calculator.h"

int main()
{

    /*{
        TokenList tokenList;
        Token token{ Token::Type::Number, "30" };

        auto size = 30;
        for(int i = 0; i < size; ++i)
            tokenList += { Token::Type::Number, "30"};

        tokenList.remove(5, 1);

        for (int i = 0; i < size - 1; ++i)
            tokenList[i] = { Token::Type::Number, "20" };
    }*/

    system("pause");
    Calculator calculator;
    while (calculator.isActive())
    {
        calculator.run();
    }
    system("pause");
}