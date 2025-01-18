#include "main.h"
#include <iostream>

Game::States::Area::Area(Game::GameStateManager& gms, sf::View view) : GameState(gms, view) {}

void Game::States::Area::Init() {
	tilemap = Tilemap();
	
	tilemap.UpdateMapForRoom(2);
	areaBounds = tilemap.GetAreaBounds();

	player = Game::Player(Game::Tilemap::GetPlayerStart(2, areaBounds), sf::Vector2i(84, 192), &tilemap);

	entities = Game::Entities(&player);
	entities.UpdateEntitiesForRoom(2);

	entityTexture.create(areaBounds.x, areaBounds.y);
	entitySprite = sf::Sprite(entityTexture.getTexture());

	fadeOutShape = sf::RectangleShape();

	pauseMenu = false;
	pauseMenuShape = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH / 8 * 6, WINDOW_HEIGHT / 8 * 6));
	pauseMenuShape.setOutlineThickness(30);
	pauseMenuShape.setOutlineColor(sf::Color(255, 255, 255, 255));
	pauseMenuShape.setFillColor(sf::Color(0, 0, 0, 255));

	encounter = false;

	Game::Assets::area1.setLoop(true);
	Game::Assets::area1.setVolume(50);
	//Game::Assets::area1.play();
}
void Game::States::Area::HandleEvents(sf::Event e) {
	player.HandleEvents(e);
	if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::I && fadeOutA == 0) {
		pauseMenu = !pauseMenu;
		player.SetMove(!pauseMenu);
	}
	entities.HandleEvents(e);
}

void Game::States::Area::Update(double dt) {
	player.Update(dt);
	sf::Vector2i lastOffset(viewOffset);
	if (areaBounds.x >= WINDOW_WIDTH) {
		if (player.GetPosition().x + 42 > gameView.getSize().x / 2 && player.GetPosition().x + 42 < areaBounds.x - gameView.getSize().x / 2) {
			viewOffset.x = player.GetPosition().x + 42;
		}
		else if (player.GetPosition().x + 42 < gameView.getSize().x / 2) {
			viewOffset.x = gameView.getSize().x / 2;
		}
		else if (player.GetPosition().x + 42 > areaBounds.x - gameView.getSize().x / 2) {
			viewOffset.x = areaBounds.x - gameView.getSize().x / 2;
		}
	}
	else {
		viewOffset.x = areaBounds.x / 2;
	}
	if (areaBounds.y >= WINDOW_HEIGHT) {
		if (player.GetPosition().y + 96 > gameView.getSize().y / 2 && player.GetPosition().y + 96 < areaBounds.y - gameView.getSize().y / 2) {
			viewOffset.y = player.GetPosition().y + 96;
		}
		else if (player.GetPosition().y + 96 < gameView.getSize().y / 2) {
			viewOffset.y = gameView.getSize().y / 2;
		}
		else if (player.GetPosition().y + 96 > areaBounds.y - gameView.getSize().y / 2) {
			viewOffset.y = areaBounds.y - gameView.getSize().y / 2;
		}
	}
	else {
		viewOffset.y = areaBounds.y / 2;
	}

	gameView.setCenter(viewOffset.x, viewOffset.y);
	tilemap.Update(dt);

	if (player.JumpToArea() > 0) {
		fadeOutShape.setSize(sf::Vector2f(tilemap.GetAreaBounds().x, tilemap.GetAreaBounds().y));
		fadeOutA += 12 * dt;
		if (fadeOutA > 255) {
			int jumpArea = player.JumpToArea();
			entities.UpdateEntitiesForRoom(player.JumpToArea());
			tilemap.UpdateMapForRoom(player.JumpToArea());
			areaBounds = tilemap.GetAreaBounds();
			sf::Vector2i playerStart = Game::Tilemap::GetPlayerStart(jumpArea, areaBounds);

			fadeOutA = 255;
			
			player.SetPosition(playerStart);
		}
		fadeOutShape.setFillColor(sf::Color(0, 0, 0, fadeOutA));
		player.SetMove(false);
	}
	if (player.JumpToArea() == 0 && fadeOutA > 0) {
		fadeOutA -= 12 * dt;
		if (fadeOutA < 0) {
			fadeOutA = 0;
		}
		fadeOutShape.setFillColor(sf::Color(0, 0, 0, fadeOutA));
		player.SetMove(true);
	}

	if (fadeOutA > 0 && resume) {
		fadeOutA -= 5 * dt;
		if (fadeOutA <= 0) {
			fadeOutA = 0;
			resume = false;
		}
		fadeOutShape.setFillColor(sf::Color(0, 0, 0, fadeOutA));
	}

	entities.Update(dt);

	if (pauseMenu) {
		pauseMenuShape.setPosition(gameView.getCenter().x - WINDOW_WIDTH / 8 * 3, gameView.getCenter().y - WINDOW_HEIGHT / 8 * 3);
	}

	if (player.Encounter()) {
		encounter = true;
		toBattleTimer = clock();
	}

	if (encounter && (clock() - toBattleTimer) / (double)CLOCKS_PER_SEC >= 1) {
		Game::States::Battle* battleState = new Game::States::Battle(gms, gameView, Game::States::Battle::Enemy::ROCKY);
		Game::Assets::area1.stop();
		gms.Push(battleState);
	}

	if (encounter) {
		Game::Assets::area1.setVolume(50 - ((clock() - toBattleTimer) / (double)CLOCKS_PER_SEC * 50));
	}
	else {
		if (Game::Assets::area1.getVolume() < 50) {
			Game::Assets::area1.setVolume(Game::Assets::area1.getVolume() + 1);
		}
	}
}

void Game::States::Area::Resume() {
	resume = true;
	encounter = false;
	fadeOutA = 255;
	fadeOutShape.setSize(sf::Vector2f(tilemap.GetAreaBounds().x, tilemap.GetAreaBounds().y));
	fadeOutShape.setFillColor(sf::Color(0, 0, 0, fadeOutA));
	player.Resume();
	Game::Assets::area1.play();
}

void Game::States::Area::Draw(sf::RenderTarget& window) {
	entityTexture.clear(sf::Color(0, 0, 0, 0));
	entities.Draw(entityTexture);
	entityTexture.display();
	entitySprite.setTexture(entityTexture.getTexture());
	entitySprite.setPosition(0, 0);
	entitySprite.setTextureRect(sf::IntRect(0, 0, areaBounds.x, player.GetPosition().y + 192));

	window.setView(gameView);
	bool playerDrawn = false;
	if (!encounter) {
		playerDrawn = tilemap.Draw(window, player, entitySprite);
	}

	entitySprite.setPosition(0, player.GetPosition().y + 192);
	entitySprite.setTextureRect(sf::IntRect(0, player.GetPosition().y + 192, areaBounds.x, areaBounds.y - (player.GetPosition().y + 192)));
	if (!encounter) window.draw(entitySprite);

	if (!playerDrawn)player.Draw(window);
	if (!encounter) tilemap.DrawTopLayer(window, player);
	window.draw(fadeOutShape);
	entities.DrawEffect(window);
	if (pauseMenu)window.draw(pauseMenuShape);
}