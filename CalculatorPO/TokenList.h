#pragma once

#include <iostream>
#include "Token.h"

#define DEFAULT_ARRAY_SIZE 300

class TokenList
{
public:
	TokenList() = default;

	~TokenList()
	{
		clear();
	}

	void operator+=(const Token& token) 
	{
		addToken(token);
	}

	inline Token* front() const
	{
		return head;
	}

	inline Token* back() const
	{
		return tail;
	}

	inline bool empty() const
	{
		return size_ != 0 ? false : true;
	}

	void	clear();
	void	addToken(const Token& token);
	void	removeToken(const Token* token);
	bool	existsOperators(const Token* lToken, const Token* rToken);

	const Token* getPriorityOperator(const Token* tokenOperator);

	friend std::ostream& operator<<(std::ostream& os, const TokenList& tokenList);
private:
	size_t			size_ = 0;

	Token* head = nullptr;
	Token* tail = nullptr;
};

static std::ostream& operator<<(std::ostream& os, const TokenList& tokenList)
{
	Token* token = tokenList.head;
	while (token != nullptr)
	{
		os << *token;
		token = token->next();
	}
	return os;
}