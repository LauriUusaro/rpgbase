#include "main.h"
#include <iostream>

Game::EntityTypes::Talker::Talker(sf::Sprite sprite, sf::Vector2i pos, sf::Vector2i dim, Game::Player* player, Game::Dialogue dialogue, int talkFrames) : Entity(pos, dim, player), sprite(sprite), dialogue(dialogue), talkFrames(talkFrames) {
	(*this).sprite.setPosition(pos.x, pos.y);
	(*this).sprite.setScale(3, 3);
	lastTime = clock();
	currFrame = 0;
	origRect = sprite.getTextureRect();
}

void Game::EntityTypes::Talker::HandleEvents(sf::Event e) {
	if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::E && GetBounds().intersects(sf::IntRect(player->GetPosition().x, player->GetPosition().y + 132, 84, 60)) && !dialogue.GetDisplaying())dialogue.Start();
	dialogue.HandleEvents(e);
}

void Game::EntityTypes::Talker::Update(double dt) {
	dialogue.Update(dt);
	sprite.setTextureRect(sf::IntRect(origRect.left + (currFrame + dialogue.GetMessageNum() * talkFrames) * origRect.width, origRect.top, origRect.width, origRect.height));
	if ((clock() - lastTime) / (double)CLOCKS_PER_SEC >= 0.2 && dialogue.GetDisplaying()) {
		currFrame++;
		if (currFrame >= talkFrames) {
			currFrame -= 2;
			if (currFrame < 0) {
				currFrame = 0;
			}
		}
		lastTime = clock();
	}
	if(!dialogue.GetDisplaying() || !dialogue.GetTalking()) {
		currFrame = 0;
		sprite.setTextureRect(sf::IntRect(origRect.left + (talkFrames - 1) * origRect.width, origRect.top, origRect.width, origRect.height));
	}
}

void Game::EntityTypes::Talker::Draw(sf::RenderTarget& window) {
	window.draw(sprite);
}

void Game::EntityTypes::Talker::DrawEffect(sf::RenderTarget& window) {
	dialogue.Draw(window);
}

Game::EntityTypes::AnimTalker::AnimTalker(sf::Sprite sprite, sf::Vector2i pos, sf::Vector2i dim, Game::Player* player, Game::Dialogue dialogue, int maxFrames) : Entity(pos, dim, player), sprite(sprite), dialogue(dialogue), maxFrames(maxFrames) {
	(*this).sprite.setPosition(pos.x, pos.y);
	(*this).sprite.setScale(3, 3);
	lastTime = clock();
	currFrame = 0;
	origRect = sprite.getTextureRect();
}

void Game::EntityTypes::AnimTalker::HandleEvents(sf::Event e) {
	if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::E && GetBounds().intersects(sf::IntRect(player->GetPosition().x, player->GetPosition().y + 132, 84, 60)) && !dialogue.GetDisplaying())dialogue.Start();
	dialogue.HandleEvents(e);
}

void Game::EntityTypes::AnimTalker::Update(double dt) {
	dialogue.Update(dt);
	sprite.setTextureRect(sf::IntRect(origRect.left + currFrame/* + dialogue.GetMessageNum() * maxFrames)*/ * origRect.width, origRect.top, origRect.width, origRect.height));
	if ((clock() - lastTime) / (double)CLOCKS_PER_SEC >= 0.2) {
		currFrame++;
		if (currFrame >= maxFrames) {
			currFrame = 0;
		}
		lastTime = clock();
	}
}

void Game::EntityTypes::AnimTalker::Draw(sf::RenderTarget& window) {
	window.draw(sprite);
}

void Game::EntityTypes::AnimTalker::DrawEffect(sf::RenderTarget& window) {
	dialogue.Draw(window);
}

Game::EntityTypes::BlueberryPerson::BlueberryPerson(sf::Sprite sprite, sf::Vector2i pos, sf::Vector2i dim, Game::Player* player) : Entity(pos, dim, player), sprite(sprite), maxFrames(3) {
	(*this).sprite.setPosition(pos.x, pos.y);
	(*this).sprite.setScale(3, 3);
	lastTime = clock();
	currFrame = 0;
	origRect = sprite.getTextureRect();

	std::vector<std::string> strings = std::vector<std::string>();
	strings.push_back("It's an ordinary boxwood shrub.");
	strings.push_back("Wait, something is staring at \n you behind the leaves...");
	strings.push_back("The mysterious eyes disappear.");

	std::vector<std::string> strings2 = strings;

	std::vector<std::string> stringArray[2] = { strings, strings2 };

	std::vector<Game::Dialogue::Face> faces{ Game::Dialogue::NONE, Game::Dialogue::NONE, Game::Dialogue::NONE };

	dialogue = Game::Dialogue::Dialogue(stringArray, 20, player, 0, faces);
	messageSetOrdinal = 0;
}

