#include <iostream>
#include "GameLogic.h"


GameLogic::GameLogic(bool who_starts) {
	endOfMatch = 0;
	cellsLeft = 9;

	whoStarted = who_starts;
	whoseTurn = who_starts;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			GameLogic::board[i][j] = 0;
		}
	}
}

void GameLogic::reset() {
	endOfMatch = 0;
	cellsLeft = 9;

	whoStarted = !whoStarted;
	whoseTurn = whoStarted;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			GameLogic::board[i][j] = 0;
		}
	}
}

int GameLogic::getElementByIndex(int x, int y) {
	return board[x][y];
}

int GameLogic::makeMove(int x, int y) {
	if (isEmptyOnIndex(x, y)) {
		if (isXTour()) {
			insertX(x, y);
			whoseTurn = 0;
			std::cout << "X on [" << x << ", " << y << "]" << std::endl;
		} else {
			insertO(x, y);
			whoseTurn = 1;
			std::cout << "O on [" << x << ", " << y << "]" << std::endl;
		}
		cellsLeft --;
		return whoWin();
	} else {
		return -1;
	}
}

void GameLogic::setElementByIndex(int new_value, int x, int y) {
	board[x][y] = new_value;
}

void GameLogic::insertO(int x, int y) {
	setElementByIndex(1, x, y);
}

void GameLogic::insertX(int x, int y) {
	setElementByIndex(2, x, y);
}

bool GameLogic::isEmptyOnIndex(int x, int y) {
	if (getElementByIndex(x, y) == 0) 
		return true;
	else
		return false;
}

bool GameLogic::isXTour() {
	return whoseTurn;
}

bool GameLogic::isOTour() {
	return !whoseTurn;
}

bool GameLogic::isEndOfMatch() {
	return endOfMatch;
}

int GameLogic::whoWin() {
	
	if (getElementByIndex(1, 1) != 0 && (
		(getElementByIndex(0, 0) == getElementByIndex(1, 1) && getElementByIndex(1, 1) == getElementByIndex(2, 2)) ||
		(getElementByIndex(2, 0) == getElementByIndex(1, 1) && getElementByIndex(1, 1) == getElementByIndex(0, 2)) ||
		(getElementByIndex(0, 1) == getElementByIndex(1, 1) && getElementByIndex(1, 1) == getElementByIndex(2, 1)) ||
		(getElementByIndex(1, 0) == getElementByIndex(1, 1) && getElementByIndex(1, 1) == getElementByIndex(1, 2)))) {

		endOfMatch = 1;
		return getElementByIndex(1, 1);

	}  else if (getElementByIndex(0, 0) != 0 && (
				   (getElementByIndex(0, 0) == getElementByIndex(1, 0) && getElementByIndex(1, 0) == getElementByIndex(2, 0)) ||
				   (getElementByIndex(0, 0) == getElementByIndex(0, 1) && getElementByIndex(0, 1) == getElementByIndex(0, 2)))) {

		endOfMatch = 1;
		return getElementByIndex(0, 0);

	} else if (getElementByIndex(2, 2) != 0 && (
				  (getElementByIndex(0, 2) == getElementByIndex(1, 2) && getElementByIndex(1, 2) == getElementByIndex(2, 2)) ||
				  (getElementByIndex(2, 0) == getElementByIndex(2, 1) && getElementByIndex(2, 1) == getElementByIndex(2, 2)))) {

		endOfMatch = 1;
		return getElementByIndex(2, 2);

	} else if (cellsLeft == 0) {
		endOfMatch = 1;
		return 3;
	}
	else {
		return 0;
	}
}

GameLogic::~GameLogic() {
}
