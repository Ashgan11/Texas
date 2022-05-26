#include "CardAndDeck.h"
#include <string>
#pragma once

enum playerFlag {
	Unfinished,
	Finished,
	Fold
};
static const char* enum_playerFlag[] = {
		"Has Not Acted",
		"Has Acted",
		"Fold"
};

class Player
{
private:
	std::string name;

	int chipsTotal = 0;
	int chipsWager = 0;

	Card hole[2];

	playerFlag flag = Unfinished;

	Hand* hand = nullptr;
public:
	Player();
	Player(std::string n, int s);

	std::string toString();

	//Gameplay
	void addWager(int amount);
	void revealHole();
	void hideHole();

	//Setters
	void setFlag(playerFlag newFlag);
	void setHole(Card newHole[2]);

	//Getters
	Card* getHole();

	playerFlag getFlag();

	int getWager();
	int getStack();

	std::string getName();

	bool hasPlayerActed();
};