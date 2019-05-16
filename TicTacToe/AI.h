#pragma once

#include "GameLogic.h"

class AI
{
public:
	AI(GameLogic& logic, bool aiChar);
	int makeMove();
	~AI();
private:
	GameLogic& gameLogic;				// Logika gry
	bool aiCharB;									// Zmienna przechowuj¹ca informacje o znaku którym gra AI (0 - kó³ko, 1 - krzy¿yk)
	int aiChar;										// Zmienna przechowuj¹ca informacje o znaku którym gra AI (0 - kó³ko, 1 - krzy¿yk)
	int board(int x, int y);						// Funkcja zwracaj¹ca zawartoœæ komórki o podanym indeksie z logiki gry
	bool checkWin(int* x, int* y);			// Funkcja sprawdzaj¹ca, czy w tej wurze mo¿na wygraæ, zwraca true jeœli tak lub false w przeciwnym wypadku. Przyjmuje tak¿e dwa argumenty - s¹ to zmienne wskaŸnikowe pod które zostan¹ podstawione wspó³rzêdne zwyciêskiego ruchu
	bool defendYourself(int* x, int* y);	// Funkcja sprawdzaj¹ca, czy w tej wurze przeciwnik mo¿e wygraæ, zwraca true jeœli tak lub false w przeciwnym wypadku. Przyjmuje tak¿e dwa argumenty - s¹ to zmienne wskaŸnikowe pod które zostan¹ podstawione wspó³rzêdne ruchu do obrony
	void makeRandomMove(int* x, int* y);	// Funkcja wykonuje losowy ruch (przyjmuje dwa argumenty - zmienne wskaŸnikowe pod które zostan¹ podstawione wspó³rzêdne losowego ruchu
	bool isEmpty(int x, int y);				// Czy komórka o podanym indeksie jest pusta
	bool isMine(int x, int y);					// Czy komórka o podanym indeksie nale¿y do AI
	bool isOpponent(int x, int y);			// Czy komórka o podanym indeksie nale¿y do przeciwnika
	bool isCornersEmpty();					// Czy rogi s¹ puste
	bool isCentersEmpty();					// Czy pola na œrodkach s¹ puste
	int cellsLeft();
};

