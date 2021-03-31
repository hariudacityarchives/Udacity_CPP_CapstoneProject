#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>

enum class GameState { PLAY, EXIT };
class GameEngine {

public:
  GameEngine();
  ~GameEngine();

  void run();

private:
  SDL_Window *_window;
  int _screenWidth;
  int _screenHeight;

  GameState _gameState;

  void gameLoop();
  void processInput();
  void drawGame();
  void initsystem();
};