#pragma once

class GameLogic
{
public:
	GameLogic(bool who_starts);
	int getElementByIndex(int x, int y);
	int makeMove(int x, int y);
	bool isEmptyOnIndex(int x, int y);
	bool isXTour();
	bool isOTour();
	int whoWin();
	~GameLogic();
private:
	int board[3][3];			// Stan planszy do gry (0 - puste pole, 1 - kó³ko, 2 - krzy¿yk)
	bool whoseTurn;	// Czyja tura (0 - kó³ko, 1 - krzy¿yk)
	int cellsLeft;				// Liczba pustych pul
	void setElementByIndex(int new_value, int x, int y);
	void insertO(int x, int y);
	void insertX(int x, int y);
};

