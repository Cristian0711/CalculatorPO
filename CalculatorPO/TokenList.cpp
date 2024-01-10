#include "TokenList.h"

// This function also checks for validity, works with 2 tokens also where third is nullptr
Token* TokenList::priorityOperatorOfTokens(Token* first, Token* second, Token* third) const
{
	if (first == nullptr || second == nullptr)
		return nullptr;

	Token* returnOperator = nullptr;

	if (third != nullptr)
	{
		if (first->priority() >= second->priority() && first->priority() >= third->priority())
		{
			returnOperator = first;
		}
		else if (second->priority() >= third->priority())
		{
			returnOperator = second;
		}
		else
		{
			returnOperator = third;
		}
	}
	else
	{
		if (first->priority() >= second->priority())
			returnOperator = first;
		else
			returnOperator = second;
	}

	// Used to check if the both terms of the operation are numbers else the parenthesis needs to be solved
	if (!returnOperator->prev()->isNumber() || !returnOperator->next()->isNumber())
		return nullptr;

	return returnOperator;
}

Token* TokenList::getPriorityOperator(Token* tokenOperator) const
{
	Token* nextNumber = tokenOperator->next();
	Token* prevNumber = tokenOperator->prev();

	Token* nextOperator = nextNumber->next();
	Token* prevOperator = prevNumber->prev();

	if (prevOperator == nullptr && nextOperator == nullptr)
		return tokenOperator;

	/* If both of them aren't operators return the current token for cases like (2+3)*3
		where prevOperator = '(' and nextOperator = ')'*/
	if (prevOperator != nullptr && nextOperator != nullptr &&
		!prevOperator->isOperator() && !nextOperator->isOperator())
	{
		if (!prevNumber->isNumber() || !nextNumber->isNumber())
			return nullptr;

		return tokenOperator;
	}

	// 2+2*3 if we check this for the addition operator it has no previous operator
	if (prevOperator == nullptr)
	{
		/* Used in case nextOperator is not a number and it's because tokenOperator's next is a paraenthesis
			and in this case we need to solve the parenthesis first '2*(3-4)' */
		if (!nextOperator->isOperator())
			return nullptr;

		/* We always need to have 3 operators when possible to compare for cases like '2-3*3#2'
			without this check it would have returned the multiply operator*/
		Token* thirdOperator = nextOperator->next()->next();
		if (thirdOperator != nullptr && !thirdOperator->isOperator())
			thirdOperator = nullptr;

		// If the third operator isn't an operator this will compare only the 2 of them (thirdOperator = nullptr)
		return priorityOperatorOfTokens(tokenOperator, nextOperator, thirdOperator);
	}

	// 2+2*3 if we check this for the multiplication operator it has no next operator
	if (nextOperator == nullptr)
	{
		/* Used in case prevOperator is not a number and it's because tokenOperator's prev is a paraenthesis
			and in this case we need to solve the parenthesis first '(3-4)*2'*/
		if (!prevOperator->isOperator())
			return nullptr;

		/* We always need to have 3 operators when possible to compare for cases like '3#2*3-2'
			without this check it would have returned the multiply operator*/
		Token* thirdOperator = prevOperator->prev()->prev();
		if (thirdOperator != nullptr && thirdOperator->isOperator())
			return priorityOperatorOfTokens(thirdOperator, prevOperator, tokenOperator);

		// If the third operator isn't an operator this will compare only the 2 of them (thirdOperator = nullptr)
		return priorityOperatorOfTokens(prevOperator, tokenOperator);
	}

	// Search for the highest priority between all 3 operators if all exists
	return priorityOperatorOfTokens(prevOperator, tokenOperator, nextOperator);
}

void TokenList::addToken(const Token& token)
{
	Token* temp = new Token(token);

	if (head == nullptr)
	{
		head = tail = temp;
	}
	else
	{
		tail->setNext(temp);
		temp->setPrev(tail);
		tail = temp;

		tail->setNext(nullptr);
	}

	size_++;
}

void TokenList::removeToken(const Token* token)
{
	if (head == nullptr || token == nullptr)
		return;

	if (head == token)
		head = token->next();

	if (token->next() != nullptr)
		token->next()->setPrev(token->prev());

	if (token->prev() != nullptr)
		token->prev()->setNext(token->next());

	size_--;
	delete token;
}

void TokenList::clear()
{
	Token* token = head;
	while (token != nullptr)
	{
		Token* next = token->next();
		delete token;
		token = next;
	}
	head = nullptr;
	size_ = 0;
}

std::ostream& operator<<(std::ostream& os, const TokenList& tokenList)
{
	Token* token = tokenList.head;
	while (token != nullptr)
	{
		os << *token;
		token = token->next();
	}
	return os;
}