void Game::EntityTypes::BlueberryPerson::HandleEvents(sf::Event e) {
	if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::E && GetBounds().intersects(sf::IntRect(player->GetPosition().x, player->GetPosition().y + 132, 84, 60)) && !dialogue.GetDisplaying()) {
		std::vector<std::string> strings = std::vector<std::string>();
		std::vector<std::string> strings2 = std::vector<std::string>();

		std::vector<Game::Dialogue::Face> faces;
		int action = -1;
		int hasBerries = -1;

		switch (messageSetOrdinal)
		{
		case 0:
			strings.push_back("(It's an ordinary boxwood shrub.)");
			strings.push_back("(Wait, something is staring at \n you behind the leaves...)");
			strings.push_back("(The mysterious eyes disappear.)");
			strings2 = strings;

			faces = { Game::Dialogue::NONE, Game::Dialogue::NONE, Game::Dialogue::NONE };
			break;
		case 1:
			strings.push_back("•Hmph? You again?");
			strings.push_back("•Please, leave now. Can't you \n see I'm busy?");
			strings2 = strings;

			faces = { Game::Dialogue::NONE, Game::Dialogue::NONE };
			break;
		case 2:
			strings.push_back("Hmph? \"Busy on what?\"");
			strings.push_back("Well, I guess i can't force \n you to leave anyway, \n so let me explain.");
			strings.push_back("This one woman told me that \n a blend of a blueberry \n and resin of a spruce");
			strings.push_back("does good for your skin. \n Now, I don't know if that's true, \n but I might as well give it a try");
			strings.push_back("See, I've got skin problems \n all my life, and, well, age doesn't \n make it any better.");
			strings.push_back("A couple days ago I decided \n to change that, and went to Dr. - to \n get a medication for it.");
			strings.push_back("Surprisingly, though experienced \n with rashes, he didn't \n know any solution for my problem.");
			strings.push_back("I walked home feeling down, but \n suddenly a pretty woman asked \n me what was wrong.");
			strings.push_back("I explained everything, and \n she suggested me the salve I told you about earlier. \n Strange, huh? I guess people are kinder than I thought.");
			strings2 = strings;

			faces = { Game::Dialogue::NONE, Game::Dialogue::NONE, Game::Dialogue::NONE, Game::Dialogue::NONE, Game::Dialogue::NONE, Game::Dialogue::NONE, Game::Dialogue::NONE, Game::Dialogue::NONE,Game::Dialogue::NONE };
			break;
		case 3:
			strings.push_back("I have already found the resin, \n but now I'm looking for the berries.");
			strings.push_back("What? Blueberries don't grow \n here? Damn it, I knew something was \n off the whole time");

			strings2.push_back("I have already found the resin, \n but now I'm looking for the berries.");
			strings2.push_back("What? Blueberries don't grow \n here? Damn it, I knew something was \n off the whole time");

			hasBerries = -1;
			for (int i = 0; i < Game::Profile::items.size(); i++) {
				if (Game::Profile::items.at(i) == Game::Profile::BLUEBERRIES) {
					hasBerries = i;
				}
			}
			if (hasBerries > -1) {
				strings.push_back("(Offer blueberries to him?) \n     •Yes \n      No");
				strings.push_back("What, you have them? \n For me?");
				strings.push_back("Thank you so much, stranger!");

				strings2.push_back("(Offer blueberries to him?) \n      Yes \n     •No");

				action = 2;
			}

			faces = { Game::Dialogue::NONE, Game::Dialogue::NONE, Game::Dialogue::NONE, Game::Dialogue::NONE, Game::Dialogue::NONE };
			break;
		case 4:
			strings.push_back("I'll just stay here for now. \n I'm sure I saw something \n blue at one point though.");

			strings2.push_back("I'll just stay here for now. \n I'm sure I saw something \n blue at one point though.");

			hasBerries = -1;
			for (int i = 0; i < Game::Profile::items.size(); i++) {
				if (Game::Profile::items.at(i) == Game::Profile::BLUEBERRIES) {
					hasBerries = i;
				}
			}
			if (hasBerries > -1) {
				strings.push_back("(Offer blueberries to him?) \n     •Yes \n      No");
				strings.push_back("What, you have them? \n For me?");
				strings.push_back("Thank you so much, stranger");

				strings2.push_back("Offer blueberries to him? \n      Yes \n     •No");

				action = 1;
			}

			faces = { Game::Dialogue::NONE, Game::Dialogue::NONE, Game::Dialogue::NONE, Game::Dialogue::NONE, Game::Dialogue::NONE };
			break;
		case 5:
			strings.push_back("I'm just kinda... chillin' here now. \n I realized it's actually pretty comfortable \n here. But thanks again! I owe you one!");
			faces = { Game::Dialogue::NONE };
		}

		std::vector<std::string> stringArray[2] = { strings, strings2 };
		dialogue.SetMessages(stringArray, faces, action);

		currMessageSetOrdinal = messageSetOrdinal;
		dialogue.Start();
		if (messageSetOrdinal < 4) {
			messageSetOrdinal++;
		}
		currFrame = 0;
	}
	dialogue.HandleEvents(e);
}

