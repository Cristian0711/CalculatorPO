#include "GUI.h"

void GUI::showConsoleMenu()
{
	std::cout << "Calculator Menu\n";
	std::cout << "Type exit to close the calculator\n";
	std::cout << "1 - Solve from console input\n";
	std::cout << "2 - Solve from file and show onto console\n";
	std::cout << "3 - Solve from file and save into file\n";
	std::cout << "4 - Load variables from file\n";
	std::cout << "5 - Save variables to file\n";
	std::cout << "6 - Show variables in memory\n";
	std::cout << "7 - Clear variables from memory\n";
	std::cout << "Selection: ";
}