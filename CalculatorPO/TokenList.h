#pragma once

#include <iostream>
#include "Token.h"

#define DEFAULT_ARRAY_SIZE 300

class TokenList
{
public:
	TokenList() 
		: allocated_size(DEFAULT_ARRAY_SIZE)
	{
		pTokenList = new Token[DEFAULT_ARRAY_SIZE];
	}

	TokenList(size_t size) 
		: allocated_size(size)
	{
		pTokenList = new Token[size];
	}

	~TokenList()
	{
		delete[] pTokenList;
	}

	Token& operator[](size_t index) const
	{
		if (index < 0 && index >= size_)
			throw std::exception("TOKENLIST: The given index is invalid!");

		return pTokenList[index];
	}

	void operator+=(const Token& token) 
	{
		if (size_ >= allocated_size)
			throw std::exception("TOKENLIST: There are not enough allocated tokens!");

		pTokenList[size_] = token;
		size_ += 1;
	}

	void addToken(Token token)
	{
		if(size_ >= allocated_size)
			throw std::exception("TOKENLIST: There are not enough allocated tokens!");

		pTokenList[size_] = token;
		size_ += 1;
	}

	inline Token& back() const
	{
		return pTokenList[size_ - 1];
	}

	inline size_t size() const
	{
		return size_;
	}

	bool empty() const
	{
		return size_ != 0 ? false : true;
	}

	inline void clear()
	{
		size_ = 0;
	}

	bool	existsParentheses();
	void	remove(size_t index, size_t size);
	bool	existsOperators(size_t lIndex, size_t rIndex);
	size_t	getPriorityOperator(size_t lIndex, size_t rIndex);

	friend std::ostream& operator<<(std::ostream& os, const TokenList& tokenList);

private:
	Token*			pTokenList;
	size_t			size_ = 0;
	const size_t    allocated_size;
};

static std::ostream& operator<<(std::ostream& os, const TokenList& tokenList)
{
	for(int i = 0; i < tokenList.size_; i++)
		os << tokenList[i];
	return os;
}