#pragma once

#include <iostream>
#include "Token.h"

class TokenList
{
public:
	TokenList()
	{
		pTokenList = new Token[DEFAULT_ARRAY_SIZE];
	}

	TokenList(int size)
	{
		pTokenList = new Token[size];
	}

	~TokenList()
	{
		delete[] pTokenList;
	}

	Token& operator[](int index) const
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

	inline size_t size() const
	{
		return size_;
	}

	inline void clear()
	{
		size_ = 0;
	}

	bool	existsParentheses();
	void	remove(size_t index, size_t size);
	bool	existsOperators(size_t lIndex, size_t rIndex);
	size_t	getMaxPriority(size_t lIndex, size_t rIndex);
	size_t	getPriorityOperator(size_t lIndex, size_t rIndex);

private:
	Token*		pTokenList;
	size_t		size_ = 0;
	const int	DEFAULT_ARRAY_SIZE = 150;
};