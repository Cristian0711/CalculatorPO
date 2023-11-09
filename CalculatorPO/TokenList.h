#pragma once

#include <iostream>
#include "Token.h"

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

	int getMaxPriority();
	bool existsParentheses();
	void solve(int index);

private:
	Token* pTokenList;
	unsigned int	size_ = 0;
};
