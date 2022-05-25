#include <algorithm>
#include <iostream>
#include <exception>
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
	Card(Rank r, Suit s, bool hidden);
	std::string toString();
};

class Deck {
private:
	Card Stack[52];
	int deckSize = 52;
public:
	Deck();
	std::string toString();

	void Shuffle();
	Card dealCard();
};

class Hand {

};