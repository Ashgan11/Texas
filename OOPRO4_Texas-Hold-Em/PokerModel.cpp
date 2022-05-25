#include "PokerModel.h"

PokerModel::PokerModel()
{
}

void PokerModel::advancePlayer()
{
	if (++activePlayer == playerNumber) activePlayer = 0;
}

void PokerModel::checkFolds()
{
	int activePlayers = 0;
	int winningIndex = -1;
	for (int i = 0; i < playerNumber; i++) {
		if (players[i].getFlag() != Fold) {
			activePlayers++;
			winningIndex = i;
		}
	}
	if (activePlayers == 1) {
		gameState = winningIndex;
	}
}

void PokerModel::playerCall()
{
	getActivePlayer()->addWager(getHighestBid());
	getActivePlayer()->setFlag(Finished);
	advancePlayer();
}

void PokerModel::playerRaise(int amount)
{
	if (amount >= getHighestBid() * 2) {
		getActivePlayer()->addWager(amount);
		getActivePlayer()->setFlag(Finished);
		advancePlayer();
	}
	else throw std::exception("Wager must be at least twice the value of the current highest bid!");
}

void PokerModel::playerFold()
{
	getActivePlayer()->setFlag(Fold);
	advancePlayer();
	checkFolds();
}

void PokerModel::playerCheck()
{
	if (isCheckLegal()) {
		getActivePlayer()->setFlag(Finished);
		advancePlayer();
	}
	else throw std::exception("You cannot check when someone else has already pitched a wager this round!");
}

void PokerModel::playerAllIn()
{
	getActivePlayer()->addWager(getActivePlayer()->getStack());
	advancePlayer();
}

void PokerModel::setPlayers(Player* p)
{
	players = p;
}

void PokerModel::setPlayerNumber(int n)
{
	playerNumber = n;
}

void PokerModel::resetPlayerFlags()
{
	for (int i = 0; i < playerNumber; i++) {
		players[i].setFlag(Unfinished);
	}
}

Player* PokerModel::getPlayers()
{
	return players;
}

Card PokerModel::getCommunityCard(int index)
{
	if (index < 5 && index >= 0) return communityCards[index];
	else throw std::exception("Bad access to communityCards!");
}

int PokerModel::getPlayerNumber()
{
	return playerNumber;
}

int PokerModel::getGameState()
{
	return gameState;
}

int PokerModel::getRound()
{
	return round;
}

int PokerModel::getHighestBid()
{
	int highBid = 0;
	for (int i = 0; i < playerNumber; i++) {
		if (players[i].getWager() > highBid) highBid = players[i].getWager();
	}
	return highBid;
}

Player* PokerModel::getActivePlayer()
{
	return &players[activePlayer];
}

bool PokerModel::allPlayersActed()
{
	for (int i = 0; i < playerNumber; i++) {
		if (!players[i].hasPlayerActed()) return false;
	}
	return true;
}

bool PokerModel::allWagersEqual()
{
	int currentWager = 0;
	for (int i = 0; i < playerNumber; i++) {
		if (players[i].getFlag() != Fold) currentWager = players[i].getWager();
	}
	for (int i = 0; i < playerNumber; i++) {
		if (players[i].getFlag() != Fold && players[i].getWager() != currentWager) return false;
	}
	return true;
}

bool PokerModel::isCheckLegal()
{
	return false;
}
