#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <stack>
#include <memory>
#include <time.h>
#include <cmath>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define TILE_WIDTH 96
#define TILE_HEIGHT 72

namespace Game {
	struct Assets {
	public:
		static sf::Texture player, tiles, tilesTop, entities, playerFight, spotlight, versus, enemies, littleChar, projectiles, winner, bg, speechBubble, plane, selectionArrows, faces;
		static sf::Texture arrowLeft, arrowRight, arrowUp, arrowDown;
		static sf::Font font;
		static sf::SoundBuffer textB, blipB, getHitB, menuMoveB;
		static sf::Sound text, blip, getHit, menuMove;
		static sf::Music battle, area1;

		static std::vector<std::vector<int>> rooms[2];

		static bool LoadAssets();
		static bool LoadRooms();
	};

	struct GameStateManager;
	struct GameState {
	protected:
		GameStateManager& gms;
		sf::View gameView;

	public:
		GameState(Game::GameStateManager& gms, sf::View view);

		virtual void Init() = 0;
		virtual void HandleEvents(sf::Event e) = 0;
		virtual void Update(double dt) = 0;
		virtual void Draw(sf::RenderTarget& window) = 0;
		virtual void Resume() = 0;
	};
	struct GameStateManager {
	public:
		void Push(Game::GameState* state);
		void ReplaceTop(Game::GameState* state);
		void Pop();
		void Clear();

		void HandleEvents(sf::Event e);
		void Update(double dt);
		void Draw(sf::RenderTarget& window);

	private:
		std::stack<std::unique_ptr<GameState>> states;
	};

	struct Tilemap;
	struct Player {
	public:
		Player();
		Player(sf::Vector2i pos, sf::Vector2i dim, Game::Tilemap* tilemap);
		~Player();

		void HandleEvents(sf::Event e);
		void Update(double dt);
		void Draw(sf::RenderTarget& window);
		sf::Vector2i GetPosition();
		void SetMove(bool move);
		void SetPosition(sf::Vector2i pos);
		void Resume();

		int JumpToArea();
		bool Encounter();

	private:
		sf::Vector2i pos, dim;
		int speed;
		sf::Sprite sprite;

		int numFrames, currFrame, numAnim;
		long lastFrameTime;
		long frameDuration;

		int horDir, vertDir;
		int flip;

		Tilemap* tilemap;

		bool move;

		int encounter;
		long invincible;

		void SetAnim(int axis, int dir);
	};

	struct Entities;
	struct Tilemap {
	public:
		Tilemap();
		~Tilemap();

		void UpdateMapForRoom(int roomId);
		void Update(double dt);
		bool Draw(sf::RenderTarget& window, Player& player, sf::Sprite entities);
		void DrawTopLayer(sf::RenderTarget& window, Game::Player& player);

		bool CollidesWithTiles(sf::IntRect rect);
		int CollidesWithDoor(sf::IntRect rect);

		sf::Vector2i GetAreaBounds();

		static sf::Vector2i GetPlayerStart(int areaNum, sf::Vector2i areaBounds);

	private:
		std::vector<std::vector<int>> tiles;
		sf::Sprite tileSprite, topSprite;
	};

	struct Entity {
	public:
		Entity(sf::Vector2i pos, sf::Vector2i dim, Player* player);
		
		virtual void HandleEvents(sf::Event e) = 0;
		virtual void Update(double dt) = 0;
		virtual void Draw(sf::RenderTarget& window) = 0;
		virtual void DrawEffect(sf::RenderTarget& window) = 0;
		sf::IntRect GetBounds();

	protected:
		sf::Vector2i pos, dim;
		Player* player;		
	};

	struct Entities {
	public:
		Entities();
		Entities(Player* player);
		
		void UpdateEntitiesForRoom(int roomId);
		void HandleEvents(sf::Event e);
		void Update(double dt);
		void Draw(sf::RenderTarget& window);
		void DrawEffect(sf::RenderTarget& window);

	private:
		std::vector<std::unique_ptr<Entity>> entities;
		Player* player;
	};

	struct CombatPlayer {
	public:
		CombatPlayer();
		CombatPlayer(sf::Vector2i pos);

