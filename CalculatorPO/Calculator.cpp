#include "Calculator.h"

Calculator::Calculator()
{

}

void Calculator::run()
{
	std::string line;
	std::getline(std::cin, line);

	std::cout << line << '\n';
}