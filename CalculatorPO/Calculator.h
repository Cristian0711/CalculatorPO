#pragma once

#include <iostream>
#include <string>

class Calculator
{
private:
	std::string consoleExpression = "";
	bool		active = true;
public:
	Calculator();

	void		run();

	inline bool isActive()
	{
		return active;
	}
};

