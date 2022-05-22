#include "CardAndHand.h"
#pragma once

enum playerFlag {
	Unfinished,
	Finished,
	Check,
	Fold
};

class Player
{
private:
	std::string name;
	int stack;
	int bet;
	Card hole[5];
	Hand hand;
	playerFlag flag;
public:
	Player(std::string name, int stakes);

	playerFlag getPlayerFlag();
	void setPlayerFlag(playerFlag newFlag);

	void setStake(int newStake);

	void bet(int value);
	std::string toString();
};