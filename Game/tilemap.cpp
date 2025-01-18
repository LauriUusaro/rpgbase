#include <vector>
#include "main.h"
#include <iostream>

Game::Tilemap::Tilemap() {
	tiles = std::vector<std::vector<int>>();

	tileSprite = sf::Sprite(Game::Assets::tiles);
	tileSprite.setScale(3, 3);

	topSprite = sf::Sprite(Game::Assets::tilesTop);
	topSprite.setScale(3, 3);
}

Game::Tilemap::~Tilemap(){
	
}

void Game::Tilemap::UpdateMapForRoom(int roomId) {
	tiles = Game::Assets::rooms[roomId - 1];
}

bool Game::Tilemap::CollidesWithTiles(sf::IntRect rect) {
	for (int y = 1; y < tiles.size() - 1; y++) {
		for (int x = 1; x < tiles.at(y).size() - 1; x++) {
			int tileType = tiles.at(y).at(x);

			sf::IntRect tile((x - 1) * TILE_WIDTH, (y - 1) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);

			sf::IntRect ledge;
			if (tileType == 15 || tileType == 33) {
				ledge = sf::IntRect((x - 1) * TILE_WIDTH, (y - 1) * TILE_HEIGHT, 1, TILE_HEIGHT);
				if (rect.intersects(ledge))return true;
			}
			else if (tileType == 16 || tileType == 34) {
				ledge = sf::IntRect((x - 1) * TILE_WIDTH + (TILE_WIDTH - 1), (y - 1) * TILE_HEIGHT, 1, TILE_HEIGHT);
				if (rect.intersects(ledge))return true;
			}
			else {
				if (rect.intersects(tile) && tileType != 0 && tileType != 13 && tileType != 17 && tileType != 36 && tileType != 32 && tileType != 31 &&
					tileType != 44 && tileType != 42 && tileType != 38 && tileType != 39 && tileType != 43 && tileType != 41 && tileType != 45) {
					return true;
				}
			}
		}
	}
	return false;
}

int Game::Tilemap::CollidesWithDoor(sf::IntRect rect) {
	for (int y = 0; y < tiles.size(); y++) {
		for (int x = 0; x < tiles.at(y).size(); x++) {
			sf::IntRect tile((x - 1) * TILE_WIDTH, (y - 1) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
			int tileType = tiles.at(y).at(x);
			if (rect.intersects(tile) && tileType < 0)return tileType;
		}
	}
	return 0;
}

sf::Vector2i Game::Tilemap::GetPlayerStart(int areaNum, sf::Vector2i areaBounds) {
	switch (areaNum){
	case 1:
		return sf::Vector2i(areaBounds.x - TILE_WIDTH, TILE_HEIGHT * 5.5);
	case 2:
		return sf::Vector2i(TILE_WIDTH * 5.5, TILE_HEIGHT * 5); // -2.5
	}
	return sf::Vector2i(0, 0);
}

sf::Vector2i Game::Tilemap::GetAreaBounds() {
	int width = 0;
	for (int i = 1; i < tiles.size() - 1; i++) {
		if (tiles.at(i).size() > width) {
			width = tiles.at(i).size();
		}
	}
	return sf::Vector2i((width - 2) * TILE_WIDTH, (tiles.size() - 2) * TILE_HEIGHT);
}

bool Game::Tilemap::Draw(sf::RenderTarget& window, Game::Player& player, sf::Sprite entities) {
	bool playerDrawn = false;
	//std::cout << window.mapCoordsToPixel(sf::Vector2f(10 * 96 - 96, 10 * 72 - 72), window.getView()).x << ", " << window.mapCoordsToPixel(sf::Vector2f(10 * 96 - 96, 10 * 72 - 72), window.getView()).y << std::endl;
	for (int y = 1; y < tiles.size() - 1; y++) {
		for (int x = 1; x < tiles.at(y).size() - 1; x++) {
			tileSprite.setPosition(x * 96 - 96, y * 72 - 72);

			int rectY = 0, rectX = 0;
			if (tiles.at(y).at(x) != 0) {
				rectX = tiles.at(y).at(x) % 25;
				rectY = std::floor(tiles.at(y).at(x) / 25);
			}

			tileSprite.setTextureRect(sf::IntRect(rectX * 32, rectY * 24, 32, 24));
			
			window.draw(tileSprite);

			topSprite.setPosition(x * 96 - 96, y * 72 - 72);

			rectY = 0; rectX = 0;
			if (tiles.at(y).at(x) != 0) {
				rectX = tiles.at(y).at(x) % 25;
				rectY = std::floor(tiles.at(y).at(x) / 25);
			}

			topSprite.setTextureRect(sf::IntRect(rectX * 32, rectY * 24, 32, 24));

			if (y * TILE_HEIGHT + TILE_HEIGHT < player.GetPosition().y + 192) {
				window.draw(topSprite);
			}
		}
		if (y * TILE_HEIGHT > player.GetPosition().y + 192) {
			if (!playerDrawn) {
				window.draw(entities);
				player.Draw(window);
				playerDrawn = true;
			}
		}
	}
	return playerDrawn;
}

void Game::Tilemap::DrawTopLayer(sf::RenderTarget& window, Game::Player& player) {
	for (int y = 1; y < tiles.size() - 1; y++) {
		for (int x = 1; x < tiles.at(y).size() - 1; x++) {
			topSprite.setPosition(x * 96 - 96, y * 72 - 72);

			int rectY = 0, rectX = 0;
			if (tiles.at(y).at(x) != 0) {
				rectX = tiles.at(y).at(x) % 25;
				rectY = std::floor(tiles.at(y).at(x) / 25);
			}

			topSprite.setTextureRect(sf::IntRect(rectX * 32, rectY * 24, 32, 24));

			if (y * TILE_HEIGHT + TILE_HEIGHT >= player.GetPosition().y + 192) {
				window.draw(topSprite);
			}
		}
	}
}

void Game::Tilemap::Update(double dt) {

}