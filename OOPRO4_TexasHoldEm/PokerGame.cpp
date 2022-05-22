#include "PokerGame.h"

void PokerGame::playGame()
{
	PokerModel m;
	PokerView v(&m);
	PokerController c(&m, &v);

	//While loop could be introduced to play consecutive rounds with persistent data
	c.playGame();
}
