#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <fstream>
#include <iostream>
#include "Exceptions.h"

// not allowed using auto?
typedef std::tuple<std::string, std::string> variableTuple;

class VariableList
{
public:
	void addVariable(std::string_view name, std::string_view value);

	void loadVariablesFromFile(const std::string& path);
	void saveVariablesToFile(const std::string& path);

	void clear();

	std::string operator[](std::string_view) const;
	friend std::ostream& operator<<(std::ostream& os, const VariableList& variableList);
private:
	std::vector<variableTuple> variableList;
};