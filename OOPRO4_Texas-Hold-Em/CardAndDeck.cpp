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

	if (fours == 1) {
		int index = 0;
		for (int i = 0; i < 13; i++) {
			if (cardCounts[i] == 4) index = i;
		}
		updateHandValue((index + 2) + 103, "Four-of-a-Kind");
	}
	else if (threes >= 1 && pairs >= 1) {
		int indexThrees = 0;
		for (int i = 0; i < 13; i++) {
			if (cardCounts[i] == 3) indexThrees = i;
		}
		int indexPairs = 0;
		for (int i = 0; i < 13; i++) {
			if (cardCounts[i] == 2) indexPairs = i;
		}
		updateHandValue((indexThrees + 2) + (indexPairs + 2) + 77, "Full House");
	}
	else if (threes >= 1) {
		int index = 0;
		for (int i = 0; i < 13; i++) {
			if (cardCounts[i] == 3) index = i;
		}
		updateHandValue((index + 2) + 49, "Three-of-a-Kind");
	}
	else if (pairs >= 2) {
		int indexFirst = 0;
		int indexSecond = 0;
		for (int i = 12; i >= 0; i--) {
			if (cardCounts[i] == 2 && indexFirst == 0) indexFirst = i;
			else if (cardCounts[i] == 2 && indexSecond == 0) indexSecond = i;
		}
		updateHandValue((indexFirst + 2) + (indexSecond + 2) + 23, "Two-Pair");
	}
	else if (pairs == 1) {
		int index = 0;
		for (int i = 0; i < 13; i++) {
			if (cardCounts[i] == 2) index = i;
		}
		updateHandValue((index + 2) + 13, "One-Pair");
	}

	//Evaluate Sequences
	bool flush = 0;
	bool straight = 0;

	std::sort(Stack.begin(), Stack.end(), sortByRank);
	std::sort(Stack.begin(), Stack.end(), sortBySuit);
	if (Stack[0].suit == Stack[4].suit || Stack[1].suit == Stack[5].suit || Stack[2].suit == Stack[6].suit) {
		flush = 1;
	}

	int count = 0;
	int highIndex = 0;
	for (int i = 0; i < 6; i++) {
		if (Stack[i].rank + 1 == Stack[i + 1].rank) {
			if (++count == 4) {
				straight = 1;
				highIndex = i+1;
			}
		}
		else if (!(Stack[i].rank == Stack[i + 1].rank)) count = 0;
	}

	
	if (straight && flush) {
		updateHandValue(Stack[highIndex].rank + 112, "Straight Flush");
		if (Stack[0].rank == 10 && Stack[4].rank == 14 && Stack[0].suit == Stack[4].suit ||
			Stack[1].rank == 10 && Stack[5].rank == 14 && Stack[1].suit == Stack[5].suit ||
			Stack[2].rank == 10 && Stack[6].rank == 14 && Stack[2].suit == Stack[6].suit) {
				updateHandValue(130, "Royal Flush");
		}
	}
	else if (flush) {
		updateHandValue(Stack[highIndex].rank + 67, "Flush");
	}
	else {
		std::sort(Stack.begin(), Stack.end(), sortByRank);
		int count = 0;
		for (int i = 0; i < 6; i++) {
			if (Stack[i].rank + 1 == Stack[i + 1].rank) {
				if (++count == 4) {
					straight = 1;
					highIndex = i+1;
				}
			}
			else if (!(Stack[i].rank == Stack[i + 1].rank)) count = 0;
		}
		if (Stack[0].rank == 14 && Stack[4].rank == 5 ||
			Stack[1].rank == 14 && Stack[5].rank == 5 ||
			Stack[2].rank == 14 && Stack[6].rank == 5) {
			straight = 1;
		}
		if (straight && handValue < 5) {
			updateHandValue(Stack[highIndex].rank + 58, "Straight");
		}
	}

	//Default: High Card
	if (handValue == -1) {
		updateHandValue(getHighCard(), "High Card");
	}
}

int Hand::getHighCard()
{
	int highVal = 0;
	for (int i = 0; i < 7; i++) {
		if (Stack[i].rank > highVal) highVal = Stack[i].rank;
	}
	return highVal;
}

void Hand::updateHandValue(int newVal, std::string newName)
{
	if (handValue < newVal) {
		handValue = newVal;
		handName = newName;
	}
}

bool sortByRank(Card a, Card b)
{
	return (a.rank < b.rank);
}

bool sortBySuit(Card a, Card b)
{
	return (a.suit < b.suit);
}
