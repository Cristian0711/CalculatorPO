#pragma once

#include <iostream>
#include "Token.h"

class TokenList : public Printable
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

	const std::string string() const;

	void	clear();
	void	addToken(const Token& token);
	void	removeToken(const Token* token);

	Token* getPriorityOperator(Token* tokenOperator) const;
	Token* priorityOperatorOfTokens(Token* first, Token* second, Token* third = nullptr) const;

	friend std::ostream& operator<<(std::ostream& os, const TokenList& tokenList);
private:
	size_t	size_ = 0;

	Token*	head = nullptr;
	Token*	tail = nullptr;
};