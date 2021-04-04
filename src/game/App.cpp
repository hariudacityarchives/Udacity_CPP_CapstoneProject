#include "App.h"
#include "Errors.h"
#include <string>

void App() { std::cout << "App Function" << std::endl; }

GameEngine::GameEngine()
    : _window(nullptr), _screenWidth(300), _screenHeight(400), _time(0.0f),
      _gameState(GameState::PLAY) {}

GameEngine::~GameEngine() {}

void GameEngine::run() {

  initsystem();

  _sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);

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

  initShaders();
}

void GameEngine::initShaders() {

  _colorProgram.compileShaders("../shaders/colorShading.ver",
                               "../shaders/colorShading.frag");
  _colorProgram.addAttribute("vertexPosition");
  _colorProgram.addAttribute("vertexColor");
  _colorProgram.linkShaders();
}

void GameEngine::gameLoop() {
  while (_gameState != GameState::EXIT) {
    // The below function reads the event in the window Space
    processInput();

    _time += 0.01;

    // This Function updates the Features of the Window
    // Window Color and Shapes that are drawn with the window space
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

  // Set Base depth to 1.0
  glClearDepth(1.0);

  // Clear Color and Depth Buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _colorProgram.use();

  GLuint timelocation = _colorProgram.getUniformLocation("time");

  glUniform1f(timelocation, _time);

  _sprite.draw();

  _colorProgram.unuse();

  // Swap our Buffer and draw everything to screen
  SDL_GL_SwapWindow(_window);
}
