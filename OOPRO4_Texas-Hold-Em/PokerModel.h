#include "Player.h"
#pragma once

//Model component. Handles the game logic.
class PokerModel
{
private:
	Player* players;

	Deck pokerDeck;

	Card communityCards[5];

	int playerNumber;
	int gameState = 0;
	int round = 0;
	int activePlayer = 0;
	int raisesCalled = 0;
public:
	PokerModel();

	//Gameplay
	void distributeCards();
	void checkFolds();
	void advancePlayer();
	void endRound();

	//Player Actions
	void playerCall();
	void playerRaise(int amount);
	void playerFold();
	void playerCheck();
	void playerPeek();
	void playerAllIn();

	//Setters
	void setPlayers(Player* p);
	void setPlayerNumber(int n);
	void resetPlayerFlags();

	//Getters
	Player* getActivePlayer();
	Player* getPlayers();

	Card getCommunityCard(int index);

	int getPlayerNumber();
	int getGameState();
	int getRound();
	int getHighestBid();	

	//Boolean Validations
	bool allPlayersActed();
	bool allWagersEqual();
	bool isCheckLegal();
};