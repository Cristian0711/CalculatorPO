// CalculatorPO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Calculator.h"

int main(int argc, char** argv)
{
    Calculator calculator;
    if (argc >= 2)
    {
        calculator.run(argv[1]);
        return 0;
    }

    while (calculator.isActive())
    {
        calculator.run("");
    }
    system("pause");
}