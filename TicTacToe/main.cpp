#include <SFML/Graphics.hpp>
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
	RenderWindow window(VideoMode(598, 598), "Tic Tac Toe", Style::Titlebar | Style::Close);	// Tworzenie okna graficznego
	

	/* £aduj tekstury */
	Texture t1;																				// Za³adowanie tekstury 
	if (!t1.loadFromFile("img/board.png"))									// planszy do gry oraz
		cout << "Blad: nie mozna zaladowac tekstur z pliku!";	// obs³uga b³êdu

	Sprite gameBoard;																	//
	gameBoard.setTexture(t1);													// Za³adowanie planszy do gry
	gameBoard.setPosition(BORDER, BORDER);					//

	GameLogic gameLogic(1);																				// Inicjalizacja logiki gry (argument to kto zaczyna, O - kó³ko, 1 - krzy¿yk)
	GameSprites gameSprites(gameLogic);															// Inicjalizacja komórek (w formie sprat'ów w które bêd¹ wstawiane odpowiednie znaki w oparciu o logikê gry
	gameSprites.loadCells("img/characters.png", BORDER, SIZE, SPACE);	// Za³adowanie komórek (podanie œcie¿ki do tekstury, ustawienie pozycji, itp.)

	while (window.isOpen())
	{
		Vector2i mousePos = Mouse::getPosition(window);		// Pozycja myszki

		/* Obs³uga zdarzeñ */
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {

				// Zamkniêcie okna
				case (Event::Closed) :
					window.close();
					break;

				// Klikniêcie lewym przyciskiem myszy (wykonanie ruchu)
				case (Event::MouseButtonPressed) :
					
					if (event.mouseButton.button == Mouse::Left) {
						
						if (!gameLogic.isEndOfMatch()) {					// Czy jest ju¿ koniec meczu
							for (int i = 0; i < 3; i++)
								for (int j = 0; j < 3; j++) {
									if (gameSprites.spriteContains(i, j, mousePos.x, mousePos.y) &&	// Sprawdzanie, czy klikniêto w obrêbie jakiegoœ sprayt'a
										gameLogic.isEmptyOnIndex(i, j)) {													// Sprawdzanie, czy wybrane pole (sprayt) jest puste - czy nie ma w nim jeszcze ¿adnego znaku

										/* Wykonaj ruch i sprawdŸ, czy ktoœ wygra³*/
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

										/* Gdy mecz siê zakoñczy */
										if (gameLogic.isEndOfMatch()) {
											window.clear(Color::White);		// Czyszczenie okna i wype³nianie go bia³ym kolorem
											window.draw(gameBoard);		// Rysowanie planszy do gry
											window.draw(gameSprites);		// Rysowanie pól ze znakami (kó³ko lub krzy¿yk) w formie sprayt'ów
											window.display();						// Wyœwietlenie okna

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
													cout << "Podano z³a odpowiedz. Wpisz \'t\' lub \'n\'.";
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
		window.clear(Color::White);		// Czyszczenie okna i wype³nianie go bia³ym kolorem
		window.draw(gameBoard);		// Rysowanie planszy do gry
		window.draw(gameSprites);		// Rysowanie pól ze znakami (kó³ko lub krzy¿yk) w formie sprayt'ów
		window.display();						// Wyœwietlenie okna
	}

	return 0;
}