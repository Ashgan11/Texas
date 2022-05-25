#include "PokerModel.h"

Card PokerModel::dealCard()
{
    while (true) {
        Card newCard(static_cast<Cards::rank>(randomNumber(12)+2), static_cast<Cards::suit>(randomNumber(4)));
        if (!doesCardExist(newCard)) {
            dealtCards.push_back(newCard);
            return newCard;
        }
    }
}

bool PokerModel::doesCardExist(Card card)
{
    for (std::list<Card>::iterator it = dealtCards.begin(); it != dealtCards.end(); it++) {
        if (*it == card) return true;
    }
    return false;
}

void PokerModel::advanceCurrentPlayer() {
    if (++currentPlayer == players.end()) currentPlayer = players.begin();
}

bool PokerModel::isFoldLegal() {
    for (std::list<Player>::iterator it = players.begin(); it != players.end(); it++) {
        if (it->getPlayerFlag() == player::Finished) return false;
    }
    return true;
}

PokerModel::PokerModel()
{
    srand(time(NULL));

    //Deal Community Cards
    for (int i = 0; i < 5; i++) {
        Card newCard = dealCard();
        communityCards.push_back(newCard);
    }
}

int PokerModel::randomNumber(int max)
{
    return rand() % max;
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

int PokerModel::getHighestBet()
{
    return highestBet;
}

Player PokerModel::getPlayer(int index)
{
    std::list<Player>::iterator it = players.begin();
    for (int i = 0; i < index; i++) {
        it++;
    }
    return *it;
}

int PokerModel::getCurrentPlayerNumber()
{
    int iteration = 0;
    for (std::list<Player>::iterator it = players.begin(); it != currentPlayer; it++) {
        iteration++;
    }
    return iteration+1;
}

Card PokerModel::getCommunityCard(int index)
{
    std::list<Card>::iterator it = communityCards.begin();
    for (int i = 0; i < index; i++) {
        it++;
    }
    return *it;
}

bool PokerModel::allPlayersFinished()
{
    for (std::list<Player>::iterator it = players.begin(); it != players.end(); it++) {
        if (it->getPlayerFlag() == player::Unfinished || it->getPlayerFlag() == player::Check) return false;
    }
    return true;
}

void PokerModel::resetPlayerFlags()
{
    for (std::list<Player>::iterator it = players.begin(); it != players.end(); it++) {
        if (it->getPlayerFlag() != player::Fold) it->setPlayerFlag(player::Unfinished);
    }
    currentPlayer = players.begin();
    round++;
}

void PokerModel::checkFolds()
{
    int foldedPlayers = 0;
    for (std::list<Player>::iterator it = players.begin(); it != players.end(); it++) {
        if (it->getPlayerFlag() == player::Fold) foldedPlayers++;
    }
    if (foldedPlayers == players.size() - 1) {
        int playerIndex = 0;
        for (std::list<Player>::iterator it = players.begin(); it != players.end(); it++) {
            if (it->getPlayerFlag() != player::Fold) {
                gameState = playerIndex;
            }
            playerIndex++;
        }
    }
}

void PokerModel::addPlayer(std::string name, int stakes) {
    Player newPlayer(name, stakes);
    players.push_back(newPlayer);
    newPlayer.setHole(dealCard(), 0);
    newPlayer.setHole(dealCard(), 1);
}

void PokerModel::setStakes(int stakes) {
    for (std::list<Player>::iterator it = players.begin(); it != players.end(); it++) {
        it->setStake(stakes);
    }
}

void PokerModel::shufflePlayers()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(players.begin(), players.end(), std::default_random_engine(seed));
}

void PokerModel::playerCall() {
    currentPlayer->addBet(highestBet);
    currentPlayer->setPlayerFlag(player::Finished);
    advanceCurrentPlayer();
}

void PokerModel::playerRaise(int amount) {
    if (amount < highestBet * 2) throw std::invalid_argument("You must raise by at least twice the highest current bid!");
    else currentPlayer->addBet(amount);
    currentPlayer->setPlayerFlag(player::Finished);
    advanceCurrentPlayer();
    highestBet = amount;
}

void PokerModel::playerFold() {
    currentPlayer->setPlayerFlag(player::Fold);
    advanceCurrentPlayer();
    checkFolds();
}

void PokerModel::playerCheck() {
    if (isFoldLegal()) {
        currentPlayer->setPlayerFlag(player::Check);
        advanceCurrentPlayer();
    }
    else throw std::invalid_argument("You cannot check anymore in this round!");
}

void PokerModel::playerAllIn() {
    currentPlayer->addBet(currentPlayer->getStack());
}

void PokerModel::playerPick(int picks[5]) {
    //
}

void PokerModel::playerPostBlinds() {
    playerRaise(1);
    playerRaise(2);
}