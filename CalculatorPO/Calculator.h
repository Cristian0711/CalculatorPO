#pragma once

#include <iostream>
#include <string>

class Calculator
{
private:
	std::string consoleExpression = "";
	bool		active = true;
public:
	Calculator()
	{
		system("title Proiect Calculator PO");
	}

	Calculator(const std::string& consoleTitle)
	{
		const std::string title = "title " + consoleTitle;
		system(title.c_str());
	}

	void run();
	void getExpressions();

	inline bool isActive()
	{
		return active;
	}
};

