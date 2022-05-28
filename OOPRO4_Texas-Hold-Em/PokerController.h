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
	
	//Gameplay
	void postBlinds();
	void bettingRound();	
	void bettingRoundInput();
	void showDown();

	//Input Acquisition
	std::string getInput();	
	int convertInput(std::string input);
	void inputToLower(std::string &input);	

	//Input Validation
	bool isNumber(const std::string& s);

public:
	PokerController(PokerModel* m, PokerView* v);

	//Setup
	void playerSetup(Player* players);
	void playGame();

	//Game Continuation
	bool continueGame();
};