#define _USE_MATH_DEFINES

#include "main.h"
#include <iostream>

Game::States::Battle::Battle(Game::GameStateManager& gms, sf::View view, Enemy enemyType) : GameState(gms, view), enemyType(enemyType) {

}

void Game::States::Battle::Init() {
	bg = sf::Sprite(Game::Assets::bg);
	bg.setScale(3, 3);

	bGShape = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	bGShape.setFillColor(sf::Color(23, 27, 53));

	plane = sf::Sprite(Game::Assets::plane);
	plane.setScale(3, 3);
	plane.setPosition(-42, 15);

	player = sf::Sprite(Game::Assets::playerFight);
	player.setTextureRect(sf::IntRect(0, 0, 208, 67));
	player.setScale(3, 3);
	player.setPosition(WINDOW_WIDTH / 4 * 3 - 201 / 2, WINDOW_HEIGHT - 792);
	playerPos = sf::Vector2i(WINDOW_WIDTH / 4 * 3 - 201 / 2, WINDOW_HEIGHT - 792);

	spotlight = sf::Sprite(Game::Assets::spotlight);
	spotlight.setScale(3, 3);
	spotlight.setPosition(WINDOW_WIDTH / 4 * 3 - 151, WINDOW_HEIGHT - 270);
	spotlightPos = sf::Vector2i(WINDOW_WIDTH / 4 * 3 - 151, WINDOW_HEIGHT - 270);

	healthbarBg = sf::RectangleShape(sf::Vector2f(342, 40));
	healthbarBg.setPosition(WINDOW_WIDTH / 4 * 3 - 151, WINDOW_HEIGHT - 80);
	healthbarBg.setFillColor(sf::Color::Red);

	healthbar = sf::RectangleShape(sf::Vector2f(342, 40));
	healthbar.setPosition(WINDOW_WIDTH / 4 * 3 - 151, WINDOW_HEIGHT - 80);
	healthbar.setFillColor(sf::Color::Green);

	enemy = sf::Sprite(Game::Assets::enemies);
	enemy.setScale(3, 3);

	speechBubble = sf::Sprite(Game::Assets::speechBubble);
	speechBubble.setScale(3, 3);
	speechBubble.setPosition(WINDOW_WIDTH / 4 - 191, 380);

	message = sf::Text("", Game::Assets::font, 40);
	message.setPosition(WINDOW_WIDTH / 4 - 140, 530);
	message.setFillColor(sf::Color::Black);

	strings.push_back("Knockout!");
	strings.push_back("*huff \n *puff");
	strings.push_back("No pain, \n no gain.");

	stoneEnemy = sf::Sprite(Game::Assets::enemies);
	stoneEnemy.setScale(3, 3);

	enemySpotlight = sf::Sprite(Game::Assets::spotlight);
	enemySpotlight.setScale(3, 3);
	enemySpotlight.setPosition(WINDOW_WIDTH / 4 - 191, 270);
	enemySpotlightPos = sf::Vector2i(WINDOW_WIDTH / 4 - 191, 270);

	damageDealt = sf::Text("", Game::Assets::font, 70);
	damageDealt.setPosition(WINDOW_WIDTH / 4 - 10, 550);
	damageDealt.setOrigin(50, 25);

	enemyHealthbarBg = sf::RectangleShape(sf::Vector2f(342, 40));
	enemyHealthbarBg.setPosition(WINDOW_WIDTH / 4 - 191, 460);
	enemyHealthbarBg.setFillColor(sf::Color::Red);

	enemyHealthbar = sf::RectangleShape(sf::Vector2f(342, 40));
	enemyHealthbar.setPosition(WINDOW_WIDTH / 4 - 191, 460);
	enemyHealthbar.setFillColor(sf::Color::Green);

	versus = sf::Sprite(Game::Assets::versus);
	versus.setOrigin(57, 30);
	versus.setRotation(-30);
	versus.setScale(3, 3);
	versus.setPosition(-100, -100);
	versusPos = sf::Vector2i(WINDOW_WIDTH, 0);

	fadeOutA = 0;
	fadeOutShape = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	fadeOutShape.setFillColor(sf::Color(255, 255, 255, fadeOutA));

	choicebox = sf::RectangleShape(sf::Vector2f(500, 700));
	choicebox.setFillColor(sf::Color(255, 255, 255, 150));
	choicebox.setOutlineColor(sf::Color::Black);
	choicebox.setOutlineThickness(30);
	choicebox.setOrigin(250, 350);
	choicebox.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	titleBox = sf::RectangleShape(sf::Vector2f(500, 100));
	titleBox.setFillColor(sf::Color(255, 255, 255, 0));
	titleBox.setOutlineColor(sf::Color::Black);
	titleBox.setOutlineThickness(30);
	titleBox.setOrigin(250, 350);
	titleBox.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	winText = sf::Text("", Game::Assets::font, 50);
	winText.setPosition(WINDOW_WIDTH / 2 - 240, WINDOW_HEIGHT / 2 - 190);
	winText.setFillColor(sf::Color::Black);

	arrowBoundsTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
	arrowBounds = sf::Sprite(arrowBoundsTexture.getTexture());
	arrowBounds.setTextureRect(sf::IntRect(WINDOW_WIDTH / 2 - 250, WINDOW_HEIGHT / 2 - 200, 500, 400));
	arrowBounds.setPosition(WINDOW_WIDTH / 2 - 250, WINDOW_HEIGHT / 2 - 210);

	middleLine = sf::RectangleShape(sf::Vector2f(500, 50));
	middleLine.setFillColor(sf::Color(255, 100, 100, 255));
	middleLine.setOrigin(250, 25);
	middleLine.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	littlePlayer = Game::CombatPlayer(sf::Vector2i(WINDOW_WIDTH / 2 - 28, WINDOW_HEIGHT / 2 - 64));

	title = sf::Text("ATTACK", Game::Assets::font, 80);
	title.setPosition(WINDOW_WIDTH / 2 - title.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 - 355);
	title.setFillColor(sf::Color::Black);

	rSelect = sf::Sprite(Game::Assets::selectionArrows);
	rSelect.setScale(6, 6);
	rSelect.setTextureRect(sf::IntRect(0, 0, 10, 10));
	rSelect.setPosition(WINDOW_WIDTH / 2 + 175, WINDOW_HEIGHT / 2 - 330);

	lSelect = sf::Sprite(Game::Assets::selectionArrows);
	lSelect.setScale(6, 6);
	lSelect.setTextureRect(sf::IntRect(10, 0, 10, 10));
	lSelect.setPosition(WINDOW_WIDTH / 2 - 230, WINDOW_HEIGHT / 2 - 330);
	lSelect.setColor(sf::Color(255, 255, 255, 150));

	narration = sf::Text("", Game::Assets::font, 50);
	narration.setPosition(WINDOW_WIDTH / 2 - 240, WINDOW_HEIGHT / 2 - 340);
	narration.setFillColor(sf::Color::Black);

	selectIcon = sf::CircleShape(10);
	selectIcon.setFillColor(sf::Color::White);

	fadeInA = 255;
	fadeInShape = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	fadeInShape.setFillColor(sf::Color(0, 0, 0, fadeInA));

	hpBattle = sf::Text("", Game::Assets::font, 50);
	if (Game::Profile::health < 10) {
		hpBattle.setString("HP: 0" + std::to_string(Game::Profile::health) + ":" + std::to_string(Game::Profile::maxHealth));
	}
	else {
		hpBattle.setString("HP: " + std::to_string(Game::Profile::health) + ":" + std::to_string(Game::Profile::maxHealth));
	}
	hpBattle.setOrigin(hpBattle.getGlobalBounds().width / 2, 0);
	hpBattle.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 450);

	phase = TRANSITION;

	Game::Assets::battle.setVolume(40);
	Game::Assets::battle.setLoop(true);
	//Game::Assets::battle.play();

	lastTime = clock();
	enemyLastTime = clock();
	zoom = 1;
	currFrame = 0;
	enemyCurrFrame = 0;
	enemyHealth = 50;
	stoneAmount = 0;

	actionDone = false;
}

