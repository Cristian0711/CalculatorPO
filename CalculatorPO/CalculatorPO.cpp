// CalculatorPO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Calculator.h"

int main()
{

    Calculator calculator;
    while (calculator.isActive())
    {
        try
        {
            calculator.run();
        }
        catch (const std::invalid_argument& exception)
        {
            std::cout << exception.what() << '\n';
        }
    }
    system("pause");
}