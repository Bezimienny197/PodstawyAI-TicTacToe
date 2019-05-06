#include "GameSprites.h"
#include "GameLogic.h"

GameSprites::GameSprites(GameLogic& logic) : gameLogic(logic) {
	border = 0;
	size = 0;
	space = 0;
}

bool GameSprites::loadCells(const std::string texture, int border, int size, int space) {
	if (!this->texture.loadFromFile(texture)) {
		return false;
	} else {
		this->border = border;
		this->size = size;
		this->space = space;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				f[i][j].setPosition((space + border + i * (space + size)), (space + border + j * (space + size)));
				f[i][j].setTexture(this->texture);
				f[i][j].setTextureRect(IntRect((size * gameLogic.getElementByIndex(i, j)), 0, size, size));
			}
		return true;
	}
}

void GameSprites::refresh() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			f[i][j].setTextureRect(IntRect((size * gameLogic.getElementByIndex(i, j)), 0, size, size));
		}
}

Sprite GameSprites::getSpriteByIndex(int x, int y) {
	return f[x][y];
}

void GameSprites::draw(RenderWindow& target) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			target.draw(f[i][j]);
		}
}

void GameSprites::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			target.draw(f[i][j]);
		}
}

GameSprites::~GameSprites() {
}
