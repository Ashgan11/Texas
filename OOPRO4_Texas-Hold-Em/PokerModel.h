#include "Player.h"
#pragma once

struct playerHandPair {
	Player* player;
	Hand hand;
	int oldIndex;

	std::string toString();

	bool operator < (playerHandPair& other);
};

//Model component. Handles the game logic.
class PokerModel
{
private:
	Player* players;
	std::vector<Player*> winners;

	std::vector<playerHandPair> finalHands;

	Deck pokerDeck;

	Card communityCards[5];

	int playerNumber;
	int gameState = 0;
	int round = 0;
	int activePlayer = 0;
	int raisesCalled = 0;
public:
	PokerModel();
	PokerModel(Player* players, int playerNumber);

	//Gameplay
	void distributeCards();
	void checkFolds();
	void advancePlayer();
	void endRound();
	void showDown();
	int distributePot();
	playerHandPair getPlayerHandPair(int index);

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
	std::vector<Player*> getWinners();

	Card* getCommunityCard(int index);

	int getPlayerNumber();
	int getGameState();
	int getRound();
	int getHighestBid();	
	int getCurrentPot();

	//Boolean Validations
	bool allPlayersActed();
	bool allWagersEqual();
	bool isCheckLegal();
};