#include "PokerModel.h"

void PokerModel::advanceCurrentPlayer() {
    if (++currentPlayer == players.end()) currentPlayer = players.begin();
}

bool PokerModel::isFoldLegal() {
    for (std::list<Player>::iterator it = players.begin(); it != players.end(); it++) {
        if (it->getPlayerFlag() == Finished) return false;
    }
    return true;
}

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
    currentPlayer = players.begin();
}

void PokerModel::addPlayer(std::string name, int stakes) {
    Player newPlayer(name, stakes);
    players.push_back(newPlayer);

    //TODO: deal cards
}

void PokerModel::setStakes(int stakes) {
    for (std::list<Player>::iterator it = players.begin(); it != players.end(); it++) {
        it->setStake(stakes);
    }
}

void PokerModel::playerCall() {
    currentPlayer->addBet(highestBet);
    currentPlayer->setPlayerFlag(Finished);
    advanceCurrentPlayer();
}

void PokerModel::playerRaise(int amount) {
    if (amount < highestBet * 2) throw std::invalid_argument("You must raise by at least twice the highest current bid!");
    else currentPlayer->addBet(amount);
    currentPlayer->setPlayerFlag(Finished);
    advanceCurrentPlayer();
}

void PokerModel::playerFold() {
    currentPlayer->setPlayerFlag(Fold);
    advanceCurrentPlayer();
}

void PokerModel::playerCheck() {
    if (isFoldLegal()) {
        currentPlayer->setPlayerFlag(Check);
        advanceCurrentPlayer();
    }
    else throw std::invalid_argument("You cannot fold anymore in this round!");
}

void PokerModel::playerAllIn() {
    currentPlayer->addBet(currentPlayer->getStack());
}

void PokerModel::playerPick(int picks[5]) {
    //
}

void PokerModel::playerPostBlinds() {
    currentPlayer->addBet(1);
    advanceCurrentPlayer();
    currentPlayer->addBet(2);
    advanceCurrentPlayer();
}