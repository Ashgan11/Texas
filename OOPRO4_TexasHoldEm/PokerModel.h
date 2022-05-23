#include <list>
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
	std::list<Player>::iterator currentPlayer;

	Card dealCard();
	void advanceCurrentPlayer();
	bool isFoldLegal();
public:
	int getGameState();
	int getRound();
	int getPlayerCount();
	bool allPlayersFinished();

	void resetPlayerFlags(); //Must reset currentPlayer to begin of list

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