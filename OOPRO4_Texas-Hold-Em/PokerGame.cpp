#include "PokerGame.h"

void PokerGame::shufflePlayers()
{
	std::random_shuffle(players, players + m.getPlayerNumber());
}

PokerGame::PokerGame(): m(), v(&m), c(&m, &v) {
	for (int i = 0; i < 10; i++) {
		players[i] = Player();
	}
}

void PokerGame::playGame()
{
	c.playerSetup(players);
	shufflePlayers();
	c.playGame();
}
