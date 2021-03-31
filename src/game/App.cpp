#include "App.h"

void App() { std::cout << "App Function" << std::endl; }

GameEngine::GameEngine() {
  _window = nullptr;
  _screenWidth = 1028;
  _screenHeight = 768;
  _gameState = GameState::PLAY;
}

GameEngine::~GameEngine() {}

void GameEngine::run() {
  initsystem();
  gameLoop();
}

void GameEngine::initsystem() {

  // SDL initialization
  SDL_Init(SDL_INIT_EVERYTHING);

  _window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, _screenWidth,
                             _screenHeight, SDL_WINDOW_OPENGL);
}

void GameEngine::gameLoop() {
  while (_gameState != GameState::EXIT) {
    processInput();
  }
}

void GameEngine::processInput() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {

    case SDL_QUIT:
      _gameState = GameState::EXIT;
      break;

    case SDL_MOUSEMOTION:
      std::cout << event.motion.x << " " << event.motion.y << std::endl;
      break;
    }
  }
}