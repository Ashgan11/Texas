#include "PokerGame.h"

void PokerGame::shufflePlayers()
{
	std::random_shuffle(players, players + m.getPlayerNumber());
}

void PokerGame::rotatePlayers()
{
	Player first = players[0];
	for (int i = 0; i < m.getPlayerNumber()-1; i++) {
		players[i] = players[i + 1];
	}
	players[m.getPlayerNumber() - 1] = first;
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

	while (gameOn) {
		int num = 0;
		for (int i = 0; i < 10; i++) {
			if (players[i].getStack() >= 0) num++;
		}
		m = PokerModel(players, num);
		v = PokerView(&m);
		c = PokerController(&m, &v);

		c.playGame();
		if (c.continueGame()) rotatePlayers();
		else {
			gameOn = false;
			v.displayFinalTally();
		}
	}
}