		void HandleEvents(sf::Event e);
		void Update(double dt);
		void Draw(sf::RenderTarget& window);

		void SetPosition(sf::Vector2i pos);

		bool IsInvincible();
		void TakeHit(int dmg);

		sf::IntRect GetBounds();

	protected:
		sf::Sprite sprite;
		sf::Vector2i pos;
		int speed;

		int numFrames, currFrame, numAnim;
		long lastFrameTime;
		long frameDuration;

		int horDir, vertDir;
		int flip;
		bool move;

		long invincible;

		void SetAnim(int axis, int dir);
	};

	struct Attack {
	public:
		void create(int type, CombatPlayer* player);
		Attack();

		void Update(double dt);
		void Draw(sf::RenderTarget& window);

	private:
		std::vector<sf::Sprite> projectiles;
		long timer;

		int type;
		CombatPlayer* player;

		sf::RenderTexture canvas;
		sf::Sprite canvasSprite;

		int sequence;
	};

	struct Profile {
	public:
		enum Weapon {
			Fists
		};

		enum ItemType {
			BLUEBERRIES
		};

		static std::vector<ItemType> items;

		static std::vector<Weapon> weapons;
		static int health, maxHealth;
	};

	namespace States {
		struct Area : GameState {
		public:
			Area(Game::GameStateManager& gms, sf::View view);

			void Init();
			void HandleEvents(sf::Event e);
			void Update(double dt);
			void Draw(sf::RenderTarget& window);
			void Resume();

		private:
			Game::Player player;
			Game::Tilemap tilemap;
			Game::Entities entities;

			sf::Vector2i areaBounds;
			sf::Vector2i viewOffset;

			int fadeOutA;
			sf::RectangleShape fadeOutShape, pauseMenuShape;

			bool pauseMenu;
			long toBattleTimer;
			bool encounter;

			bool resume;

			sf::RenderTexture entityTexture;
			sf::Sprite entitySprite;
		};

		struct Battle : GameState {
		public:
			enum Phase {
				TRANSITION, CHOOSE_ACTION, ATTACK, ENEMY_ATTACK, WIN, DIALOGUE
			};
			enum Enemy {
				ROCKY
			};

			Battle(Game::GameStateManager& gms, sf::View view, Enemy enemyType);

			void Init();
			void HandleEvents(sf::Event e);
			void Update(double dt);
			void Draw(sf::RenderTarget& window);
			void Resume();

		private:
			sf::Sprite plane;

			Enemy enemyType;
			Attack attack;

			sf::Sprite spotlight, enemySpotlight, player, enemy, bg, speechBubble;
			int currFrame, enemyCurrFrame;
			sf::Sprite versus;

			sf::Text message;
			std::vector<std::string> strings;
			int currentString, currentLetter;
			long letterTimer;

			int fadeOutA, sideFadeout, fadeInA;
			sf::RectangleShape fadeOutShape, bGShape, choicebox, fadeInShape;

			sf::Text title;
			std::vector<sf::Text> options;
			int selected;
			sf::CircleShape selectIcon;

			sf::Sprite rSelect, lSelect;
			int selectedPartition;
			bool actionDone;

			sf::Text narration;
			std::string narrationMessage;
			int currentNarrationLetter;
			long narrationLetterTimer;

			sf::RectangleShape middleLine, titleBox;

			sf::RectangleShape enemyHealthbar, enemyHealthbarBg, healthbar, healthbarBg;
			sf::Text damageDealt;
			int damageDealtNum, enemyHealth, health;

			int shakeDir, wavesNum;
			int shakeOffset;

			int attackDone;

			long missLastTime;

			std::vector<sf::Sprite> arrows;
			std::vector<int> arrowDirs;
			int currentArrow;

			sf::Sprite arrowBounds;
			sf::RenderTexture arrowBoundsTexture;

			long lastTime, enemyLastTime;
			sf::Vector2i offset;
			sf::Vector2i playerPos, enemyPos, spotlightPos, enemySpotlightPos;

			sf::Vector2i versusPos, versusOffset;

			Phase phase;

			float zoom;

			CombatPlayer littlePlayer;
			long lastEnemyBattleTime;
			bool enemyAttackDone;

			long winTimer;
			float stoneAmount;

