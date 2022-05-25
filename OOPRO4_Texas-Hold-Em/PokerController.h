#include "PokerModel.h"
#include "PokerView.h"
#include "Player.h"
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#include <string>
#include <exception>
#pragma once

//Controller component. Handles user input and passes instructions to the model (data) and view (output). Controller is responsible for the general flow of the program.
class PokerController
{
private:
	PokerModel* model;
	PokerView* view;
public:
	PokerController(PokerModel* m, PokerView* v);

	//Setup
	void playerSetup(Player* players);
	void playGame();

	//Gameplay
	void postBlinds();
	void bettingRound();
	void showDown();
	void bettingRoundInput();

	//Input Acquisition
	std::string getInput();

	//Input Validation
	bool isNumber(const std::string& s);
};