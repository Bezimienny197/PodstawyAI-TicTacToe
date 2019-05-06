#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "GameLogic.h"
#include "GameSprites.h"

using namespace std;
using namespace sf;

int BORDER = 50;		// Obramowanie (odstêp pomiêdzy ramk¹ okna a plansz¹)
int SIZE = 150;			// Rozmiar jednej komórki
int SPACE = 12;			// Odstêp pomiedzy komórkami

int main()
{
	RenderWindow window(VideoMode(598, 598), "Tic Tac Toe");

	/* £aduj tekstury */
	Texture t1;																				// Za³adowanie tekstury 
	if (!t1.loadFromFile("img/board.png"))									// planszy do gry oraz
		cout << "Blad: nie mozna zaladowac tekstur z pliku!";	// obs³uga b³êdu

	Sprite gameBoard;																	//
	gameBoard.setTexture(t1);													// Za³adowanie planszy do gry
	gameBoard.setPosition(BORDER, BORDER);					//

	int m, n;

	GameLogic gameLogic;
	GameSprites gameSprites(gameLogic);
	gameSprites.loadCells("img/characters.png", BORDER, SIZE, SPACE);

	while (window.isOpen())
	{
		Vector2i mousePos = Mouse::getPosition(window);		// Pozycja myszki

		/* Obs³uga zdarzeñ */
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