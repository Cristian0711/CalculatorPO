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
			throw std::invalid_argument("TOKENLIST: The given index is invalid!");

		return pTokenList[index];
	}

	void operator+=(const Token& token) {

		pTokenList[size_] = token;
		size_ += 1;
	}

	void addToken(Token token)
	{
		pTokenList[size_] = token;
		size_ += 1;
	}

	inline unsigned int size()
	{
		return size_;
	}

	inline void clear()
	{
		size_ = 0;
	}

	bool	existsParentheses();
	void	remove(int index, int size);
	int		getMaxPriority(int lIndex, int rIndex);

private:
	Token*			pTokenList;
	unsigned int	size_ = 0;
	const int		DEFAULT_LIST_SIZE = 50;
};