#include "Player.h"

Player::Player()
{
	
}

Player::Player(std::string n, int s = 100)
{
	name = n;
	chipsTotal = s;
}

std::string Player::toString()
{
	std::string output;
	std::string str_flag = enum_playerFlag[flag];
	output += name + " | Stack: " + std::to_string(chipsTotal) + " | Wager: " + std::to_string(chipsWager) + "\n" + hole[0].toString() + " " + hole[1].toString() + "\n" + str_flag + "\n\n";
	return output;
}

void Player::addWager(int amount)
{
	if (chipsTotal >= amount) {
		chipsTotal -= amount;
		chipsWager += amount;
	}
	else throw std::exception("Not enough chips!");
}

void Player::revealHole()
{
	hole[0].hidden = false;
	hole[1].hidden = false;
}

void Player::hideHole()
{
	hole[0].hidden = true;
	hole[1].hidden = true;
}

void Player::setFlag(playerFlag newFlag)
{
	if (flag != Fold && chipsTotal != 0) flag = newFlag;
}

void Player::setHole(Card newHole[2])
{
	hole[0] = newHole[0];
	hole[1] = newHole[1];
	//hole[0].hidden = false;
	//hole[1].hidden = false;
}

Card* Player::getHole()
{
	return hole;
}

playerFlag Player::getFlag()
{
	return flag;
}

int Player::getWager()
{
	return chipsWager;
}

int Player::getStack()
{
	return chipsTotal;
}

std::string Player::getName()
{
	return name;
}

bool Player::hasPlayerActed()
{
	return (flag != Unfinished);
}
