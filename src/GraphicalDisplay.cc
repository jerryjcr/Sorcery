#include "GraphicalDisplay.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void GraphicalDisplay::clear() {
  SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
  SDL_RenderClear(renderer.get());
}

void GraphicalDisplay::drawBackground(int width, int height) {
  if (!backgroundTexture) {
    std::cerr << "Error: Null background texture." << std::endl;
    return;
  }

  SDL_Rect destRect(0, 0, width, height);

  SDL_RenderCopy(renderer.get(), backgroundTexture.get(), nullptr, &destRect);
}

void GraphicalDisplay::drawCard(size_t index, int x, int y, int w, int h) {
  if (index >= cardTextures.size()) {
    std::cerr << "Error: Card index out of bounds." << std::endl;
    return;
  }

  if (!cardTextures[index]) {
    std::cerr << "Error: Null card texture." << std::endl;
    return;
  }

  SDL_Rect destRect(x, y, w, h);

  SDL_RenderCopy(renderer.get(), cardTextures[index].get(), nullptr, &destRect);
}

void GraphicalDisplay::present() { SDL_RenderPresent(renderer.get()); }

void GraphicalDisplay::update() {
  clear();
  drawBackground();

  int x = 50;
  int y = 50;
  int cardWidth = 100;
  int cardHeight = 150;
  int spacing = 10;

  for (size_t i = 0; i < cardTextures.size())
}

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

bool GraphicalDisplay::loadTextures(const std::string& backgroundPath,
                                    const std::vector<std::string>& cardPaths) {
  if (!renderer) {
    std::cerr << "Error: Cannot load texture without a renderer." << std::endl;
    return false;
  }

  std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> backgroundSurface(
      IMG_Load(backgroundPath.c_str()), SDL_FreeSurface);

  if (!backgroundSurface) {
    std::cerr << "Error: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_Texture* rawTexture =
      SDL_CreateTextureFromSurface(renderer.get(), backgroundSurface.get());

  if (!rawTexture) {
    std::cerr << "Error: " << SDL_GetError() << std::endl;
    return false;
  }

  texturePtr texture(rawTexture, SDL_DestroyTexture);

  backgroundTexture = std::move(texture);

  for (const auto& path : cardPaths) {
    std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface(
        IMG_Load(path.c_str()), SDL_FreeSurface);

    if (!surface) {
      std::cerr << "Error: " << SDL_GetError() << std::endl;
      return false;
    }

    SDL_Texture* rawTexture =
        SDL_CreateTextureFromSurface(renderer.get(), surface.get());

    if (!rawTexture) {
      std::cerr << "Error: " << SDL_GetError() << std::endl;
      return false;
    }

    texturePtr texture(rawTexture, SDL_DestroyTexture);

    cardTextures.emplace_back(std::move(texture));
  }

  return true;
}

bool GraphicalDisplay::isInitialized() const { return window != nullptr; }
