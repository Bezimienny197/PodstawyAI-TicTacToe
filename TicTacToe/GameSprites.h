#pragma once

#include <SFML/Graphics.hpp>

#include "GameLogic.h"

using namespace sf;

class GameSprites : public Drawable, public Transformable {
public:
	GameSprites(GameLogic& logic);
	bool loadCells(const std::string texture, int border, int size, int space);
	void refresh();
	Sprite getSpriteByIndex(int x, int y);
	bool spriteContains(int m, int n, int x, int y);
	void draw(RenderWindow& target);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	~GameSprites();
private:
	GameLogic& gameLogic;		// Logika gry
	Sprite f[3][3];							// Znaki (kó³ko albo krzy¿yk)
	Texture texture;						// Tekstura
	int border, size, space;			// Wymiary planszy
};

