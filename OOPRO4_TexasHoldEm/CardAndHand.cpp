#include "CardAndHand.h"

Card::Card(Cards::rank r, Cards::suit s)
{
	Rank = r;
	Suit = s;
}

std::string Card::toString()
{
	if (isHidden) return "[ ? ]";
	else return "[" + rankToString(Rank) + " " + suitToString(Suit) + "]";
}

std::string Cards::rankToString(rank r)
{
	return rankNames[r];
}

std::string Cards::suitToString(suit r)
{
	return suitNames[r];
}