void Game::EntityTypes::BlueberryPerson::Update(double dt) {
	dialogue.Update(dt);
	if (dialogue.GetMessageNum() != lastMessage) {
		currFrame = 0;
		lastTime = clock();
	}
	if (dialogue.GetChoice() == 0 && (messageSetOrdinal == 3 || messageSetOrdinal == 4)) {
		for (int i = 0; i < Game::Profile::items.size(); i++) {
			if (Game::Profile::items.at(i) == Game::Profile::BLUEBERRIES) {
				Game::Profile::items.erase(Game::Profile::items.begin() + i);
				messageSetOrdinal = 5;
			}
		}
	}
	switch (currMessageSetOrdinal){
	case 0:
		switch (dialogue.GetMessageNum()) {
		case 0:
			face = 0;
			break;
		case 1:
			face = 1;
			break;
		case 2:
			face = 2;
			break;
		}
		break;
	case 1:
		switch (dialogue.GetMessageNum()) {
		case 0:
			face = 1;
			break;
		case 1:
			face = 2;
			break;
		}
		break;
	case 2:
		switch (dialogue.GetMessageNum()) {
		case 0:
			face = 1;
			break;
		case 1:
			face = 4;
			break;
		case 2:
			face = 4;
			break;
		case 3:
			face = 4;
			break;
		case 4:
			face = 4;
			break;
		case 5:
			face = 4;
			break;
		case 6:
			face = 6;
			break;
		case 7:
			face = 4;
			break;
		case 8:
			face = 4;
			break;
		}
		break;
	case 3:
		switch (dialogue.GetMessageNum()) {
		case 0:
			face = 7;
			break;
		case 1:
			face = 3;
			break;
		case 2:
			face = 3;
			break;
		case 3:
			face = 5;
			break;
		case 4:
			face = 5;
			break;
		}
		break;
	case 4:
		switch (dialogue.GetMessageNum()) {
		case 0:
			face = 7;
			break;
		case 1:
			face = 4;
			break;
		case 2:
			face = 5;
			break;
		case 3:
			face = 5;
			break;
		}
		break;
	case 5:
		face = 5;
		break;
	}

	sprite.setTextureRect(sf::IntRect((currFrame + face * 3) * origRect.width, origRect.top, origRect.width, origRect.height));
	if ((clock() - lastTime) / (double)CLOCKS_PER_SEC >= 0.2 && dialogue.GetDisplaying()) {
		if(currFrame < 2)currFrame++;
		lastTime = clock();
	}
	
	if (!dialogue.GetDisplaying()) {
		if (messageSetOrdinal == 5) sprite.setTextureRect(sf::IntRect(480, 48, 32, 24));
		else sprite.setTextureRect(sf::IntRect(0, 48, 32, 24));
	}

	lastMessage = dialogue.GetMessageNum();
}

void Game::EntityTypes::BlueberryPerson::Draw(sf::RenderTarget& window) {
	window.draw(sprite);
}

void Game::EntityTypes::BlueberryPerson::DrawEffect(sf::RenderTarget& window) {
	dialogue.Draw(window);
}