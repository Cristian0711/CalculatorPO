#pragma once

#include <iostream>
#include <string>
#include <fstream>

class Printable
{
public:
	virtual const std::string string() const = 0;
};

class GUI
{
public:
	static void print(Printable* print);
	static void showConsoleMenu();
};

