#include "TokenList.h"

bool TokenList::existsParentheses()
{
	const Token* token = head;
	while (token != nullptr)
	{
		if (token->type() == Token::Type::LeftParenthesis
			|| token->type() == Token::Type::RightParenthesis)
			return true;

		token = token->next();
	}
	return false;
}

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

const Token* TokenList::getPriorityOperator(const Token* lToken, const Token* rToken)
{
	size_t maxPriority = 0;

	const Token* token = lToken, *returnToken = nullptr;;
	while (token != rToken && token != nullptr)
	{
		if (maxPriority == TOKEN_MAX_PRIORITY)
			break;

		if (token->type() != Token::Type::Operator)
		{
			token = token->next();
			continue;
		}

		// Search for operator that has the biggest priority in that parenthesis
		if (token->priority() <= maxPriority)
		{
			token = token->next();
			continue;
		}

		returnToken = token;
		maxPriority = token->priority();

		token = token->next();
	}

	return returnToken;
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