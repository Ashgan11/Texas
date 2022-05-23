#include "PokerModel.h"
#include <iostream>
#pragma once

using namespace std;

class PokerView
{
private:
	PokerModel* model;
public:
	PokerView(PokerModel* m);
	void displayEmptyLine();
	void displayStart();
	void displayTable();
	void displayPlayerOptions();
	void displayPromptPlayerNumber();
	void displayPromptPlayerName();
	void displayPromptStakes();
	void displayPostBlinds();
	void displayPlayerHole();
	void displayWinner();
	void displayException(exception e);
};