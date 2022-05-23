#include "Player.h"

std::string flagToString(int flagVal) {
    std::string tmp(playerFlag_str[flagVal]);
    return tmp;
}

Player::Player(std::string name, int stakes)
{
    this->name = name;
    stack = stakes;
}

playerFlag Player::getPlayerFlag()
{
    return flag;
}

void Player::setPlayerFlag(playerFlag newFlag)
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

std::string Player::toString()
{
    std::string output;
    output += name + " | Stack: " + std::to_string(stack) + " | Bet: " + std::to_string(bet) + "\n" + flagToString(flag) + "\n\n";
    return output;
}