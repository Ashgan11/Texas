#include "CardAndDeck.h"

Deck::Deck()
{
	//Initialize random seed
	srand(time(NULL));
	seed = rand() % 1000;

	//Initialize deck
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			Stack[(j) + i * 13] = Card(static_cast<Rank>(j+2), static_cast<Suit>(i), true);
		}
	}

	//Shuffle deck
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
	std::shuffle(Stack, Stack + 52, std::default_random_engine(seed));
}

Card Deck::dealCard()
{
	if (--deckSize <= 0) throw std::exception("No cards in deck!");
	else return Stack[deckSize];
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

Card::Card(int r, int s)
{
	rank = (Rank)r;
	suit = (Suit)s;
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

bool Card::operator<(Card const& other)
{
	return (rank < other.rank);
}

bool Card::operator==(int const& other)
{
	return (rank == other);
}

Hand::Hand(Card inputStack[7])
{
	for (int i = 0; i < 7; i++) {
		Stack[i] = inputStack[i];
		Stack[i].hidden = false;
	}
}

int Hand::getValue()
{
	if (handValue == -1) evaluateHand();
	return handValue;
}

std::string Hand::getName()
{
	if (handValue == -1) evaluateHand();
	return handName;
}

std::string Hand::toString()
{
	std::string output;
	for (int i = 0; i < 7; i++) {
		output += Stack[i].toString() + "\n";
	}
	return output;
}

void Hand::evaluateHand()
{
	//Evaluate Multiples
	std::array<int, 13> cardCounts;
	cardCounts[0]	= std::count(Stack.begin(), Stack.end(), 2);
	cardCounts[1]	= std::count(Stack.begin(), Stack.end(), 3);
	cardCounts[2]	= std::count(Stack.begin(), Stack.end(), 4);
	cardCounts[3]	= std::count(Stack.begin(), Stack.end(), 5);
	cardCounts[4]	= std::count(Stack.begin(), Stack.end(), 6);
	cardCounts[5]	= std::count(Stack.begin(), Stack.end(), 7);
	cardCounts[6]	= std::count(Stack.begin(), Stack.end(), 8);
	cardCounts[7]	= std::count(Stack.begin(), Stack.end(), 9);
	cardCounts[8]	= std::count(Stack.begin(), Stack.end(), 10);
	cardCounts[9]	= std::count(Stack.begin(), Stack.end(), 11);
	cardCounts[10]	= std::count(Stack.begin(), Stack.end(), 12);
	cardCounts[11]	= std::count(Stack.begin(), Stack.end(), 13);
	cardCounts[12]	= std::count(Stack.begin(), Stack.end(), 14);

	int pairs		= std::count(cardCounts.begin(), cardCounts.end(), 2);
	int threes		= std::count(cardCounts.begin(), cardCounts.end(), 3);
	int fours		= std::count(cardCounts.begin(), cardCounts.end(), 4);

	if (fours >= 1) {
		handValue = 8;
		handName = "Four-of-a-Kind";
	}
	else if (threes >= 1 && pairs >= 1) {
		handValue = 7;
		handName = "Full House";
	}
	else if (threes >= 1) {
		handValue = 4;
		handName = "Three-of-a-Kind";
	}
	else if (pairs >= 2) {
		handValue = 3;
		handName = "Two-Pair";
	}
	else if (pairs == 1) {
		handValue = 2;
		handName = "One-Pair";
	}

	//Evaluate Sequences
	//Flush
	bool flush = 0;
	bool straight = 0;

	std::sort(Stack.begin(), Stack.end(), sortByRank);
	std::sort(Stack.begin(), Stack.end(), sortBySuit);
	if (Stack[0].suit == Stack[4].suit || Stack[1].suit == Stack[5].suit || Stack[2].suit == Stack[6].suit) {
		flush = 1;
	}

	//Straight
	int count = 0;
	for (int i = 0; i < 6; i++) {
		if (Stack[i].rank + 1 == Stack[i + 1].rank) {
			if (++count == 4) straight = 1;
		}
		else if (!(Stack[i].rank == Stack[i + 1].rank)) count = 0;
	}

	
	if (straight && flush && handValue < 9) {
		handValue = 9;
		handName = "Straight Flush";
		if (Stack[0].rank == 10 && Stack[4].rank == 14 && Stack[0].suit == Stack[4].suit ||
			Stack[1].rank == 10 && Stack[5].rank == 14 && Stack[1].suit == Stack[5].suit ||
			Stack[2].rank == 10 && Stack[6].rank == 14 && Stack[2].suit == Stack[6].suit) {
				handValue = 10;
				handName = "Royal Flush";
		}
	}
	else if (flush && handValue < 6) {
		handValue = 6;
		handName = "Flush";
	}
	else {
		//TEST
		std::sort(Stack.begin(), Stack.end(), sortByRank);
		int count = 0;
		for (int i = 0; i < 6; i++) {
			if (Stack[i].rank + 1 == Stack[i + 1].rank) {
				if (++count == 4) straight = 1;
			}
			else if (!(Stack[i].rank == Stack[i + 1].rank)) count = 0;
		}
		//
		if (straight && handValue < 5) {
			handValue = 5;
			handName = "Straight";
		}
	}

	//Check if it is a flush, then if it is a straight
	//If both == 1 then its a straight flush -> check for royal flush on top (first card in sequence)
	//If only one == 1 then it is that
	//Else its not a sequence
	//And if it wasnt a multiple either then default to high card
	if (handValue == -1) {
		handValue = 1;
		handName = "High Card";
	}
}

bool Hand::royalFlush()
{
	return false;
}

bool Hand::straightFlush()
{
	return false;
}

bool Hand::flush()
{
	return false;
}

bool Hand::straight()
{
	return false;
}

bool sortByRank(Card a, Card b)
{
	return (a.rank < b.rank);
}

bool sortBySuit(Card a, Card b)
{
	return (a.suit < b.suit);
}
