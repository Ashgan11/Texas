#include "PokerModel.h"

int PokerModel::getGameState()
{
    return gameState;
}

int PokerModel::getRound()
{
    return round;
}

int PokerModel::getPlayerCount()
{
    return players.size();
}

bool PokerModel::allPlayersFinished()
{
    for (std::list<Player>::iterator it = players.begin(); it != players.end(); it++) {
        if (it->getPlayerFlag() == Unfinished || it->getPlayerFlag() == Check) return false;
    }
    return true;
}

void PokerModel::resetPlayerFlags()
{
    for (std::list<Player>::iterator it = players.begin(); it != players.end(); it++) {
        if (it->getPlayerFlag() != Fold) it->setPlayerFlag(Unfinished);        
    }
    currentPlayer = &players.front();
}

void PokerModel::addPlayer(std::string name, int stakes) {
    Player newPlayer(name, stakes);
    players.push_back(newPlayer);
}

void PokerModel::setStakes(int stakes) {
    for (std::list<Player>::iterator it = players.begin(); it != players.end(); it++) {
        it->setStake(stakes);
    }
}