#include "TokenList.h"

int TokenList::getMaxPriority()
{
	auto maxPriority = -1;
	for (auto i = 0; i < size_; i++)
		if (pTokenList[i].priority() > maxPriority)
			maxPriority = pTokenList[i].priority();
	return maxPriority;
}

int TokenList::getMaxPriority(int lIndex, int rIndex)
{
    auto maxPriority = -1;
    for (auto i = lIndex + 1; i < rIndex; i++)
        if (pTokenList[i].priority() > maxPriority)
            maxPriority = pTokenList[i].priority();
    return maxPriority;
}

bool TokenList::existsParentheses()
{
	for (auto i = 0; i < size_; i++)
		if (pTokenList[i].type() == Token::Type::LeftParenthesis
			|| pTokenList[i].type() == Token::Type::RightParenthesis)
			return true;
    return false;
}

void TokenList::remove(int index, int size)
{
    memmove(&pTokenList[index], &pTokenList[index + size], (size_ - size) * sizeof(Token));
    size_ -= size;
}