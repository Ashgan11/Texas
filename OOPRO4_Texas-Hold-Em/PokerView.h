#include "PokerModel.h"
#include <exception>
#include <iostream>
#include <string>
#pragma once
class PokerView
{
private:
	PokerModel* model;
public:
	PokerView(PokerModel* m);

	void displayStart();
	void displayPromptPlayerNumber();
	void displayPromptPlayerName();
	void displayWinner();
	void displayTable();
	void displayOptions();
	void displayException(std::exception e);
};