			sf::Sprite stoneEnemy;
			sf::Text winText;
			float characters;

			sf::Text hpBattle;

			float bubbleShakeOffset;
			int timesMoved, bubbleWavesNum;

			void SetOptions(int selection);
		};

		struct GameOver : GameState {
		public:
			GameOver(Game::GameStateManager& gms, sf::View view, sf::Vector2i playerPos);

			void Init();
			void HandleEvents(sf::Event e);
			void Update(double dt);
			void Draw(sf::RenderTarget& window);
			void Resume();

		private:
			sf::Sprite player;
			sf::Text gameOver;
			int gameOverFadeIn;

			int fadeOutA;
			sf::RectangleShape fadeOutShape;

			long animTimer;
			int currFrame;

			long shineTimer;
		};
	}

	struct Dialogue {
	public:
		enum Face {
			ROCK_DUDE, ROCK_DUDE_ANGRY, ROCK_DUDE_TIRED, NONE
		};

		Dialogue(std::vector<std::string> strings[2], int charsInSec, Game::Player* player, int actionMessage, std::vector<Face> faces);
		Dialogue();

		void HandleEvents(sf::Event e);
		void Update(double dt);
		void Draw(sf::RenderTarget& window);
		void Start();
		void Stop();
		void SetMessages(std::vector<std::string> strings[2], std::vector<Game::Dialogue::Face> faces, int actionFrame);

		bool GetDisplaying();
		bool GetTalking();
		int GetMessageNum();

		int GetChoice();

	private:
		std::vector<std::string> strings[2];
		int currentMessage;
		int charsInSec;
		int currentChar;

		long lastTime;

		sf::RectangleShape dialogueBox;
		sf::Text text;

		bool displaying, talking;

		Game::Player* player;

		int soundPlayed;

		int selectedOption;
		int actionMessage;

		std::vector<Face> faces;
		sf::Sprite faceSprite;
	};

	namespace EntityTypes {
		struct Talker : Entity {
		public:
			Talker(sf::Sprite sprite, sf::Vector2i pos, sf::Vector2i dim, Game::Player* player, Game::Dialogue dialogue, int talkFrames);

			void HandleEvents(sf::Event e);
			void Update(double dt);
			void Draw(sf::RenderTarget& window);
			void DrawEffect(sf::RenderTarget& window);

		private:
			sf::Sprite sprite;
			sf::IntRect origRect;

			int talkFrames;
			int currFrame;
			long lastTime;

			Dialogue dialogue;
		};

		struct BlueberryPerson : Entity {
		public:
			BlueberryPerson(sf::Sprite sprite, sf::Vector2i pos, sf::Vector2i dim, Game::Player* player);

			void HandleEvents(sf::Event e);
			void Update(double dt);
			void Draw(sf::RenderTarget& window);
			void DrawEffect(sf::RenderTarget& window);

		private:
			sf::Sprite sprite;
			sf::IntRect origRect;

			int maxFrames;
			int currFrame;
			long lastTime;

			Dialogue dialogue;

			int messageSetOrdinal, currMessageSetOrdinal;
			int face;

			int lastMessage;
		};

		struct AnimTalker : Entity {
		public:
			AnimTalker(sf::Sprite sprite, sf::Vector2i pos, sf::Vector2i dim, Game::Player* player, Game::Dialogue dialogue, int frames);

			void HandleEvents(sf::Event e);
			void Update(double dt);
			void Draw(sf::RenderTarget& window);
			void DrawEffect(sf::RenderTarget& window);

		private:
			sf::Sprite sprite;
			sf::IntRect origRect;

			int maxFrames;
			int currFrame;
			long lastTime;

			Dialogue dialogue;
		};

		struct Item : Entity {
		public:
			Item(Profile::ItemType item, sf::Vector2i pos, sf::Vector2i dim, Game::Player* player, Game::Dialogue dialogue, Game::Dialogue outOfSpace);

			void HandleEvents(sf::Event e);
			void Update(double dt);
			void Draw(sf::RenderTarget& window);
			void DrawEffect(sf::RenderTarget& window);

		private:
			Profile::ItemType itemType;

			sf::Sprite sprite;

			bool pickedUp;

			Dialogue dialogue, outOfSpace;
		};
	}
}