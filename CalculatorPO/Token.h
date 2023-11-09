#pragma once

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

	Token() : type(Type::Undefined), priority(0), sign(false)
	{

	}

	Token(Type type, const std::string& string, int priority = -1, bool sign = false, bool right = false)
		: type(type), string_(string), priority(priority), sign(sign), right(false)
	{

	}

	void operator=(const Token &token)
	{
		type = token.type;
		string_ = token.string_;
		priority = token.priority;
		sign = token.sign;
		right = token.right;
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

	inline const std::string& string()
	{
		return string_;
	}

private:
	Type		type;
	int			priority;
	bool		sign;
	bool		right;
	std::string string_;
};

class TokenList
{
public:
	TokenList()
	{
		pTokenList = new Token[DEFAULT_LIST_SIZE];
	}

	TokenList(int size)
	{
		pTokenList = new Token[size];
	}

	~TokenList()
	{
		delete[] pTokenList;
	}

	Token& operator[](int index)
	{
		if (index < 0 && index >= size_)
			throw std::invalid_argument("Invalid index");

		return pTokenList[index];
	}

	void addToken(Token token) 
	{
		pTokenList[size_] = token;
		size_ += 1;
	}

	inline Token& back()
	{
		return pTokenList[size_ - 1];
	}

	inline unsigned int size()
	{
		return size_;
	}

	inline void clear()
	{
		size_ = 0;
	}

private:
	Token*			pTokenList;
	unsigned int	size_ = 0;
};
