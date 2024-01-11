#include "VariableList.h"

void VariableList::addVariable(std::string_view name, std::string_view value)
{
	for (variableTuple& tuple : variableList)
	{
		std::string_view varName = std::get<0>(tuple);
		if (varName == name)
		{
			std::get<1>(tuple) = value;
			return;
		}
	}
	variableList.push_back({ std::string(name), std::string(value) });
}

void VariableList::addVariable(variableTuple tuple)
{
	variableList.push_back(tuple);
}

std::string VariableList::operator[](std::string_view name) const
{
	for (const variableTuple& tuple : variableList)
	{
		std::string_view varName = std::get<0>(tuple);
		if (varName == name)
			return std::get<1>(tuple);
	}
	throw VariableNotInList();
}

void VariableList::loadVariablesFromFile(const std::string& path)
{
	//file stream not working with string_view
	std::ifstream file(path, std::ios::binary);
	std::string line;

	if (file.fail())
		throw std::exception("CALCULATOR: Invalid file path!");

	size_t size = 0;
	file.read(reinterpret_cast<char*>(&size), sizeof(size_t));

	for (size_t i = 0; i < size; ++i)
	{
		size_t nameSize = 0;
		size_t valueSize = 0;
		std::string varName;
		std::string varValue;

		file.read(reinterpret_cast<char*>(&nameSize), sizeof(size_t));
		varName.resize(nameSize);
		file.read(reinterpret_cast<char*>(&varName[0]), nameSize);

		file.read(reinterpret_cast<char*>(&valueSize), sizeof(size_t));
		varValue.resize(valueSize);
		file.read(reinterpret_cast<char*>(&varValue[0]), valueSize);

		addVariable(varName, varValue);
	}

	file.close();

}

void VariableList::saveVariablesToFile(const std::string& path)
{
	std::ofstream file(path, std::ios::binary);

	if (file.fail())
		throw std::exception("CALCULATOR: Invalid file path!");

	size_t size = variableList.size();
	file.write(reinterpret_cast<const char*>(&size), sizeof(size_t));

	for (variableTuple& tuple : variableList)
	{
		size_t nameSize = std::get<0>(tuple).size();
		size_t valueSize = std::get<1>(tuple).size();

		file.write(reinterpret_cast<const char*>(&nameSize), sizeof(size_t));
		file.write(reinterpret_cast<const char*>(&std::get<0>(tuple)[0]), nameSize);

		file.write(reinterpret_cast<const char*>(&valueSize), sizeof(size_t));
		file.write(reinterpret_cast<const char*>(&std::get<1>(tuple)[0]), valueSize);
	}

	file.close();
}