#include "main.h"

void Game::GameStateManager::Push(Game::GameState* state) {
	state->Init();
	states.push(std::unique_ptr<Game::GameState>(state));
}

void Game::GameStateManager::ReplaceTop(Game::GameState* state) {
	states.pop();
	state->Init();
	states.push(std::unique_ptr<Game::GameState>(state));
}

void Game::GameStateManager::Pop() {
	states.pop();
	states.top()->Resume();
}

void Game::GameStateManager::Clear() {
	for (int i = 0; i < states.size(); i++) {
		delete states.top().release();
		states.pop();
	}
}

void Game::GameStateManager::HandleEvents(sf::Event e) {
	states.top()->HandleEvents(e);
}

void Game::GameStateManager::Update(double dt) {
	states.top()->Update(dt);
}

void Game::GameStateManager::Draw(sf::RenderTarget& window) {
	states.top()->Draw(window);
}

Game::GameState::GameState(Game::GameStateManager& gms, sf::View view) : gms(gms), gameView(view) {}