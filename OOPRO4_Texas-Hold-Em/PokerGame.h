#include "PokerModel.h"
#include "PokerView.h"
#include "PokerController.h"
#include "Player.h"
#include <algorithm>
#pragma once

//Wrapper class for MVC model. Also stores player information to sustain between multiple rounds of play.
class PokerGame
{
private:
	PokerModel m;
	PokerView v;
	PokerController c;

	Player players[10];

	bool gameOn = true;

	void shufflePlayers();
	void rotatePlayers();
public:
	PokerGame();

	void playGame();
};