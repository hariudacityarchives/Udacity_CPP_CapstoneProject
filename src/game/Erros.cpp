#include "Errors.h"
#include <cstdlib>

void fatalError(std::string errorString) {
  std::cout << errorString << std::endl;
  std::cout << "Enter any String\n";
  int tmp;
  std::cin >> tmp;
  SDL_Quit();
  exit(69);
}