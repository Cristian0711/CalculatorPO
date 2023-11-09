#pragma once

#include <string>

#define DEFAULT_LIST_SIZE 50

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

	Token() : type_(Type::Undefined), string_(""), priority_(0), sign_(false), right_(false)
	{

	}

	Token(Type type, const std::string& string, int priority = -1, bool sign = false, bool right = false)
		: type_(type), string_(string), priority_(priority), sign_(sign), right_(false)
	{

	}

	void operator=(const Token &token)
	{
		type_ = token.type_;
		string_ = token.string_;
		priority_ = token.priority_;
		sign_ = token.sign_;
		right_ = token.right_;
	}

	inline Type type()
	{
		return type_;
	}

	inline int priority()
	{
		return priority_;
	}

	inline bool sign()
	{
		return sign_;
	}

	inline bool right()
	{
		return right_;
	}

	inline const std::string& string()
	{
		return string_;
	}

	const std::string& normalize()
	{
		for (auto i = string_.size() - 1; i >= 0; i--)
		{
			if (string_[i] == '0' || string_[i] == '.')
			{
				string_.erase(i, 1);
			}
			else
			{
				break;
			}
		}
		return string_;
	}

	long double toDouble()
	{
		if(type_ != Type::Number)
			throw std::invalid_argument("TOKEN: This token is not a number!");
		std::stod(string_);
	}

private:
	Type		type_;
	int			priority_;
	bool		sign_;
	bool		right_;
	std::string string_;
};