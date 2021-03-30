#include "App.h"

void App() { std::cout << "App Function" << std::endl; }

GameEngine::GameEngine() {
  _window = nullptr;
  _screenWidth = 1028;
  _screenHeight = 768;
}

GameEngine::~GameEngine() {}

void GameEngine::run() { initsystem(); }
void GameEngine::initsystem() {

  // SDL initialization
  SDL_Init(SDL_INIT_EVERYTHING);

  _window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, _screenWidth,
                             _screenHeight, SDL_WINDOW_OPENGL);
}