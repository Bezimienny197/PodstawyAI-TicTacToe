#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameLogic.h"
#include "GameSprites.h"
#include "AI.h"

using namespace std;
using namespace sf;

int BORDER = 50;		// Obramowanie (odstêp pomiêdzy ramk¹ okna a plansz¹)
int SIZE = 150;			// Rozmiar jednej komórki
int SPACE = 12;			// Odstêp pomiedzy komórkami


int main()
{
	bool aiTour, aiStarted;							// Czy to tura komputera, czy komputer zaczyna
	bool ai_char, who_starts;

	bool b1 = 0;
	do {
		char answer;

		cout << "Wybierz, jakim znakiem chcesz grac - kolkiem czy krzyzykiem. (O/X)" << endl;
		cin >> answer;

		switch (answer) {
		case 'X':
		case 'x':
			ai_char = 0;
			b1 = 0;
			break;
		case 'O':
		case 'o':
			ai_char = 1;
			b1 = 0;
			break;
		default:
			cout << "Podano z³a odpowiedz. Wpisz \'O\' lub \'X'.";
			b1 = 1;
			break;
		}
	} while (b1);

	bool b2 = 0;
	do {
		char answer;

		cout << "Czy to ty masz zaczac mecz? (t/n)" << endl;
		cin >> answer;

		switch (answer) {
		case 'T':
		case 't':
			who_starts = !ai_char;
			aiStarted = 0;
			aiTour = aiStarted;
			b2 = 0;
			break;
		case 'N':
		case 'n':
			who_starts = ai_char;
			aiStarted = 1;
			aiTour = aiStarted;
			b2 = 0;
			break;
		default:
			cout << "Podano z³a odpowiedz. Wpisz \'t\' lub \'n\'.";
			b2 = 1;
			break;
		}
	} while (b2);


	RenderWindow window(VideoMode((2 * BORDER + 3 * SIZE + 4 * SPACE), (2 * BORDER + 3 * SIZE + 4 * SPACE)), "Tic Tac Toe", Style::Titlebar | Style::Close);	// Tworzenie okna graficznego

	/* £aduj tekstury */
	Texture t1;																				// Za³adowanie tekstury 
	if (!t1.loadFromFile("img/board.png"))									// planszy do gry oraz
		cout << "Blad: nie mozna zaladowac tekstur z pliku!";	// obs³uga b³êdu

	Sprite gameBoard;																	//
	gameBoard.setTexture(t1);													// Za³adowanie planszy do gry
	gameBoard.setPosition(BORDER, BORDER);					//
	
	GameLogic gameLogic(who_starts);																// Inicjalizacja logiki gry (argument to kto zaczyna, O - kó³ko, 1 - krzy¿yk)
	GameSprites gameSprites(gameLogic);															// Inicjalizacja komórek (w formie sprat'ów w które bêd¹ wstawiane odpowiednie znaki w oparciu o logikê gry
	AI ai(gameLogic, ai_char);																				// Inicjalizacja sztucznej inteligencji
	gameSprites.loadCells("img/characters.png", BORDER, SIZE, SPACE);	// Za³adowanie komórek (podanie œcie¿ki do tekstury, ustawienie pozycji, itp.)

	while (window.isOpen()) {
		
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
						
					if (!gameLogic.isEndOfMatch() && !aiTour) {													// Czy jest ju¿ koniec meczu i czy to tura gracza
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
									aiTour = 1;
								}
							}
					}
				}
				break;
			}
		}

		/* Ruch komputera */
		if (!gameLogic.isEndOfMatch() && aiTour) {	// Czy jest ju¿ koniec meczu i czy to tura komputera
			
			/* Wykonaj ruch i sprawdŸ, czy ktoœ wygra³*/
			switch (ai.makeMove()) {
			case -1:
				cout << "Nie mozna wykonac ruchu!" << endl;
				break;
			case 0:
				break;
			case 1:
				cout << "Wygralo kolko." << endl;
				break;
			case 2:
				cout << "Wygral krzyzyk." << endl;
				break;
			case 3:
				cout << "Remis." << endl;
				break;
			default:
				cout << "Blad: otrzymano zly wynik z funkcji \'makeMove()\' !" << endl;
				break;
			}
			gameSprites.refresh();
			aiTour = 0;
		}

		/* Rysuj */
		window.clear(Color::White);		// Czyszczenie okna i wype³nianie go bia³ym kolorem
		window.draw(gameBoard);		// Rysowanie planszy do gry
		window.draw(gameSprites);		// Rysowanie pól ze znakami (kó³ko lub krzy¿yk) w formie sprayt'ów
		window.display();						// Wyœwietlenie okna

		/* Gdy mecz siê zakoñczy */
		if (gameLogic.isEndOfMatch()) {
			char answer;
			bool b3 = 0;

			do {
				cout << "Czy chcesz kontynuowac gre? (t/n)" << endl;
				cin >> answer;

				switch (answer) {
				case 'T':
				case 't':
					gameLogic.reset();
					gameSprites.refresh();
					aiStarted = !aiStarted;
					aiTour = aiStarted;
					b3 = 0;
					break;
				case 'N':
				case 'n':
					window.close();
					b3 = 0;
					break;
				default:
					cout << "Podano z³a odpowiedz. Wpisz \'t\' lub \'n\'.";
					b3 = 1;
					break;
				}
			} while (b3);
		}
	}

	return 0;
}