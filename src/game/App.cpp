#include "App.h"
#include <string>

void App() { std::cout << "App Function" << std::endl; }

void fatalError(std::string errorString) {
  std::cout << errorString << std::endl;
  std::cout << "Enter any String\n";
  int tmp;
  std::cin >> tmp;
  SDL_Quit();
}

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

  if (_window == nullptr) {
    fatalError("SDL Window Count could not be created!");
  }

  SDL_GLContext glContext = SDL_GL_CreateContext(_window);
  if (glContext == nullptr) {
    fatalError("SDL_GL Context could not be created!");
  }

  GLenum errorGl = glewInit();
  if (errorGl != GLEW_OK) {
    fatalError("GLEW Initialize Failed!");
  }

  // Create 2 Buffer Windows
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  glClearColor(0.0f, 0.0f, 1.0f, 1.0);
}

void GameEngine::gameLoop() {
  while (_gameState != GameState::EXIT) {
    processInput();
    drawGame();
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

void GameEngine::drawGame() {

  glClearDepth(1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex2f(0, 0);
  glVertex2f(0, 500);
  glVertex2f(500, 500);

  glEnd();

  SDL_GL_SwapWindow(_window);
}