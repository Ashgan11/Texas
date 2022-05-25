#include "PokerController.h"

PokerController::PokerController(PokerModel* m, PokerView* v)
{
	model = m;
	view = v;
}

void PokerController::playerSetup(Player* players)
{
	view->displayStart();
	view->displayPromptPlayerNumber();
	
	bool valid = false;
	while (!valid) {
		try {
			std::string input;
			input = getInput();
			if (isNumber(input)) {
				int playerNumber = stoi(input);
				model->setPlayerNumber(playerNumber);
				if (playerNumber > 10) throw std::invalid_argument("You cannot have more than 10 players!");
				if (playerNumber < 2)  throw std::invalid_argument("You cannot have fewer than 2 players!");
				for (int i = 0; i < playerNumber; i++) {
					view->displayPromptPlayerName();
					input = getInput();
					players[i] = Player(input, 100);
				}
				valid = true;
			}
			else throw std::invalid_argument("You must input a number!");
		}
		catch (std::invalid_argument& e) {
			view->displayException(e);
		}
	}
	model->setPlayers(players);
}

void PokerController::playGame()
{
	postBlinds();
	while (model->getGameState() == 0 && model->getRound() < 4) {
		bettingRound();
	}
	if (model->getGameState() == 0) showDown();
	view->displayWinner();
}

void PokerController::postBlinds()
{
	//Change order if heads-up game
	if (model->getPlayerNumber() == 2) {
		model->advancePlayer();
		model->playerRaise(1);
		model->playerRaise(2);
		//Player post small blind -> advance -> post big blind
	}
	else {
		model->playerRaise(1);
		model->playerRaise(2);
	}
}

void PokerController::bettingRound()
{
	model->resetPlayerFlags();	

	while (!(model->allPlayersActed() && model->allWagersEqual())) {
		view->displayTable();
		bettingRoundInput();
	}
}

void PokerController::showDown()
{
	std::cout << "Showdown!";
}

void PokerController::bettingRoundInput()
{
	//Get Input
	std::string input = getInput();

	//End Activation
	model->advancePlayer();
}

std::string PokerController::getInput()
{	
	std::cout << "> ";
	std::string input;
	std::cin >> input;
	std::cout << "\n";
	return input;
}

bool PokerController::isNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
