#include <string>
#include "CardAndHand.h"
#pragma once

enum playerFlag {
	Unfinished,
	Finished,
	Check,
	Fold
};

static const char* playerFlag_str[] = {
	"Unfinished",
	"Finished",
	"Check",
	"Fold"
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
	Player();
	Player(std::string name, int stakes);

	playerFlag getPlayerFlag();
	void setPlayerFlag(playerFlag newFlag);

	int getStack();
	void setStake(int newStake);	

	int getCurBet();
	void addBet(int value);	

	std::string toString();
};