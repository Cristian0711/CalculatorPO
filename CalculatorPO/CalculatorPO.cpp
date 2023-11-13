// CalculatorPO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Calculator.h"

int main()
{
    Calculator calculator;
    while (calculator.isActive())
    {
        calculator.run();
    }
}