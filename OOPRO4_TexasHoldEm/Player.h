#include <string>
#include "CardAndHand.h"
#pragma once

namespace player {
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
}

std::string flagToString(int flagVal);

class Player
{
private:
	std::string name;
	int stack;
	int bet;
	Card hole[2];
	Hand hand;
	player::playerFlag flag;
public:
	Player(std::string name, int stakes);

	player::playerFlag getPlayerFlag();
	void setPlayerFlag(player::playerFlag newFlag);

	int getStack();
	void setStake(int newStake);	

	int getCurBet();
	void addBet(int value);	

	void setHole(Card card, int index);

	std::string toString();
};