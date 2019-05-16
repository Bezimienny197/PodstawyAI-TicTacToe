#include <iostream>
#include <ctime>
#include <cstdlib>

#include "AI.h"
#include "GameLogic.h"

using namespace std;

AI::AI(GameLogic& logic, bool aiChar) : gameLogic(logic) {
	this->aiCharB = aiChar;
	this->aiChar = aiChar + 1;
}

/* Wykonaj ruch (drzewo decyzyjne AI) */
int AI::makeMove() {
	int x, y;

	if (checkWin(&x, &y)) {
		
	} else if (defendYourself(&x, &y)) {
		
	} else if (isEmpty(1, 1)) {
		x = 1; y = 1;
		

	} else if (isMine(1, 1)) {
		if (cellsLeft() == 7) {
			if (isCornersEmpty()) {
				if (!isEmpty(0, 1) || !isEmpty(1, 0)) {
					x = 0; y = 0;
				} else if (!isEmpty(1, 2) || !isEmpty(2, 1)) {
					x = 2; y = 2;
				} 
			} else if (isCentersEmpty()) {
				if (!isEmpty(0, 0)) {
					x = 2; y = 2;
				} else if (!isEmpty(2, 0)) {
					x = 0; y = 2;
				} else if (!isEmpty(0, 2)) {
					x = 2; y =  0;
				} else if (!isEmpty(2, 2)) {
					x = 0; y = 0;
				}
			}

		} else if (cellsLeft() == 5) {
			if (isCentersEmpty()) {
				if (isOpponent(0, 0) && isOpponent(2, 0)) {
					x = 1; y = 0;
				} else if (isOpponent(2, 0) && isOpponent(2, 2)) {
					x = 2; y = 1;
				} else if (isOpponent(2, 2) && isOpponent(0, 2)) {
					x = 1; y = 2;
				} else if (isOpponent(0, 2) && isOpponent(0, 0)) {
					x = 0; y = 1;
				}
			} else {
				if ((isMine(0, 0) && isEmpty(0, 1)) || (isMine(2, 2) && isEmpty(1, 2))) {
					x = 0; y = 2;
				} else if ((isMine(0, 2) && isEmpty(1, 2)) || (isMine(2, 0) && isEmpty(2, 1))) {
					x = 2; y = 2;
				} else if ((isMine(2, 2) && isEmpty(2, 1)) || (isMine(0, 0) && isEmpty(1, 0))) {
					x = 2; y = 0;
				} else if ((isMine(2, 0) && isEmpty(1, 0)) || (isMine(0, 2) && isEmpty(0, 1))) {
					x = 0; y = 0;
				}
			}
		
		} else {
			makeRandomMove(&x, &y);
		}


	} else if (isOpponent(1, 1)) {
		if (cellsLeft() == 8) {
			x = 0; y = 0;
		} else if (cellsLeft() == 6) {
			if (defendYourself(&x, &y)) {

			} else if (isEmpty(2, 0)) {
				x = 2; y = 0;
			} else  {
				x = 0; y = 2;
			}
		
		} else {
			makeRandomMove(&x, &y);
		}
	}

	return gameLogic.makeMove(x, y);
}

int AI::board(int x, int y) {
	return gameLogic.getElementByIndex(x, y);
}

bool AI::checkWin(int* x, int* y) {
	if (isEmpty(0, 0) &&
		((isMine(0, 2) && isMine(0, 1)) ||
		(isMine(2, 2) && isMine(1, 1)) ||
		(isMine(2, 0) && isMine(1, 0)))) {

		*x = 0; *y = 0;
		return true;
	} else if (isEmpty(2, 0) &&
				 ((isMine(0, 0) && isMine(1, 0)) ||
				  (isMine(0, 2) && isMine(1, 1)) ||
				  (isMine(2, 2) && isMine(2, 1)))) {

		*x = 2; *y = 0;
		return true;
	} else if (isEmpty(2, 2) &&
				 ((isMine(2, 0) && isMine(2, 1)) ||
				  (isMine(0, 0) && isMine(1, 1)) ||
				  (isMine(0, 2) && isMine(1, 2)))) {

		*x = 2; *y = 2;
		return true;
	} else if (isEmpty(0, 2) &&
				 ((isMine(0, 0) && isMine(0, 1)) ||
				  (isMine(2, 0) && isMine(1, 1)) ||
				  (isMine(2, 2) && isMine(1, 2)))) {

		*x = 0; *y = 2;
		return true;
	} else if (isEmpty(1, 0) &&
				 ((isMine(0, 0) && isMine(2, 0)) ||
				  (isMine(1, 2) && isMine(1, 1)))) {

		*x = 1; *y = 0;
		return true;
	} else if (isEmpty(2, 1) &&
				 ((isMine(2, 0) && isMine(2, 2)) ||
				  (isMine(0, 1) && isMine(1, 1)))) {

		*x = 2; *y = 1;
		return true;
	} else if (isEmpty(1, 2) &&
				 ((isMine(0, 2) && isMine(2, 2)) ||
				  (isMine(1, 0) && isMine(1, 1)))) {

		*x = 1; *y = 2;
		return true;
	} else if (isEmpty(0, 1) &&
				 ((isMine(0, 0) && isMine(0, 2)) ||
				  (isMine(2, 1) && isMine(1, 1)))) {

		*x = 0; *y = 1;
		return true;
	} else if (isEmpty(1, 1) &&
				 ((isMine(0, 0) && isMine(2, 2)) ||
				  (isMine(1, 0) && isMine(1, 2)) ||
				  (isMine(2, 0) && isMine(0, 2)) ||
				  (isMine(2, 1) && isMine(0, 1)))) {

		*x = 1; *y = 1;
		return true;
	} else {
		return false;
	}
}

