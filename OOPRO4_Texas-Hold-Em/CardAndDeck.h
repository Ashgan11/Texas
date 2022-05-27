#include <algorithm>
#include <iostream>
#include <exception>
#include <array>
#include <random>
#include <chrono>
#pragma once

enum Rank {
	Two=2,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
	Ace
};
static const char* enum_Rank[] = {
	"2 ",
	"3 ",
	"4 ",
	"5 ",
	"6 ",
	"7 ",
	"8 ",
	"9 ",
	"10",
	"J ",
	"Q ",
	"K ",
	"A "
};

enum Suit {
	Hearts,
	Clubs,
	Spades,
	Diamonds
};
static const char* enum_Suit[] = {
	"H",
	"C",
	"S",
	"D"
};

class Card {
public:
	Rank rank;
	Suit suit;
	bool hidden = false;

	Card();
	Card(Rank r, Suit s);
	Card(int r, int s);
	Card(Rank r, Suit s, bool hidden);
	std::string toString();

	bool operator < (Card const& other);
	bool operator == (int const& other);
};

class Deck {
private:
	Card Stack[52];
	int deckSize = 52;
	unsigned seed = 0;
public:
	Deck();
	std::string toString();

	void Shuffle();
	Card dealCard();
};

bool sortByRank(Card a, Card b);
bool sortBySuit(Card a, Card b);

class Hand {
private:
	std::array<Card, 7> Stack;
	std::string handName = "";
	int handValue = -1;

	void evaluateHand();

	//Individual Type Evaluations
	bool royalFlush();
	bool straightFlush();
	bool flush();
	bool straight();
	
public:
	Hand(Card inputStack[7]);
	int getValue();
	std::string getName();
	std::string toString();
};