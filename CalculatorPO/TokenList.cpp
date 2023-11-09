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

void TokenList::solveCalculation(int index)
{
	auto& token         = pTokenList[index];
	auto leftNumber     = std::stof(pTokenList[index - 1].string());
	auto rightNumber    = std::stof(pTokenList[index + 1].string());

    auto result = 0.f;

    switch (token.string()[0]) {
    default:
        throw std::invalid_argument("Operator error");
        return;
    case '^':
        //stack.push_back(static_cast<int>(pow(lhs, rhs)));
        break;
    case '*':
        result = leftNumber * rightNumber;
        break;
    case '/':
        result = leftNumber / rightNumber;
        break;
    case '+':
        result = leftNumber + rightNumber;
        break;
    case '-':
        result = leftNumber - rightNumber;
        break;
    }

    pTokenList[index - 1] = { Token::Type::Number, std::to_string(result) };

    remove(index, 2);

    for (auto i = 0; i < size_; i++)
    {
        std::cout << pTokenList[i].string();
    }
    std::cout << '\n';
}