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

void PokerView::displayFinalHand(int index)
{
	std::cout << model->getPlayerHandPair(index).toString() + "\n";
}

void PokerView::displayPotDistribution(int totalPot)
{
	std::vector<Player*> winnerRef = model->getWinners();
	if (model->getWinners().size() > 1) {
		std::cout << "\nA pot of " + std::to_string(totalPot) + " has been divided between:\n";
		for (std::vector<Player*>::iterator it = winnerRef.begin(); it < winnerRef.end(); it++) {
			std::string winner = (*it)->getName();
			std::cout << winner + "\n";
		}
	}
	else {
		std::cout << "\nA pot of " + std::to_string(totalPot) + " has been awared to: " + (*winnerRef.begin())->getName();
	}
	std::cout << "\nCongratulations!\n";
}

void PokerView::displayWinner()
{
	if (model->getGameState() > 0) {
		//std::string winner = model->getPlayers()[model->getGameState() - 1].getName();
		std::string winner = model->getWinners().back()->getName();
		std::cout << "Winner = " + winner;
	}
	else {
		std::vector<Player*> winnerRef = model->getWinners();
		std::cout << "\nWinners: \n";
		for (std::vector<Player*>::iterator it = winnerRef.begin(); it < winnerRef.end(); it++) {
			std::string winner = (*it)->getName();
			std::cout << winner + "\n";
		}
	}
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
	for (int i = 0; i < 5; i++) std::cout << (*model->getCommunityCard(i)).toString() + " ";

	//Display Highest Bid
	std::cout << "\nHighest Bid: " + std::to_string(model->getHighestBid()) + "\n";

	//Display Current Pot
	std::cout << "\nCurrent Pot: " + std::to_string(model->getCurrentPot()) + "\n\n";

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

void PokerView::displayFinalTally()
{
	std::cout << "Final Tally\n-----------\n";
	for (int i = 0; i < model->getPlayerNumber(); i++) {
		std::cout << model->getPlayers()[i].getName() + ": " + std::to_string(model->getPlayers()[i].getStack()) + " chips\n";
	}
}

void PokerView::displayPromptContinueGame()
{
	std::cout << "Do you want to play another round?\n";
}

void PokerView::displayException(std::exception e)
{
	std::cout << e.what();
	std::cout << "\n\n";
}
