#define _USE_MATH_DEFINES

#include "main.h"
#include <iostream>

Game::States::GameOver::GameOver(Game::GameStateManager& gms, sf::View view, sf::Vector2i pos) : GameState(gms, view) {
	player = sf::Sprite(Game::Assets::littleChar);
	player.setTextureRect(sf::IntRect(0, 128, 32, 64));
	player.setScale(2, 2);

	player.setPosition(pos.x, pos.y);
}

void Game::States::GameOver::Init() {
	animTimer = clock();
	currFrame = 0;

	gameOver = sf::Text("GAME OVER", Game::Assets::font, 160);
	gameOver.setOrigin(gameOver.getGlobalBounds().width / 2, 0);
	gameOver.setPosition(WINDOW_WIDTH / 2, 100);
	gameOver.setFillColor(sf::Color(255, 255, 255, 0));
	gameOver.setOutlineThickness(3);

	gameOverFadeIn = 0;

	fadeOutA = 0;
	fadeOutShape = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	fadeOutShape.setFillColor(sf::Color(0, 0, 0, fadeOutA));

	sf::View view(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	gameView = view;
}
void Game::States::GameOver::HandleEvents(sf::Event e) {
	if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter) {
		fadeOutA += 15;
		fadeOutShape.setFillColor(sf::Color(0, 0, 0, fadeOutA));
	}
}

void Game::States::GameOver::Update(double dt) {
	if ((clock() - animTimer) / (double)CLOCKS_PER_SEC >= 0.12) {
		animTimer = clock();
		currFrame++;
		if (currFrame < 14) {
			player.setTextureRect(sf::IntRect(currFrame % 14 * 32, 128, 32, 64));
		}
	}
	if (currFrame >= 28 && gameOverFadeIn < 255) {
		gameOverFadeIn += 10 * dt;
		if (gameOverFadeIn > 255) {
			gameOverFadeIn = 255;
			shineTimer = clock();
		}
	}
	if (gameOverFadeIn == 255) {
		gameOver.setOutlineColor(sf::Color(255, 255, 255, (int) std::abs((sin(M_PI * (clock() - shineTimer) / (double)CLOCKS_PER_SEC) * 255))));
	}
	if (fadeOutA > 0) {
		fadeOutA += 15 * dt;
		if (fadeOutA >= 255) {
			fadeOutA = 255;
			gms.Pop();
		}
		fadeOutShape.setFillColor(sf::Color(0, 0, 0, fadeOutA));
	}
	gameOver.setFillColor(sf::Color(255, 255, 255, gameOverFadeIn));
}

void Game::States::GameOver::Resume() {
	
}

void Game::States::GameOver::Draw(sf::RenderTarget& window) {
	window.setView(gameView);
	window.draw(player);
	window.draw(gameOver);
	window.draw(fadeOutShape);
}