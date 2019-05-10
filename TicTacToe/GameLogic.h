#pragma once

class GameLogic
{
public:
	GameLogic(bool who_starts);			// who_starts - wstaw 0, je�li zaczyna� ma k�ko, lub 1 - je�li zaczyna� ma krzy�yk
	void reset();											// Resetuje stan gry
	int getElementByIndex(int x, int y);	// Zwraca kom�rk� o podanym indeksie
	int makeMove(int x, int y);					// Wykonaj ruch
	bool isEmptyOnIndex(int x, int y);		// Czy kom�rka o podanym indeksie jest pusta
	bool isXTour();									// Czy to tura krzy�yka
	bool isOTour();									// Czy to tura k�ka
	bool isEndOfMatch();							// Czy to ju� koniec meczu
	int whoWin();										// Zwraca 0 - je�li nikt jeszcze nie wygra�, 1 - je�li wygra�o k�ko, 2 - je�li wygra� krzy�yk
	~GameLogic();
private:
	int board[3][3];										// Stan planszy do gry (0 - puste pole, 1 - k�ko, 2 - krzy�yk)
	bool whoStarted;								// Zmienna przechowuj�ca informacje o tym, kto zaczyna� mecz (0 - k�ko, 1 - krzy�yk)
	bool whoseTurn;								// Czyja tura (0 - k�ko, 1 - krzy�yk)
	int cellsLeft;											// Liczba pustych p�l
	bool endOfMatch;								// Zmienna przechowuj�ca warto�� ko�ca meczu
	void setElementByIndex(int new_value, int x, int y);	// Ustawia now� warto�� w kom�rce o podanym indeksie
	void insertO(int x, int y);						// Wstaw k�ko na podane wsp��dne
	void insertX(int x, int y);						// Wstaw krzy�yk na podane wsp��dne
};

