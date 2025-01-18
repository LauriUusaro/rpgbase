#include "main.h"
#include <iostream>

Game::EntityTypes::Item::Item(Profile::ItemType item, sf::Vector2i pos, sf::Vector2i dim, Game::Player* player, Game::Dialogue dialogue, Game::Dialogue outOfSpace) : Entity(pos, dim, player), dialogue(dialogue), outOfSpace(outOfSpace), itemType(item) {
	sprite = sf::Sprite(Game::Assets::entities);
	
	switch (item)
	{
	case Game::Profile::BLUEBERRIES:
		sprite.setTextureRect(sf::IntRect(0, 24, 32, 24));
		break;
	}
	
	sprite.setPosition(pos.x, pos.y);
	sprite.setScale(3, 3);

	pickedUp = false;
}

void Game::EntityTypes::Item::HandleEvents(sf::Event e) {
	if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::E && GetBounds().intersects(sf::IntRect(player->GetPosition().x, player->GetPosition().y + 132, 84, 60)) && !dialogue.GetDisplaying() && !pickedUp)dialogue.Start();
	dialogue.HandleEvents(e);
	outOfSpace.HandleEvents(e);
}

void Game::EntityTypes::Item::Update(double dt) {
	if (dialogue.GetChoice() == 0 && !pickedUp) {
		if (Game::Profile::items.size() < 3) {
			Game::Profile::items.push_back(itemType);
			pickedUp = true;
			std::cout << "item" << std::endl;
			Game::Assets::blip.play();
		}
		else {
			dialogue.Stop();std::cout << Game::Profile::items.size() << std::endl;
			outOfSpace.Start();
		}
	}

	dialogue.Update(dt);
	outOfSpace.Update(dt);
}

void Game::EntityTypes::Item::Draw(sf::RenderTarget& window) {
	if(!pickedUp)window.draw(sprite);
}

void Game::EntityTypes::Item::DrawEffect(sf::RenderTarget& window) {
	dialogue.Draw(window);
	outOfSpace.Draw(window);
}