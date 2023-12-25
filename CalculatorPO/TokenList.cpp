#include "TokenList.h"

bool TokenList::existsOperators(const Token* lToken, const Token* rToken)
{
	const Token* token = lToken;
	while (token != rToken && token != nullptr)
	{
		if (token->type() == Token::Type::Operator)
			return true;

		token = token->next();
	}
	return false;
}

const Token* priorityOperatorOfThree(const Token* first, const Token* second, const Token* third)
{
	if (first->priority() >= second->priority() && first->priority() >= third->priority())
	{
		return first;
	}
	else if (second->priority() >= third->priority())
	{
		return second;
	}
	else
	{
		return third;
	}
}

const Token* TokenList::getPriorityOperator(const Token* tokenOperator)
{
	Token* nextNumber = tokenOperator->next();
	Token* prevNumber = tokenOperator->prev();

	Token* nextOperator = nextNumber->next();
	Token* prevOperator = prevNumber->prev();

	if (prevOperator == nullptr && nextOperator == nullptr)
		return tokenOperator;

	// 2+2*3 if we check this for the addition operator it has no previous operator
	if (prevOperator == nullptr)
	{
		/* Used in case nextOperator is not a number and it's because tokenOperator's next is a paraenthesis
		  and in this case we need to solve the parenthesis first '2*(3-4)' */
		if (!nextOperator->isOperator())
			return nullptr;

		/* We always need to have 3 operators to compare for cases like '2-3*3#2'
			without this check it would have returned the multiply operator*/
		if (nextOperator->next()->next() != nullptr)
			return nullptr;

		if (tokenOperator->priority() >= nextOperator->priority())
			return tokenOperator;
		else if (nextOperator->next()->isNumber())
			return nextOperator;
		else
			return nullptr;  /* In this case it should not return the multiplication operator 2+2*(3-4) */
		
	}

	// 2+2*3 if we check this for the multiplication operator it has no next operator
	if (nextOperator == nullptr)
	{
		/* Used in case prevOperator is not a number and it's because tokenOperator's prev is a paraenthesis
		  and in this case we need to solve the parenthesis first '(3-4)*2'*/
		if (!prevOperator->isOperator())
			return nullptr;

		if (prevOperator->prev()->prev() != nullptr)
			return nullptr;

		if (tokenOperator->priority() >= prevOperator->priority())
			return tokenOperator;
		else if (prevOperator->prev()->isNumber())
			return prevOperator;
		else 
			return nullptr; /* In this case it should not return the multiplication operator (3-4)*2+2 */
	}

	// Search for the highest priority between all 3 operators and save it to check if it is valid
	const Token* returnOperator = priorityOperatorOfThree(tokenOperator, prevOperator, nextOperator);

	// Used to check if the both terms of the operation are numbers else the parenthesis needs to be solved
	if (!returnOperator->prev()->isNumber() || !returnOperator->next()->isNumber())
		return nullptr;

	return returnOperator;
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