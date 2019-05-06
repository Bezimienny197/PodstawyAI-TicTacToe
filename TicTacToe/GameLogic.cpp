#include "GameLogic.h"


GameLogic::GameLogic() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			GameLogic::board[i][j] = 0;
		}
	}
}

int GameLogic::getElementByIndex(int x, int y) {
	return board[x][y];
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

GameLogic::~GameLogic() {
}
