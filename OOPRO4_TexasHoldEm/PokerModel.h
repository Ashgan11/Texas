#include <list>
#include <algorithm>
#include <random>
#include <chrono>
#include "Player.h"
#include "CardAndHand.h"
#pragma once

class PokerModel
{
private:
	std::list<Player> players;
	std::list<Card> dealtCards;
	std::list<Card> communityCards;
	int gameState = 0;
	int round = -1;
	int highestBet = 0;
	std::list<Player>::iterator currentPlayer = players.begin();

	Card dealCard();
	bool doesCardExist(Card card);
	void advanceCurrentPlayer();
	bool isFoldLegal();
public:
	PokerModel();
	int randomNumber(int max);
	int getGameState();
	int getRound();
	int getPlayerCount();
	int getHighestBet();
	Player getPlayer(int index);
	int getCurrentPlayerNumber();
	Card getCommunityCard(int index);
	bool allPlayersFinished();

	void resetPlayerFlags();
	void checkFolds();

	void addPlayer(std::string name, int stakes);
	void setStakes(int stakes);
	void shufflePlayers();

	//Player Actions
	void playerCall();
	void playerRaise(int amount);
	void playerFold();
	void playerCheck();
	void playerAllIn();
	void playerPick(int picks[5]);
	void playerPostBlinds();
};