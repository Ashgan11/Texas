#include "PokerModel.h"
#include <exception>
#include <iostream>
#include <string>
#pragma once

//View component. Handles text output for the game.
class PokerView
{
private:
	PokerModel* model;
public:
	PokerView(PokerModel* m);

	//Setup Displays
	void displayStart();

	//Input Prompt Displays
	void displayPromptPlayerNumber();
	void displayPromptPlayerName();
	void displayPromptContinueGame();

	//Update Displays
	void displayTable();
	void displayOptions();

	//End Game Displays
	void displayFinalHand(int index);
	void displayPotDistribution(int totalPot);
	void displayWinner();
	void displayFinalTally();
	
	//Exception Display
	void displayException(std::exception e);
};