void Game::States::Battle::HandleEvents(sf::Event e) {
	if (phase == CHOOSE_ACTION) {
		if (e.type == sf::Event::KeyReleased) {
			if (e.key.code == sf::Keyboard::W) {
				if (options.size() > 1) {
					selected--;
					if (selected < 0)selected = 0;
					else Game::Assets::menuMove.play();
				}
			}
			else if(e.key.code == sf::Keyboard::S){
				if (options.size() > 1) {
					selected++;
					if (selected > options.size() - 1)selected = options.size() - 1;
					else Game::Assets::menuMove.play();
				}
			}
			else if (e.key.code == sf::Keyboard::A) {
				selectedPartition--;
				SetOptions(selectedPartition);
				if (selectedPartition < 0) {
					selectedPartition = 0;
				}
			}
			else if (e.key.code == sf::Keyboard::D) {
				selectedPartition++;
				SetOptions(selectedPartition);
				if (selectedPartition > 1) {
					selectedPartition = 1;
				}
			}
			else if (e.key.code == sf::Keyboard::Enter) {
				if (options.size() > 0) {
					if (!actionDone) {
						if (selectedPartition == 0) {
							Game::Assets::blip.play();

							phase = ATTACK;
							arrows = std::vector<sf::Sprite>();
							arrowDirs = std::vector<int>();
							for (int i = 0; i < 3; i++) {
								sf::Sprite arrow = sf::Sprite();
								switch (rand() % 4)
								{
								case 0:
									arrow.setTexture(Game::Assets::arrowLeft);
									arrowDirs.push_back(0);
									break;
								case 1:
									arrow.setTexture(Game::Assets::arrowRight);
									arrowDirs.push_back(1);
									break;
								case 2:
									arrow.setTexture(Game::Assets::arrowUp);
									arrowDirs.push_back(2);
									break;
								case 3:
									arrow.setTexture(Game::Assets::arrowDown);
									arrowDirs.push_back(3);
									break;
								}
								arrow.setScale(3, 3);
								arrow.setPosition(WINDOW_WIDTH / 2 - 33, WINDOW_HEIGHT / 2 - 266 - 200 * i);
								arrow.setColor(sf::Color(0, 0, 0, 255));
								arrow.setTextureRect(sf::IntRect(0, 0, 22, 22));
								arrows.push_back(arrow);

								currentArrow = 0;
								damageDealtNum = 0;
								wavesNum = 50;
								attackDone = 0;
							}
						}
						else if (selectedPartition == 1) {
							currentNarrationLetter = 0;
							narrationLetterTimer = clock();

							switch (Game::Profile::items.at(selected)) {
							case Profile::ItemType::BLUEBERRIES:
								narrationMessage = "You healed 10 HP.";
								Game::Profile::health += 10;
								break;
							}

							Game::Profile::items.erase(Game::Profile::items.begin() + selected);

							if (Game::Profile::health > Game::Profile::maxHealth) {
								Game::Profile::health = Game::Profile::maxHealth;
							}
						}

						actionDone = true;
					}
					else {
						if (selectedPartition == 1) {
							if (currentNarrationLetter < narrationMessage.size()) {
								currentNarrationLetter = narrationMessage.size();
							}
							else {
								phase = DIALOGUE;

								bubbleShakeOffset = 0;
								bubbleWavesNum = -40;
								timesMoved = 0;

								letterTimer = clock();
								currentString = rand() % 3;
								currentLetter = 0;
							}
						}
					}
				}
			}
		}
	}
	else if (phase == ATTACK) {
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::W | sf::Keyboard::S | sf::Keyboard::A | sf::Keyboard::D && attackDone == 0) {
			if (arrowDirs.at(currentArrow) == 2 && e.key.code == sf::Keyboard::W) {
				if(arrows.at(currentArrow).getPosition().y + 33 <= WINDOW_HEIGHT / 2 + 25 && arrows.at(currentArrow).getPosition().y + 33 > WINDOW_HEIGHT / 2 - 25){
					arrowDirs.at(currentArrow) = -1;
					arrows.at(currentArrow).setOrigin(11, 11);
					arrows.at(currentArrow).setPosition(arrows.at(currentArrow).getPosition().x + 33, arrows.at(currentArrow).getPosition().y + 33);
					damageDealtNum += rand() % 999 + 5;
					damageDealt.setString(std::to_string(damageDealtNum));
					damageDealt.setOrigin(damageDealt.getGlobalBounds().width / 2, 0);
					damageDealt.setRotation(rand() % 2 * 70 - 35);
					damageDealt.setScale(1.3, 1.3);
				}
				else if (arrowDirs.at(currentArrow) != -1) {
					arrows.at(currentArrow).setColor(sf::Color(255, 255, 255, 150));
				}
			}
			else if (arrowDirs.at(currentArrow) == 3 && e.key.code == sf::Keyboard::S) {
				if (arrows.at(currentArrow).getPosition().y + 33 <= WINDOW_HEIGHT / 2 + 25 && arrows.at(currentArrow).getPosition().y + 33 > WINDOW_HEIGHT / 2 - 25) {
					arrowDirs.at(currentArrow) = -1;
				    arrows.at(currentArrow).setOrigin(11, 11);
					arrows.at(currentArrow).setPosition(arrows.at(currentArrow).getPosition().x + 33, arrows.at(currentArrow).getPosition().y + 33);
					damageDealtNum += rand() % 999 + 5;
					damageDealt.setString(std::to_string(damageDealtNum));
					damageDealt.setOrigin(damageDealt.getGlobalBounds().width / 2, 0);
					damageDealt.setRotation(rand() % 45 - 22);
					damageDealt.setScale(1.3, 1.3);
				}
				else if (arrowDirs.at(currentArrow) != -1) {
					arrows.at(currentArrow).setColor(sf::Color(255, 255, 255, 150));
				}
			}
			else if (arrowDirs.at(currentArrow) == 0 && e.key.code == sf::Keyboard::A) {
				if (arrows.at(currentArrow).getPosition().y + 33 <= WINDOW_HEIGHT / 2 + 25 && arrows.at(currentArrow).getPosition().y + 33 > WINDOW_HEIGHT / 2 - 25) {
					arrowDirs.at(currentArrow) = -1;
					arrows.at(currentArrow).setOrigin(11, 11);
					arrows.at(currentArrow).setPosition(arrows.at(currentArrow).getPosition().x + 33, arrows.at(currentArrow).getPosition().y + 33);
					damageDealtNum += rand() % 999 + 5;
					damageDealt.setString(std::to_string(damageDealtNum));
					damageDealt.setOrigin(damageDealt.getGlobalBounds().width / 2, 0);
					damageDealt.setRotation(rand() % 45 - 22);
					damageDealt.setScale(1.3, 1.3);
				}
				else if (arrowDirs.at(currentArrow) != -1) {
					arrows.at(currentArrow).setColor(sf::Color(255, 255, 255, 150));
				}
			}
			else if (arrowDirs.at(currentArrow) == 1 && e.key.code == sf::Keyboard::D) {
				if (arrows.at(currentArrow).getPosition().y + 33 <= WINDOW_HEIGHT / 2 + 25 && arrows.at(currentArrow).getPosition().y + 33 > WINDOW_HEIGHT / 2 - 25) {
					arrowDirs.at(currentArrow) = -1;
					arrows.at(currentArrow).setOrigin(11, 11);
					arrows.at(currentArrow).setPosition(arrows.at(currentArrow).getPosition().x + 33, arrows.at(currentArrow).getPosition().y + 33);
					damageDealtNum += rand() % 999 + 5;
					damageDealt.setString(std::to_string(damageDealtNum));
					damageDealt.setOrigin(damageDealt.getGlobalBounds().width / 2, 0);
					damageDealt.setRotation(rand() % 45 - 22);
					damageDealt.setScale(1.3, 1.3);
				}
				else if (arrowDirs.at(currentArrow) != -1) {
					arrows.at(currentArrow).setColor(sf::Color(255, 255, 255, 150));
				}
			}else{
				arrows.at(currentArrow).setColor(sf::Color(255, 255, 255, 150));
			}
			
			if (currentArrow == arrows.size() - 1)attackDone = 1;
			currentArrow++;
			if (currentArrow >= arrows.size()) {
				currentArrow = arrows.size() - 1;
			}
		}
	}
	else if (phase == DIALOGUE) {
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter) {
			phase = ENEMY_ATTACK;
			sideFadeout = 255;

			littlePlayer.SetPosition(sf::Vector2i(WINDOW_WIDTH / 2 - 28, WINDOW_HEIGHT / 2 - 64));
			lastEnemyBattleTime = clock();
			enemyAttackDone = false;

			attack.create(0, &littlePlayer);
		}
	}
	else if (phase == ENEMY_ATTACK) {
		if (!enemyAttackDone)littlePlayer.HandleEvents(e);
	}
}

