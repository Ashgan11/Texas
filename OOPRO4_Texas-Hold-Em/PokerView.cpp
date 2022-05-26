#include "PokerView.h"

PokerView::PokerView(PokerModel* m)
{
	model = m;
}

void PokerView::displayStart()
{
	std::cout << "Welcome to Texas Hold 'Em Poker! \n\n";
}

void PokerView::displayPromptPlayerNumber()
{
	std::cout << "How many players do you want at the table?\n";
}

void PokerView::displayPromptPlayerName()
{
	std::cout << "Enter player name:\n";
}

void PokerView::displayWinner()
{
	displayTable();
	std::string winner = model->getPlayers()[model->getGameState() - 1].getName();
	std::cout << "Winner = " + winner;
}

void PokerView::displayTable()
{
	std::string str_round = std::to_string(model->getRound()+1);
	std::string roundName;

	switch (model->getRound()) {
	case 0:
		roundName = "Pre-Flop";
		break;
	case 1:
		roundName = "Flop";
		break;
	case 2:
		roundName = "Turn";
		break;
	case 3:
		roundName = "River";
		break;
	case 4:
		roundName = "Showdown";
		break;
	}

	//Display Round Header
	std::cout << "ROUND " + str_round + " - " + roundName + "\n";
	std::cout << "------------------\n";

	//Display Community Cards
	std::cout << "Community Cards: ";	
	for (int i = 0; i < 5; i++) std::cout << model->getCommunityCard(i).toString() + " ";

	//Display Highest Bid
	std::cout << "\nHighest Bid: " + std::to_string(model->getHighestBid()) + "\n\n";

	//Display Players
	for (int i = 0; i < model->getPlayerNumber(); i++) std::cout << model->getPlayers()[i].toString();
}

void PokerView::displayOptions()
{
	std::cout << "Options:\n";
	std::cout << "Call\n";
	std::cout << "Raise #\n";
	std::cout << "All In\n";
	std::cout << "Fold\n";
	std::cout << "Check\n";
	std::cout << "Peek\n\n";
}

void PokerView::displayException(std::exception e)
{
	std::cout << e.what();
	std::cout << "\n\n";
}
