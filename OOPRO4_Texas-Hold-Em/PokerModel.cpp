#include "PokerModel.h"

PokerModel::PokerModel()
{
}

PokerModel::PokerModel(Player* players, int playerNumber)
{
	this->players = players;
	this->playerNumber = playerNumber;
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

void PokerModel::showDown()
{
	for (int i = 0; i < playerNumber; i++) {
		players[i].revealHole();
		Card cardStack[7]{
				communityCards[0],
				communityCards[1],
				communityCards[2],
				communityCards[3],
				communityCards[4],
				players[i].getHole()[0],
				players[i].getHole()[1]
		};
		Hand newHand(cardStack);
		finalHands.push_back({ &players[i], newHand, i });
	}

	std::sort(finalHands.begin(), finalHands.end());

	for (std::vector<playerHandPair>::iterator it = finalHands.begin(); it < finalHands.end(); it++) {
		if (it->hand.getValue() == finalHands.back().hand.getValue()) {
			winners.push_back(it->player);
		}
	}
	if (winners.size()>1) {
		gameState = -1;
	}
	else {		
		gameState = finalHands.back().oldIndex;
	}
}

int PokerModel::distributePot()
{
	int totalPot = 0;
	for (int i = 0; i < playerNumber; i++) {
		totalPot += players[i].getWager();
		players[i].resetWager();
	}
	for (std::vector<Player*>::iterator it = winners.begin(); it < winners.end(); it++) {
		(*it)->receiveWinnings(totalPot / winners.size());
	}

	//If the pot is not cleanly divisible, add the odd chip to the player closest to the "left" of the dealer
	if (totalPot % winners.size()) {
		(*winners.begin())->receiveWinnings(1);
	}

	return totalPot;
}

playerHandPair PokerModel::getPlayerHandPair(int index)
{
	return finalHands[index];
}

void PokerModel::distributeCards()
{
	//Testing set of fixed cards
	//communityCards[0] = Card(Two, Spades);
	//communityCards[1] = Card(Two, Hearts);
	//communityCards[2] = Card(Four, Spades);
	//communityCards[3] = Card(Five, Spades);
	//communityCards[4] = Card(Six, Spades);

	for (int i = 0; i < 5; i++) {
		communityCards[i] = pokerDeck.dealCard();
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
		winners.push_back(&players[winningIndex]);
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
		players[i].resetFlag();
	}

	//Reset table activation order at end of round
	activePlayer = 0;
}

Player* PokerModel::getPlayers()
{
	return players;
}

std::vector<Player*> PokerModel::getWinners()
{
	return winners;
}

Card* PokerModel::getCommunityCard(int index)
{
	if (index < 5 && index >= 0) return &communityCards[index];
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

int PokerModel::getCurrentPot()
{
	int totalPot = 0;
	for (int i = 0; i < playerNumber; i++) {
		totalPot += players[i].getWager();
	}
	return totalPot;
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

std::string playerHandPair::toString()
{
	return player->getName() + ": " + hand.getName() + "(" + std::to_string(hand.getValue()) + ")";
}

bool playerHandPair::operator<(playerHandPair& other)
{
	return hand.getValue() < other.hand.getValue();
}