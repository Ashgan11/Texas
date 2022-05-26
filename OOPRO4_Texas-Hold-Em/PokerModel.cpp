#include "PokerModel.h"

PokerModel::PokerModel()
{
}

void PokerModel::advancePlayer()
{
	getActivePlayer()->hideHole();
	if (++activePlayer == playerNumber) activePlayer = 0;
	if (getActivePlayer()->getFlag() == Fold || getActivePlayer()->getStack() == 0) advancePlayer();
}

void PokerModel::endRound()
{
	round++;
	raisesCalled = 0;
	resetPlayerFlags();	
}

void PokerModel::distributeCards()
{
	for (int i = 0; i < 5; i++) {
		communityCards[i] = pokerDeck.dealCard();
		//communityCards[i].hidden = false;
	}
	for (int i = 0; i < playerNumber; i++) {
		Card newHole[2]{ pokerDeck.dealCard(),pokerDeck.dealCard() };
		players[i].setHole(newHole);
	}
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
		gameState = winningIndex+1;
	}
}

void PokerModel::playerCall()
{
	int missingWager = getHighestBid() - getActivePlayer()->getWager();
	if (missingWager != 0) {
		getActivePlayer()->addWager(missingWager);
		getActivePlayer()->setFlag(Finished);
		advancePlayer();
	}
	else throw std::invalid_argument("Cannot call when your wager already matches the highest bid!");
}

void PokerModel::playerRaise(int amount)
{
	if (++raisesCalled > 3) throw std::exception("A raise cannot be called more than three times per betting round!");
	if (amount >= getHighestBid() * 2) {
		getActivePlayer()->addWager(amount-getActivePlayer()->getWager());
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
		//getActivePlayer()->setFlag(Finished);
		advancePlayer();
	}
	else throw std::exception("You cannot check when someone else has already pitched a wager this round!");
}

void PokerModel::playerPeek()
{
	getActivePlayer()->revealHole();
}

void PokerModel::playerAllIn()
{
	getActivePlayer()->addWager(getActivePlayer()->getStack());
	getActivePlayer()->setFlag(Finished);
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
	//Set everyone's flag to unfinished (unless they folded)
	for (int i = 0; i < playerNumber; i++) {
		players[i].setFlag(Unfinished);
	}

	//Reset table activation order at end of round
	activePlayer = 0;
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
	for (int i = 0; i < playerNumber; i++) {
		if (players[i].getFlag() == Finished) return false;
	}
	return true;
}
