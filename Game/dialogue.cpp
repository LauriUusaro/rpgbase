#include "main.h"
#include <iostream>

Game::Dialogue::Dialogue(std::vector<std::string> strings[2], int charsInSec, Game::Player* player, int actionMessage, std::vector<Face> faces) : charsInSec(charsInSec), player(player), actionMessage(actionMessage), selectedOption(0), faces(faces) {
	(*this).strings[0] = strings[0];(*this).strings[1] = strings[1];

	currentMessage = strings[selectedOption].size();

	dialogueBox = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH / 6 * 4, WINDOW_HEIGHT / 4));
	dialogueBox.setFillColor(sf::Color::Black);
	dialogueBox.setOutlineColor(sf::Color::White);
	dialogueBox.setOutlineThickness(30);

	text = sf::Text("", Game::Assets::font, 50);

	soundPlayed = 0;

	faceSprite = sf::Sprite(Game::Assets::faces);
	faceSprite.setScale(4.5, 4.5);
}

Game::Dialogue::Dialogue(){}

void Game::Dialogue::SetMessages(std::vector<std::string> strings2[2], std::vector<Game::Dialogue::Face> faces2, int actionMessage2) {
	(*this).strings[0] = strings2[0]; (*this).strings[1] = strings2[1];
	faces = faces2;
	actionMessage = actionMessage2;

	currentMessage = strings[selectedOption].size();
}

void Game::Dialogue::HandleEvents(sf::Event e) {
	if (currentMessage < strings[selectedOption].size()) {		
		if (e.type == sf::Event::KeyPressed) {
			if (e.key.code == sf::Keyboard::Enter) {
				if (currentChar < strings[selectedOption].at(currentMessage).size() - 1) {
					currentChar = strings[selectedOption].at(currentMessage).size() - 1;
					talking = false;
				}
				else {
					talking = true;
					currentMessage++;
					if (currentMessage < strings[selectedOption].size()) {
						currentChar = 1;
						text.setString(strings[selectedOption].at(currentMessage).substr(0, currentChar));
					}
				}
			}
		}
		if (e.type == sf::Event::KeyReleased) {
			if (currentMessage == actionMessage) {
				int lastOption = selectedOption;
				selectedOption = 0;
				if (e.key.code == sf::Keyboard::W) {
					if (currentChar < strings[selectedOption].at(currentMessage).size() - 1) {
						currentChar = strings[selectedOption].at(currentMessage).size() - 1;
						talking = false;
					}
					else {
						if(lastOption != selectedOption)Game::Assets::menuMove.play();
					}
				}
				if (e.key.code == sf::Keyboard::S) {
					selectedOption = 1;
					if (currentChar < strings[selectedOption].at(currentMessage).size() - 1) {
						currentChar = strings[selectedOption].at(currentMessage).size() - 1;
						talking = false;
					}
					else {
						if (lastOption != selectedOption)Game::Assets::menuMove.play();
					}
				}
			}
		}
	}
}

void Game::Dialogue::Start() {
	if(!displaying){
		talking = true;
		displaying = true;
		currentMessage = 0;
		currentChar = 1;
		selectedOption = 0;

		text.setString(strings[selectedOption].at(currentMessage).substr(0, currentChar));

		lastTime = clock();

		player->SetMove(false);
		Game::Assets::text.play();
		Game::Assets::text.setVolume(50);
		soundPlayed++;
	}
}

void Game::Dialogue::Stop() {
	if (displaying) {
		currentMessage = strings[selectedOption].size();
	}
}

bool Game::Dialogue::GetDisplaying() {
	return displaying;
}

int Game::Dialogue::GetMessageNum() {
	if (currentMessage < strings[selectedOption].size()) return currentMessage;
	return -1;
}

bool Game::Dialogue::GetTalking() {
	return talking;
}

void Game::Dialogue::Update(double dt) {
	if (currentMessage < strings[selectedOption].size()) {
		if ((clock() - lastTime) / (double)CLOCKS_PER_SEC >= 1.0 / charsInSec && currentChar < strings[selectedOption].at(currentMessage).size()) {
			lastTime = clock();
			if (soundPlayed == 0 && strings[selectedOption].at(currentMessage).at(currentChar) != ' ' | '!' | '?' | '.' | '-') {
				Game::Assets::text.play();
			}
			soundPlayed++;
			if (soundPlayed > 1) {
				soundPlayed = 0;
			}
			currentChar++;
		}

		if (displaying) {
			if (currentChar >= strings[selectedOption].at(currentMessage).size() - 1) {
				talking = false;
			}
		}

		text.setString(strings[selectedOption].at(currentMessage).substr(0, currentChar));

		switch (faces.at(currentMessage))
		{
		case Game::Dialogue::ROCK_DUDE:
			faceSprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
			break;
		case Game::Dialogue::ROCK_DUDE_ANGRY:
			faceSprite.setTextureRect(sf::IntRect(40, 0, 40, 40));
			break;
		case Game::Dialogue::ROCK_DUDE_TIRED:
			faceSprite.setTextureRect(sf::IntRect(80, 0, 40, 40));
			break;
		}
	}
	if (currentMessage >= strings[selectedOption].size() && displaying) {
		talking = false;
		displaying = false;
		player->SetMove(true);
	}
}

int Game::Dialogue::GetChoice() {
	if (currentMessage > actionMessage && actionMessage > -1 && currentMessage < strings[selectedOption].size()) {
		return selectedOption;
	}
	return -1;
}

void Game::Dialogue::Draw(sf::RenderTarget& window) {
	if (currentMessage < strings[selectedOption].size()) {
		dialogueBox.setPosition(window.getView().getCenter().x - WINDOW_WIDTH / 6 * 2, window.getView().getCenter().y + 200);
		if (faces.at(currentMessage) != NONE) {
			text.setPosition(window.getView().getCenter().x - WINDOW_WIDTH / 6 * 2 + 260, window.getView().getCenter().y + 200 + 40);
		}
		else {
			text.setPosition(window.getView().getCenter().x - WINDOW_WIDTH / 6 * 2 + 20, window.getView().getCenter().y + 200 + 40);
		}
		window.draw(dialogueBox);
		window.draw(text);

		faceSprite.setPosition(window.getView().getCenter().x - WINDOW_WIDTH / 6 * 2 + 40, window.getView().getCenter().y + 200 + 20);
		if (faces.at(currentMessage) != NONE)window.draw(faceSprite);
	}
}