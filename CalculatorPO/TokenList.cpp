#include "TokenList.h"

int TokenList::getMaxPriority()
{
	auto maxPriority = -1;
	for (auto i = 0; i < size_; i++)
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
}


void TokenList::solve(int index)
{
	auto& token = pTokenList[index];
	auto& leftToken = pTokenList[index - 1];
	auto& rightToken = pTokenList[index + 1];
}