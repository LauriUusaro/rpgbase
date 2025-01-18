#include "main.h"
#include <iostream>

void Game::Attack::create(int type, CombatPlayer* player) {
	this->player = player;
	this->type = type;

	timer = clock();

	canvas.create(WINDOW_WIDTH, WINDOW_HEIGHT);
	canvasSprite = sf::Sprite(canvas.getTexture());
	canvasSprite.setTextureRect(sf::IntRect(WINDOW_WIDTH / 2 - 400, WINDOW_HEIGHT / 2 - 400, 800, 800));
	canvasSprite.setOrigin(400, 400);
	canvasSprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	projectiles.clear();

	sequence = 0;
}

Game::Attack::Attack(){}

void Game::Attack::Update(double dt) {
	switch (type)
	{
	case 0:
		if ((clock() - timer) / (double)CLOCKS_PER_SEC > 0.5) {
			timer = clock();
			sf::Sprite projectile = sf::Sprite(Assets::projectiles);
			projectile.setTextureRect(sf::IntRect(0, 0, 37, 27));
			projectile.setOrigin(19, 14);
			projectile.setScale(2, 2);

			if (sequence % 2 == 0) {
				projectile.setPosition(WINDOW_WIDTH / 2 - 361, WINDOW_HEIGHT / 2 - 363 + rand() % 9 * 80);
			}
			else {
				projectile.setPosition(WINDOW_WIDTH / 2 + 363, WINDOW_HEIGHT / 2 - 363 + rand() % 9 * 80);
				projectile.setRotation(180);
			}
			projectiles.push_back(projectile);

			sequence++;
		}
		break;
	}
	for (int i = 0; i < projectiles.size(); i++) {
		switch (type)
		{
		case 0:
			if (projectiles.at(i).getRotation() == 0) {
				projectiles.at(i).setPosition(projectiles.at(i).getPosition().x + ((projectiles.at(i).getPosition().x - 500) / (800 / 8)) * dt, projectiles.at(i).getPosition().y);
			}else if (projectiles.at(i).getRotation() == 180) {
				projectiles.at(i).setPosition(projectiles.at(i).getPosition().x - ((WINDOW_WIDTH - (projectiles.at(i).getPosition().x + 500)) / (800 / 8)) * dt, projectiles.at(i).getPosition().y);
			}

			sf::IntRect bounds = sf::IntRect(projectiles.at(i).getGlobalBounds().left, projectiles.at(i).getGlobalBounds().top, projectiles.at(i).getGlobalBounds().width, projectiles.at(i).getGlobalBounds().height);

			if (bounds.intersects(player->GetBounds())) {
				if (!player->IsInvincible()) {
					player->TakeHit(3);
					Game::Profile::health -= 7;
					if (Game::Profile::health < 0) {
						Game::Profile::health = 0;
					}
					Game::Assets::getHit.play();
				}
			}

			if (bounds.left + bounds.width < WINDOW_WIDTH / 2 - 400 || bounds.left > WINDOW_WIDTH / 2 + 400) {
				projectiles.erase(projectiles.begin() + i);
			}
			break;
		}
	}
	
}

void Game::Attack::Draw(sf::RenderTarget& window) {
	canvas.clear(sf::Color(0, 0, 0, 0));
	for (int i = 0; i < projectiles.size(); i++) {
		switch (type)
		{
		case 0:
			canvas.draw(projectiles.at(i));
			break;
		}
	}
	canvas.display();
	canvasSprite.setTexture(canvas.getTexture());
	window.draw(canvasSprite);
}