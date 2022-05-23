#include "Player.h"

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
