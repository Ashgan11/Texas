#include "PokerModel.h"
#include "PokerView.h"
#include <string>
#include <exception>
#pragma once

class PokerController
{
private:
	PokerModel* model;
	PokerView* view;

	const int maxAllowedPlayers = 10;
	const int defaultStakes = 50;

	void initGame();
	void playerSetup();
	void tableStakes();
	void placeBlinds();

	void bettingRound();
	void showDown();

	void userInput();
	bool isNumber(const std::string& s);
public:
	PokerController(PokerModel* m, PokerView* v);

	void playGame();

	//std::string verifyInput(std::string input);
};