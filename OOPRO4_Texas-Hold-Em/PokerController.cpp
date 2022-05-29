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
	model->distributeCards();
	while (model->getGameState() == 0 && model->getRound() < 4) {
		bettingRound();
	}
	if (model->getGameState() == 0) showDown();
	view->displayPotDistribution(model->distributePot());
}

bool PokerController::continueGame()
{
	while (true) {
		try {
			view->displayPromptContinueGame();
			std::string input;
			input = getInput();
			inputToLower(input);
			if (input == "yes") return true;
			else if (input == "no") return false;
			else throw std::exception("Please respond with either \"yes\" or \"no\"");
		}
		catch (std::exception& e) {
			view->displayException(e);
		}
	}	
}

void PokerController::postBlinds()
{
	model->resetPlayerFlags();
	//Change order if heads-up game
	if (model->getPlayerNumber() == 2) model->advancePlayer();
	model->playerRaise(1);
	model->playerRaise(2);
}

void PokerController::bettingRound()
{
	while (!(model->allPlayersActed() && model->allWagersEqual()) && model->getGameState() == 0) {
		switch (model->getRound()) {
		case 1: {
			(*model->getCommunityCard(0)).hidden = false;
			(*model->getCommunityCard(1)).hidden = false;
			(*model->getCommunityCard(2)).hidden = false;
			break;
		}
		case 2: {
			(*model->getCommunityCard(3)).hidden = false;
			break;
		}
		case 3: {
			(*model->getCommunityCard(4)).hidden = false;
			break;
		}
		}
		view->displayTable();
		bettingRoundInput();
	}
	if (model->getGameState() == 0) model->endRound();
}

void PokerController::showDown()
{
	model->showDown();

	view->displayTable();

	for (int i = 0; i < model->getPlayerNumber(); i++) {
		view->displayFinalHand(i);
	}
}

void PokerController::bettingRoundInput()
{
	//Display Options
	view->displayOptions();
	//Get Input
	bool valid = false;
	while (!valid) {
		try {
			std::string input = getInput();
			inputToLower(input);
			switch (convertInput(input)) {
			case 0: {
				model->playerCall();
				valid = true;
				break;
			}
			case 1: {
				std::string remainingString = input.substr(input.find(" "));
				remainingString.erase(0, 1);
				if (isNumber(remainingString)) {
					model->playerRaise(stoi(remainingString));
					valid = true;
				}
				else throw std::invalid_argument("You must raise by a number!");
				break;
			}
			case 2: {
				model->playerFold();
				valid = true;
				break;
			}
			case 3: {
				model->playerCheck();
				valid = true;
				break;
			}
			case 4: {
				model->playerPeek();
				valid = true;
				break;
			}
			case 5: {
				model->playerAllIn();
				valid = true;
				break;
			}
			}
		}
		catch (std::exception& e) {
			view->displayException(e);
		}
	}
}

std::string PokerController::getInput()
{
	if (model->getActivePlayer() != nullptr && model->getGameState() == 0) std::cout << model->getActivePlayer()->getName() + " > ";
	else std::cout << "> ";
	std::string input;
	std::getline(std::cin, input);
	std::cout << "\n";
	return input;
}

int PokerController::convertInput(std::string input)
{
	if (input == "call") return 0;
	if ((input.substr(0, input.find(" ")) == "raise")) return 1;
	if (input == "fold") return 2;
	if (input == "check") return 3;
	if (input == "peek") return 4;
	if (input == "all in") return 5;
	else throw std::invalid_argument("Unrecognized input!");
}

void PokerController::inputToLower(std::string& input)
{
	std::transform(input.begin(), input.end(), input.begin(), 
		[](unsigned char c) {
			return std::tolower(c); 
		}
	);
}

bool PokerController::isNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}