bool AI::defendYourself(int* x, int* y) {
	if (isEmpty(0, 0) &&
		((isOpponent(0, 2) && isOpponent(0, 1)) ||
		(isOpponent(2, 2) && isOpponent(1, 1)) ||
		(isOpponent(2, 0) && isOpponent(1, 0)))) {

		*x = 0; *y = 0;
		return true;
	} else if (isEmpty(2, 0) &&
				 ((isOpponent(0, 0) && isOpponent(1, 0)) ||
				  (isOpponent(0, 2) && isOpponent(1, 1)) ||
				  (isOpponent(2, 2) && isOpponent(2, 1)))) {

		*x = 2; *y = 0;
		return true;
	} else if (isEmpty(2, 2) &&
				 ((isOpponent(2, 0) && isOpponent(2, 1)) ||
				  (isOpponent(0, 0) && isOpponent(1, 1)) ||
				  (isOpponent(0, 2) && isOpponent(1, 2)))) {

		*x = 2; *y = 2;
		return true;
	} else if (isEmpty(0, 2) &&
				 ((isOpponent(0, 0) && isOpponent(0, 1)) ||
				  (isOpponent(2, 0) && isOpponent(1, 1)) ||
				  (isOpponent(2, 2) && isOpponent(1, 2)))) {

		*x = 0; *y = 2;
		return true;
	} else if (isEmpty(1, 0) &&
				 ((isOpponent(0, 0) && isOpponent(2, 0)) ||
				  (isOpponent(1, 2) && isOpponent(1, 1)))) {

		*x = 1; *y = 0;
		return true;
	} else if (isEmpty(2, 1) &&
				 ((isOpponent(2, 0) && isOpponent(2, 2)) ||
				  (isOpponent(0, 1) && isOpponent(1, 1)))) {

		*x = 2; *y = 1;
		return true;
	} else if (isEmpty(1, 2) &&
				 ((isOpponent(0, 2) && isOpponent(2, 2)) ||
				  (isOpponent(1, 0) && isOpponent(1, 1)))) {

		*x = 1; *y = 2;
		return true;
	} else if (isEmpty(0, 1) &&
				 ((isOpponent(0, 0) && isOpponent(0, 2)) ||
				  (isOpponent(2, 1) && isOpponent(1, 1)))) {

		*x = 0; *y = 1;
		return true;
	} else if (isEmpty(1, 1) &&
				 ((isOpponent(0, 0) && isOpponent(2, 2)) ||
				  (isOpponent(1, 0) && isOpponent(1, 2)) ||
				  (isOpponent(2, 0) && isOpponent(0, 2)) ||
				  (isOpponent(2, 1) && isOpponent(0, 1)))) {

		*x = 1; *y = 1;
		return true;
	} else {
		return false;
	}
}

void AI::makeRandomMove(int* x, int* y) {
	srand(time(0));

	do {
		*x = rand() % 3;
		*y = rand() % 3;
	} while (!isEmpty(*x, *y));
}

bool AI::isEmpty(int x, int y) {
	return gameLogic.isEmptyOnIndex(x, y);
}

bool AI::isMine(int x, int y) {
	return (board(x, y) == aiChar);
}

bool AI::isOpponent(int x, int y) {
	return (board(x, y) != aiChar && !isEmpty(x, y));
}

bool AI::isCornersEmpty() {
	return (isEmpty(0, 0) && isEmpty(2, 0) && isEmpty(0, 2) && isEmpty(2, 2));
}

bool AI::isCentersEmpty() {
	return (isEmpty(0, 1) && isEmpty(1, 0) && isEmpty(1, 2) && isEmpty(2, 1));
}

int AI::cellsLeft() {
	return gameLogic.howCellsLeft();
}

AI::~AI() {}