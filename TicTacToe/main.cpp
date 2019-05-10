#include <SFML/Graphics.hpp>
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
	RenderWindow window(VideoMode(598, 598), "Tic Tac Toe", Style::Titlebar | Style::Close);	// Tworzenie okna graficznego
	

	/* �aduj tekstury */
	Texture t1;																				// Za�adowanie tekstury 
	if (!t1.loadFromFile("img/board.png"))									// planszy do gry oraz
		cout << "Blad: nie mozna zaladowac tekstur z pliku!";	// obs�uga b��du

	Sprite gameBoard;																	//
	gameBoard.setTexture(t1);													// Za�adowanie planszy do gry
	gameBoard.setPosition(BORDER, BORDER);					//

	GameLogic gameLogic(1);																				// Inicjalizacja logiki gry (argument to kto zaczyna, O - k�ko, 1 - krzy�yk)
	GameSprites gameSprites(gameLogic);															// Inicjalizacja kom�rek (w formie sprat'�w w kt�re b�d� wstawiane odpowiednie znaki w oparciu o logik� gry
	gameSprites.loadCells("img/characters.png", BORDER, SIZE, SPACE);	// Za�adowanie kom�rek (podanie �cie�ki do tekstury, ustawienie pozycji, itp.)

	while (window.isOpen())
	{
		Vector2i mousePos = Mouse::getPosition(window);		// Pozycja myszki

		/* Obs�uga zdarze� */
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {

				// Zamkni�cie okna
				case (Event::Closed) :
					window.close();
					break;

				// Klikni�cie lewym przyciskiem myszy (wykonanie ruchu)
				case (Event::MouseButtonPressed) :
					
					if (event.mouseButton.button == Mouse::Left) {
						
						if (!gameLogic.isEndOfMatch()) {					// Czy jest ju� koniec meczu
							for (int i = 0; i < 3; i++)
								for (int j = 0; j < 3; j++) {
									if (gameSprites.spriteContains(i, j, mousePos.x, mousePos.y) &&	// Sprawdzanie, czy klikni�to w obr�bie jakiego� sprayt'a
										gameLogic.isEmptyOnIndex(i, j)) {													// Sprawdzanie, czy wybrane pole (sprayt) jest puste - czy nie ma w nim jeszcze �adnego znaku

										/* Wykonaj ruch i sprawd�, czy kto� wygra�*/
										switch(gameLogic.makeMove(i, j)) {
										case -1 :
											cout << "Nie mozna wykonac ruchu!" << endl;
											break;
										case 0 :
											break;
										case 1 :
											cout << "Wygralo kolko." << endl;
											break;
										case 2 :
											cout << "Wygral krzyzyk." << endl;
											break;
										case 3 :
											cout << "Remis." << endl;
											break;
										default :
											cout << "Blad: otrzymano zly wynik z funkcji \'makeMove()\' !" << endl;
											break;
										}
										gameSprites.refresh();

										/* Gdy mecz si� zako�czy */
										if (gameLogic.isEndOfMatch()) {
											window.clear(Color::White);		// Czyszczenie okna i wype�nianie go bia�ym kolorem
											window.draw(gameBoard);		// Rysowanie planszy do gry
											window.draw(gameSprites);		// Rysowanie p�l ze znakami (k�ko lub krzy�yk) w formie sprayt'�w
											window.display();						// Wy�wietlenie okna

											char answer;
											bool a = 0;

											do {
												cout << "Czy chcesz kontynuowac gre? (t/n)" << endl;
												cin >> answer;

												switch (answer) {
												case 't' : 
													gameLogic.reset();
													gameSprites.refresh();
													a = 0;
													break;
												case 'n':
													window.close();
													a = 0;
													break;
												default :
													cout << "Podano z�a odpowiedz. Wpisz \'t\' lub \'n\'.";
													a = 1;
													break;
												}
											} while (a);
										}

									}
								}
						}
					}
					break;
			}
		}

		/* Rysuj */
		window.clear(Color::White);		// Czyszczenie okna i wype�nianie go bia�ym kolorem
		window.draw(gameBoard);		// Rysowanie planszy do gry
		window.draw(gameSprites);		// Rysowanie p�l ze znakami (k�ko lub krzy�yk) w formie sprayt'�w
		window.display();						// Wy�wietlenie okna
	}

	return 0;
}