void Game::States::Battle::Update(double dt) {
	if ((clock() - lastTime) / (double)CLOCKS_PER_SEC < 1) {
		versusOffset.x = cos(M_PI * ((clock() - lastTime) / (double)CLOCKS_PER_SEC)) * WINDOW_WIDTH / 2;
		versusOffset.y = -cos(M_PI * ((clock() - lastTime) / (double)CLOCKS_PER_SEC)) * WINDOW_HEIGHT / 2;
	}
	else if ((clock() - lastTime) / (double)CLOCKS_PER_SEC > 1 && (clock() - lastTime) / (double)CLOCKS_PER_SEC < 2) {
		versusOffset.x = -WINDOW_WIDTH - cos(M_PI * ((clock() - lastTime) / (double)CLOCKS_PER_SEC)) * WINDOW_WIDTH / 2;
		versusOffset.y = WINDOW_HEIGHT + cos(M_PI * ((clock() - lastTime) / (double)CLOCKS_PER_SEC)) * WINDOW_HEIGHT / 2;
	}

	if ((clock() - lastTime) / (double)CLOCKS_PER_SEC <= 1.0) {
		offset.x = -sin(M_PI / 2 + M_PI / 2 * ((clock() - lastTime) / (double)CLOCKS_PER_SEC) / 1.0) * (WINDOW_WIDTH / 6 * 5);
		offset.y = sin(M_PI * ((clock() - lastTime) / (double)CLOCKS_PER_SEC) / 1.0) * (WINDOW_HEIGHT / 4);
	}
	else if ((clock() - lastTime) / (double)CLOCKS_PER_SEC > 1.0 && (clock() - lastTime) / (double)CLOCKS_PER_SEC < 1.1) {
		zoom = 1.0 - 2 * ((clock() - lastTime) / (double)CLOCKS_PER_SEC - 1.0);

		offset.x = 0;
		offset.y = 0;
	}
	else if ((clock() - lastTime) / (double)CLOCKS_PER_SEC > 1.1 && (clock() - lastTime) / (double)CLOCKS_PER_SEC < 1.3) {
		if (fadeOutA == 0) {
			fadeOutA = 100;
		}
		else {
			fadeOutA = 100 - 500 * ((clock() - lastTime) / (double)CLOCKS_PER_SEC - 1.1);
			fadeOutShape.setFillColor(sf::Color(255, 255, 255, fadeOutA));
		}
		if (zoom == 1) {
			zoom = 1.2;
		}
		else {
			zoom = 1.0 - (1.3 - (clock() - lastTime) / (double)CLOCKS_PER_SEC);
		}
		offset.x = 0;
		offset.y = 0;
	}
	else if((clock() - lastTime) / (double)CLOCKS_PER_SEC > 1.5) {
		if (phase == TRANSITION) {
			phase = CHOOSE_ACTION;
			choicebox.setScale(0.9, 0.9);
			titleBox.setScale(0.9, 0.9);
			title.setString("ATTACK");

			options = std::vector<sf::Text>();

			options.push_back(sf::Text(" Hit", Game::Assets::font, 50));
			options.push_back(sf::Text(" Kick", Game::Assets::font, 50));
			options.push_back(sf::Text(" Fireball", Game::Assets::font, 50));
			options.push_back(sf::Text(" Slash", Game::Assets::font, 50));

			selected = 0;
		}
	}
	
	if ((clock() - lastTime) / (double)CLOCKS_PER_SEC > 3) {
		lastTime = clock() - (double)CLOCKS_PER_SEC * 2;
		currFrame++;
		if (currFrame >= 4) {
			currFrame = 0;
		}
		
	}
	if ((clock() - enemyLastTime) / (double)CLOCKS_PER_SEC > 2.15 && phase != WIN) {
		enemyLastTime = clock() - (double)CLOCKS_PER_SEC * 2;
		enemyCurrFrame++;
		if (enemyCurrFrame >= 12) {
			enemyCurrFrame = 0;
		}
	}

	double scale = choicebox.getScale().x;
	if (scale < 1) {
		choicebox.setScale(scale + (0.1 / 5 * dt), scale + (0.5 / 5 * dt));
		titleBox.setScale(scale + (0.1 / 5 * dt), scale + (0.5 / 5 * dt));
	}
	else {
		choicebox.setScale(1, 1);
		titleBox.setScale(1, 1);
	}

	switch (phase)
	{
	case ATTACK:
		if (choicebox.getSize().y > 400) {
			choicebox.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, choicebox.getPosition().y + 15 * dt));
			choicebox.setSize(sf::Vector2f(500, choicebox.getSize().y - 30 * dt));
		}
		else {
			for (int i = 0; i < arrows.size(); i++) {
				if (arrowDirs.at(i) != -1) {
					arrows.at(i).setPosition(arrows.at(i).getPosition().x, arrows.at(i).getPosition().y + 6 * dt);
					if (arrows.at(i).getPosition().y + 33 > WINDOW_HEIGHT / 2 + 25 && arrows.at(i).getColor().a != 150) {
						arrows.at(i).setColor(sf::Color(255, 255, 255, 150));
						
						if (currentArrow == arrows.size() - 1) {
							attackDone = 1;
						}
						currentArrow++;
						if (currentArrow >= arrows.size()) {
							currentArrow = arrows.size() - 1;
						}
					}
				}

				int a = arrows.at(i).getColor().a - 5;
				if (arrowDirs.at(i) == -1 && a > -1) {
					if (currentArrow == arrows.size() - 1 && i == currentArrow) {
						arrows.at(i).setScale(arrows.at(i).getScale().x + 0.4 * dt, arrows.at(i).getScale().y + 0.4 * dt);
					}
					else {
						arrows.at(i).setScale(arrows.at(i).getScale().x + 0.1 * dt, arrows.at(i).getScale().y + 0.1 * dt);
					}

					if (arrows.at(i).getColor().a < 0) {
						a = 0;
					}
					arrows.at(i).setColor(sf::Color(0, 0, 0, a));
				}
			}
		}

		if (damageDealt.getScale().x > 1) {
			damageDealt.setScale(damageDealt.getScale().x - 0.02, damageDealt.getScale().y - 0.02);
		}

		if (attackDone == 1) {
			attackDone = 2;

			if (damageDealtNum > 0) {
				enemyHealth -= damageDealtNum;
				shakeDir = 5;
				wavesNum = 0;
			}
			else {
				missLastTime = clock();
				damageDealt.setString("Miss");
				damageDealt.setOrigin(damageDealt.getGlobalBounds().width / 2, 0);
				damageDealt.setRotation(0);
				damageDealt.setScale(1.3, 1.3);
			}
		}

		if ((clock() - missLastTime) / (double)CLOCKS_PER_SEC > 1 && attackDone == 2 && damageDealtNum == 0) {
			if (enemyHealth > 0) {
				phase = DIALOGUE;

				bubbleShakeOffset = 0;
				bubbleWavesNum = -40;
				timesMoved = 0;

				letterTimer = clock();
				currentString = rand() % 3;
				currentLetter = 0;

				message.setString("");
			}
			else {
				phase = WIN;
				winTimer = clock();
				stoneAmount = 0;
				characters = 0;
			}
		}

		if (enemyHealth < 0) {
			enemyHealth = 0;
		}
		if (enemyHealthbar.getSize().x / (enemyHealthbarBg.getSize().x / 50) > enemyHealth) {
			enemyHealthbar.setSize(sf::Vector2f(enemyHealthbar.getSize().x - enemyHealthbarBg.getSize().x / 50 / 2 * dt, 40));
		}
		
		if (wavesNum < 50) {
			if (wavesNum % 5 == 0) {
				shakeDir = -shakeDir;
			}
			shakeOffset += shakeDir;
			wavesNum += 1;
		}
		else if(enemyHealthbar.getSize().x / (enemyHealthbarBg.getSize().x / 50) <= enemyHealth) {
			shakeOffset = 0;
			if (attackDone == 2 && damageDealtNum > 0) {
				if (enemyHealth > 0) {
					phase = DIALOGUE;

					bubbleShakeOffset = 0;
					bubbleWavesNum = -40;
					timesMoved = 0;

					letterTimer = clock();
					currentString = rand() % 3;
					currentLetter = 0;

					message.setString("");
				}
				else {
					phase = WIN;
					winTimer = clock();
					stoneAmount = 0;
					characters = 0;
				}
			}
		}

		
		break;
	case CHOOSE_ACTION:
		if (choicebox.getSize().y > 700) {
			choicebox.setPosition(sf::Vector2f(choicebox.getPosition().x, choicebox.getPosition().y + 15 * dt));
			choicebox.setSize(sf::Vector2f(choicebox.getSize().x, choicebox.getSize().y - 30 * dt));
		}
		else {
			choicebox.setPosition(sf::Vector2f(choicebox.getPosition().x, WINDOW_HEIGHT / 2));
			choicebox.setSize(sf::Vector2f(choicebox.getSize().x, 700));
		}
		if (choicebox.getSize().x > 500) {
			choicebox.setPosition(sf::Vector2f(choicebox.getPosition().x + 15 * dt, choicebox.getPosition().y));
			choicebox.setSize(sf::Vector2f(choicebox.getSize().x - 30 * dt, choicebox.getSize().y));
		}
		else {
			choicebox.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, choicebox.getPosition().y));
			choicebox.setSize(sf::Vector2f(500, choicebox.getSize().y));
		}
		damageDealt.setString("");

		lSelect.setColor(sf::Color(255, 255, 255, 255));
		rSelect.setColor(sf::Color(255, 255, 255, 255));

		if (selectedPartition == 0) {
			lSelect.setColor(sf::Color(255, 255, 255, 150));
		}
		else if (selectedPartition == 1) {
			rSelect.setColor(sf::Color(255, 255, 255, 150));
		}

		if ((clock() - narrationLetterTimer) / (double)CLOCKS_PER_SEC >= 0.05) {
			narrationLetterTimer = clock();
			currentNarrationLetter++;
			if (currentNarrationLetter > narrationMessage.size()) {
				currentNarrationLetter = narrationMessage.size();
			}
			narration.setString(narrationMessage.substr(0, currentNarrationLetter));
		}
		break;
	case ENEMY_ATTACK:
		attack.Update(dt);

		if (choicebox.getSize().y < 800) {
			choicebox.setPosition(sf::Vector2f(choicebox.getPosition().x, choicebox.getPosition().y - 15 * dt));
			choicebox.setSize(sf::Vector2f(choicebox.getSize().x, choicebox.getSize().y + 30 * dt));
		}
		if (choicebox.getSize().x < 800) {
			choicebox.setPosition(sf::Vector2f(choicebox.getPosition().x - 15 * dt, choicebox.getPosition().y));
			choicebox.setSize(sf::Vector2f(choicebox.getSize().x + 30 * dt, choicebox.getSize().y));
		}
		if (sideFadeout > 0 && !enemyAttackDone) {
			sideFadeout -= 15 * dt;
			if (sideFadeout < 0) {
				sideFadeout = 0;
			}
			sf::Color c = sf::Color(255, 255, 255, sideFadeout);
			enemy.setColor(c);
			player.setColor(c);
			spotlight.setColor(c);
			enemySpotlight.setColor(c);
		}
		if(!enemyAttackDone)littlePlayer.Update(dt);

		if ((clock() - lastEnemyBattleTime) / (double)CLOCKS_PER_SEC > 16) {
			enemyAttackDone = true;
		}
		if (enemyAttackDone) {
			sideFadeout += 15 * dt;
			if (sideFadeout > 255) {
				sideFadeout = 255;
				phase = CHOOSE_ACTION;

				actionDone = false;
				/*wavesNum = 50;
				attackDone = 0;
				damageDealtNum = 0;
				currentArrow = 0;*/
			}
			sf::Color c = sf::Color(255, 255, 255, sideFadeout);
			enemy.setColor(c);
			player.setColor(c);
			spotlight.setColor(c);
			enemySpotlight.setColor(c);
		}
		
		if (Game::Profile::health == 0) {
			Game::Assets::battle.stop();

			Game::States::GameOver* gameOverState = new Game::States::GameOver(gms, gameView, sf::Vector2i(littlePlayer.GetBounds().left, littlePlayer.GetBounds().top));
			gms.ReplaceTop(gameOverState);
			return;
		}
		else {
			if (Game::Profile::health < 10) {
				hpBattle.setString("HP: 0" + std::to_string(Game::Profile::health) + ":" + std::to_string(Game::Profile::maxHealth));
			}
			else {
				hpBattle.setString("HP: " + std::to_string(Game::Profile::health) + ":" + std::to_string(Game::Profile::maxHealth));
			}
		}
		break;
	case WIN:
		if ((clock() - winTimer) / (double)CLOCKS_PER_SEC >= 1) {
			if (enemyCurrFrame == 0) {
				stoneAmount += std::ceil(2 * dt);
				if (stoneAmount >= 240) {
					stoneAmount = 240;
					enemyCurrFrame = 12;
				}
			}
		}
		
		if (stoneAmount >= 240) {
			if ((clock() - enemyLastTime) / (double)CLOCKS_PER_SEC >= 0.1) {
				enemyLastTime = clock();
				enemyCurrFrame++;

				if (enemyCurrFrame >= 24) {
					enemyCurrFrame = 23;
				}
			}
		}
		else {
			enemyCurrFrame = 0;
		}
		
		stoneEnemy.setTextureRect(sf::IntRect(0, 480, 150, std::floor(stoneAmount)));
		stoneEnemy.setPosition(enemy.getPosition());

		if (characters < std::string("You won!").length()) {
			characters += 0.2f * dt;
			if (characters > std::string("You won!").length()) {
				characters = std::string("You won!").length();
			}
		}

		winText.setString(std::string("You won!").substr(0, std::floor(characters)));

		if (fadeOutA < 255 && (clock() - winTimer) / (double)CLOCKS_PER_SEC >= 8) {
			if (Game::Assets::battle.getVolume() - 4 < 0) {
				Game::Assets::battle.stop();
			}
			else {
				Game::Assets::battle.setVolume(Game::Assets::battle.getVolume() - 4 * dt);
			}

			fadeOutA += 10 * dt;
			if (fadeOutA >= 255) {
				fadeOutA = 255;

				Game::Assets::battle.stop();
				gms.Pop();
			}
			fadeOutShape.setFillColor(sf::Color(0, 0, 0, fadeOutA));
		}
		break;
	case DIALOGUE:
		int lastXPos = speechBubble.getPosition().x - bubbleShakeOffset;
		int lastXPos2 = message.getPosition().x - bubbleShakeOffset;

		if (bubbleWavesNum > 0) {
			
			if (timesMoved < 5) {
				if (bubbleWavesNum < 3) {
					bubbleShakeOffset += bubbleWavesNum / 2.0 * dt;
				}
				else {
					bubbleShakeOffset += (3 - (bubbleWavesNum - 3)) / 2.0 * dt;
				}
			}
			else if (timesMoved >= 5 && timesMoved < 15) {
				if (bubbleWavesNum < 3) {
					bubbleShakeOffset -= bubbleWavesNum / 2.0 * dt;
				}
				else {
					bubbleShakeOffset -= (3 - (bubbleWavesNum - 3)) / 2.0 * dt;
				}
			}
			else {
				if (bubbleWavesNum < 3) {
					bubbleShakeOffset += bubbleWavesNum / 2.0 * dt;
				}
				else {
					bubbleShakeOffset += (3 - (bubbleWavesNum - 3)) / 2.0 * dt;
				}
			}
			timesMoved++;
			if (timesMoved >= 20) {
				timesMoved = 0;
				if (bubbleWavesNum < 6) {
					bubbleWavesNum += std::ceil(dt);
				}
				else {
					bubbleWavesNum = -10;
				}
			}
		}
		else {
			bubbleWavesNum++;
		}

		if ((clock() - letterTimer) / (double)CLOCKS_PER_SEC >= 0.05) {
			letterTimer = clock();
			currentLetter++;
			if (currentLetter > strings.at(currentString).size()) {
				currentLetter = strings.at(currentString).size();
			}
			message.setString(strings.at(currentString).substr(0, currentLetter));
		}

		speechBubble.setPosition(lastXPos + bubbleShakeOffset, speechBubble.getPosition().y);
		message.setPosition(lastXPos2 + bubbleShakeOffset, message.getPosition().y);
		break;
	}

	healthbar.setSize(sf::Vector2f((enemyHealthbarBg.getSize().x / 50) * Game::Profile::health, 40));

	player.setTextureRect(sf::IntRect(67 * currFrame, 0, 67, 208));
	enemy.setTextureRect(sf::IntRect(150 * (enemyCurrFrame % 6), 240 * (int)(enemyCurrFrame / 6), 150, 240));

	spotlight.setPosition(spotlightPos.x/* + offset.x*/, spotlightPos.y/* + offset.y*/);
	player.setPosition(playerPos.x/* + offset.x*/, playerPos.y/* + offset.y*/);
	enemySpotlight.setPosition(enemySpotlightPos.x/* - offset.x*/, enemySpotlightPos.y/* - offset.y*/);
	enemy.setPosition(enemySpotlightPos.x + shakeOffset, enemyPos.y/* - offset.y*/ - 90);

	versus.setPosition(versusPos.x + versusOffset.x, versusPos.y + versusOffset.y);

	if (fadeInA > 0) {
		fadeInA -= 15 * dt;
		if (fadeInA < 0) {
			fadeInA = 0;
		}
		fadeInShape.setFillColor(sf::Color(0, 0, 0, fadeInA));
	}
}

