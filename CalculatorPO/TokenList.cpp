#include "TokenList.h"

bool TokenList::existsParentheses()
{
	for (auto i = 0; i < size_; ++i)
		if (pTokenList[i].type() == Token::Type::LeftParenthesis
			|| pTokenList[i].type() == Token::Type::RightParenthesis)
			return true;
	return false;
}

bool TokenList::existsOperators(size_t lIndex, size_t rIndex)
{
	for (auto i = lIndex; i < rIndex; ++i)
		if (pTokenList[i].type() == Token::Type::Operator)
			return true;
	return false;
}

void TokenList::remove(size_t index, size_t size)
{
	/*memmove(&pTokenList[index], &pTokenList[index + size], (size_ - size) * sizeof(Token));*/
	while (size)
	{
		for (int i = index; i < size_ - 1; ++i)
			pTokenList[i] = pTokenList[i + 1];
		size_ -= 1;
		size -= 1;
	}
}

size_t TokenList::getMaxPriority(size_t lIndex, size_t rIndex)
{
	size_t maxPriority = 0;
	for (auto i = lIndex + 1; i < rIndex; ++i)
	{
		const auto& token = pTokenList[i];
		if (token.type() != Token::Type::Operator)
			continue;

		if (token.priority() > maxPriority)
			maxPriority = token.priority();
	}
	return maxPriority;
}

size_t TokenList::getPriorityOperator(size_t lIndex, size_t rIndex)
{
	size_t index = 0;
	const auto maxPriority = getMaxPriority(lIndex, rIndex);
	for (auto i = lIndex + 1; i < rIndex; ++i)
	{
		const auto& token = pTokenList[i];

		if (token.type() != Token::Type::Operator)
			continue;

		// Search for operator that has the biggest priority in that parenthesis
		if (token.priority() != maxPriority)
			continue;

		index = i;
		break;
	}
	return index;
}