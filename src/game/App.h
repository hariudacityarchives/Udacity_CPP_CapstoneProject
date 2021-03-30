#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>

class GameEngine {

public:
  GameEngine();
  ~GameEngine();

  void run();
  void initsystem();

private:
  SDL_Window *_window;
  int _screenWidth;
  int _screenHeight;
};