#pragma once

class CalculatorException : public std::exception
{
public:
	virtual const char* what() const = 0;
	virtual const char* print() const = 0;
};

class ZeroException : public CalculatorException{
public:
	const char* what() const
	{
		return "CALCULATOR: Cannot divide by 0!";
	}
	const char* print() const
	{
		return "invalid, cannot divide by 0!";
	}
};

class InvalidOperator : public CalculatorException {
public:
	const char* what() const
	{
		return "CALCULATOR: The given operator is invalid!";
	}
	const char* print() const
	{
		return "invalid operator given!";
	}
};

class InvalidNumber : public CalculatorException {
public:
	const char* what() const
	{
		return "CALCULATOR: Invalid number was given!";
	}
	const char* print() const
	{
		return "invalid number given!";
	}
};

class InvalidExpression : public CalculatorException {
public:
	const char* what() const
	{
		return "CALCULATOR: Invalid expression was given!";
	}
	const char* print() const
	{
		return "invalid expression given!";
	}
};

class InvalidParenthesis : public CalculatorException {
public:
	const char* what() const
	{
		return "CALCULATOR: Invalid parenthesis!";
	}
	const char* print() const
	{
		return "invalid parenthesis given!";
	}
};

class InvalidMathExpression : public CalculatorException {
public:
	const char* what() const
	{
		return "CALCULATOR: Invalid math expression was given!";
	}
	const char* print() const
	{
		return "invalid math expression given!";
	}
};