void Game::States::Battle::SetOptions(int selection) {
	switch (selection)
	{
	case 0:
		options.clear();

		options.push_back(sf::Text(" Hit", Game::Assets::font, 50));
		options.push_back(sf::Text(" Kick", Game::Assets::font, 50));
		options.push_back(sf::Text(" Fireball", Game::Assets::font, 50));
		options.push_back(sf::Text(" Slash", Game::Assets::font, 50));

		selected = 0;

		title.setString("ATTACK");
		break;
	case 1:
		options.clear();

		for (int i = 0; i < Game::Profile::items.size(); i++) {
			switch (Game::Profile::items.at(i))
			{
			case Game::Profile::BLUEBERRIES:
				options.push_back(sf::Text(" Blueberries", Game::Assets::font, 50));
				break;
			}
		}		

		selected = 0;

		title.setString("ITEM");
		break;
	}

	title.setPosition(WINDOW_WIDTH / 2 - title.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 - 355);
}

void Game::States::Battle::Draw(sf::RenderTarget& window) {
	sf::View view(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	view.zoom(zoom);
	window.setView(view);
	window.draw(bGShape);
	/*window.draw(plane);
	window.draw(bg);*/
	
	window.draw(enemySpotlight);
	//if ((stoneAmount < 240 && enemyCurrFrame == 0) || (stoneAmount >= 240 && enemyCurrFrame >= 12)) {
		window.draw(enemy);
	//}
	window.draw(spotlight);
	window.draw(player);

	window.draw(fadeInShape);

	if (phase == ATTACK) {
		window.draw(choicebox);
		window.draw(middleLine);
		
		arrowBoundsTexture.clear(sf::Color(0, 0, 0, 0));
		for (int i = 0; i < arrows.size(); i++) {
			arrowBoundsTexture.draw(arrows.at(i));
		}
		arrowBoundsTexture.display();
		arrowBounds.setTexture(arrowBoundsTexture.getTexture());
		window.draw(arrowBounds);

		window.draw(healthbarBg);
		window.draw(healthbar);
		window.draw(enemyHealthbarBg);
		window.draw(enemyHealthbar);
		window.draw(damageDealt);
	}

	if (phase == CHOOSE_ACTION) {
		window.draw(choicebox);

		if (!actionDone) {
			window.draw(titleBox);
			window.draw(title);
			window.draw(rSelect);
			window.draw(lSelect);

			for (int i = 0; i < options.size(); i++) {
				if (selected == i) {
					options.at(i).setString(options.at(i).getString().toAnsiString().replace(0, 1, "-"));
				}
				else {
					options.at(i).setString(options.at(i).getString().toAnsiString().replace(0, 1, " "));
				}
				options.at(i).setPosition(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 200 + 60 * i);
				options.at(i).setFillColor(sf::Color::Black);
				window.draw(options.at(i));
			}
		}
		else {
			window.draw(narration);
		}

		window.draw(healthbarBg);
		window.draw(healthbar);
		window.draw(enemyHealthbarBg);
		window.draw(enemyHealthbar);
	}

	if (phase == ENEMY_ATTACK) {
		window.draw(choicebox);
		if (!enemyAttackDone)littlePlayer.Draw(window);
		attack.Draw(window);
		window.draw(hpBattle);
	}

	if (phase == WIN) {
		if((clock() - winTimer) / (double)CLOCKS_PER_SEC >= 1 && enemyCurrFrame < 12)window.draw(stoneEnemy);
		window.draw(choicebox);
		window.draw(winText);
	}

	if (phase == DIALOGUE) {
		window.draw(speechBubble);
		window.draw(message);
	}

	view.zoom(1);
	window.setView(view);
	window.draw(versus);
	window.draw(fadeOutShape);
}

void Game::States::Battle::Resume() {}

Game::CombatPlayer::CombatPlayer() {}

Game::CombatPlayer::CombatPlayer(sf::Vector2i pos) : pos(pos) {
	sprite = sf::Sprite(Game::Assets::littleChar);
	sprite.setScale(2, 2);
	sprite.setPosition(pos.x, pos.y);
	speed = 4;

	numAnim = 1;
	numFrames = 8;
	currFrame = 0;
	lastFrameTime = clock();

	horDir = 0;
	vertDir = 0;
	flip = 0;

	move = true;
	sprite.setTextureRect(sf::IntRect(28 * currFrame, 64, 28, 64));
}

void Game::CombatPlayer::HandleEvents(sf::Event e) {
	if (e.type == sf::Event::EventType::KeyPressed && move) {
		switch (e.key.code) {
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
	}
	else if (e.type == sf::Event::EventType::KeyReleased) {
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

void Game::CombatPlayer::SetAnim(int axis, int dir) {
	if (axis == 1) {
		if (dir == -speed) {
			flip = 28;
			numAnim = 0;
			numFrames = 8;
		}
		else if (dir == speed) {
			flip = 0;
			numAnim = 0;
			numFrames = 8;
		}
	}
	else if (axis == 0) {
		if (dir == -speed) {
			flip = 0;
			numAnim = 1;
			numFrames = 8;
		}
		else if (dir == speed) {
			flip = 0;
			numAnim = 1;
			numFrames = 8;
		}
	}
}

void Game::CombatPlayer::Update(double dt) {
	if (move) {
		int lastPos = pos.x;
		pos.x += horDir;
		if (pos.x < WINDOW_WIDTH / 2 - 400 || pos.x > WINDOW_WIDTH / 2 + 340) {
			pos.x = lastPos;
		}

		lastPos = pos.y;
		pos.y += vertDir;
		if (pos.y < WINDOW_HEIGHT / 2 - 400 || pos.y > WINDOW_HEIGHT / 2 + 280) {
			pos.y = lastPos;
		}
	}

	if ((clock() - lastFrameTime) / (double)CLOCKS_PER_SEC >= 0.15) {
		lastFrameTime = clock();
		currFrame++;
		if (currFrame >= numFrames) {
			currFrame = 0;
		}
		if ((horDir == 0 && vertDir == 0) || !move)currFrame = 8;
	}
	if (currFrame == 8)sprite.setTextureRect(sf::IntRect(28 * currFrame, 64, 28, 64));
	else sprite.setTextureRect(sf::IntRect(currFrame * 28 + flip, numAnim * 64, 28 - flip * 2, 64));
	sprite.setPosition(pos.x, pos.y);

	if (std::fmod((clock() - invincible) / (double)CLOCKS_PER_SEC, 0.3) <= 0.15 && IsInvincible()) {
		sprite.setColor(sf::Color::Transparent);
	}
	else {
		sprite.setColor(sf::Color::White);
	}
}

void Game::CombatPlayer::SetPosition(sf::Vector2i newPos) {
	pos = newPos;
	horDir = 0;
	vertDir = 0;
	SetAnim(1, speed);

	invincible = clock() - CLOCKS_PER_SEC * 2;
}

void Game::CombatPlayer::Draw(sf::RenderTarget& window) {
	window.draw(sprite);
}

sf::IntRect Game::CombatPlayer::GetBounds() {
	return sf::IntRect(sprite.getGlobalBounds().left + 5, sprite.getGlobalBounds().top + 7, sprite.getGlobalBounds().width -10, sprite.getGlobalBounds().height - 14);
}

bool Game::CombatPlayer::IsInvincible() {
	return (clock() - invincible) / (double)CLOCKS_PER_SEC < 2;
}

void Game::CombatPlayer::TakeHit(int dmg) {
	invincible = clock();
}


