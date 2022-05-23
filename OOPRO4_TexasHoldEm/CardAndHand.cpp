#include "CardAndHand.h"

Card::Card()
{
}

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

int Card::getValue()
{
	return 0;
}

bool Card::operator==(Card const& other)
{
	return other.Rank == this->Rank;
}

std::ostream& Card::operator<<(std::ostream& os)
{	
	os << toString();
	return os;
}

std::string Cards::rankToString(rank r)
{
	return rankNames[r];
}

std::string Cards::suitToString(suit s)
{
	return suitNames[s];
}

Hand::Hand()
{
}

Hand::Hand(Card[5])
{
}

std::string Hand::toString()
{
	return std::string();
}

int Hand::getValue()
{
	return 0;
}
