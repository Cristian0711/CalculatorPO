#pragma once

#include <iostream>
#include "Token.h"

class TokenList
{
public:
	TokenList() = default;

	~TokenList()
	{
		clear();
	}

	inline size_t size() const
	{
		return size_;
	}

	inline bool empty() const
	{
		return size_ != 0 ? false : true;
	}

	inline Token* front() const
	{
		return head;
	}

	inline Token* back() const
	{
		return tail;
	}
	
	void operator+=(const Token& token)
	{
		addToken(token);
	}

	void	clear();
	void	addToken(const Token& token);
	void	removeToken(const Token* token);

	const Token* getPriorityOperator(const Token* tokenOperator) const;
	const Token* priorityOperatorOfTokens(const Token* first, const Token* second, const Token* third = nullptr) const;

	friend std::ostream& operator<<(std::ostream& os, const TokenList& tokenList);
private:
	size_t	size_ = 0;

	Token*	head = nullptr;
	Token*	tail = nullptr;
};