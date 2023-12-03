#include "TokenList.h"

bool TokenList::existsParentheses()
{
	for (size_t i = 0; i < size_; ++i)
		if (pTokenList[i].type() == Token::Type::LeftParenthesis
			|| pTokenList[i].type() == Token::Type::RightParenthesis)
			return true;
	return false;
}

bool TokenList::existsOperators(size_t lIndex, size_t rIndex)
{
	for (size_t i = lIndex; i < rIndex; ++i)
		if (pTokenList[i].type() == Token::Type::Operator)
			return true;
	return false;
}

void TokenList::remove(size_t index, size_t size)
{
	/*memmove(&pTokenList[index], &pTokenList[index + size], (size_ - size) * sizeof(Token));*/
	while (size)
	{
		for (size_t i = index; i < size_ - 1; ++i)
			pTokenList[i] = pTokenList[i + 1];
		size_ -= 1;
		size -= 1;
	}
}

size_t TokenList::getPriorityOperator(size_t lIndex, size_t rIndex)
{
	size_t index = 0;
	size_t maxPriority = 0;
	for (size_t i = lIndex + 1; i < rIndex; ++i)
	{
		const Token& token = pTokenList[i];

		//if maxPriority is 4 it's already the maximum possible (efficiency)
		if (maxPriority == TOKEN_MAX_PRIORITY)
			break;

		if (token.type() != Token::Type::Operator)
			continue;

		// Search for operator that has the biggest priority in that parenthesis
		if (token.priority() <= maxPriority)
			continue;

		index = i;
		maxPriority = token.priority();
	}
	return index;
}
