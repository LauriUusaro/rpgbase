#include "main.h"

Game::Entity::Entity(sf::Vector2i pos, sf::Vector2i dim, Player* player) : pos(pos), dim(dim), player(player) {}

Game::Entities::Entities(Player* player) : player(player) {}
Game::Entities::Entities() {}

sf::IntRect Game::Entity::GetBounds() {
	return sf::IntRect(pos.x - TILE_WIDTH / 2, pos.y - TILE_HEIGHT / 2, dim.x + TILE_WIDTH, dim.y + TILE_HEIGHT);
}

void Game::Entities::HandleEvents(sf::Event e) {
	for (int i = 0; i < entities.size(); i++) {
		entities.at(i)->HandleEvents(e);
	}
}

void Game::Entities::Update(double dt) {
	for (int i = 0; i < entities.size(); i++) {
		entities.at(i)->Update(dt);
	}
}

void Game::Entities::Draw(sf::RenderTarget& window) {
	for (int i = 0; i < entities.size(); i++) {
		entities.at(i)->Draw(window);
	}
}

void Game::Entities::DrawEffect(sf::RenderTarget& window) {
	for (int i = 0; i < entities.size(); i++) {
		entities.at(i)->DrawEffect(window);
	}
}

void Game::Entities::UpdateEntitiesForRoom(int room) {
	entities.clear();
	switch (room)
	{
	case 2:
		std::vector<Game::Dialogue::Face> nullFaces(100, Game::Dialogue::NONE);

		//Rock dude
		{
			sf::Sprite talker = sf::Sprite(Game::Assets::entities);
			talker.setTextureRect(sf::IntRect(0, 0, 32, 24));

			std::vector<std::string> strings = std::vector<std::string>();
			strings.push_back("Rock? No! By no means should \n the father of the great house \n of Igneous be called a rock!");
			strings.push_back("Don't they teach any manners \n to the children today?");
			strings.push_back("Youngsters like you just make \n the remainder of my days worse.");
			strings.push_back("Now, get moving already! \n I will forgive you this time, \n stranger.");

			std::vector<std::string> strings2 = strings;

			std::vector<std::string> stringArray[2] = { strings, strings2 };

			std::vector<Game::Dialogue::Face> faces{ Game::Dialogue::ROCK_DUDE_ANGRY, Game::Dialogue::ROCK_DUDE, Game::Dialogue::ROCK_DUDE_TIRED, Game::Dialogue::ROCK_DUDE };

			Game::Dialogue dialogue = Game::Dialogue::Dialogue(stringArray, 20, player, -1, faces);
			Game::EntityTypes::Talker* entity = new Game::EntityTypes::Talker(talker, sf::Vector2i(TILE_WIDTH * 7, TILE_HEIGHT * 13), sf::Vector2i(TILE_WIDTH, TILE_HEIGHT), player, dialogue, 2);
			entities.push_back(std::unique_ptr<Entity>(entity));
		}

		//Bush 1
		{
			sf::Sprite bush = sf::Sprite(Game::Assets::entities);
			bush.setTextureRect(sf::IntRect(0, 48, 32, 24));

			std::vector<std::string> strings = std::vector<std::string>();
			strings.push_back("(It's an ordinary boxwood shrub.)");

			std::vector<std::string> strings2 = strings;

			std::vector<std::string> stringArray[2] = { strings, strings2 };

			std::vector<Game::Dialogue::Face> faces{ Game::Dialogue::NONE };

			Game::Dialogue dialogue = Game::Dialogue::Dialogue(stringArray, 20, player, -1, faces);
			Game::EntityTypes::Talker* entity = new Game::EntityTypes::Talker(bush, sf::Vector2i(TILE_WIDTH * 20, TILE_HEIGHT * 8), sf::Vector2i(TILE_WIDTH, TILE_HEIGHT), player, dialogue, 1);
			entities.push_back(std::unique_ptr<Entity>(entity));
		}

		//Bush 2
		{
			sf::Sprite bush = sf::Sprite(Game::Assets::entities);
			bush.setTextureRect(sf::IntRect(0, 48, 32, 24));

			Game::EntityTypes::BlueberryPerson* entity = new Game::EntityTypes::BlueberryPerson(bush, sf::Vector2i(TILE_WIDTH * 29, TILE_HEIGHT * 8), sf::Vector2i(TILE_WIDTH, TILE_HEIGHT), player);
			entities.push_back(std::unique_ptr<Entity>(entity));
		}

		//Fountain
		{
			sf::Sprite fountain = sf::Sprite(Game::Assets::entities);
			fountain.setTextureRect(sf::IntRect(0, 501, 128, 96));

			std::vector<std::string> strings = std::vector<std::string>();
			strings.push_back("(It's a water fountain.)");

			std::vector<std::string> strings2 = strings;

			std::vector<std::string> stringArray[2] = { strings, strings2 };

			std::vector<Game::Dialogue::Face> faces{ Game::Dialogue::NONE };

			Game::Dialogue dialogue = Game::Dialogue::Dialogue(stringArray, 20, player, -1, faces);
			Game::EntityTypes::AnimTalker* entity = new Game::EntityTypes::AnimTalker(fountain, sf::Vector2i(TILE_WIDTH * 23, TILE_HEIGHT * 10), sf::Vector2i(TILE_WIDTH * 4, TILE_HEIGHT * 4 + 10), player, dialogue, 2);
			entities.push_back(std::unique_ptr<Entity>(entity));
		}

		//Blueberries
		{
			std::vector<std::string> strings = std::vector<std::string>();
			strings.push_back("(Blueberries. Take them?) \n     •Yes \n      No");
			strings.push_back("You took the berries.");

			std::vector<std::string> strings2 = std::vector<std::string>();
			strings2.push_back("(Blueberries. Take them?) \n      Yes \n     •No");
			strings2.push_back("(You left the berries.)");

			std::vector<std::string> stringArray[2] = { strings, strings2 };

			Game::Dialogue dialogue = Game::Dialogue::Dialogue(stringArray, 20, player, 0, nullFaces);

			std::vector<std::string> strings3 = std::vector<std::string>();
			strings3.push_back("(You have no more room in \n your pockets.)");

			std::vector<std::string> stringArray2[2] = { strings3, strings3 };

			Game::Dialogue outOfSpace = Game::Dialogue::Dialogue(stringArray2, 20, player, -1, nullFaces);

			Game::EntityTypes::Item* entity = new Game::EntityTypes::Item(Game::Profile::BLUEBERRIES, sf::Vector2i(TILE_WIDTH * 14, TILE_HEIGHT * 11), sf::Vector2i(TILE_WIDTH, TILE_HEIGHT), player, dialogue, outOfSpace);
			entities.push_back(std::unique_ptr<Entity>(entity));
		}

		{
			std::vector<std::string> strings = std::vector<std::string>();
			strings.push_back("(Blueberries. Take them?) \n     •Yes \n      No");
			strings.push_back("You took the berries.");

			std::vector<std::string> strings2 = std::vector<std::string>();
			strings2.push_back("(Blueberries. Take them?) \n      Yes \n     •No");
			strings2.push_back("(You left the berries.)");

			std::vector<std::string> stringArray[2] = { strings, strings2 };

			Game::Dialogue dialogue = Game::Dialogue::Dialogue(stringArray, 20, player, 0, nullFaces);

			std::vector<std::string> strings3 = std::vector<std::string>();
			strings3.push_back("(You have no more room in \n your pockets.)");

			std::vector<std::string> stringArray2[2] = { strings3, strings3 };

			Game::Dialogue outOfSpace = Game::Dialogue::Dialogue(stringArray2, 20, player, -1, nullFaces);

			Game::EntityTypes::Item* entity = new Game::EntityTypes::Item(Game::Profile::BLUEBERRIES, sf::Vector2i(TILE_WIDTH * 24, TILE_HEIGHT * 24), sf::Vector2i(TILE_WIDTH, TILE_HEIGHT), player, dialogue, outOfSpace);
			entities.push_back(std::unique_ptr<Entity>(entity));
		}
		break;
	}
}