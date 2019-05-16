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
	bool aiCharB;									// Zmienna przechowuj�ca informacje o znaku kt�rym gra AI (0 - k�ko, 1 - krzy�yk)
	int aiChar;										// Zmienna przechowuj�ca informacje o znaku kt�rym gra AI (0 - k�ko, 1 - krzy�yk)
	int board(int x, int y);						// Funkcja zwracaj�ca zawarto�� kom�rki o podanym indeksie z logiki gry
	bool checkWin(int* x, int* y);			// Funkcja sprawdzaj�ca, czy w tej wurze mo�na wygra�, zwraca true je�li tak lub false w przeciwnym wypadku. Przyjmuje tak�e dwa argumenty - s� to zmienne wska�nikowe pod kt�re zostan� podstawione wsp�rz�dne zwyci�skiego ruchu
	bool defendYourself(int* x, int* y);	// Funkcja sprawdzaj�ca, czy w tej wurze przeciwnik mo�e wygra�, zwraca true je�li tak lub false w przeciwnym wypadku. Przyjmuje tak�e dwa argumenty - s� to zmienne wska�nikowe pod kt�re zostan� podstawione wsp�rz�dne ruchu do obrony
	void makeRandomMove(int* x, int* y);	// Funkcja wykonuje losowy ruch (przyjmuje dwa argumenty - zmienne wska�nikowe pod kt�re zostan� podstawione wsp�rz�dne losowego ruchu
	bool isEmpty(int x, int y);				// Czy kom�rka o podanym indeksie jest pusta
	bool isMine(int x, int y);					// Czy kom�rka o podanym indeksie nale�y do AI
	bool isOpponent(int x, int y);			// Czy kom�rka o podanym indeksie nale�y do przeciwnika
	bool isCornersEmpty();					// Czy rogi s� puste
	bool isCentersEmpty();					// Czy pola na �rodkach s� puste
	int cellsLeft();
};

