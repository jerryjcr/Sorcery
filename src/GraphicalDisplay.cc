#include "GraphicalDisplay.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

GraphicalDisplay::GraphicalDisplay()
    : window(nullptr, SDL_DestroyWindow),
      renderer(nullptr, SDL_DestroyRenderer),
      backgroundTexture(nullptr, SDL_DestroyTexture) {}

bool GraphicalDisplay::createWindow(const std::string& title, int width,
                                    int height) {
  window.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, width, height,
                                SDL_WINDOW_SHOWN));
  if (!window) {
    std::cerr << "Error: " << SDL_GetError() << std::endl;
    return false;
  }
  return true;
}

bool GraphicalDisplay::createRenderer() {
  if (!window) {
    std::cerr << "Error: Cannot create renderer without a window." << std::endl;
    return false;
  }

  renderer.reset(SDL_CreateRenderer(window.get(), -1, 0));

  if (!renderer) {
    std::cerr << "Error: " << SDL_GetError() << std::endl;
    return false;
  }
  return true;
}

bool GraphicalDisplay::loadBackgroundTexture(const std::string& filePath) {
  if (!renderer) {
    std::cerr << "Error: Cannot load texture without a renderer." << std::endl;
    return false;
  }

  std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface(
      IMG_Load(filePath.c_str()), SDL_FreeSurface);

  if (!surface) {
    std::cerr << "Error: " << SDL_GetError() << std::endl;
    return false;
  }
}

bool GraphicalDisplay::loadCardTextures(
    const std::vector<std::string>& filePaths) {
  if (!renderer) {
    std::cerr << "Error: Cannot load texture without a renderer." << std::endl;
    return false;
  }

  for (const auto& path : filePaths) {
    std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface(
        IMG_Load(path.c_str()), SDL_FreeSurface);

    if (!surface) {
      std::cerr << "Error: " << SDL_GetError() << std::endl;
      return false;
    }
  }
}

bool GraphicalDisplay::isInitialized() const { return window != nullptr; }
