#include <SFML\Graphics.hpp>
#include "main.h"
#include <iostream>
#include <Windows.h>
#include <fstream>

sf::Texture Game::Assets::player;
sf::Texture Game::Assets::tiles;
sf::Texture Game::Assets::tilesTop;
sf::Texture Game::Assets::entities;
sf::Texture Game::Assets::playerFight;
sf::Texture Game::Assets::spotlight;
sf::Texture Game::Assets::versus;
sf::Texture Game::Assets::enemies;
sf::Texture Game::Assets::arrowUp;
sf::Texture Game::Assets::arrowDown;
sf::Texture Game::Assets::arrowLeft;
sf::Texture Game::Assets::arrowRight;
sf::Texture Game::Assets::littleChar;
sf::Texture Game::Assets::projectiles;
sf::Texture Game::Assets::winner;
sf::Texture Game::Assets::bg;
sf::Texture Game::Assets::speechBubble;
sf::Texture Game::Assets::plane;
sf::Texture Game::Assets::selectionArrows;
sf::Texture Game::Assets::faces;

sf::Font Game::Assets::font;

sf::SoundBuffer Game::Assets::textB;
sf::SoundBuffer Game::Assets::blipB;
sf::SoundBuffer Game::Assets::getHitB;
sf::SoundBuffer Game::Assets::menuMoveB;

sf::Sound Game::Assets::text;
sf::Sound Game::Assets::blip;
sf::Sound Game::Assets::getHit;
sf::Sound Game::Assets::menuMove;

sf::Music Game::Assets::battle;
sf::Music Game::Assets::area1;

int Game::Profile::health;
int Game::Profile::maxHealth;

std::vector<Game::Profile::ItemType> Game::Profile::items;

std::string texturePath = "assets/sprites/";
std::string sfxPath = "assets/sfx/";
std::string fontPath = "assets/fonts/";

bool Game::Assets::LoadAssets() {
	if (!player.loadFromFile(texturePath + "char.png"))return false;
	if (!tiles.loadFromFile(texturePath + "tiles.png"))return false;
	if (!entities.loadFromFile(texturePath + "entities.png"))return false;
	if (!playerFight.loadFromFile(texturePath + "charbattle.png"))return false;
	if (!spotlight.loadFromFile(texturePath + "spotlight.png"))return false;
	if (!versus.loadFromFile(texturePath + "versus.png"))return false;
	if (!enemies.loadFromFile(texturePath + "enemies.png"))return false;
	if (!arrowUp.loadFromFile(texturePath + "arrow_up.png"))return false;
	if (!arrowDown.loadFromFile(texturePath + "arrow_down.png"))return false;
	if (!arrowLeft.loadFromFile(texturePath + "arrow_left.png"))return false;
	if (!arrowRight.loadFromFile(texturePath + "arrow_right.png"))return false;
	if (!littleChar.loadFromFile(texturePath + "charbattle_little.png"))return false;
	if (!projectiles.loadFromFile(texturePath + "projectiles.png"))return false;
	if (!winner.loadFromFile(texturePath + "winner.png"))return false;
	if (!bg.loadFromFile(texturePath + "bg.png"))return false;
	if (!speechBubble.loadFromFile(texturePath + "speech_bubble.png"))return false;
	if (!plane.loadFromFile(texturePath + "plane.png"))return false;
	if (!selectionArrows.loadFromFile(texturePath + "selection_arrows.png"))return false;
	if (!faces.loadFromFile(texturePath + "faces.png"))return false;
	if (!tilesTop.loadFromFile(texturePath + "tiles_top.png"))return false;
	
	if (!font.loadFromFile(fontPath + "dpcomic.ttf"))return false;

	if (!textB.loadFromFile(sfxPath + "text.wav"))return false;
	if (!blipB.loadFromFile(sfxPath + "menu_blip.wav"))return false;
	if (!getHitB.loadFromFile(sfxPath + "get_hit.wav"))return false;
	if (!menuMoveB.loadFromFile(sfxPath + "menu_move.wav"))return false;

	text.setBuffer(textB);
	blip.setBuffer(blipB);
	getHit.setBuffer(getHitB);
	menuMove.setBuffer(menuMoveB);

	if (!battle.openFromFile(sfxPath + "taisteluteema.wav"))return false;
	if (!area1.openFromFile(sfxPath + "level1.wav"))return false;

	return true;
}

std::vector<std::vector<int>> Game::Assets::rooms[2];

std::string mapPath = "maps/";

bool Game::Assets::LoadRooms() {
	for (int i = 0; i < 2; i++) {
		std::string file = mapPath + "r" + std::to_string(i) + ".txt";

		std::ifstream stream(file);
		std::string line;

		int countY = 0;
		while (std::getline(stream, line)) {
			
			Game::Assets::rooms[i].push_back(std::vector<int>());
			int countX = 0;
			while (true) {
				std::string tile = line.substr(0, line.find_first_of('_') + 1);
				tile.erase(std::remove(tile.begin(), tile.end(), '_'), tile.end());

				line.erase(0, line.find_first_of('_') + 1);

				Game::Assets::rooms[i].at(countY).push_back(std::stoi(tile.c_str(), nullptr));

				if (line.length() <= 0)break;
				countX++;
			}

			countY++;
		}

		stream.close();
		stream.clear();
	}
	return true;
}

int main(int argc, char** argv)
{
	if (!Game::Assets::LoadAssets()) {
		return EXIT_FAILURE;
	}

	if (!Game::Assets::LoadRooms()) {
		return EXIT_FAILURE;
	}

	sf::RenderWindow window(sf::VideoMode::getFullscreenModes().at(0), "Game", sf::Style::Fullscreen);
	//window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	sf::View view = window.getDefaultView();
	/*view.setViewport(sf::FloatRect(0.1, 0.1, 0.8, 0.8));
	window.setView(view);*/

	Game::Profile::maxHealth = 50;
	Game::Profile::health = Game::Profile::maxHealth;

	Game::GameStateManager gms = Game::GameStateManager();

	Game::States::Area* areaState = new Game::States::Area(gms, view);
	gms.Push(areaState);
	srand(time(NULL));

	long startTime;
	double dt = 1.0;

	while (window.isOpen()) 
	{
		startTime = clock();
		sf::Event event;
		while (window.pollEvent(event))
		{
			gms.HandleEvents(event);
			if (event.type == sf::Event::Closed)window.close();
			else if (event.type == sf::Event::KeyPressed) {
				if(event.key.code == sf::Keyboard::Escape)window.close();
			}
		}

		gms.Update(dt);

		window.clear();
		gms.Draw(window);
		window.display();
		dt = (clock() - startTime) / (double)CLOCKS_PER_SEC / (1.0 / 60.0);
	}

	gms.Clear();
	return EXIT_SUCCESS;
}