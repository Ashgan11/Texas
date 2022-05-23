#include "PokerView.h"

PokerView::PokerView(PokerModel* m)
{
	model = m;
}

void PokerView::displayStart()
{
	cout << "Welcome to Texas Hold 'Em Poker! \n\n";
}

void PokerView::displayTable()
{
	std::string round_str = to_string(model->getRound());
	std::string round_name;

	switch (model->getRound()) {
	case 0: {
		round_name = "Pre-Flop";
		break;
	}
	case 1: {
		round_name = "Flop";
		break;
	}
	case 2: {
		round_name = "Turn";
		break;
	}
	case 3: {
		round_name = "River";
		break;
	}
	case 4: {
		round_name = "Showdown";
		break;
	}
	}

	cout << "ROUND " + round_str + " - " + round_name + "\n";
	cout << "------------------\n\n";
	cout << "Community Cards: ";
	for (int i = 0; i < 5; i++) cout << model->getCommunityCard(i).toString() + " ";
	cout << "Highest Bid: " + to_string(model->getHighestBet()) + "\n\n";
	for (int i = 0; i < model->getPlayerCount(); i++) model->getPlayer(i).toString() + "\n\n";
}

void PokerView::displayPlayerOptions()
{
	cout << "Options:\n";
	cout << "Call\n";
	cout << "Raise #\n";
	cout << "All In\n";
	cout << "Fold\n";
	cout << "Check\n";
	cout << "Peek\n\n";
	cout << "Player" + to_string(model->getCurrentPlayerNumber()) + ": ";
}

void PokerView::displayPromptPlayerNumber()
{
	cout << "How many players do you want at the table?\n";
}

void PokerView::displayPromptPlayerName()
{
	cout << "Enter player name:\n";
}

void PokerView::displayPromptStakes()
{
	cout << "Set the stakes for this game:\n";
}

void PokerView::displayPostBlinds()
{
	int bigBlind = model->getHighestBet();
	cout << "Small Blind: " + to_string(bigBlind / 2) + "\nBig Blind: " + to_string(bigBlind) + "\n";
}

void PokerView::displayPlayerHole()
{
	cout << "Display Plyer Hole";
}

void PokerView::displayWinner()
{
	int winnerIndex = model->getGameState();
	cout << "Congratulations player " + to_string(winnerIndex);
}

void PokerView::displayException(exception e)
{
	cout << e.what();
}
