#pragma once

#include <string>

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

	Token(Type type, const std::string& string, int priority = 0)
		: type_(type), string_(string), priority_(priority)
	{

	}

	void operator=(const Token& token)
	{
		type_ = token.type_;
		string_ = token.string_;
		priority_ = token.priority_;
	}

	friend std::ostream& operator<<(std::ostream& os, const Token& token);

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
		if (type_ != Type::Number)
			throw std::invalid_argument("TOKEN: This token is not a number!");

		return std::stod(string_);
	}

private:
	Type		type_;
	size_t		priority_;
	std::string	string_;
};

static std::ostream& operator<<(std::ostream& os, const Token& token)
{
	os << token.string_;
	return os;
}