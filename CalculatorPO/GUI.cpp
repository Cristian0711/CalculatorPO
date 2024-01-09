#include "GUI.h"

void GUI::print(Printable* print)
{
	std::cout << print->string() << '\n';
}

void GUI::showConsoleMenu()
{
	std::cout << "Calculator Menu\n";
	std::cout << "Type exit to close the calculator\n";
	std::cout << "1 - Solve from console input\n";
	std::cout << "2 - Solve from file and show onto console\n";
	std::cout << "3 - Solve from file and save into file\n";
	std::cout << "Selection: ";
}