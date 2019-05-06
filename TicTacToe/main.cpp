#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "GameLogic.h"
#include "GameSprites.h"

using namespace std;
using namespace sf;

int BORDER = 50;		// Obramowanie (odst�p pomi�dzy ramk� okna a plansz�)
int SIZE = 150;			// Rozmiar jednej kom�rki
int SPACE = 12;			// Odst�p pomiedzy kom�rkami

int main()
{
	RenderWindow window(VideoMode(598, 598), "Tic Tac Toe");

	/* �aduj tekstury */
	Texture t1;																				// Za�adowanie tekstury 
	if (!t1.loadFromFile("img/board.png"))									// planszy do gry oraz
		cout << "Blad: nie mozna zaladowac tekstur z pliku!";	// obs�uga b��du

	Sprite gameBoard;																	//
	gameBoard.setTexture(t1);													// Za�adowanie planszy do gry
	gameBoard.setPosition(BORDER, BORDER);					//

	int m, n;

	GameLogic gameLogic;
	GameSprites gameSprites(gameLogic);
	gameSprites.loadCells("img/characters.png", BORDER, SIZE, SPACE);

	while (window.isOpen())
	{
		Vector2i mousePos = Mouse::getPosition(window);		// Pozycja myszki

		/* Obs�uga zdarze� */
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
				case (Event::Closed) :
					window.close();
				case (Event::MouseButtonPressed) :
					if (event.mouseButton.button == Mouse::Left) {
						gameSprites.refresh();
					}
			}
		}

		/* Rysuj */
		window.clear(Color::White);
		window.draw(gameBoard);
		window.draw(gameSprites);
		window.display();
	}

	return 0;
}