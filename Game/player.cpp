#include "main.h"

Game::Player::Player(sf::Vector2i pos, sf::Vector2i dim, Game::Tilemap* tilemap) : pos(pos), dim(dim), tilemap(tilemap) {
	sprite = sf::Sprite(Game::Assets::player);
	sprite.setTextureRect(sf::IntRect(0, 0, 28, 64));
	sprite.setScale(3, 3);

	sprite.setPosition(pos.x, pos.y);
	speed = 6;

	numAnim = 1;
	numFrames = 8;
	currFrame = 0;
	lastFrameTime = clock();

	horDir = 0;
	vertDir = 0;
	flip = 0;

	SetMove(true);
}

Game::Player::Player() {}

Game::Player::~Player() {}

void Game::Player::SetPosition(sf::Vector2i newPos) {
	pos = newPos;
}

sf::Vector2i Game::Player::GetPosition() {
	return pos;
}

void Game::Player::SetMove(bool newMove) {
	move = newMove;
}

void Game::Player::HandleEvents(sf::Event e) {
	if (e.type == sf::Event::EventType::KeyPressed && move) {
		switch (e.key.code){
		case sf::Keyboard::A:
			horDir = -speed;
			if (vertDir == 0) {
				SetAnim(1, horDir);
			}
			break;
		case sf::Keyboard::D:
			horDir = speed;
			if (vertDir == 0) {
				SetAnim(1, horDir);
			}
			break;
		case sf::Keyboard::S:
			vertDir = speed;
			if (horDir == 0) {
				SetAnim(0, vertDir);
			}
			break;
		case sf::Keyboard::W:
			vertDir = -speed;
			if (horDir == 0) {
				SetAnim(0, vertDir);
			}
			break;
		}
	} else if (e.type == sf::Event::EventType::KeyReleased) {
		switch (e.key.code) {
		case sf::Keyboard::A:
			horDir = 0;
			if (vertDir != 0) {
				SetAnim(0, vertDir);
			}
			break;
		case sf::Keyboard::D:
			horDir = 0;
			if (vertDir != 0) {
				SetAnim(0, vertDir);
			}
			break;
		case sf::Keyboard::S:
			vertDir = 0;
			if (horDir != 0) {
				SetAnim(1, horDir);
			}
			break;
		case sf::Keyboard::W:
			vertDir = 0;
			if (horDir != 0) {
				SetAnim(1, horDir);
			}
			break;
		}
	}
}

int Game::Player::JumpToArea() {
	if ((*tilemap).CollidesWithDoor(sf::IntRect(pos.x, pos.y + 132, 84, 60)) < 0) {
		return -(*tilemap).CollidesWithDoor(sf::IntRect(pos.x, pos.y + 132, 84, 60));
	}
	return 0;
}

void Game::Player::SetAnim(int axis, int dir) {
	if (axis == 1) {
		if (dir == -speed) {
			flip = 28;
			numAnim = 1;
			numFrames = 8;
		} else if (dir == speed) {
			flip = 0;
			numAnim = 1;
			numFrames = 8;
		}
	} else if (axis == 0) {
		if (dir == -speed) {
			flip = 0;
			numAnim = 2;
			numFrames = 8;
		} else if (dir == speed) {
			flip = 0;
			numAnim = 3;
			numFrames = 8;
		}
	}
}

bool Game::Player::Encounter() {
	if (encounter == 1) {
		encounter = 2;
		SetMove(false);
		return true;
	}
	return false;
}

void Game::Player::Update(double dt) {
	if (move) {
		int lastPos = pos.x;
		if(horDir < 0)pos.x += std::floor(horDir * dt);
		else pos.x += horDir;
		if ((*tilemap).CollidesWithTiles(sf::IntRect(pos.x, pos.y + 132, 84, 60))) {
			pos.x = lastPos;
		}
		else if(rand() % (int)(10000 * dt) == 0 && pos.x != lastPos) {
			invincible = clock();
			encounter = 1;
		}

		lastPos = pos.y;
		if (vertDir < 0)pos.y += std::floor(vertDir * dt);
		else pos.y += vertDir;
		if ((*tilemap).CollidesWithTiles(sf::IntRect(pos.x, pos.y + 132, 84, 60))) {
			pos.y = lastPos;
		}
		else if(rand() % (int)(10000 * dt) == 0 && pos.y != lastPos) {
			invincible = clock();
			encounter = 1;
		}
	}

	if ((clock() - lastFrameTime) / (double) CLOCKS_PER_SEC >= 0.1) {
		lastFrameTime = clock();
		currFrame++;
		if (currFrame >= numFrames) {
			currFrame = 0;
		}
		if ((horDir == 0 && vertDir == 0) || !move)currFrame = 8;
	}
	sprite.setTextureRect(sf::IntRect(currFrame * 28 + flip, numAnim * 64, 28 - flip * 2, 64));
	sprite.setPosition(pos.x, pos.y);

	if (std::fmod((clock() - invincible) / (double)CLOCKS_PER_SEC, 0.2) <= 0.10 && encounter == 2) {
		sprite.setColor(sf::Color::Transparent);
	}
	else {
		sprite.setColor(sf::Color::White);
	}
}

void Game::Player::Resume() {
	encounter = 0;
	SetMove(true);
}

void Game::Player::Draw(sf::RenderTarget& window) {
	window.draw(sprite);
}

