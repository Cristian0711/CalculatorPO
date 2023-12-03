#pragma once

#include <string>

#define TOKEN_MAX_PRIORITY 4

class Token
{
public:
	enum class Type {
		Undefined,
		Number,
		Operator,
		LeftParenthesis,
		RightParenthesis
	};

	Token() : type_(Type::Undefined), string_(""), priority_(0)
	{

	}

	Token(const Token& token) 
		: type_(token.type_), string_(token.string_), priority_(token.priority_)
	{

	}

	Token(Type type, const long double number, unsigned int priority = 0)
		: type_(type), string_(std::to_string(number)), priority_(priority)
	{

	}

	Token(Type type, const std::string& string, unsigned int priority = 0)
		: type_(type), string_(string), priority_(priority)
	{

	}

	inline Type type() const
	{
		return type_;
	}

	inline size_t priority() const
	{
		return priority_;
	}

	inline const std::string& string() const
	{
		return string_;
	}

	// Remove the 0's after the decimal point and the decimal point if needed
	inline const std::string normalize() const
	{
		std::string buffer = string_;
		// It doesn't need to be normalized
		if (buffer.find('.') == std::string::npos)
			return buffer;

		while (!buffer.empty() && buffer.back() == '0' || buffer.back() == '.')
			buffer.pop_back();

		return buffer;
	}

	inline long double toDouble() const
	{
		//if (type_ != Type::Number)
		//	throw std::invalid_argument("TOKEN: This token is not a number!");

		return std::stod(string_);
	}


	Token& operator=(const Token& token)
	{
		type_ = token.type_;
		string_ = token.string_;
		priority_ = token.priority_;

		return *this;
	}

	Token& operator=(const double number)
	{
		type_ = Type::Number;
		string_ = std::to_string(number);
		priority_ = 0;

		return *this;
	}

	operator double() const
	{
		return toDouble();
	}

	friend Token operator+(const Token& firstToken, const Token& secondToken);
	friend Token operator-(const Token& firstToken, const Token& secondToken);
	friend Token operator*(const Token& firstToken, const Token& secondToken);
	friend Token operator/(const Token& firstToken, const Token& secondToken);
	friend std::ostream& operator<<(std::ostream& os, const Token& token);

private:
	Type		type_;
	size_t		priority_;
	std::string	string_;
};

static Token operator+(const Token& firstToken, const Token& secondToken)
{
	return { Token::Type::Number, firstToken.toDouble() + secondToken.toDouble() };
}

static Token operator-(const Token& firstToken, const Token& secondToken)
{
	return { Token::Type::Number, firstToken.toDouble() - secondToken.toDouble() };
}

static Token operator*(const Token& firstToken, const Token& secondToken)
{
	return { Token::Type::Number, firstToken.toDouble() * secondToken.toDouble() };
}

static Token operator/(const Token& firstToken, const Token& secondToken)
{
	return { Token::Type::Number, firstToken.toDouble() / secondToken.toDouble() };
}

static std::ostream& operator<<(std::ostream& os, const Token& token)
{
	os << token.normalize();
	return os;
}