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

	Token(Type type, const std::string& string, int priority = -1)
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

	inline Type type()
	{
		return type_;
	}

	inline int priority()
	{
		return priority_;
	}

	inline const std::string& string()
	{
		return string_;
	}

	// Remove the 0's after the decimal point and the decimal point if needed
	const std::string& normalize()
	{
		// It doesn't need to be normalized
		if (string_.find('.') == std::string::npos)
			return string_;

		for (auto i = string_.size() - 1; i >= 0; i--)
		{
			if (string_[i] == '0')
				string_.erase(i, 1);
			else if(string_[i] == '.')
			{
				string_.erase(i, 1);
				break;
			}
			else
				break;
		}
		return string_;
	}

	long double toDouble()
	{
		if (type_ != Type::Number)
		{
			std::cout << (int)type_ << '\n';
			throw std::invalid_argument("TOKEN: This token is not a number!");
		}
		return std::stod(string_);
	}

private:
	Type		type_;
	int			priority_;
	std::string string_;
};

static std::ostream& operator<<(std::ostream& os, const Token& token)
{
	os << token.string_;
	return os;
}