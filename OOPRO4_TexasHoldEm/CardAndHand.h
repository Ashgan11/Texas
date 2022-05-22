#include <iostream>
#include <list>
#pragma once

namespace Cards {
	enum winningHand { 
		HighCard, 
		OnePair			= 20, 
		TwoPair			= 30,
		ThreeOfAKind	= 40,
		Straight		= 50,
		Flush			= 60,
		FullHouse		= 70,
		FourOfAKind		= 80,
		StraightFlush	= 90,
		RoyalFlush		= 100
	};
	enum rank {
		Two		= 2,
		Three	= 3,
		Four	= 4,
		Five	= 5,
		Six		= 6,
		Seven	= 7,
		Eight	= 8,
		Nine	= 9,
		Ten		= 10,
		Jack	= 11,
		Queen	= 12,
		King	= 13,
		Ace		= 14
	};
	enum suit {
		Spades,
		Hearts,
		Clubs,
		Diamonds
	};
}

class Card {
private:
	Cards::rank Rank;
	Cards::suit Suit;
public:
	Card();
	std::string toString();
	int getValue();

	//Used when dealing cards to see if the newly generated card already exists in the game.
	bool operator == (Card const& other);

	//Used to output to string directly.
	std::ostream& operator<<(std::ostream& os);
};

class Hand {
public:
	std::list<Card> cards;

	Hand(Card[5]);
	std::string toString();
	int getValue();
};