#include "Player.h"

std::string flagToString(int flagVal) {
    std::string tmp(player::playerFlag_str[flagVal]);
    return tmp;
}

Player::Player(std::string name, int stakes)
{
    this->name = name;
    stack = stakes;
}

std::string Player::getName()
{
    return name;
}

player::playerFlag Player::getPlayerFlag()
{
    return flag;
}

void Player::setPlayerFlag(player::playerFlag newFlag)
{
    flag = newFlag;
}

int Player::getStack()
{
    return stack;
}

void Player::setStake(int newStake)
{
    stack = newStake;
}

int Player::getCurBet()
{
    return bet;
}

void Player::addBet(int value)
{
    if (stack < value) throw std::invalid_argument("You do not have enough chips to do this!");
    else {
        stack -= value;
        bet += value;
    }
}

void Player::setHole(Card card, int index)
{
    hole[index] = card;
}

std::string Player::toString()
{
    std::string output;
    output += name + " | Stack: " + std::to_string(stack) + " | Bet: " + std::to_string(bet) + "\n" + flagToString(static_cast<int>(flag)) + "\n\n";
    return output;
}