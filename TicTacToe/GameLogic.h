#pragma once

class GameLogic
{
public:
	GameLogic(bool who_starts);			// who_starts - wstaw 0, jeœli zaczynaæ ma kó³ko, lub 1 - jeœli zaczynaæ ma krzy¿yk
	void reset();											// Resetuje stan gry
	int getElementByIndex(int x, int y);	// Zwraca komórkê o podanym indeksie
	int makeMove(int x, int y);					// Wykonaj ruch
	bool isEmptyOnIndex(int x, int y);		// Czy komórka o podanym indeksie jest pusta
	bool isXTour();									// Czy to tura krzy¿yka
	bool isOTour();									// Czy to tura kó³ka
	bool isEndOfMatch();							// Czy to ju¿ koniec meczu
	int whoWin();										// Zwraca 0 - jeœli nikt jeszcze nie wygra³, 1 - jeœli wygra³o kó³ko, 2 - jeœli wygra³ krzy¿yk
	~GameLogic();
private:
	int board[3][3];										// Stan planszy do gry (0 - puste pole, 1 - kó³ko, 2 - krzy¿yk)
	bool whoStarted;								// Zmienna przechowuj¹ca informacje o tym, kto zaczyna³ mecz (0 - kó³ko, 1 - krzy¿yk)
	bool whoseTurn;								// Czyja tura (0 - kó³ko, 1 - krzy¿yk)
	int cellsLeft;											// Liczba pustych pól
	bool endOfMatch;								// Zmienna przechowuj¹ca wartoœæ koñca meczu
	void setElementByIndex(int new_value, int x, int y);	// Ustawia now¹ wartoœæ w komórce o podanym indeksie
	void insertO(int x, int y);						// Wstaw kó³ko na podane wspó³¿êdne
	void insertX(int x, int y);						// Wstaw krzy¿yk na podane wspó³¿êdne
};

