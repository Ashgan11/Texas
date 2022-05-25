#include "CardAndDeck.h"

Deck::Deck()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			Stack[(j) + i * 13] = Card(static_cast<Rank>(j+2), static_cast<Suit>(i), true);
		}
	}
	Shuffle();
}

std::string Deck::toString()
{
	std::string output;
	for (int i = 0; i < 52; i++) {
		output += Stack[i].toString() + "\n";
	}
	return output;
}

void Deck::Shuffle()
{
	std::random_shuffle(Stack, Stack + 52);
}

Card Deck::dealCard()
{
	if (--deckSize <= 0) throw std::exception("No cards in deck!");
	else return Stack[deckSize - 1];
}

Card::Card()
{
	rank = Two;
	suit = Hearts;
}

Card::Card(Rank r, Suit s)
{
	rank = r;
	suit = s;
}

Card::Card(Rank r, Suit s, bool hidden)
{
	rank = r;
	suit = s;
	this->hidden = hidden;
}

std::string Card::toString()
{
	std::string str_rank = enum_Rank[rank - 2];
	std::string str_suit = enum_Suit[suit];
	if (hidden) return "[ ? ]";
	else return "[ " + str_rank + " " + str_suit + " ]";
}