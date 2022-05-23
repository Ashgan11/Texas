#include "PokerController.h"

PokerController::PokerController(PokerModel* m, PokerView* v)
{
	model = m;
	view = v;
}

void PokerController::playGame()
{
	initGame(); //Deals with small & big blind, adjusts activeplayer
	while (model->getGameState() == 0 && model->getRound() < 4) {
		bettingRound();
	}
	if (model->getGameState() == 0) showDown();
	view->displayWinner();
}

void PokerController::initGame()
{
	view->displayStart();
	playerSetup();
	tableStakes();
	placeBlinds();
}

void PokerController::playerSetup()
{
	view->displayPromptPlayerNumber();
	bool valid = false;
	while (!valid) {
		try {
			std::string input;
			cin >> input;
			if (isNumber(input)) {
				int playerNumber = stoi(input);
				if (playerNumber > maxAllowedPlayers) throw invalid_argument("You cannot have more than 10 players!");
				else if (playerNumber < 2) throw invalid_argument("You cannot play with fewer than 2 players!");
				for (int i = 0; i < playerNumber; i++) {
					view->displayPromptPlayerName();
					cin >> input;
					model->addPlayer(input, defaultStakes);
				}
				model->shufflePlayers();
				valid = true;
			}
			else throw invalid_argument("You must input a number!");
		}
		catch (invalid_argument& e) {
			view->displayException(e);
		}
	}
}

void PokerController::tableStakes()
{
	view->displayPromptStakes();
	bool valid = false;
	while (!valid) {
		try {
			std::string input;
			cin >> input;
			if (isNumber(input)) {
				int stakes = stoi(input);
				if (stakes < 10) throw invalid_argument("The stakes cannot be smaller than 10!");
				model->setStakes(stakes);
				valid = true;
			}
			else throw invalid_argument("You must input a number!");
		}
		catch (invalid_argument& e) {
			view->displayException(e);
		}
	}
}

void PokerController::placeBlinds()
{
	model->resetPlayerFlags();
	model->playerPostBlinds();
	view->displayPostBlinds();
}

void PokerController::bettingRound()
{
	view->displayTable();
	model->resetPlayerFlags();

	while (!model->allPlayersFinished()) {
		userInput();
	}
}

void PokerController::userInput()
{	
	view->displayPlayerOptions();
	bool valid = false;
	while (!valid) {
		try {
			string input;
			getline(std::cin, input);

			//Do stuff. If input good, set valid to true, else keep looping
			//Check for input that matches a command
			//Check if valid command is actually legal (check -> is possible // call, raise -> has the cash)
			//If its legal, do it. If check, no flag, otherwise set "done" flag on players
			// 
			//Player has player flag enum
			//Check gets skipped as if finished until there are no more unfinished players
			//In short: the model decided autonomously which player is currently active, the controller doesn't care

			//Ghetto Switch Case Begin
			if (input == "Call" || input == "call") {
				model->playerCall();
				valid = true;
			}
			if ((input.substr(0, input.find(" ")) == "Raise" || (input.substr(0, input.find(" ")) == "raise"))) {
				string remainingString = input.substr(input.find(" "));
				if (isNumber(remainingString)) {
					model->playerRaise(stoi(remainingString));
					valid = true;
				}
				else {
					throw invalid_argument("You must raise by a number!");
				}
			}
			if (input == "Fold" || input == "fold") {
				model->playerFold();
				valid = true;
			}
			if (input == "Check" || input == "check") {
				model->playerCheck();
				valid = true;
			}
			if (input == "Peek" || input == "peek") {
				view->displayPlayerHole();
				//No valid flag because we don't want to end the turn
			}
			if (input == "All In" || input == "all in") {
				model->playerAllIn();
				valid = true;
			}
			if ((input.substr(0, input.find(" ")) == "Pick" || (input.substr(0, input.find(" ")) == "pick"))) {
				throw exception("Command not implemented yet!");
				//TODO: Validate
				valid = true;
			}
			if (!valid) throw invalid_argument("Unrecognized Input!");
			//Ghetto Switch Case End
		}
		catch (invalid_argument& e) {
			view->displayException(e);
		}
	}
}

bool PokerController::isNumber(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}