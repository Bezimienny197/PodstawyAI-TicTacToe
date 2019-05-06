#pragma once

class GameLogic
{
public:
	GameLogic();
	int getElementByIndex(int x, int y);
	void setElementByIndex(int new_value, int x, int y);
	void insertO(int x, int y);
	void insertX(int x, int y);
	~GameLogic();
private:
	int board[3][3];
};

