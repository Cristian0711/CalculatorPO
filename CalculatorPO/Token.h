#pragma once
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

	Token() : type(Type::Undefined), priority(0), sign(false)
	{

	}

	Token(Type type, int priority, bool sign) : type(type), priority(priority), sign(sign)
	{

	}

	inline Type getType()
	{
		return type;
	}

	inline int getPriority()
	{
		return priority;
	}

	inline bool isSign()
	{
		return sign;
	}

private:
	const Type	type;
	const int	priority;
	const bool	sign;
};

