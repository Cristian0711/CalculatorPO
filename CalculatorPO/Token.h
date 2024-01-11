#pragma once

#include <string>
#include <stdexcept>
#include "GUI.h"

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

	Token(const long double number)
		: type_(Type::Number), string_(std::to_string(number)), priority_(0)
	{

	}

	Token(Type type, std::string_view string, unsigned int priority = 0)
		: type_(type), string_(string), priority_(priority)
	{

	}

	~Token() = default;

	inline Type type() const
	{
		return type_;
	}

	inline unsigned char priority() const
	{
		return priority_;
	}

	inline std::string_view string() const
	{
		return string_;
	}

	inline long double toDouble() const
	{
		if (type_ != Type::Number)
			throw std::exception("TOKEN: This token is not a number!");

		return std::stold(string_);
	}

	inline bool isLeftParenthesis() const
	{
		if (type_ == Type::LeftParenthesis)
			return true;
		return false;
	}

	inline bool isRightParenthesis() const
	{
		if (type_ == Type::RightParenthesis)
			return true;
		return false;
	}

	inline bool isOperator() const
	{
		if (type_ == Type::Operator)
			return true;
		return false;
	}

	inline bool isNumber() const
	{
		if (type_ == Type::Number)
			return true;
		return false;
	}

	inline Token* next() const
	{
		return next_;
	}

	inline Token* prev() const
	{
		return prev_;
	}

	inline void setString(std::string_view string)
	{
		string_ = string;
	}

	inline void setNext(Token* token)
	{
		next_ = token;
	}

	inline void setPrev(Token* token)
	{
		prev_ = token;
	}

	// Remove the 0's after the decimal point and the decimal point if needed
	inline const std::string normalize() const
	{
		std::string buffer = string_;
		// It doesn't need to be normalized
		if (buffer.find('.') == std::string::npos)
			return buffer;

		while (!buffer.empty() && buffer.back() == '0')
			buffer.pop_back();

		if (buffer.back() == '.')
			buffer.pop_back();

		return buffer;
	}

	Token& operator=(const Token& token)
	{
		type_ = token.type_;
		string_ = token.string_;
		priority_ = token.priority_;

		return *this;
	}

	Token& operator=(const long double number)
	{
		type_ = Type::Number;
		string_ = std::to_string(number);
		priority_ = 0;

		return *this;
	}

	operator long double() const
	{
		return toDouble();
	}

	friend Token operator+(const Token& firstToken, const Token& secondToken);
	friend Token operator-(const Token& firstToken, const Token& secondToken);
	friend Token operator*(const Token& firstToken, const Token& secondToken);
	friend Token operator/(const Token& firstToken, const Token& secondToken);
	friend std::ostream& operator<<(std::ostream& os, const Token& token);
private:
	Token* next_ = nullptr;
	Token* prev_ = nullptr;

	Type			type_;
	unsigned char	priority_;
	std::string		string_;
};

static Token operator+(const Token& firstToken, const Token& secondToken)
{
	return { firstToken.toDouble() + secondToken.toDouble() };
}

static Token operator-(const Token& firstToken, const Token& secondToken)
{
	return { firstToken.toDouble() - secondToken.toDouble() };
}

static Token operator*(const Token& firstToken, const Token& secondToken)
{
	return { firstToken.toDouble() * secondToken.toDouble() };
}

static Token operator/(const Token& firstToken, const Token& secondToken)
{
	return { firstToken.toDouble() / secondToken.toDouble() };
}

static std::ostream& operator<<(std::ostream& os, const Token& token)
{
	os << token.normalize();
	return os;
}

class ErrorToken : public Token
{
public:
	ErrorToken(std::string_view error)
	{
		setString(error);
	}
};